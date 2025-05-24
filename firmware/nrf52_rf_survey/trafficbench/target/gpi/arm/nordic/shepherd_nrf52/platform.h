/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2025, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/shepherd_nrf52/platform.h
 *
 *	@brief					platform interface functions, specific for nRF52 Shepherd target
 *
 *	@version				$Id: b94d7af217a60f4ee3622f58dfb96cc9cb13d85c $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF_SHEPHERD_NRF52_PLATFORM_H__
#define __GPI_ARM_nRF_SHEPHERD_NRF52_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "../nrf528xx/platform.h" // nRF528xx common functionality

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

#define GPI_LED_NONE       0
#define GPI_LED_0          BV(24) // P1.13 (+11)
#define GPI_LED_2P         BV(3)  // P0.03

// On Shepherd targets, GPIOs are typically used as output pins (with GPIO tracing capabilities
// on the base board). Hence, we provide all such pins as LEDs for simplicity.
#define GPI_LED_GPIO0      BV(23) // P0.21 (+2)
#define GPI_LED_GPIO1      BV(8)  // P0.08
#define GPI_LED_GPIO2      BV(4)  // P0.04
#define GPI_LED_GPIO3      BV(5)  // P0.05
#define GPI_LED_GPIO4      BV(20) // P1.09 (+11)
#define GPI_LED_GPIO5      BV(28) // P0.26 (+2)
#define GPI_LED_GPIO6      BV(14) // P1.03 (+11)
#define GPI_LED_GPIO7      BV(11) // P0.11
#define GPI_LED_GPIO8      BV(13) // P0.13
#define GPI_LED_GPIO9      BV(18) // P0.16 (+2)
#define GPI_LED_GPIO10     BV(12) // P0.12
#define GPI_LED_GPIO11     BV(10) // P0.10
#define GPI_LED_GPIO12     BV(21) // P0.19 (+2)
#define GPI_LED_GPIO13     BV(22) // P0.20 (+2)
#define GPI_LED_GPIO14     BV(26) // P0.24 (+2)
#define GPI_LED_GPIO15     BV(29) // P0.27 (+2)

#define GPI_BUTTON_PWRGD_H BV(7)  // P0.07
#define GPI_BUTTON_PWRGD_L BV(23) // P0.23
#define GPI_BUTTON_MAX_INT BV(25) // P0.25
#define GPI_BUTTON_RTC_INT BV(30) // P0.30

// internal mapping to P0 and P1
// ATTENTION: concept works as long as bit positions at P0 and P1 do not overlap.
// If they do, shift bit mapping at P0 or P1 by a constant to find a non-overlapping combination.
// If impossible, there is more work to do.
// for details see gpi_led_on()
#define _GPI_LED_P0_MASK                                                                           \
    (GPI_LED_2P | GPI_LED_GPIO0 | GPI_LED_GPIO1 | GPI_LED_GPIO2 | GPI_LED_GPIO3 | GPI_LED_GPIO5 |  \
     GPI_LED_GPIO7 | GPI_LED_GPIO8 | GPI_LED_GPIO9 | GPI_LED_GPIO10 | GPI_LED_GPIO11 |             \
     GPI_LED_GPIO12 | GPI_LED_GPIO13 | GPI_LED_GPIO14 | GPI_LED_GPIO15)
#define _GPI_LED_P1_MASK   (GPI_LED_0 | GPI_LED_GPIO4 | GPI_LED_GPIO6)
#define _GPI_LED_P0b_SHIFT 2  // shift between upper 16 bit of P0 and MASK
#define _GPI_LED_P1_SHIFT  11 // shift between P1 and MASK
#define _GPI_BUTTON_P0_MASK                                                                        \
    (GPI_BUTTON_PWRGD_H | GPI_BUTTON_PWRGD_L | GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT)
#define _GPI_BUTTON_P1_MASK  0
#define _GPI_BUTTON_INV_MASK (GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT)

