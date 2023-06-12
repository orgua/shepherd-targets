/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2021 - 2022, Networked Embedded Systems Lab, TU Dresden
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *		  notice, this list of conditions and the following disclaimer.
 *		* Redistributions in binary form must reproduce the above copyright
 *		  notice, this list of conditions and the following disclaimer in the
 *		  documentation and/or other materials provided with the distribution.
 *		* Neither the name of the NES Lab or TU Dresden nor the
 *		  names of its contributors may be used to endorse or promote products
 *		  derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***********************************************************************************************//**
 *
 *	@file					logging.c
 *
 *	@brief					log thread and related functionality
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/
//***** Trace Settings *****************************************************************************

#include "gpi/trace.h"

// message groups for TRACE messages (used in GPI_TRACE_MSG() calls)
// define groups appropriate for your needs, assign one bit per group
// values > GPI_TRACE_LOG_USER (i.e. upper bits) are reserved
#define TRACE_INFO    GPI_TRACE_MSG_TYPE_INFO
#define TRACE_WARNING GPI_TRACE_MSG_TYPE_WARNING
#define TRACE_ERROR   GPI_TRACE_MSG_TYPE_ERROR
#define TRACE_VERBOSE GPI_TRACE_MSG_TYPE_VERBOSE

// select active message groups, i.e., the messages to be printed (others will be dropped)
#ifndef GPI_TRACE_BASE_SELECTION
  #define GPI_TRACE_BASE_SELECTION GPI_TRACE_LOG_STANDARD /*| GPI_TRACE_LOG_PROGRAM_FLOW*/
#endif
#ifndef GPI_TRACE_USER_SELECTION
  #define GPI_TRACE_USER_SELECTION GPI_TRACE_LOG_USER
