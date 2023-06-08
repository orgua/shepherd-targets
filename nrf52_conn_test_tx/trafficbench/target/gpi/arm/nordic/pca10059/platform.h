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
 *	@file					gpi/arm/nordic/pca10059/platform.h
 *
 *	@brief					platform interface functions, specific for Nordic nRF52840 USB Dongle
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

#ifndef __GPI_ARM_nRF_PCA10059_PLATFORM_H__
#define __GPI_ARM_nRF_PCA10059_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>
#include <string.h>
#include <stdio.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

// NOTE: Regarding default value warnings, we do not trigger #warning directly because this would
// issue the warning with every file including platform.h, which unnecessarily clutters the output.
// Instead, we store each warning message in a macro and print it during compilation of a related
// implementation file, e.g. platform.c.

// stdio UART baudrate
#ifndef GPI_STDOUT_UART_BAUDRATE
	#define GPI_STDOUT_UART_BAUDRATE					115200
	#define _GPI_STDOUT_UART_BAUDRATE_DEFAULT_WARNING	\
		"GPI_STDOUT_UART_BAUDRATE undefined, default = 115200"
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

#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)

	#define _GPI_ARM_nRF_PCA10059_UART_TXD_PORT		1
	#define _GPI_ARM_nRF_PCA10059_UART_TXD_PIN		10
	#define _GPI_ARM_nRF_PCA10059_UART_RXD_PORT		0
	#define _GPI_ARM_nRF_PCA10059_UART_RXD_PIN		24
	// NOTE: According to nRF52840 PS v1.1, pin P1.10 is only recommended for low frequency I/O.

	// On FlockLab, LEDs are output pins with GPIO tracing capabilities.
	// Hence, we provide all such output pins as LEDs for simplicity.
	#define GPI_LED_NONE		0
	#define GPI_LED_1			BV(13)	// LED1
	#define GPI_LED_2			BV(15)	// LED2
	#define GPI_LED_3			BV(17)	// LED3
	#define GPI_LED_INT1		BV(20)	// INT1
	#define GPI_LED_INT2		BV(22)	// INT2

	// following names are deprecated, use GPI_LED_INTx instead
	static const int __attribute__((deprecated("use GPI_LED_INT1 instead"))) GPI_LED_4 = GPI_LED_INT1;
	static const int __attribute__((deprecated("use GPI_LED_INT2 instead"))) GPI_LED_5 = GPI_LED_INT2;

	// On FlockLab, buttons are input pins with GPIO actuation capabilities.
	// Hence, we provide all such input pins as buttons for simplicity.
	#define GPI_BUTTON_SIG1		BV(31)	// SIG1
	#define GPI_BUTTON_SIG2		BV(29)	// SIG2
	
#else

	#define GPI_LED_NONE		0
	#define GPI_LED_1			BV(6)		// LED1
	#define GPI_LED_2_R			BV(8)		// LED2 red
	#define GPI_LED_2_B			BV(12)		// LED2 blue
	#define GPI_LED_2_G			BV(16+9))	// LED2 green at P1.09

	// following names are deprecated, use GPI_LED_2 instead
	static const int __attribute__((deprecated("use GPI_LED_2_R instead"))) GPI_LED_2 = GPI_LED_2_R;
	static const int __attribute__((deprecated("use GPI_LED_2_B instead"))) GPI_LED_3 = GPI_LED_2_B;

	#define GPI_BUTTON_1		BV(6)		// SW1
	
#endif

// for details see comments in gpi/platform.h
static ALWAYS_INLINE int gpi_led_index_to_mask(int i)
{
	// NOTE: with optimization enabled, the switch block gets replaced by
	// * a constant if i is constant (due to constant propagation)
	// * a lookup table with preceding 1 <= i <= i_max test, or
	// * a fast conditional execution block (on ARM)
	switch (i)
	{
#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)
		case 1:		return GPI_LED_1;
		case 2:		return GPI_LED_2;
		case 3:		return GPI_LED_3;
		case 4:		return GPI_LED_INT1;
		case 5:		return GPI_LED_INT2;
#else
		case 1:		return GPI_LED_1;
		case 2:		return GPI_LED_2_R;
		case 3:		return GPI_LED_2_B;
		case 4:		return GPI_LED_2_G;
#endif
		default:	return 0;
	}
}