// for details see comments in gpi/platform.h
static ALWAYS_INLINE int gpi_led_index_to_mask(int i)
{
    // NOTE: with optimization enabled, the switch block gets replaced by
    // * a constant if i is constant (due to constant propagation)
    // * a lookup table with preceding 1 <= i <= i_max test, or
    // * a fast conditional execution block (on ARM)
    switch (i)
    {
        case 1: return GPI_LED_0;
        case 2: return GPI_LED_2P;
        case 3: return GPI_LED_GPIO0;
        case 4: return GPI_LED_GPIO1;
        case 5: return GPI_LED_GPIO2;
        case 6: return GPI_LED_GPIO3;
        case 7: return GPI_LED_GPIO4;
        case 8: return GPI_LED_GPIO5;
        case 9: return GPI_LED_GPIO6;
        case 10: return GPI_LED_GPIO7;
        case 11: return GPI_LED_GPIO8;
        case 12: return GPI_LED_GPIO9;
        case 13: return GPI_LED_GPIO10;
        case 14: return GPI_LED_GPIO11;
        case 15: return GPI_LED_GPIO12;
        case 16: return GPI_LED_GPIO13;
        case 17: return GPI_LED_GPIO14;
        case 18: return GPI_LED_GPIO15;
        default: return GPI_LED_NONE;
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
        case 1: return GPI_BUTTON_PWRGD_H;
        case 2: return GPI_BUTTON_PWRGD_L;
        case 3: return GPI_BUTTON_MAX_INT;
        case 4: return GPI_BUTTON_RTC_INT;
        default: return 0;
    }
}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// UART pins
#define _GPI_ARM_nRF_UART_TXD_PORT 0
#define _GPI_ARM_nRF_UART_TXD_PIN  8
#define _GPI_ARM_nRF_UART_RXD_PORT 0
#define _GPI_ARM_nRF_UART_RXD_PIN  21

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
    register int mask0 = mask & _GPI_LED_P0_MASK;
    register int mask1 = mask & _GPI_LED_P1_MASK;

    if (mask0) NRF_P0->OUTSET = (mask0 & 0xFFFF) | ((mask0 & 0xFFFF0000) >> _GPI_LED_P0b_SHIFT);

    if (mask1) NRF_P1->OUTSET = mask1 >> _GPI_LED_P1_SHIFT;
}

static ALWAYS_INLINE void gpi_led_off(int mask)
{
    register int mask0 = mask & _GPI_LED_P0_MASK;
    register int mask1 = mask & _GPI_LED_P1_MASK;

    if (mask0) NRF_P0->OUTCLR = (mask0 & 0xFFFF) | ((mask0 & 0xFFFF0000) >> _GPI_LED_P0b_SHIFT);

    if (mask1) NRF_P1->OUTCLR = mask1 >> _GPI_LED_P1_SHIFT;
}

static ALWAYS_INLINE void gpi_led_toggle(int mask)
{
    register int mask0 = mask & _GPI_LED_P0_MASK;
    register int mask1 = mask & _GPI_LED_P1_MASK;

    if (mask0) NRF_P0->OUT ^= (mask0 & 0xFFFF) | ((mask0 & 0xFFFF0000) >> _GPI_LED_P0b_SHIFT);

    if (mask1) NRF_P1->OUT ^= mask1 >> _GPI_LED_P1_SHIFT;
}

//**************************************************************************************************

static ALWAYS_INLINE uint_fast32_t gpi_button_read(int mask)
{
    uint_fast32_t x = 0;

    if (mask & _GPI_BUTTON_P0_MASK) x |= NRF_P0->IN & _GPI_BUTTON_P0_MASK;

    if (mask & _GPI_BUTTON_P1_MASK) x |= NRF_P1->IN & _GPI_BUTTON_P1_MASK;

    x ^= _GPI_BUTTON_INV_MASK;
    x &= mask;

    return x;
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF_SHEPHERD_NRF52_PLATFORM_H__
