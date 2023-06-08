/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2018 - 2022, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/platform.h
 *
 *	@brief					platform interface functions
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details
	
	
	# LEDs
	
	Normally, LEDs are identified by naming macros like GPI_LED_1, and used like this:
	
		gpi_led_on(GPI_LED_1);
		gpi_led_off(GPI_LED_2);

	It must not be assumed that the naming macros wrap consecutive indices, so it is not allowed
	to use abbreviations like gpi_led_on(1). Instead, the convention is that names can be combined
	to a mask, i.e. one can write things like
	
		gpi_led_toggle(GPI_LED_1 | GPI_LED_2);
		
	Some (older) GPI platform implementations defined a macro GPI_LED(i), which translates a
	consecutive 1-based index i into a mask. With this macro it is possible to write things like
	gpi_led_on(GPI_LED(1)). We decided to generalize this functionality for all platforms
	because it allows to do some potentially helpful things in a platform independent manner
	that are difficult otherwise. For instance, toggling all LEDs could be realized as follows:
	
		for (i = 1; i < 32; i++)
		{
			m = GPI_LED(i);
			if (!m)
				break;
			gpi_led_toggle(m);
		}
			
	However, a pure macro implementation (whose value could be evaluated by the preprocessor)
	can become expensive when i is not constant (as in the example above). For this reason,
	from now on we encapsulate the platform specific implementation in gpi_led_index_to_mask()
	and provide GPI_LED() as a wrapper. It is up to the developer if she uses GPI_LED(i) or
	gpi_led_index_to_mask(i) (the latter appears more explicit). Different to the old versions,
	the new way removes the possibility to evaluate GPI_LED() expressions by the preprocessor
	(as in #if X == GPI_LED(1)), which does not appear as an issue.
	
	
	# Buttons
	
	The basic concept is the same as with LEDs (see above), with the major difference that
	the support of masks marking multiple buttons in gpi_button_read() is platform specific.
	The return value when called with such masks is one of the following:
		* always 0 or invalid (= functionality not supported)
		* AND or OR combination of all requested button states
		* a bitfield marking the individual button states
		  (evaluating this value logically is equivalent to an OR combination)
	
	Normally this is not a big deal, as buttons are typically evaluated individually.
	It can be of interest if a platform provides access to other input signals via button
	functions (e.g. trigger inputs). However, this possibility should not be overstressed
	(maybe it is better to provide platform specific functions that fit better in case).

 **************************************************************************************************/

#ifndef __GPI_PLATFORM_H__
#define __GPI_PLATFORM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"
#include GPI_PLATFORM_PATH(platform.h)

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

// see comments above
// a pure macro implementation could look like this:
// #define GPI_LED(x) (((1 == (x)) * GPI_LED_1) | ((2 == (x)) * GPI_LED_2) | ... )
#define GPI_LED(i)		gpi_led_index_to_mask(i)
#define GPI_BUTTON(i)	gpi_button_index_to_mask(i)

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************



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

void			gpi_platform_init();

void			gpi_led_on(int mask);
void			gpi_led_off(int mask);
void			gpi_led_toggle(int mask);
int				gpi_led_index_to_mask(int index);

uint_fast8_t	gpi_button_read(int mask);
int				gpi_button_index_to_mask(int index);

void			gpi_sleep();
	// some universal sleep mode. platform may provide more detailed platform-specific functions
	// gpi_[<platform>]_enter_low_power_mode(...)

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************
/*
static ALWAYS_INLINE __attribute__((deprecated("use gpi_led_index_to_mask() instead"))) 
int gpi_led_index_to_mask_wrapper(int i)
{
	return gpi_led_index_to_mask(i);
}
*/
//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_PLATFORM_H__
