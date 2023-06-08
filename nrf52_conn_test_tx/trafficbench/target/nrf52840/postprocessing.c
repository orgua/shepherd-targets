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
 *	@file					postprocessing.c
 *
 *	@brief					RSSI samples postprocessing thread
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
  #define GPI_TRACE_BASE_SELECTION (GPI_TRACE_LOG_STANDARD | GPI_TRACE_LOG_PROGRAM_FLOW)
#endif
#ifndef GPI_TRACE_USER_SELECTION
  #define GPI_TRACE_USER_SELECTION GPI_TRACE_LOG_USER
#endif
GPI_TRACE_CONFIG(postprocessing, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "traffic_bench.h"

#include "gpi/interrupts.h"
#include "gpi/protothreads.h"
#include "gpi/tools.h"

#include <assert.h>
#include <inttypes.h>
//#include <stdlib.h>
#include <string.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

#ifdef NDEBUG
  #define RUNTIME_CHECKS 1
#else
  #define RUNTIME_CHECKS 0
#endif

#if RUNTIME_CHECKS
  #define ASSERT_ELSE(cond) if (!(cond))
#else
  #define ASSERT_ELSE(cond)                                                                        \
    if (1) assert(cond);                                                                           \
    else
#endif

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************


//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************


//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Local Functions ****************************************************************************

// 4x uint8_t subtraction (SIMD)
static inline uint32_t usub8(uint32_t a, uint32_t b)
{
    uint32_t r;

    asm("usub8 %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));

    return r;
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

// postprocessing thread
PT_THREAD(postproc_thread())
{
    struct pt *const pt = pt_postprocess;

    static uint32_t  rssi_space_num_written_postproc;

    uint32_t rx_queue_num_read = rx_queue_num_written_postproc; // faster because non-volatile

    PT_BEGIN(pt);

    rssi_space_num_written_postproc = rssi_space_num_written_radio;

    // first call = init
    GPI_TRACE_MSG(TRACE_INFO, "postprocessing thread started");
    PT_YIELD(pt);

    while (1)
    {
        Rx_Queue_Entry *q;
        uint32_t        n;

        // wait until data available
        PT_WAIT_UNTIL(pt, rx_queue_num_read != rx_queue_num_written_trx);

        // current rx queue entry
        q                                = &rx_queue[rx_queue_num_read % NUM_ELEMENTS(rx_queue)];

        // copy critical data to local variables (to ensure consistency)
        uint_fast8_t is_rx               = !(q->packet.is_tx);
        uint_fast8_t is_header           = q->packet.header_detected;
        uint_fast8_t is_timeout          = q->packet.timeout_triggered;
        uint32_t     timestamp_ref       = q->timestamp_ref;
        uint32_t     timestamp_end       = q->timestamp_end;
        uint32_t     rssi_space_nw_begin = q->rssi_space_num_written_begin;

        REORDER_BARRIER();

        // check rx_queue overflow
        n = rx_queue_num_writing - rx_queue_num_read;
        if (n > NUM_ELEMENTS(rx_queue))
        {
            // ATTENTION: do not advance beyond rx_queue_num_written_trx
            n = rx_queue_num_written_trx - rx_queue_num_read;

            GPI_TRACE_MSG(TRACE_WARNING, "rx queue overflow, %u entries lost", n);
            rx_queue_num_read += n;
            rx_queue_num_written_postproc = rx_queue_num_read;
            continue;
        }

        // postprocess rssi data
        // ATTENTION: rx_queue does also contain tx packets
        if (is_rx)
        {
            Rssi_Buffer *src_buf =
                    (Rssi_Buffer *) &rssi_space[rssi_space_nw_begin % NUM_ELEMENTS(rssi_space)];
            Rssi_Buffer *dst_buf;
            uint8_t      hdr_data[offsetof(Rssi_Buffer, samples)];
            Rssi_Buffer *hdr = (Rssi_Buffer *) &hdr_data[0];

            // copy critical data to local variables (to ensure consistency)
            memcpy(hdr, src_buf, sizeof(hdr_data));

            REORDER_BARRIER();

            GPI_TRACE_MSG(TRACE_INFO, "postprocessing Rx packet [%u]", rx_queue_num_read);

            // check rssi_space overflow

            // we expect rssi_space_num_written_postproc behind rssi_space_nw_begin
            ASSERT_ELSE((int32_t) (rssi_space_nw_begin - rssi_space_num_written_postproc) >= 0)
            {
                GPI_TRACE_MSG(TRACE_ERROR, "assertion failed, dropping RSSI samples");
                hdr->num_written = 0; // drop rssi samples
            }

            // if rssi_space_num_written_postproc overflow: advance to rssi_space_nw_begin
            // NOTE: we do not lose anything by doing so
            // NOTE: one reason for this is overflow during last postproc. cycle (see below)
            if (rssi_space_num_writing - rssi_space_num_written_postproc > NUM_ELEMENTS(rssi_space))
            {
                GPI_TRACE_MSG(TRACE_VERBOSE, "adjusting rssi_nw_postproc (+%u)",
                              rssi_space_nw_begin - rssi_space_num_written_postproc);

                rssi_space_num_written_postproc = rssi_space_nw_begin;
            }

            // if overflow: drop samples
            // NOTE: this avoids damaging samples from other packets (see below)
            if (rssi_space_num_writing - rssi_space_nw_begin > NUM_ELEMENTS(rssi_space))
            {
                GPI_TRACE_MSG(TRACE_WARNING, "RSSI space overflow (q)");
                hdr->num_written = 0; // drop rssi samples
            }

            uint32_t src_buf_size = 1 << hdr->size_msb; // pure sample buffer
            uint32_t rssi_nw_end  = hdr->num_written;
            uint32_t dst_size; // full buffer (incl. header)

// DEBUG: test for invalid RSSI samples when reading the buffer
// (indicates that something went wrong, e.g. with buffer management)
#if 0
  #if 1 // standard case
					uint32_t is_invalid_samples = 0;
    #define CHECK_SAMPLES(x)     is_invalid_samples |= x
    #define IS_INVALID_SAMPLES() (is_invalid_samples & 0x80808080)
  #else // dummy sawtooth signal (see sampling ISR)
					int_fast16_t	is_invalid_samples = -1;
					uint8_t			x_last;
    #define CHECK_SAMPLES(x_)                                                                      \
      do {                                                                                         \
        uint32_t x = x_;                                                                           \
        for (int_fast8_t i = 4; i-- > 0;)                                                          \
        {                                                                                          \
          if (is_invalid_samples < 0) is_invalid_samples = 0;                                      \
          else is_invalid_samples |= (uint8_t) x - x_last - UINT8_C(1);                            \
          x_last = x;                                                                              \
          x >>= 8;                                                                                 \
        }                                                                                          \
      }                                                                                            \
      while (0)
    #define IS_INVALID_SAMPLES() is_invalid_samples
  #endif
#else
  #define CHECK_SAMPLES(x)     if (0)
  #define IS_INVALID_SAMPLES() 0
#endif

            GPI_TRACE_MSG(
                    TRACE_VERBOSE,
                    "RSSI space: "
                    "nw_hot 0x%08x, nw_pp 0x%08x, nw_radio 0x%08x, buf 0x%08x, buf_size 0x%05x",
                    rssi_space_num_writing, rssi_space_num_written_postproc,
                    rssi_space_num_written_radio, rssi_space_nw_begin, src_buf_size);

            assert(!(rssi_space_num_writing % 4));
            assert(!(rssi_space_num_written_radio % 4));
            assert(!(rssi_space_num_written_postproc % 4));
            assert(!(rssi_space_nw_begin % 4));
            assert(!(src_buf_size % 4));

#if 0
	trace_dump("RSSI hdr: ", hdr, sizeof(Rssi_Buffer));
	trace_dump("RSSI:", src_buf->samples, MIN(rssi_nw_end, src_buf_size));
#endif

            // determine window with relevant samples
            {
                uint32_t n1;

                n  = MIN(rssi_nw_end, src_buf_size);
                n1 = 0;

                GPI_TRACE_MSG(TRACE_VERBOSE, "%u samples available (nw_end 0x%08x)", n,
                              rssi_nw_end);

                // cut excess samples after packet
                if (!is_timeout)
                {
                    n1 = gpi_tick_fast_to_us(hdr->timestamp_rssi_end - timestamp_end);
                    GPI_TRACE_MSG(TRACE_VERBOSE, "%u posttrigger samples available", MIN(n, n1));

                    // +3 as the subsequent alignment step can cut up to 3 samples
                    n1 -= gpi_tick_fast_to_us(hdr->posttrigger_time) + 3;
                    n1 = ((int32_t) n1 > 0) ? MIN(n, n1) : 0;
                }

                // align end at word boundary
                n1 += MIN(n - n1, (rssi_nw_end - n1) % sizeof(uint32_t));

                if (n1 > 0)
                {
                    GPI_TRACE_MSG(TRACE_VERBOSE, "cutting %u posttrigger samples", n1);

                    hdr->timestamp_rssi_end -= n1 * GPI_TICK_US_TO_FAST(1);
                    rssi_nw_end -= n1;
                    n -= n1;
                }

                // cut excess samples before packet
                if (is_header)
                {
                    ASSERT_CT(GPI_FAST_CLOCK_RATE >= 1000000);

                    // n1 = timestamp_start
                    // NOTE: compute n1 based on timestamp_ref (not timestamp_end)
                    // to minimize the influence of clock drift between transmitter and receiver
                    // (the slight difference between nominal and effective packet air time can
                    // get appreciable in case of long packets, especially in BLE 125K mode)
                    n1 = timestamp_ref - radio_get_ref_timestamp_offset(gpi_radio_get_mode());
                    //n1 = timestamp_end - radio_get_packet_airtime(payload_length);

                    // n1 = num. samples to keep
                    // +1 as gpi_tick_fast_to_us() may round towards 0 (floor)
                    // +3 as the subsequent alignment step can cut up to 3 samples
                    n1 = gpi_tick_fast_to_us(hdr->timestamp_rssi_end - n1) + 1 +
                         gpi_tick_fast_to_us(hdr->pretrigger_time) + 3;

                    // n1 = num. samples to cut
                    n1 = n - n1;

                    if ((int32_t) n1 >= 0)
                    {
                        // >= as the subsequent alignment step can cut additional samples (up to 3)
                        GPI_TRACE_MSG(TRACE_VERBOSE, "cutting >= %u pretrigger samples", n1);
                        n -= n1;
                    }
                    else
                        GPI_TRACE_MSG(TRACE_INFO,
                                      "lacking %u samples to fulfill pre-/posttrigger time", -n1);
                }

                // align size (and implicitly begin) at word boundary
                n -= n % sizeof(uint32_t);
                //n &= ~(sizeof(uint32_t) - 1);
            }

            // choose destination for postproc. data inside rssi_space
            dst_size = sizeof(Rssi_Buffer) + n;
            {
                uint32_t space = NUM_ELEMENTS(rssi_space) -
                                 (rssi_space_num_written_postproc % NUM_ELEMENTS(rssi_space));

                if (dst_size > space)
                {
                    rssi_space_num_written_postproc += space;

                    ASSERT_ELSE((int32_t) (rssi_space_nw_begin - rssi_space_num_written_postproc) >=
                                0)
                    {
                        GPI_TRACE_MSG(TRACE_ERROR, "assertion failed, dropping RSSI samples");
                        n = 0; // drop samples
                    }
                }
            }

            dst_buf = (Rssi_Buffer *) &rssi_space[rssi_space_num_written_postproc %
                                                  NUM_ELEMENTS(rssi_space)];

            GPI_TRACE_MSG(TRACE_VERBOSE, "postprocessing %u samples, dst_buf 0x%05x", n,
                          rssi_space_num_written_postproc % NUM_ELEMENTS(rssi_space));

            //trace_dump("hdr:", hdr, sizeof(Rssi_Buffer));
            //trace_dump("buf before:", src_buf, sizeof(Rssi_Buffer) + src_buf_size);

            // postprocess data
            // NOTE: this can damage other data in case of buffer overflow, which is handled below
            {
                uint32_t       *s_buf         = (uint32_t *) &(src_buf->samples[0]);
                uint32_t *const s_buf_end     = (uint32_t *) &(src_buf->samples[src_buf_size]);
                uint32_t        rssi_nw_begin = rssi_nw_end - n;
                ptrdiff_t       n1;
                uint32_t       *d, *s, *s_end;
                uint32_t        x, y;
                uint8_t         y_prev = 0;

                // ATTENTION: n and rssi_nw_end must be word-aligned (which is established above)
                n /= sizeof(uint32_t);

#ifndef __BYTE_ORDER__
  #error "byte order is unknown"
#else
                ASSERT_CT(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
#endif

// DEBUG: test RSSI samples before touching the buffer
// this is unsafe because buffer can overflow in between
#if 0
					s = (uint32_t*)&(src_buf->samples[rssi_nw_begin & (src_buf_size - 1)]);
					for (n1 = n; n1-- > 0;)
					{
						if (*s & 0x80808080)
						{
							GPI_TRACE_MSG(TRACE_ERROR, "invalid sample at 0x%05x (0x%05x, n1 = %u, n = %u)!",
								(uint8_t*)s - src_buf->samples, (uint8_t*)s - rssi_space, n1, n);
						}

						if (++s >= s_buf_end)
							s = s_buf;
					}
#endif

                // init dest and source pointers
                // NOTE: Indexing saves wrap-around of s_end if not needed (due to half-open
                // interval). The method can lead to wrong result in case of n = 0, but s_end
                // is not used in this case.
                d     = (uint32_t *) &(dst_buf->samples[0]);
                s     = (uint32_t *) &(src_buf->samples[rssi_nw_begin & (src_buf_size - 1)]);
                s_end = (uint32_t *) &(
                        src_buf->samples[((rssi_nw_end - 1) & (src_buf_size - 1)) + 1]);

                // process samples
                while (n)
                {
                    // current source segment
                    typeof(s) s_seg_end = (s < s_end) ? s_end : s_buf_end;
                    ptrdiff_t s_seg_len = s_seg_end - s;
                    n1                  = 0;

                    // find buffer constellations that can be handled with simple memcpy()-style
                    // processing in forward direction (this is most efficient)

                    // dest before source buffer
                    if (d < s_buf) n1 = MIN(s_seg_len, s_buf - d);
                    else if (
                            0

                            // dest before single (contiguous) source segment
                            || ((d < s) && (s < s_end))

                            // dest in second (wrapped-around) source segment -> handled below

                            // dest between source segments
                            || ((d < s) && (d >= s_end))

                            // dest equal to source pointer (d == s)
                            // this is a special case where processing works in place (without side effects)
                            || (d == s)

                            // dest in first (non-wrapped) / single source segment -> handled below

                            // dest behind single (contiguous) source segment
                            || ((d >= s_end) && (s < s_end))

                            // dest behind source buffer
                            || (d >= s_buf_end))
                        n1 = s_seg_len;

                    // process
                    if (n1)
                    {
                        n -= n1;
                        while (n1--)
                        {
                            // differential format (store differences)
                            y      = *s++;
                            *d++   = usub8(y, (y << 8) | y_prev);
                            y_prev = y >> 24;
                            CHECK_SAMPLES(y);
                        }

                        if (s == s_buf_end) s = s_buf;
                    }

                    // handle more painful buffer constellations

                    // dest in first (non-wrapped) / single source segment
                    else if (d > s) // && d < s_seg_end (follows from above)
                    {
                        // dest is inside source segment, so straightforwardly working
                        // from left to right would damage source data. There are two solutions:
                        // 1) Go backwards like memmove() would do. This requires one entry
                        //    look-ahead (into the past) for the differential encoding.
                        // 2) Break segment into chunks and exchange data instead of only copying it.
                        //    This uses the first part of the source segment as intermediate buffer.
                        // Solution 1) is faster, so we choose this one.

#if 1

                        d += s_seg_len;
                        s += s_seg_len;

                        x                   = *(--s);
                        uint8_t y_prev_next = x >> 24;

                        for (n1 = s_seg_len; n1-- > 0;)
                        {
                            y      = x;
                            x      = (n1) ? *(--s) : (y_prev << 24);
                            *(--d) = usub8(y, (y << 8) | (x >> 24));
                            CHECK_SAMPLES(y);
                        }

                        y_prev = y_prev_next;

                        d += s_seg_len;

#else

                        // ATTENTION: this has not been tested so far

                        typeof(s) s_start = s;
                        typeof(s) s_stop  = d;
                        typeof(s) d_stop  = d + s_seg_len;

                        while (d < d_stop)
                        {
                            s      = s_start;
                            s_stop = s + MIN(s_stop - s, d_stop - d);

                            // process with exchange of data blocks
                            while (s < s_stop)
                            {
                                x      = *d;
                                y      = *s;
                                *d++   = usub8(y, (y << 8) | y_prev);
                                *s++   = x;
                                y_prev = y >> 24;
                                CHECK_SAMPLES(y);
                            }
                        }

#endif

                        // either s = s_buf or don't care (if n == 0)
                        s = s_buf;
                        n -= s_seg_len;
                    }

                    // dest in second (wrapped-around) source segment
                    else
                    {
                        // This case is tricky because dest can overlap both source segments,
                        // and it must be ensured that none of them gets damaged. To avoid
                        // error-prone case distinctions, we use a compromise:
                        // We explicitly handle the case d == s_buf, which appears relatively
                        // often (dest and source buffer at same position, buffer quite full).
                        // In every other case we unwrap the source buffer (independent of dest)
                        // into a single contiguous segment placed at the end of the source buffer.
                        // This segment will then be handled in the next loop iteration.

                        if (d == s_buf)
                        {
                            const size_t STOP_THRESHOLD = 64 / sizeof(uint32_t);
                            int          stop           = 0;

                            //GPI_TRACE_MSG(TRACE_VERBOSE,
                            //	"d=%p, s_buf=%p, s_end=%p, s=%p, s_buf_end=%p, n=%u",
                            //	d, s_buf, s_end, s, s_buf_end, n);

                            while ((n > 0) && !stop)
                            {
                                typeof(s) sx = s;

                                // buffer layout:
                                //
                                //    s_buf       s_end       s       s_buf_end
                                //    |           |           |       |
                                // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                //   |2nd segment|free space |1st segment|
                                // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                //    |                   |
                                //    d                   d_buf_end

                                // if segment 1 < segment 2
                                if (s_buf_end - s < s_end - d)
                                {
                                    // exchange, flush
                                    n1 = s_buf_end - s;
                                    s_buf += n1;

                                    // before:
                                    //  d=s_buf       s_end       s       s_buf_end
                                    //    |           |           |       |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |4 5 6 7 8 9|           |0 1 2 3|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //
                                    // after:
                                    //      d=s_buf   s_end       s       s_buf_end
                                    //            |   |           |       |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |0 1 2 3|8 9|           |4 5 6 7|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                }

                                // if free space is so small that exchanging free space
                                // is faster than leaving the loop
                                else if ((s - s_end < STOP_THRESHOLD) && (s_buf_end - s >= s - d))
                                {
                                    // exchange, flush
                                    n1    = MIN(n, s - d);
                                    s_buf = s;
                                    s += n1;
                                    s_end += n1;

                                    // before:
                                    // d=s_buf s_end s                 s_buf_end
                                    //       |   |   |                 |
                                    //    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //      |9 A|   |0 1 2 3 4 5 6 7 8|
                                    //    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //
                                    // after:
                                    //         d=s_buf s_end s         s_buf_end
                                    //               |   |   |         |
                                    //    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //      |0 1 2 3|9 A|   |4 5 6 7 8|
                                    //    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                }

                                // segment 1 >= segment 2
                                else
                                {
                                    // exchange, squeeze, leave special handling if d != s_buf
                                    n1    = s_end - d;
                                    s_buf = s;
                                    s += n1;
                                    s_end = s;
                                    stop  = ((d + n1) != s_buf);

                                    // before:
                                    // d=s_buf  s_end     s                 s_buf_end
                                    //      |   |         |                 |
                                    //   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //     |9 A|         |0 1 2 3 4 5 6 7 8|
                                    //   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //
                                    // after:
                                    //          d     s_buf   s=s_end       s_buf_end
                                    //          |         |   |             |
                                    //   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //     |0 1|         |9 A|2 3 4 5 6 7 8|
                                    //   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                                    // before:
                                    //  d=s_buf       s_end   s       s_buf_end
                                    //    |           |       |       |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |4 5 6 7|           |0 1 2 3|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //
                                    // after:
                                    //            d      s_buf=s*     s_end=s_buf_end
                                    //            |           |       |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |0 1 2 3|           |4 5 6 7|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                    // (s* = s after wrap-around (follows below))

                                    // before:
                                    //  d=s_buf   s_end=s     s_buf_end
                                    //    |       |           |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |6 7 8 9|0 1 2 3 4 5|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+
                                    //
                                    // after:
                                    //      d=s_buf  s_end=s  s_buf_end
                                    //            |       |   |
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+
                                    //   |0 1 2 3|6 7 8 9|4 5|
                                    // +-+-+-+-+-+-+-+-+-+-+-+-+
                                }

                                // stop after wrap-around because remaining single segment
                                // will be handled efficiently above
                                if (s == s_buf_end)
                                {
                                    s    = s_buf;
                                    stop = 1;
                                }

                                //assert(n1 > 0);

                                // exchange and process
                                n -= n1;
                                while (n1--)
                                {
                                    x      = *d;
                                    y      = *sx;
                                    *d++   = usub8(y, (y << 8) | y_prev);
                                    *sx++  = x;
                                    y_prev = y >> 24;
                                    CHECK_SAMPLES(y);
                                }

                                //GPI_TRACE_MSG(TRACE_VERBOSE,
                                //	"d=%p, s_buf=%p, s_end=%p, s=%p, s_buf_end=%p, n=%u",
                                //	d, s_buf, s_end, s, s_buf_end, n);
                            }
                        }

                        else
                        {
                            // if there is enough space for an intermediate buffer
                            if (s - s_end >= s_end - s_buf)
                            {
                                memmove(s_buf_end - n, s, s_seg_len * sizeof(uint32_t));
                                s_seg_len = n - s_seg_len;
                                memcpy(s_buf_end - s_seg_len, s_buf, s_seg_len * sizeof(uint32_t));
                            }

                            // otherwise build blocks and exchange them step by step
                            // NOTE: complexity is linear (each exchange moves one item to its final place)
                            else
                            {
                                typeof(s) s_left  = s_buf;
                                typeof(s) s_mid   = s_end;
                                typeof(s) s_right = s_buf_end;

                                while ((s_left < s_mid) && (s_mid < s_right))
                                {
                                    // fix left part
                                    if (s_mid - s_left <= s_right - s_mid)
                                    {
                                        n1 = s_mid - s_left;

                                        // exchange(s_left, s_mid, n1); s_left += n1; s_mid += n1;
                                        while (n1--)
                                        {
                                            x         = *s_left;
                                            y         = *s_mid;
                                            *s_mid++  = x;
                                            *s_left++ = y;
                                        }
                                    }

                                    // fix right part
                                    else
                                    {
                                        n1 = s_right - s_mid;

                                        // exchange(s_mid - n1, s_mid, n1); s_right -= n1; s_mid -= n1;
                                        while (n1--)
                                        {
                                            x        = *(--s_right);
                                            y        = *(--s_mid);
                                            *s_mid   = x;
                                            *s_right = y;
                                        }
                                    }
                                }
                            }

                            // contiguous segment at end of buffer
                            s     = s_buf_end - n;
                            s_end = s_buf_end;
                        }
                    }
                }

                rssi_nw_end -= rssi_nw_begin;

                // temperature compensation (see 4413_510 v1.4 erratum [153] for details)
                if ((0 != rssi_nw_end) &&
                    ((('A' << 16) | ('A' << 8) | 'D') == (NRF_FICR->INFO.VARIANT >> 8)))
                {
                    static const int8_t OFFSET_LUT[] = {3, 2, 1, 0, -1, -2, -3};
                    int_fast16_t        i;
                    int8_t              offset;

                    i      = hdr->temperature;
                    i      = MAX(-30 * 4, i);
                    i      = MIN(71 * 4, i);

                    i      = (i + (30 * 4) + (20 * 4) - 1) / (20 * 4);
                    offset = OFFSET_LUT[i];

                    //i = q->temperature;
                    //if (i <= -(30 * 4))
                    //	offset = 3;
                    //else if (i <= -(10 * 4))
                    //	offset = 2;
                    //else if (i <= (10 * 4))
                    //	offset = 1;
                    //else if (i <= (30 * 4))
                    //	offset = 0;
                    //else if (i <= (50 * 4))
                    //	offset = -1;
                    //else if (i <= (70 * 4))
                    //	offset = -2;
                    //else offset = -3;

                    // due to the differential format we only need to update the first value
                    dst_buf->samples[0] += offset;
                }
            }

            // update rx_queue entry
            // ATTENTION: do not damage newer entries
            {
                register uint32_t nr = rx_queue_num_read;
                register uint32_t nw = (0 == rssi_nw_end) ? -1u : rssi_space_num_written_postproc;

                COMPUTE_BARRIER(nw);

                register int ie = gpi_int_lock();

                if (rx_queue_num_writing - nr <= NUM_ELEMENTS(rx_queue))
                    q->rssi_space_num_written_begin = nw;

                gpi_int_unlock(ie);

                // copy updated header data to destination buffer
                // NOTE: only if rssi_nw_end > 0 (else do not damage other rssi data)
                // NOTE: It is possible that q gets updated by radio rx between gpi_int_unlock() and if (...).
                // In this case the header will not get updated, which is not a problem
                // as the rssi buffer is dropped anyhow.
                if (q->rssi_space_num_written_begin == rssi_space_num_written_postproc)
                {
                    hdr->num_written = rssi_nw_end;
                    hdr->size_msb    = 0;
                    memcpy(dst_buf, hdr, sizeof(hdr_data));
                }
            }

            //trace_dump("buf after:", dst_buf, MIN(48, sizeof(Rssi_Buffer) + rssi_nw_end));

            // check for rssi_space overflow during postprocessing
            if ((0 != rssi_nw_end) && (rssi_space_num_writing - rssi_space_num_written_postproc >
                                       NUM_ELEMENTS(rssi_space)))
            {
                GPI_TRACE_MSG(TRACE_WARNING,
                              "RSSI space overflow (postproc), nw_hot 0x%08x, nw_pp 0x%08x",
                              rssi_space_num_writing, rssi_space_num_written_postproc);

                // drop all rssi data because we might have damaged samples from other packets
                radio_drop_rssi_space();

                // do not update rssi_space_num_written_postproc (will be catched with the next packet)
                // ATTENTION: this is important to ensure that rssi_space_num_written_postproc
                // stays behind rssi_space_nw_begin (see above)
                // rssi_space_num_written_postproc = rssi_space_num_written_radio;
            }

            else
            {
                // test if invalid samples have been found (if test functionality is enabled above)
                if (IS_INVALID_SAMPLES())
                //ASSERT_ELSE(!IS_INVALID_SAMPLES())
                {
                    GPI_TRACE_MSG(TRACE_ERROR, "invalid RSSI samples found! (%u, 0x%08x, 0x%08x)",
                                  rssi_nw_end, rssi_space_num_writing,
                                  rssi_space_num_written_postproc);
                }

                rssi_space_num_written_postproc += dst_size;

                // update rssi_space_num_written_radio whenever possible (to save space)
                radio_update_rssi_num_written(rx_queue_num_read + 1,
                                              rssi_space_num_written_postproc);

                GPI_TRACE_MSG(
                        TRACE_VERBOSE,
                        "postproc done, RSSI space: nw_hot 0x%08x, nw_pp 0x%08x, nw_radio 0x%08x",
                        rssi_space_num_writing, rssi_space_num_written_postproc,
                        rssi_space_num_written_radio);
            }
        }

        REORDER_BARRIER();

        rx_queue_num_written_postproc = ++rx_queue_num_read;
    }

    PT_END(pt);
}

//**************************************************************************************************
//**************************************************************************************************
