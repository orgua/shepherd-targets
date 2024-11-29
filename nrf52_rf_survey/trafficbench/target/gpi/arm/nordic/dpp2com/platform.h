/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2019, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/dpp2com/platform.h
 *
 *	@brief					platform interface functions, specific for DPP2 Com board based on nRF52840
 *
 *	@version				$Id: 34ee348a1963feb4d7f0b188a5c9de69873f744a $
 *	@date					TODO
 *
 *	@author					Fabian Mager
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF_DPP2_COM_PLATFORM_H__
#define __GPI_ARM_nRF_DPP2_COM_PLATFORM_H__

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

// ATTENTION: x is evaluated twice, so take care with side effects
#define GPI_LED(x)		(((uint_fast8_t)(x) - 1) < 1 ? (BV(25) << ((uint_fast8_t)(x) - 1)) : 0)

#define GPI_LED_NONE	0
#define GPI_LED_1		GPI_LED(1)

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// bitfield macros for CMSIS register definitions

#define BV_BY_NAME(field, value)	((field ## _ ## value << field ## _Pos) & field ## _Msk)
#define BV_BY_VALUE(field, value)	(((value) << field ## _Pos) & field ## _Msk)
//#define BV_BY_NAME(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)
//#define BV_BY_VALUE(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)

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

static ALWAYS_INLINE void gpi_led_on(int mask)
{
	if (mask)
		NRF_P0->OUTCLR = mask;
}

static ALWAYS_INLINE void gpi_led_off(int mask)
{
	if (mask)
		NRF_P0->OUTSET = mask;
}

static ALWAYS_INLINE void gpi_led_toggle(int mask)
{
	if (mask)
		NRF_P0->OUT ^= mask;
}

//**************************************************************************************************

static ALWAYS_INLINE uint_fast8_t gpi_button_read(int id)
{
	// No buttons on this board.
}

//**************************************************************************************************

static inline void gpi_nrf_uicr_read(void *dest, uintptr_t src, size_t size)
{
	src = MAX(src, sizeof(NRF_UICR->CUSTOMER));
	size = MAX(size, sizeof(NRF_UICR->CUSTOMER) - src);

	memcpy(dest, (uint8_t*)&(NRF_UICR->CUSTOMER) + src, size);
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF_DPP2_COM_PLATFORM_H__