// for details see comments in gpi/platform.h
static ALWAYS_INLINE int gpi_button_index_to_mask(int i)
{
	// NOTE: with optimization enabled, the switch block gets replaced by
	// * a constant if i is constant (due to constant propagation)
	// * a lookup table with preceding 1 <= i <= i_max test, or
	// * a fast conditional execution block (on ARM)
	switch (i)
	{
#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)
		case 1:		return GPI_BUTTON_SIG1;
		case 2:		return GPI_BUTTON_SIG2;
#else
		case 1:		return GPI_BUTTON_1;
#endif
		default:	return 0;
	}
}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// bitfield macros for CMSIS register definitions

#define BV_BY_NAME(field, value)	((field ## _ ## value << field ## _Pos) & field ## _Msk)
#define BV_BY_VALUE(field, value)	(((value) << field ## _Pos) & field ## _Msk)
//#define BV_BY_NAME(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)
//#define BV_BY_VALUE(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)

// with intermediate macro expansion
#define BV_BY_NAME_PREEXP(field, value)		BV_BY_NAME(field, value)
#define BV_BY_VALUE_PREEXP(field, value)	BV_BY_VALUE(field, value)

#define BV_TEST_BY_NAME(reg, field, value)	(BV_BY_NAME(field, value) == ((reg) & field ## _Msk))
#define BV_TEST_BY_VALUE(reg, field, value)	(BV_BY_VALUE(field, value) == ((reg) & field ## _Msk))

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
#if GPI_ARCH_IS_OS(NONE)
	void		gpi_stdin_flush();
	char* 		getsn(char* s, size_t size);
#endif

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)

	static ALWAYS_INLINE void gpi_led_on(int mask)
	{
		if (mask)
			NRF_P0->OUTSET = mask;
	}

	static ALWAYS_INLINE void gpi_led_off(int mask)
	{
		if (mask)
			NRF_P0->OUTCLR = mask;
	}
		
	static ALWAYS_INLINE void gpi_led_toggle(int mask)
	{
		if (mask)
			NRF_P0->OUT ^= mask;
	}

#else

	static ALWAYS_INLINE void gpi_led_on(int mask)
	{
		uint_fast16_t	mask0 = mask;
		uint_fast16_t	mask1 = mask >> 16;
		
		if (mask0)
			NRF_P0->OUTCLR = mask0;
			
		if (mask1)
			NRF_P1->OUTCLR = mask1;
	}

	static ALWAYS_INLINE void gpi_led_off(int mask)
	{
		uint_fast16_t	mask0 = mask;
		uint_fast16_t	mask1 = mask >> 16;
		
		if (mask0)
			NRF_P0->OUTSET = mask0;
			
		if (mask1)
			NRF_P1->OUTSET = mask1;
	}
		
	static ALWAYS_INLINE void gpi_led_toggle(int mask)
	{
		uint_fast16_t	mask0 = mask;
		uint_fast16_t	mask1 = mask >> 16;
		
		if (mask0)
			NRF_P0->OUT ^= mask0;
			
		if (mask1)
			NRF_P1->OUT ^= mask1;
	}
		
#endif

//**************************************************************************************************

static ALWAYS_INLINE uint_fast8_t gpi_button_read(int mask)
{
	// NOTE: we assume that mask is valid (= a non-zero combination of GPI_BUTTON_...)
	
	#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)
		return !!(NRF_P0->IN & mask);
	#else
		return !(NRF_P1->IN & mask);
	#endif
}

//**************************************************************************************************

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

#endif // __GPI_ARM_nRF_PCA10059_PLATFORM_H__
