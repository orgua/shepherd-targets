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
 *	@file					gpi/arm/nordic/pca10059/stdio.c
 *
 *	@brief					platform specific stdio implementation (CRT internal functions)
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Fabian Mager
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/
//***** Trace Settings *****************************************************************************



//**************************************************************************************************
//**** Includes ************************************************************************************

#include "gpi/tools.h"
#include "gpi/platform_spec.h"
#include "gpi/platform.h"
#include "gpi/resource_check.h"

#include <nrf.h>

#include <stdio.h>

GPI_RESOURCE_RESERVE_SHARED(NRF_UARTE, 0);

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

// raise error if there is no UART connection
// TODO: add support for other stdio implementations (e.g. SEGGER RTT)
#ifndef _GPI_ARM_nRF_PCA10059_UART_TXD_PORT
	#error "stdio UART is not available"
#endif

// disable GPI_STDOUT_INTERRUPT_ENABLED on platforms that do not support it
#if !(GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2))
	#undef  GPI_STDOUT_INTERRUPT_ENABLED
	#define GPI_STDOUT_INTERRUPT_ENABLED	0
#endif

#define TX_CHAIN_INDEX_MASK		(NUM_ELEMENTS(tx_chain) - 1)

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************

#if GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2)

// implementation of FILE structure
// for details see <https://wiki.segger.com/Embedded_Studio_Library_IO>
struct __SEGGER_RTL_FILE_impl
{
	uint8_t		stub;	// only needed to enforce sizeof(FILE) > 0
};

#endif

//**************************************************************************************************
//***** Forward Declarations ***********************************************************************



//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************

// RAM area
// NOTE: do not used __RAM_segment_start__ and __RAM_segment_end__, as these symbols are
// specific for the build environment (SEGGER Embedded Studio with SEGGER Linker)
// NOTE: These symbols are used to test if some address is in RAM or not, which is a pure
// hardware decision. In other words, this is not dependent from software semantics (e.g.
// if some address range is assigned to a different software component like a bootloader).
static void * const RAM_SEGMENT_START = (void*)0x20000000;
static void * const RAM_SEGMENT_END   = (void*)0x20040000;

//**************************************************************************************************

#if GPI_STDOUT_INTERRUPT_ENABLED

	ASSERT_CT_STATIC(GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS <= 32, GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS_must_not_exceed_32);
		// value > 32 would require larger tx_buffer_free_map

	ASSERT_CT_STATIC(GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE < 256, GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE_must_not_exceed_255);
		// tx_buffer_len is uint8_t
		
	static char				tx_buffer[GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS][GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE];
	static uint8_t			tx_buffer_len[NUM_ELEMENTS(tx_buffer)];
	static uint32_t			tx_buffer_free_map	= -1u >> (32 - NUM_ELEMENTS(tx_buffer));
	
	static uint8_t			tx_chain[1u << (MSB(NUM_ELEMENTS(tx_buffer) - 1) + 1)];
	static uint_fast32_t	tx_chain_num_written = 0;
	static uint_fast32_t	tx_chain_num_read = 0;
	
	static uint_fast8_t		is_tx_running = 0;

	ASSERT_CT_STATIC(IS_POWER_OF_2(NUM_ELEMENTS(tx_chain)));

#endif

//**************************************************************************************************

#if GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2)

	// stdin, stdout, stderr file descriptors for UART stdio
	static FILE stdin_file  = { 0 };
	static FILE stdout_file = { 0 };
	static FILE stderr_file = { 0 };

#endif

//**************************************************************************************************
//***** Global Variables ***************************************************************************

#if GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2)

	// stdin, stdout, stderr file descriptors for UART stdio
	FILE *stdin  = &stdin_file;
	FILE *stdout = &stdout_file;
	FILE *stderr = &stderr_file;

#endif

//**************************************************************************************************
//***** Local Functions ****************************************************************************

#if !GPI_STDOUT_INTERRUPT_ENABLED

