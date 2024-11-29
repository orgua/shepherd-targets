/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2024, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/nrf528xx/platform.h
 *
 *	@brief					common nRF528xx-specific platform interface functions
 *
 *	@version				$Id: c3d032abce69c09c01d50337f356ee05b96ac8c0 $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF528xx_PLATFORM_H__
#define __GPI_ARM_nRF528xx_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>
#include <string.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

// NOTE: Regarding default value warnings, we do not trigger #warning directly because this would
// issue the warning with every file including platform.h, which unnecessarily clutters the output.
// Instead, we store each warning message in a macro and print it during compilation of a related
// implementation file, e.g. platform.c.

// stdio UART baudrate
// ATTENTION: Without hardware flow control, baudrates >= 115200 can cause data losses at PCA10056's
// interface MCU under full UART load (e.g. printf() loop). Hence, we strongly recommend to enable
// hardware flow control if high baudrates are used (see GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE).
// (Without giving any guarantees, it seems that baudrates <= 57600 are safe without flow control.)
#ifndef GPI_STDOUT_UART_BAUDRATE
	#define GPI_STDOUT_UART_BAUDRATE					115200
	#define _GPI_STDOUT_UART_BAUDRATE_DEFAULT_WARNING	\
		"GPI_STDOUT_UART_BAUDRATE undefined, default = 115200"
#endif

// stdout UART flow control mode:
// 0 = disabled (no flow control)
// 1 = CTS with pull-down (hardware flow control, Tx unlocked while CTS not driven by receiver)
// 3 = CTS with pull-up (hardware flow control, Tx locked while CTS not driven by receiver)
#ifndef GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE
	#define GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE	0
#endif

// decide wether stdout/stderr functionality uses interrupt driven async I/O
#ifndef GPI_STDOUT_INTERRUPT_ENABLED
	#define GPI_STDOUT_INTERRUPT_ENABLED	0
#endif

// settings for interrupt driven stdout/stderr
#if GPI_STDOUT_INTERRUPT_ENABLED

	// interrupt priority level
	// must be at least as high as highest priority ISR that writes to stdout/stderr
	#ifndef GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY
		#define GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY	1
		#define _GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY_DEFAULT_WARNING	\
			"GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY undefined, default = 1"
	#endif

	// number of slots in the transmit buffer pool
	// must be >= possible number of nested print calls
	// higher number increases decoupling capabilities
	// choosing a power of 2 is most efficient
	#ifndef GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS
		#define GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS		16
		#define _GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS_DEFAULT_WARNING	\
			"GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS undefined, default = 16"
	#endif

	// size of single transmit buffer slot
	// higher number increases efficiency for print functions that are not split into putchar() calls
	// (typically (f)puts() is good, with (f)printf() it depends)
	#ifndef GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE
		#define GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE		4
		#define _GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE_DEFAULT_WARNING	\
			"GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE undefined, default = 4"
	#endif
	
#endif

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************



//**************************************************************************************************
//***** Global Variables ***************************************************************************

// mark that CPU comes from power-down
// this flag can be evaluated by the application
// NOTE: to be meaningful, the first ISR taken after power-up should clear it
extern uint_fast8_t		gpi_wakeup_event;

//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
	extern "C" {
#endif

// UICR access functions
// UICR = User Information Configuration Registers, see spec. for details
// ATTENTION: Writing to UICR or flash requires NVMC->CONFIG.WEN to be set which in turn
// invalidates the instruction cache (permanently). Besides that, UICR updates take effect
// only after reset (spec. 4413_417 v1.0 4.3.3 page 24). Therefore it is highly recommended
// to do a soft reset (e.g., by calling NVIC_SystemReset()) after updating flash or UICR.
static void		gpi_nrf_uicr_read(void *dest, uintptr_t src, size_t size);
void			gpi_nrf_uicr_erase();
void			gpi_nrf_uicr_write(uintptr_t dest, const void *src, size_t size);

// standard C library does not provide getsn(), so we do it
// NOTE: gets() has been removed in C11. The official recommendation is to use fgets() instead.
// But: The latter does not remove the trailing newline, so take care with that.
#if GPI_ARCH_IS_OS(NONE)
	void		gpi_stdin_flush();
	char* 		getsn(char* s, size_t size);
#endif

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

static inline void gpi_nrf_uicr_read(void *dest, uintptr_t src, size_t size)
{
	src = MAX(src, sizeof(NRF_UICR->CUSTOMER));
	size = MAX(size, sizeof(NRF_UICR->CUSTOMER) - src);

	// Starting with GCC 11, the compiler can generate warnings when calls to string manipulation
	// functions such as memcpy() or strcpy() are determined to overflow the destination buffer
	// or to read past the end of the source string/buffer (see -Wstringop-...). For this purpose,
	// the compiler has to determine the corresponding buffer sizes, and it seems that there are
	// some open issues related to this. For example, with GCC 11.2 (SEGGER Embedded Studio 6.34)
	// the memcpy() call below throws the warning
	// "warning: ‘memcpy’ reading 4 bytes from a region of size 0 [-Wstringop-overread]" because
	// the compiler is unable to determine the real size of the source buffer. Unfortunately,
	// the same GCC version has issues regarding the temporary deactivation of this warning. To
	// work around this, we catch GCC version 11 explicitly and give higher versions another try.

	#if __GNUC__ > 11
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wstringop-overread"
		memcpy(dest, (uint8_t*)&(NRF_UICR->CUSTOMER) + src, size);
		#pragma GCC diagnostic pop
	#elif __GNUC__ == 11
		uint8_t *d = dest;
		uint8_t *s = (uint8_t*)&(NRF_UICR->CUSTOMER) + src;
		while (size--)
			*d++ = *s++;
	#else
		memcpy(dest, (uint8_t*)&(NRF_UICR->CUSTOMER) + src, size);
	#endif
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF528xx_PLATFORM_H__
