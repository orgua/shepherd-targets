/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2021 - 2024, Networked Embedded Systems Lab, TU Dresden
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
 *	@version				$Id: 4bd65d5de44e27ef16acb6e4cf67772492158cb8 $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *	@author					Fabian Mager
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

#include "../nrf528xx/platform.h" // nRF528xx common functionality

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)

  // On FlockLab, LEDs are output pins with GPIO tracing capabilities.
  // Hence, we provide all such output pins as LEDs for simplicity.
  #define GPI_LED_NONE 0
  #define GPI_LED_1    BV(13) // LED1
  #define GPI_LED_2    BV(15) // LED2
  #define GPI_LED_3    BV(17) // LED3
  #define GPI_LED_INT1 BV(20) // INT1
  #define GPI_LED_INT2 BV(22) // INT2

// following names are deprecated, use GPI_LED_INTx instead
static const int __attribute__((deprecated("use GPI_LED_INT1 instead"))) GPI_LED_4 = GPI_LED_INT1;
static const int __attribute__((deprecated("use GPI_LED_INT2 instead"))) GPI_LED_5 = GPI_LED_INT2;

  // On FlockLab, buttons are input pins with GPIO actuation capabilities.
  // Hence, we provide all such input pins as buttons for simplicity.
  #define GPI_BUTTON_SIG1 BV(31) // SIG1
  #define GPI_BUTTON_SIG2 BV(29) // SIG2

#else

  #define GPI_LED_NONE 0
  #define GPI_LED_1    BV(6)      // LED1
  #define GPI_LED_2_R  BV(8)      // LED2 red
  #define GPI_LED_2_B  BV(12)     // LED2 blue
  #define GPI_LED_2_G  BV(16 + 9) // LED2 green at P1.09

// following names are deprecated, use GPI_LED_2 instead
static const int __attribute__((deprecated("use GPI_LED_2_R instead"))) GPI_LED_2 = GPI_LED_2_R;
static const int __attribute__((deprecated("use GPI_LED_2_B instead"))) GPI_LED_3 = GPI_LED_2_B;

  #define GPI_BUTTON_1 BV(6) // SW1

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
        case 1: return GPI_LED_1;
        case 2: return GPI_LED_2;
        case 3: return GPI_LED_3;
        case 4: return GPI_LED_INT1;
        case 5: return GPI_LED_INT2;
#else
        case 1: return GPI_LED_1;
        case 2: return GPI_LED_2_R;
        case 3: return GPI_LED_2_B;
        case 4: return GPI_LED_2_G;
#endif
        default: return 0;
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
        case 1: return GPI_BUTTON_SIG1;
        case 2: return GPI_BUTTON_SIG2;
#else
        case 1: return GPI_BUTTON_1;
#endif
        default: return 0;
    }
}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// UART pins
#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)
  #define _GPI_ARM_nRF_UART_TXD_PORT 1
  #define _GPI_ARM_nRF_UART_TXD_PIN  10
  #define _GPI_ARM_nRF_UART_RXD_PORT 0
  #define _GPI_ARM_nRF_UART_RXD_PIN  24
    // NOTE: According to nRF52840 PS v1.1, pin P1.10 is only recommended for low frequency I/O.
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

#if GPI_ARCH_IS_BOARD(nRF_PCA10059_FLOCKLAB)

static ALWAYS_INLINE void gpi_led_on(int mask)
{
    if (mask) NRF_P0->OUTSET = mask;
}

static ALWAYS_INLINE void gpi_led_off(int mask)
{
    if (mask) NRF_P0->OUTCLR = mask;
}

static ALWAYS_INLINE void gpi_led_toggle(int mask)
{
    if (mask) NRF_P0->OUT ^= mask;
}

#else

static ALWAYS_INLINE void gpi_led_on(int mask)
{
    uint_fast16_t mask0 = mask;
    uint_fast16_t mask1 = mask >> 16;

    if (mask0) NRF_P0->OUTCLR = mask0;

    if (mask1) NRF_P1->OUTCLR = mask1;
}

static ALWAYS_INLINE void gpi_led_off(int mask)
{
    uint_fast16_t mask0 = mask;
    uint_fast16_t mask1 = mask >> 16;

    if (mask0) NRF_P0->OUTSET = mask0;

    if (mask1) NRF_P1->OUTSET = mask1;
}

static ALWAYS_INLINE void gpi_led_toggle(int mask)
{
    uint_fast16_t mask0 = mask;
    uint_fast16_t mask1 = mask >> 16;

    if (mask0) NRF_P0->OUT ^= mask0;

    if (mask1) NRF_P1->OUT ^= mask1;
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
//**************************************************************************************************

#endif // __GPI_ARM_nRF_PCA10059_PLATFORM_H__