// core output function
// NOTE: inline to enable optimized usage inside the adapter functions (see below)
static inline void gpi_uart_write(const void *s, unsigned int len)
{
	// test if data is in RAM (because EasyDMA cannot access flash)
	#ifndef NDEBUG
		ASSERT(s >= (void*)RAM_SEGMENT_START && s < (void*)RAM_SEGMENT_END);
	#endif

	if (len < 1)
		return;

	// flush registers before activating DMA
	// this could be relevant when function gets inlined and highly optimized
	REORDER_BARRIER();

	// setup DMA
	NRF_UARTE0->TXD.PTR = (uintptr_t)s;
	NRF_UARTE0->TXD.MAXCNT = len;

	// flush CPU pipeline's write buffer
	// NOTE: This is not really necessary here because it has been done implicitly for sure
	// due to the short pipeline length of the Cortex-M4. We do it anyway to keep the code clean.
	__DMB();

	// wait until previous transmission has finished
	// NOTE: TXSTARTED is used as a marker for open transmissions
	if (NRF_UARTE0->EVENTS_TXSTARTED)
	{
		NRF_UARTE0->EVENTS_TXSTARTED = 0;
		while (!(NRF_UARTE0->EVENTS_ENDTX));
	}

	// start TX
	NRF_UARTE0->EVENTS_ENDTX = 0;
	NRF_UARTE0->TASKS_STARTTX = 1;

	// wait until TX has been started and TXD.PTR and TXD.MAXCNT can be accessed again
	// NOTE: TXD.PTR and TXD.MAXCNT are double-buffered (see spec. 4413_417 v1.2 page 511)
	while (!(NRF_UARTE0->EVENTS_TXSTARTED));
}

#endif

//**************************************************************************************************

// core input function
// NOTE: inline to enable optimized usage inside the adapter functions (see below)
static inline unsigned int gpi_uart_read(void *s, unsigned int max_len)
{
	if (max_len < 1)
		return max_len;

	if (max_len > 0xffff)
		max_len = 0xffff;
		
	NRF_UARTE0->RXD.PTR = (uintptr_t)s;
	NRF_UARTE0->RXD.MAXCNT = max_len;

	NRF_UARTE0->EVENTS_ENDRX = 0;
	NRF_UARTE0->EVENTS_ERROR = 0;
	
	NRF_UARTE0->TASKS_STARTRX = 1;
	
	while (!(NRF_UARTE0->EVENTS_ENDRX));

	return (NRF_UARTE0->EVENTS_ERROR) ? 0 : max_len;
}

//**************************************************************************************************

#if GPI_STDOUT_INTERRUPT_ENABLED

// UART transmit ISR
void UARTE0_UART0_IRQHandler()
{
	// ATTENTION: We assume that ISR cannot be interrupted by the write routine.

	register uint_fast32_t	nr = tx_chain_num_read;
	register int			i;

	// acknowledge IRQ
	NRF_UARTE0->EVENTS_ENDTX = 0;

	// advance tx_chain_num_read, stop if done
	if (++tx_chain_num_read == tx_chain_num_written)
		is_tx_running = 0;

	// otherwise transmit next data block
	else
	{
		i = tx_chain[tx_chain_num_read & TX_CHAIN_INDEX_MASK];
		NRF_UARTE0->TXD.PTR = (uintptr_t)&tx_buffer[i][0];
		NRF_UARTE0->TXD.MAXCNT = tx_buffer_len[i];
		NRF_UARTE0->TASKS_STARTTX = 1;
	}

	// release completed transmit buffer slot
	i = tx_chain[nr & TX_CHAIN_INDEX_MASK];
	tx_buffer_free_map |= 1u << i;
}

#endif

//**************************************************************************************************
//***** Global Functions ***************************************************************************

#if GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2)

// internal stdio functions
// provide very basic support for stdin, stdout, and stderr over UART.
// for details see <https://wiki.segger.com/Embedded_Studio_Library_IO>.
// NOTE: functions are declared as weak to allow the application to provide different
// implementations without causing conflicts

int __attribute__((weak)) __SEGGER_RTL_X_file_stat(FILE *stream)
{
	// stdin, stdout, and stderr are assumed to be valid
	if (stream == stdin || stream == stdout || stream == stderr)
		return 0;

	else return EOF;
}

int __attribute__((weak)) __SEGGER_RTL_X_file_bufsize(FILE *stream)
{
	// avoid "variable unused" warning
	(void)stream;

	return 1;
}

int __attribute__((weak)) __SEGGER_RTL_X_file_unget(FILE *stream, int c)
{
	// avoid "variable unused" warning
	(void)stream;

	// do not provide unget functionality
	// this could be changed if required,
	// see <https://wiki.segger.com/Embedded_Studio_Library_IO> for an example
	return EOF;
}
	
#endif	// GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER2)

//**************************************************************************************************

// putchar() / puts()
// ATTENTION: the simple implementations are not reentrant

#if GPI_ARCH_IS_OS(NONE)

#if GPI_ARCH_IS_CRT(SEGGER2)

