/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2019 - 2024, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/pca10056/platform.h
 *
 *	@brief					platform interface functions, specific for Nordic nRF52840 DK
 *
 *	@version				$Id: 298696a9cb3c4248746a617c920bfb2ed852e358 $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF_PCA10056_PLATFORM_H__
#define __GPI_ARM_nRF_PCA10056_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "../nrf528xx/platform.h" // nRF528xx common functionality

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

#define GPI_LED_NONE 0
#define GPI_LED_1    BV(13)
#define GPI_LED_2    BV(14)
#define GPI_LED_3    BV(15)
#define GPI_LED_4    BV(16)

#if 1 // DEFAULT wiring
  #define GPI_BUTTON_1 BV(11)
  #define GPI_BUTTON_2 BV(12)
#else // OPTIONAL wiring
  #define GPI_BUTTON_1 BV(31) | BV(7)
  #define GPI_BUTTON_2 BV(31) | BV(8)
#endif
#define GPI_BUTTON_3 BV(24)
#define GPI_BUTTON_4 BV(25)

// for details see comments in gpi/platform.h
static ALWAYS_INLINE int gpi_led_index_to_mask(int i)
{
    i -= 1;
    return (i < 4) ? BV(13) << i : 0;
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
        case 1: return GPI_BUTTON_1;
        case 2: return GPI_BUTTON_2;
        case 3: return GPI_BUTTON_3;
        case 4: return GPI_BUTTON_4;
        default: return 0;
    }
}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// UART pins
#define _GPI_ARM_nRF_UART_TXD_PORT 0
#define _GPI_ARM_nRF_UART_TXD_PIN  6
#define _GPI_ARM_nRF_UART_RXD_PORT 0
#define _GPI_ARM_nRF_UART_RXD_PIN  8
#define _GPI_ARM_nRF_UART_RTS_PORT 0
#define _GPI_ARM_nRF_UART_RTS_PIN  5
#define _GPI_ARM_nRF_UART_CTS_PORT 0
#if 1 // CTS = CTS_DEFAULT
  #define _GPI_ARM_nRF_UART_CTS_PIN 7
#else // CTS = CTS_OPTIONAL
  #define _GPI_ARM_nRF_UART_CTS_PIN 4
#endif

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************


//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

static ALWAYS_INLINE void gpi_led_on(int mask)
{
    if (mask) NRF_P0->OUTCLR = mask;
}

static ALWAYS_INLINE void gpi_led_off(int mask)
{
    if (mask) NRF_P0->OUTSET = mask;
}

static ALWAYS_INLINE void gpi_led_toggle(int mask)
{
    if (mask) NRF_P0->OUT ^= mask;
}

//**************************************************************************************************

static ALWAYS_INLINE uint_fast8_t gpi_button_read(int mask)
{
    // ATTENTION: we do not support multiple buttons masks
    // (will lead to invalid results if buttons from P0 and P1 are mixed)

    if (mask & BV(31)) return !(NRF_P1->IN & (mask ^ BV(31)));
    else return !(NRF_P0->IN & mask);
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF_PCA10056_PLATFORM_H__