#endif
GPI_TRACE_CONFIG(logging, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "cbor.h"
#include "deflate.h"
#include "traffic_bench.h"

#include "gpi/protothreads.h"
#include "gpi/tools.h"

#include <inttypes.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

#if !GPI_TRACE_MODE_IS_FLUSH_AUTO
  #define TRACE_AUTO_FLUSH() GPI_TRACE_FLUSH()
#else
  #define TRACE_AUTO_FLUSH() if (0)
#endif

#define TRACE_MSG(...)                                                                             \
  do {                                                                                             \
    GPI_TRACE_MSG(__VA_ARGS__);                                                                    \
    TRACE_AUTO_FLUSH();                                                                            \
  }                                                                                                \
  while (0)

// enable/disable TRACE flush between chunks and consecutive records
// can be used to output TRACE messages with about the same priority as log records (e.g. for
// debugging purposes). Without TRACE_INTERMEDIATE_FLUSH, log records have higher priority.
// Normally the latter is preferred, as losing TRACE messages is typically less critical than
// losing log records.
#define TRACE_INTERMEDIATE_FLUSH 0

// special control characters
// ATTENTION: We replace 0x04 (EOT) by 0x17 (ETB) because EOT gets filtered out by some (not all)
// FlockLab observers (we have seen it getting removed at node 1 and passed through at nodes 2 and 8).
// Maybe this happens because EOT is interpreted as end-of-file in some contexts, for details see
// <https://en.wikipedia.org/wiki/End-of-Transmission_character>.
#define BEGIN_RECORD             "\001" // start of record = SOH (ASCII "Start of Header")
#define BEGIN_CHUNK              "\002" // start of chunk = STX (ASCII "Start of Text")
#define END_CHUNK                "\003" // end of chunk = ETX (ASCII "End of Text")
#define END_RECORD               "\027" // end of record = ETB (ASCII "End of Transmission Block")
//#define END_RECORD	"\004"		// end of record = EOT (ASCII "End of Transmission")

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************

// CBOR serialized packet output
typedef struct __attribute__((packed)) Log_Packet
{
    cbor_uint16_t record_counter; // can be used by the reader to detect missing records
    cbor_uint8_t  node_id;
    cbor_uint32_t timestamp_schedule_global;
    cbor_uint32_t timestamp_schedule_local;
    cbor_uint32_t timestamp_ref;
    cbor_uint32_t timestamp_end;
    cbor_int16_t  timestamp_ref_deviation;
    cbor_uint16_t late_start_delay;

    cbor_uint8_t  trx_status;

    cbor_bstr16_t packet;

    // the following is added manually after the dynamic-length string
    // cbor_uint_t		tx_delay;				// 0 in case of Rx

    // TODO: radio mode

} Log_Packet;

// CBOR serialized RSSI data output
typedef struct __attribute__((packed)) Log_Rssi
{
    cbor_uint_tiny_t status; // 1 = early readout detected, 2 = late readout detected
    cbor_uint32_t    timestamp_rssi_end;
    cbor_uint32_t    num_samples_missed;

    cbor_bstr16_t    samples;

    // the following is added manually after the dynamic-length string
    // cbor_uint_tiny_t	is_valid;

} Log_Rssi;

//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************

// Logging consists of multiple stages / layers (CBOR, compression, BASE64 encoding, etc.),
// and every stage requires some kind of input and output buffer. To save RAM, we do not
// reserve explicit buffers for each stage and instead use the currently unused part of
// log_buffer as scratchpad memory whenever possible. We reserve the last bytes of log_buffer
// to ensure that there always is at least a small buffer available.

#define LOG_BUFFER_RESERVED ((LOG_BUFFER_SIZE < 512) ? 64 : (LOG_BUFFER_SIZE / 8))
ASSERT_CT_STATIC(LOG_BUFFER_SIZE - LOG_BUFFER_RESERVED >=
                 sizeof(Log_Packet) + sizeof(Radio_Packet) + 50);

static uint8_t log_buffer[LOG_BUFFER_SIZE];
#define log_buffer_end (&log_buffer[sizeof(log_buffer) - LOG_BUFFER_RESERVED])
//static uint8_t * const		log_buffer_end = &log_buffer[sizeof(log_buffer) - LOG_BUFFER_RESERVED];

//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Local Functions ****************************************************************************

// BASE64 encoder
// call with dest = NULL to (re-)init
// call with len = 0 to finalize data block and flush internal buffer
// call with ret_sel > 0 to return updated src pointer, otherwise return updated dest pointer
static void *base64_encode(void *dest, size_t dest_size, const void *src, size_t len,
                           uint_fast8_t ret_sel)
{
    const static uint8_t ALPHABET[64] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    static union
    {
        uint8_t  a[3];
        uint32_t x;
    } buffer;
    static uint_fast8_t npending = 0;

    const uint8_t      *s        = src;
    uint8_t            *d        = dest;

    // init
    if (NULL == dest) npending = 0;

    else
    {
        // flush and reinit
        if (0 == len)
        {
            assert(dest_size >= 5);

            if (0 != npending)
            {
                uint16_t     t = 0;
                uint_fast8_t n = 3 - npending;

                d              = base64_encode(d, dest_size, &t, n, 0);

                for (; n > 0; n--) d[-n] = '=';

                npending = 0;
            }
        }

        else
        {
            while ((len > 0) && (dest_size >= 5))
            {
                for (; len > 0 && npending < 3; len--) buffer.a[npending++] = *s++;

                if (3 == npending)
                {
                    asm("rev %0, %1" : "=r"(buffer.x) : "r"(buffer.x));
                    // TODO: move to (gpi_)byteswap_16/32/x()

                    *d++ = ALPHABET[buffer.x >> 26];
                    buffer.x <<= 6;
                    *d++ = ALPHABET[buffer.x >> 26];
                    buffer.x <<= 6;
                    *d++ = ALPHABET[buffer.x >> 26];
                    buffer.x <<= 6;
                    *d++ = ALPHABET[buffer.x >> 26];

                    //*d++ = ALPHABET[(buffer.x >> 18) & 0x3F];
                    //*d++ = ALPHABET[(buffer.x >> 12) & 0x3F];
                    //*d++ = ALPHABET[(buffer.x >>  6) & 0x3F];
                    //*d++ = ALPHABET[(buffer.x >>  0) & 0x3F];

                    dest_size -= 4;

                    npending = 0;
                }
            }
        }

        assert(dest_size > 0);
        *d = '\0'; // without ++
    }

    if (ret_sel) return (void *) s;
    return d;
}

//**************************************************************************************************
/*
static uint16_t fletcher16(const void *data, size_t len)
{
	static uint32_t		c0, c1;
	const uint8_t		*s = data;

	// flush and reinit
	if (NULL == data)
	{
		uint32_t c = c0 | (c1 << 8);

		c0 = c1 = 0;

		switch (len)
		{
			case 0:	break;
			case 1:
				// return (-c0 - c1) % 0xff, c1
				// If these values are appended to the data block (instead of c0, c1 as is),
				// then the checksum of the extended block becomes 0 (for details see
				// https://de.wikipedia.org/wiki/Fletcher%E2%80%99s_Checksum#Varianten).
				// To make this work, take care with the byte order.
				return ((-(c & 0xff) - (c >> 8)) % 0xff) | (c & 0xff00);
			default: assert(0);
		}

		return c;
	}

	else
	{
		while (len)
		{
			// limit block length such that c0 and c1 do not overflow for sure
			// MATLAB/Octave script to find this value:
			//	x = 255 * ones(1,10000);
			//	c0 = cumsum(x);
			//	c1 = cumsum(c0);
			//	find(c1 >= 2^32, 1) - 1
			size_t l = MIN(len, 5803);

			len -= l;

			while (l--)
			{
				c0 += *s++;
				c1 += c0;
			}

			#if 1
				c0 %= 0xff;
				c1 %= 0xff;
			#else
				// use the following if division is slow
				while (c0 > 0xff)
					c0 = (c0 & 0xff) + (c0 >> 8);
				while (c1 > 0xff)
					c1 = (c1 & 0xff) + (c1 >> 8);
			#endif
		}
	}

	return c0 | (c1 << 8);
}
*/
//**************************************************************************************************

// compute Fletcher-32 checksum
// for details see
// <https://en.wikipedia.org/wiki/Fletcher%27s_checksum>
// <https://de.wikipedia.org/wiki/Fletcher%E2%80%99s_Checksum>
static uint32_t fletcher32(const void *data, size_t len)
{
    static uint32_t c0, c1;
    static uint16_t buffer;
    static uint32_t buffer_state;
    const uint8_t  *s = data;

    // flush and reinit
    if (NULL == data)
    {
        const static uint8_t padding[1] = {0};
        uint32_t             c;

        if ((int32_t) buffer_state >= 0) c = fletcher32(&padding, sizeof(padding));
        else c = c0 | (c1 << 16);

        c0 = c1      = 0;
        buffer_state = 0xaaaaaaaa;

        switch (len)
        {
            case 0: break;
            case 1:
                // return (-c0 - c1) % 0xffff, c1
                // If these values are appended to the data block (instead of c0, c1 as is),
                // then the checksum of the extended block becomes 0 (for details see
                // https://de.wikipedia.org/wiki/Fletcher%E2%80%99s_Checksum#Varianten).
                // To make this work, take care with the byte order.
                return ((-(c & 0xffff) - (c >> 16)) % 0xffff) | (c & 0xffff0000);
            default: assert(0);
        }

        return c;
    }

    else
    {
        while (len)
        {
            // limit block length such that c0 and c1 do not overflow for sure
            // MATLAB/Octave script to find this value:
            //	x = 65535 * ones(1,1000);
            //	c0 = cumsum(x);
            //	c1 = cumsum(c0);
            //	find(c1 >= 2^32, 1) - 1
            size_t l = MIN(len, 361);

            len -= l;

            while (l--)
            {
                buffer <<= 8;
                buffer |= *s++;
                buffer_state = (buffer_state << 1) | (buffer_state >> 31); // rotate left

                if ((int32_t) buffer_state < 0)
                {
                    c0 += buffer;
                    c1 += c0;
                }
            }

#if 1
            c0 %= 0xffff;
            c1 %= 0xffff;
#else
            // use the following if division is slow
            while (c0 > 0xffff) c0 = (c0 & 0xffff) + (c0 >> 16);
            while (c1 > 0xffff) c1 = (c1 & 0xffff) + (c1 >> 16);
#endif
        }
    }

    return c0 | (c1 << 16);
}

//**************************************************************************************************

// provide functionality of puts(), but without implicit newline
static inline size_t _print(const char *s)
{
    // Normally we would use fputs(s, stdout), but for some reason stdout redirects to SEMIHOST
    // in SEGGER environment, even if STD is selected as target (SEGGER SES V5.50d).
    // We avoid using printf("%s", s) because it splits the output into putchar() calls,
    // which is much less efficient and does not exploit the full potential of GPI's tx buffer.
    // The following replacement is really dirty, but at least it does what we want.

    ASSERT_CT(GPI_ARCH_IS_CRT(SEGGER2));

    size_t n = strlen(s);

    __SEGGER_RTL_X_file_write(stdout, s, n);

    // Since we need it here anyhow, we return the length of s (can be used by the caller).
    return n;
}

//**************************************************************************************************

// flush log_buffer (print BASE64 output and update checksum)
#ifndef __OPTIMIZE__
__attribute__((optimize("Og")))
#endif
static size_t
flush_log(void *start, void *end)
{
    // MAX_LINE_LEN can be used to split the output over multiple lines, each with length <= MAX_LINE_LEN.
    // This can be necessary depending on the host, e.g. FlockLab inserts garbage (timestamps)
    // if lines get longer than 4096 bytes (1024 bytes before 2022-02-23).
    // Set MAX_LINE_LEN = 0 to deactivate line splitting.
    // (With optimization enabled, the function is reduced to a very simple version in this case.)
    const size_t  MAX_LINE_LEN = 4095; // -1 because unclear if host needs space for a trailing zero

    // reserved space (num. characters) in max_line_len:
    //	\n or \r\n (2)
    //	BEGIN/END_CHUNK markers (2)
    //	some buffer for things not counted here (BEGIN/END_RECORD markers and the like) (0)
    const size_t  max_line_len = MAX_LINE_LEN - 4;
    static size_t line_free    = max_line_len;
    uint8_t      *s            = (uint8_t *) start;
    uint8_t      *d            = (uint8_t *) end;
    ptrdiff_t     len          = d - s;
    ptrdiff_t     space        = &log_buffer[sizeof(log_buffer)] - d;

    ASSERT_CT((max_line_len >= 5) || !MAX_LINE_LEN);
    assert(space >= 5); // catch buffer overruns

    // init
    if (NULL == start)
    {
        if (MAX_LINE_LEN) line_free = max_line_len;

        return 0;
    }

    // update checksum
    fletcher32(start, len);

    // print BASE64 segment
    while (s < d)
    {
        if (MAX_LINE_LEN)
        {
            if (line_free < 5)
            {
// do not flush BASE64 buffer (chunks need not be self-contained)
// ATTENTION: otherwise concatenating chunks would result in concatenated full BASE64
// segments (with '=' chars in the middle), which would need to be handled explicitly
// base64_encode(d, space, NULL, 0, 0);
// _print(d);

// close current chunk, new line, start next chunk
#if TRACE_INTERMEDIATE_FLUSH
                _print(END_CHUNK "\n");
                GPI_TRACE_FLUSH();
                _print(BEGIN_CHUNK);
#else
                _print(END_CHUNK "\n" BEGIN_CHUNK);
#endif
                line_free = max_line_len;
            }

            s = base64_encode(d, MIN(space, line_free), s, d - s, 1);
            line_free -= _print(d);
        }

        else
        {
            s = base64_encode(d, space, s, d - s, 1);
            _print(d);
        }
    }

    return len;
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

// logging thread
PT_THREAD(log_thread())
{
    struct pt *const pt = pt_log;

    static uint32_t  rx_queue_num_read;
    Rx_Queue_Entry  *q;
    uint32_t         n;

    PT_BEGIN(pt);

    rx_queue_num_read = rx_queue_num_written_postproc;

    // first call = init
    TRACE_MSG(TRACE_INFO, "log thread started");
    PT_YIELD(pt);

    // main loop
    while (1)
    {
        // wait for data
        PT_WAIT_UNTIL(pt, rx_queue_num_read != rx_queue_num_written_postproc);

        // check for and handle rx_queue overflow
        n = rx_queue_num_written_postproc - rx_queue_num_read;
        if (n > NUM_ELEMENTS(rx_queue))
        {
            TRACE_MSG(TRACE_WARNING, "rx queue overflow, %u entries lost", n);
            rx_queue_num_read += n;
            continue;
        }

        // current rx_queue entry
        q                           = &rx_queue[rx_queue_num_read % NUM_ELEMENTS(rx_queue)];

        // copy critical data
        uint_fast8_t is_rx          = !(q->packet.is_tx);
        uint8_t      payload_length = q->packet.raw_payload_length;
        uint32_t     timestamp_end  = q->timestamp_end;
        uint32_t     rssi_nw_begin  = q->rssi_space_num_written_begin;

        REORDER_BARRIER();

        // catch potential concurrent rx_queue overflow
        n = rx_queue_num_writing - rx_queue_num_read;
        if (n >= NUM_ELEMENTS(rx_queue))
        {
            // ATTENTION: do not advance beyond rx_queue_num_written_postproc
            n = MIN(n, rx_queue_num_written_postproc - rx_queue_num_read);
            TRACE_MSG(TRACE_WARNING, "rx queue overflow, %u entries lost", n);
            rx_queue_num_read += n;
            continue;
        }

        // assemble and print output record
        // NOTE: log_buffer is used for both, binary and BASE64 data. However, the BASE64 part
        // is assigned carefully on demand, so it need not be taken care of in the following.

        uint8_t       *cp;
        cbor_bstr16_t *chunk_str;
        size_t         len = 0;

        cp                 = log_buffer;

        // start chunk list (outer CBOR format)
        cp                 = cbor_encode_array_tiny(*cp, -1);

        // start uncompressed chunk
        cp                 = cbor_encode_uint_tiny(*cp, 0);
        chunk_str          = (cbor_bstr16_t *) cp;
        cp                 = cbor_encode_bstr(*chunk_str, NULL, 0);

        // log packet
        // NOTE: setting record_counter = rx_queue_num_read enables the log parser to detect missing
        // records not only due to losses in the log file, but also due to rx_queue overruns
        {
            Log_Packet *cpacket = (Log_Packet *) cp;

            cbor_encode_uint(cpacket->record_counter, rx_queue_num_read);
            cbor_encode_uint(cpacket->node_id, my_node_id);
            cbor_encode_uint(cpacket->timestamp_schedule_global, q->timestamp_schedule_global);
            cbor_encode_uint(cpacket->timestamp_schedule_local, q->timestamp_schedule_local);
            cbor_encode_uint(cpacket->timestamp_ref, q->timestamp_ref);
            cbor_encode_uint(cpacket->timestamp_end, timestamp_end);
            cbor_encode_int(cpacket->timestamp_ref_deviation, q->timestamp_ref_deviation);
            cbor_encode_uint(cpacket->late_start_delay, q->late_start_delay);
            cbor_encode_uint(cpacket->trx_status, q->packet.trx_status >> 24);

            cp = cbor_encode_bstr(cpacket->packet, &(q->packet.ble_header), 2 + payload_length + 3);
            memcpy(cp - 3, &(q->packet.trx_status), 3);

            cp = cbor_encode_uint_by_value(*cp, is_rx ? 0 : q->tx_delay);
        }

        REORDER_BARRIER();

        // in case of concurrent rx_queue overflow: drop log data, catch overflow above
        if (rx_queue_num_writing - rx_queue_num_read >= NUM_ELEMENTS(rx_queue)) continue;

        GPI_TRACE_MSG(TRACE_INFO, "log packet [%u]", rx_queue_num_read);

        //len = cp - (uint8_t*)cpacket;
        //trace_dump("packet (CBOR):", cpacket, len);

        // init logging stack
        base64_encode(NULL, 0, NULL, 0, 0);
        fletcher32(NULL, 0);
        flush_log(NULL, NULL);

        // start transmission (print transmission header)
        {
            // add human-readable timestamp before the record
            // this is optional and simplifies the alignment of log records with the TRACE message
            // stream when evaluating log files. The timestamp has no influence of filter_logs.py.
            // NOTE: Use sprintf() instead of printf() to avoid character by character output (see
            // comments in _print() for details).
            char timestamp[16];
            sprintf(timestamp, "\n%u ", gpi_tick_fast_to_us(gpi_tick_fast_native()));
            _print(timestamp);
        }
        _print(BEGIN_RECORD "TRX:\n");

        // start message segment (character chunk)
        // maybe move this to flush_log() if segments need to be interleaved with TRACE messages
        _print(BEGIN_CHUNK);

        // log RSSI data
        if (is_rx && (-1u != rssi_nw_begin))
        {
            Rssi_Buffer *rssi =
                    (Rssi_Buffer *) &rssi_space[rssi_nw_begin % NUM_ELEMENTS(rssi_space)];
            uint32_t  nsamples = rssi->num_written;

            Log_Rssi *crssi    = (Log_Rssi *) cp;

            // ATTENTION: Log_Rssi::status is of type cbor_uint_tiny_t. Although rssi->status < 24
            // if valid, this need not hold if rssi_space overflows in between -> enforce it explicitly
            cbor_encode_uint(crssi->status, MIN(23, rssi->status));
            cbor_encode_uint(crssi->timestamp_rssi_end, rssi->timestamp_rssi_end);
            cbor_encode_uint(crssi->num_samples_missed, rssi->num_missed);

            REORDER_BARRIER();

            if (rssi_space_num_writing - rssi_nw_begin >= NUM_ELEMENTS(rssi_space)) nsamples = 0;

            cp = cbor_encode_bstr(crssi->samples, NULL, nsamples);

            if (nsamples > 0)
            {
                // close current chunk
                cbor_encode_bstr(*chunk_str, NULL, cp - (uint8_t *) (chunk_str + 1));

                len += flush_log(log_buffer, cp);
                cp = log_buffer;

                // start compressed chunk
                cp = cbor_encode_uint_tiny(*cp, 1);
                cp = cbor_encode_bstr_envelope(*cp);

                len += flush_log(log_buffer, cp);
                cp        = log_buffer;

                // prepare bstr block
                chunk_str = (cbor_bstr16_t *) cp;
                cp        = cbor_encode_bstr(*chunk_str, NULL, 0);

                // init deflate
                deflate(NULL, 0, NULL, 0, NULL, NULL, NULL, NULL);

                uint8_t *src = rssi->samples;
                size_t   nwritten, nread;
                size_t   nwritten_cum = 0;

                // open deflate block
                deflate(cp, log_buffer_end - cp, src, 0, DEFLATE_C1_DIFF1, rssi->samples, &nwritten,
                        NULL);
                //deflate(cp, log_buffer_end - cp, src, 0, DEFLATE_C2_DIFF1, rssi->samples, &nwritten, NULL);
                //deflate(cp, log_buffer_end - cp, src, 0, DEFLATE_C2_DIFF2, rssi->samples, &nwritten, NULL);
                if (0 != nwritten)
                {
                    cbor_encode_bstr(*chunk_str, NULL, nwritten);
                    len += flush_log(log_buffer, cp + nwritten);
                    nwritten_cum += nwritten;
                }

                while (nsamples > 0)
                {
                    deflate(cp, log_buffer_end - cp, src, nsamples, NULL, rssi->samples, &nwritten,
                            &nread);

                    src += nread;
                    nsamples -= nread;

                    if (0 == nsamples)
                    {
                        ASSERT_CT((intptr_t) (&log_buffer[sizeof(log_buffer)] - log_buffer_end) >
                                  8);

                        nread = nwritten;
                        deflate(cp + nwritten, 8, NULL, 0, DEFLATE_FLUSH, NULL, &nwritten, NULL);
                        nwritten += nread;
                    }

                    assert(0 != nwritten);
                    cbor_encode_bstr(*chunk_str, NULL, nwritten);
                    len += flush_log(log_buffer, cp + nwritten);
                    nwritten_cum += nwritten;
                }

                nread = src - rssi->samples;
                if (0 != nread)
                    GPI_TRACE_MSG(TRACE_INFO, "compression ratio: %u -> %u (%d%% reduction)", nread,
                                  nwritten_cum, 100 - ((nwritten_cum * 100) / nread));

                cp        = log_buffer;

                // close compressed chunk (bstr envelope)
                cp        = cbor_encode_break(*cp);

                // start uncompressed chunk
                cp        = cbor_encode_uint_tiny(*cp, 0);
                chunk_str = (cbor_bstr16_t *) cp;
                cp        = cbor_encode_bstr(*chunk_str, NULL, 0);
            }

            REORDER_BARRIER();

            // mark concurrent overflow
            if ((n = rssi_space_num_writing - rssi_nw_begin) >= NUM_ELEMENTS(rssi_space))
            {
                // use GPI_TRACE_MSG() instead of TRACE_MSG() to avoid interrupting BASE64 output
                GPI_TRACE_MSG(TRACE_WARNING, "rssi_space overflow (%u bytes)", n);
                n = 0;
            }
            else n = 1;
            cp = cbor_encode_uint_tiny(*cp, n);
        }

        // close current chunk
        cbor_encode_bstr(*chunk_str, NULL, cp - (uint8_t *) (chunk_str + 1));

        // flush to get current raw data length
        len += flush_log(log_buffer, cp);
        cp = log_buffer;

        // add an empty chunk if necessary to ensure that the full length is even
        // (simplifies checksum computation for the reader)
        if (len & 1)
        {
            cp = cbor_encode_uint_tiny(*cp, 0);
            cp = cbor_encode_bstr8(*cp, NULL, 0);
        }

        // close chunk list
        cp = cbor_encode_break(*cp);

        // prepare checksum field, but without the checksum itself (follows below)
        cbor_encode_uint32(*cp, 0);
        cp += offsetof(cbor_uint32_t, val);

        // flush again to get final checksum value
        len += flush_log(log_buffer, cp);
        cp = log_buffer;
        assert(!(len & 1));

        // append checksum
        cp = cbor_encode_uint32(*cp, fletcher32(cp, 0));
        flush_log(&log_buffer[offsetof(cbor_uint32_t, val)], cp);

        // flush BASE64 buffer
        base64_encode(log_buffer, sizeof(log_buffer), NULL, 0, 0);
        _print(log_buffer);

        // end message segment (character chunk)
        // maybe move this to flush_log() if segments need to be interleaved with TRACE messages
        _print(END_CHUNK "\n");

        // end transmission
        // NOTE: trailing CR makes this invisible at a terminal
        _print(END_RECORD "\r");

        // go to next rx_queue entry (done with current entry)
        rx_queue_num_read += 1;

#if TRACE_INTERMEDIATE_FLUSH
        GPI_TRACE_FLUSH();
#endif
    }

    PT_END(pt);
}

//**************************************************************************************************
//**************************************************************************************************