// Starting with SES 5.10 SEGGER included two runtime libaries: The legacy "Embedded Studio
// Runtime Library" (GPI_ARCH_CRT_SEGGER1) and the "SEGGER Runtime Library" (GPI_ARCH_CRT_SEGGER2).
// With SES 6.00 the legacy library has been removed (so SEGGER2 is the only remaining option),
// and in some version <= 6.34 the Library I/O option "STD" has also been removed. To implement 
// UART-based stdio, one now has to select Library I/O option "None" and provide a set of
// __SEGGER_RTL_X_file_... functions (done here). The details can be found in
// <https://wiki.segger.com/Embedded_Studio_Library_IO>.
// NOTE: In SES 5.xx the documentation of the RTL was inconsistent, for instance it stated that
// the function to provide for output is __SEGGER_RTL_stdout_putc(), which was not present and
// may refer to an older version of the library.

// NOTE: function is declared as weak to allow the application to provide a different
// implementation without causing conflicts
int __attribute__((weak)) __SEGGER_RTL_X_file_write(FILE *stream, const char *s, unsigned len)
{
	if ((stream != stdout) && (stream != stderr))
		return EOF;
	
// advanced interrupt driven implementation that enables higher level of async I/O
#if GPI_STDOUT_INTERRUPT_ENABLED

	const char* const	end = &s[len];
	register int		ie;
	register int		i;

	// process input data
	while (s != end)
	{
		// NOTE: gpi_int_(un)lock() implicitly functions as a REORDER_BARRIER(),
		// so we can save additional explicit barriers in the following
		
		// wait for a free slot in the transmit buffer pool
		// ATTENTION: If is_tx_running then some slot will become free in the near future in case 
		// buffer is full. If !is_tx_running then number of used slots <= max. number of nested calls.
		// Hence, NUM_ELEMENTS(tx_buffer) should be configured to be >= max. number of nested calls.
		// Otherwise this waiting loop can cause a deadlock.
		while (!tx_buffer_free_map)
			REORDER_BARRIER();

		// allocate slot in transmit buffer pool
		{
			ie = gpi_int_lock();

			i = gpi_get_lsb(tx_buffer_free_map);

			// The config settings should ensure that NUM_ELEMENTS(tx_buffer) >= max. number of 
			// nested calls (see above). To be on the safe side, we catch exceedings with an
			// infinite loop trap. We do not use assert() because assert() probably would try
			// to print something out, but the print stack is the origin of the problem.
			#ifndef NDEBUG
				while (!((i >= 0) || is_tx_running));
			#endif
		
			if (i >= 0)
				tx_buffer_free_map &= ~(1u << i);
		
			gpi_int_unlock(ie);
		}

		if (i < 0)
			continue;

		// copy data to buffer slot
		// NOTE: as a side effect this ensures that data is placed in RAM, which is important for EasyDMA
		size_t n = sizeof(tx_buffer[0]);
		for (char *d = &tx_buffer[i][0]; (s != end) && (n > 0); n--)
		{
			if ('\n' == *s)
			{
				if (n < 2)
					break;
					
				*d++ = '\r';
				n--;
			}
			
			*d++ = *s++;
		}
		tx_buffer_len[i] = sizeof(tx_buffer[0]) - n;

		// push buffer slot index to transmit chain (= Tx FIFO)
		{
			ie = gpi_int_lock();
		
			tx_chain[tx_chain_num_written++ & TX_CHAIN_INDEX_MASK] = i;
			
			// do not leave int lock -> if thread gets interrupted for a long time,
			// transmission could finish inbetween (we would have to check tx_chain_num_read
			// vs. tx_chain_num_written again, so savings in locked time would be marginal)
			
			// start transmitter if it is idle at present
			// (otherwise transmission continues automatically, handled by the ISR)
			if (!is_tx_running)
			{
				i = tx_chain[tx_chain_num_read & TX_CHAIN_INDEX_MASK];
				NRF_UARTE0->TXD.PTR = (uintptr_t)&tx_buffer[i][0];
				NRF_UARTE0->TXD.MAXCNT = tx_buffer_len[i];
				NRF_UARTE0->TASKS_STARTTX = 1;
				is_tx_running = 1;
			}
		
			gpi_int_unlock(ie);
		}
	}

#else	// GPI_STDOUT_INTERRUPT_ENABLED

	static char			crlf[] = "\r\n";	// do not use const char, must be in RAM for sure
	const char* const	end = &s[len];
	const char			*r;
	unsigned int		l;

	// TXSTARTED is used as a marker for open transmissions in gpi_uart_write()
	NRF_UARTE0->EVENTS_TXSTARTED = 0;

	// if data is not in RAM, we must copy it because EasyDMA has no access to flash area
	if (s < (char*)RAM_SEGMENT_START || s >= (char*)RAM_SEGMENT_END)
	{
		char c;
		for (l = len; l-- > 0;)
		{
			c = *s++;
			if (c == '\n')
				gpi_uart_write(&crlf, 2);
			else gpi_uart_write(&c, 1);
		}
	}

	else
	{
		// split s into segments separated by \n
		for (r = s; r != end;)
		{
			for (; r != end; r++)
			{
				if (*r == '\n')
					break;
			}

			// write current segment
			l = (uintptr_t)r - (uintptr_t)s;
			if (l > 0)
				gpi_uart_write(s, l);

			// write newline sequence
			if (r != end)
			{
				gpi_uart_write(&crlf, 2);
				r++;
			}

			// next segment
			s = r;
		}
	}

	// wait until transmission has finished (so data buffer can be released for sure)
	// NOTE: TXSTARTED is used as a marker for open transmissions
	if (NRF_UARTE0->EVENTS_TXSTARTED)
		while (!(NRF_UARTE0->EVENTS_ENDTX));

#endif	// GPI_STDOUT_INTERRUPT_ENABLED

	// return len if successful
	return len;
}

