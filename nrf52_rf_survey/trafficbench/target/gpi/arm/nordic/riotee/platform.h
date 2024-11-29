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
 *	@file					gpi/arm/nordic/riotee/platform.h
 *
 *	@brief					platform interface functions, specific for Nessie Circuit's Riotee
 *
 *	@version				$Id: c8107266c939df33485471629170243aebcda607 $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF_RIOTEE_PLATFORM_H__
#define __GPI_ARM_nRF_RIOTEE_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "../nrf528xx/platform.h" // nRF528xx common functionality
#include "../nrf528xx/platform_internal.h"

#include "gpi/tools.h"

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

#define GPI_LED_NONE 0
#define GPI_LED_1    BV(3)

#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
  #define GPI_LED_BOARD_1 BV(26)
#endif

#define GPI_BUTTON_PWRGD_H BV(7)
#define GPI_BUTTON_PWRGD_L BV(23)
#define GPI_BUTTON_MAX_INT BV(25)
#define GPI_BUTTON_RTC_INT BV(30)

#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
  #define GPI_BUTTON_BOARD_1 BV(3)
#endif

// internal mapping to P0 and P1
// ATTENTION: concept works as long as bit positions at P0 and P1 do not overlap.
// If they do, shift bit mapping at P0 or P1 by a constant to find a non-overlapping combination.
// If impossible, there is more work to do.
// for details see gpi_button_read()
#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
  #define _GPI_BUTTON_P0_MASK                                                                      \
      (GPI_BUTTON_PWRGD_H | GPI_BUTTON_PWRGD_L | GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT)
  #define _GPI_BUTTON_P1_MASK  (GPI_BUTTON_BOARD_1)
  #define _GPI_BUTTON_INV_MASK (GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT | GPI_BUTTON_BOARD_1)
#else
  #define _GPI_BUTTON_P0_MASK                                                                      \
      (GPI_BUTTON_PWRGD_H | GPI_BUTTON_PWRGD_L | GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT)
  #define _GPI_BUTTON_P1_MASK  0
  #define _GPI_BUTTON_INV_MASK (GPI_BUTTON_MAX_INT | GPI_BUTTON_RTC_INT)
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
        case 1: return GPI_LED_1;

#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
        case 2: return GPI_LED_BOARD_1;
#endif
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

#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
        case 5: return GPI_BUTTON_BOARD_1;
#endif
        default: return 0;
    }
}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// UART pins
#if GPI_ARCH_IS_BOARD(NESSIE_RIOTEE_NRF_BOARD)
  #define _GPI_ARM_nRF_UART_TXD_PORT 0
  #define _GPI_ARM_nRF_UART_TXD_PIN  8
  #define _GPI_ARM_nRF_UART_RXD_PORT 0
  #define _GPI_ARM_nRF_UART_RXD_PIN  21
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

#endif // __GPI_ARM_nRF_RIOTEE_PLATFORM_H__