#elif GPI_ARCH_IS_CRT(SEGGER1)

// The (old) RTL versions call __putchar(), with an additional proprietary parameter.
// NOTE: function is declared as weak to allow the application to provide a different
// implementation (e.g. from Segger RTT) without causing conflicts
// ATTENTION: thumb_crt0.s contains a weak definition of __putchar redirecting to debug_putchar.
// Hence, to ensure that putchar redirects here it is not safe to declare __putchar alone
// (if the definition shall be weak), as this would not safely overwrite the definition from
// thumb_crt0.s. Instead we provide (non-weak) debug_putchar() (to catch thumb_crt0.s) plus
// weak __putchar(). This is somewhat dirty as debug_putchar() is meant to be the low-level 
// debug output routine and should not be overwritten in general.

int __putchar(int c, __printf_tag_ptr file) __attribute__((weak, alias("debug_putchar")));

int debug_putchar(int c, __printf_tag_ptr file)
{
	uint8_t			buf[2];
	uint_fast8_t	len = 0;

	// avoid "variable unused" warning
	(void)file;

	// copy data to RAM buffer, convert "\n" to "\r\n"
	if (c == '\n')
		buf[len++] = '\r';
	buf[len++] = c;

	// TXSTARTED is used as a marker for open transmissions in gpi_uart_write()
	NRF_UARTE0->EVENTS_TXSTARTED = 0;

	gpi_uart_write(buf, len);

	// wait until transmission has finished
	while (!(NRF_UARTE0->EVENTS_ENDTX));

	return c;
}

#endif	// GPI_ARCH_IS_CRT(...)

#endif	// GPI_ARCH_IS_OS(NONE)

//**************************************************************************************************
// getchar()
// ATTENTION: implementations are very simple and not reentrant

#if GPI_ARCH_IS_OS(NONE)

#if GPI_ARCH_IS_CRT(SEGGER2)

// NOTE: function is declared as weak to allow the application to provide a different
// implementation without causing conflicts
int __attribute__((weak)) __SEGGER_RTL_X_file_read(FILE *stream, char *s, unsigned len)
{
	if (stdin != stream)
		return EOF;
	
#if 1
	len = gpi_uart_read(s, len);
#else
	unsigned int l = len;
	while (l)
	{
		unsigned int l2 = gpi_uart_read(s, l);
		s += l2;
		l -= l2;
	}
#endif

	// return len if successful
	return len;
}

#else	// GPI_ARCH_IS_CRT(SEGGER2)

// NOTE: function is declared as weak to allow the application to provide a different
// implementation without causing conflicts
int __attribute__((weak)) getchar()
{
	uint8_t	c;

	while (!gpi_uart_read(&c, 1));
	
	return c;
}

#endif	// GPI_ARCH_IS_CRT(...)

void gpi_stdin_flush()
{
	uint8_t	t[8];

	NRF_UARTE0->RXD.PTR = (uintptr_t)&t;
	NRF_UARTE0->RXD.MAXCNT = 8;

	NRF_UARTE0->EVENTS_ENDRX = 0;
	NRF_UARTE0->TASKS_FLUSHRX = 1;
	while (!(NRF_UARTE0->EVENTS_ENDRX));
}

// getsn()
#include "gpi/stdio_getsn.c"

#endif	// GPI_ARCH_IS_OS(NONE)

//**************************************************************************************************
//**************************************************************************************************
