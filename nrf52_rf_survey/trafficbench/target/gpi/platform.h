/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2018 - 2024, Networked Embedded Systems Lab, TU Dresden
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
 *	@brief					Miscellaneous platform interface functions.
 *
 * @internal
 *	@version				\$Id: 29b6b1161495840cccad6f1264022b4071f04de7 $
 *	@noop @date				git log -1 <filename>
 *
 *	@author					Carsten Herrmann
 * @endinternal
 *
 ***************************************************************************************************

 	@details
	
	This file represents the GPI's main entry point and contains several basic GPI functions.
	Besides the common functions defined here, the platform-specific platform.h may contain 
	additional functionality that is specific for the concrete platform. For example, this
	can include
	- platform-specific configuration settings
	- `GPI_LED_...` and `GPI_BUTTON_...` definitions (see \ref gpi_gpio_leds)
	- flash, EEPROM, and other kind of non-volatile memory read and write functions

 **//**
 
	@defgroup gpi_gpio Simple GPIO control (LEDs, Buttons, etc.)

	The functions in this group can be used to read and write general-purpose I/O pins (GPIO).
	On many platforms this is used to control connected LEDs and buttons, so the functions
	are called `gpi_led_...` and `gpi_button_...` for output and input, respectively.
	
	All functions are designed to be as small and fast as possible to support efficient GPIO
	handling and GPIO-based program tracing and profiling. Consequently, the functions do
	not include any add-on functionality beyond pure pin access, e.g. debounce mechanisms.

	
	## LEDs {#gpi_gpio_leds}

	Normally, LEDs are identified by board-specific naming macros like `GPI_LED_1`
	and used like this:
	
		gpi_led_on(GPI_LED_1);
		gpi_led_off(GPI_LED_2);

	It must not be assumed that the naming macros wrap consecutive indices, so it is not allowed
	to use abbreviations like `gpi_led_on(1)`. Instead, the convention is that names can be
	combined to a mask, i.e. one can write things like
	
		gpi_led_toggle(GPI_LED_1 | GPI_LED_2);
		
	to update multiple LEDs together. Depending on the platform's GPIO features and pin
	connections, such calls may indeed update all LEDs with a single operation (i.e.,
	most efficiently).
	
	Sometimes it is helpful to access LEDs in a platform-independent manner. This can be realized
	with the function gpi_led_index_to_mask(), which translates index \a i = 1...N into the
	corresponding mask or zero if \a i > N, where N equals the number of existing LEDs.
	For instance, toggling all LEDs could be realized as
	
		for (i = 1; !(m = gpi_led_index_to_mask(i)); i++)
			gpi_led_toggle(m);
	
	or
	
		m_all = 0;
		
		for (i = 1; !(m = gpi_led_index_to_mask(i)); i++)
			m_all |= m;
			
		gpi_led_toggle(m_all);
	
	### Compatibility Notes {#gpi_gpio_leds_compatibility}

	Some older GPI platform implementations defined a macro `GPI_LED()`, which translates a
	consecutive 1-based index \a i into a mask. With this macro it is possible to write things 
	like `gpi_led_on(GPI_LED(1))`. We decided to generalize this functionality for all platforms
	because it allows to do some potentially helpful things in a platform independent manner
	that are difficult otherwise. For instance, toggling all LEDs could be realized as follows:
	
		for (i = 1; i < (8 * sizeof(int)); i++)
		{
			m = GPI_LED(i);
			if (!m)
				break;
			gpi_led_toggle(m);
		}
			
	However, a pure macro implementation (whose value could be evaluated by the preprocessor)
	can become expensive when \a i is not constant (as in the example above). For this reason,
	from now on we encapsulate the platform specific implementation in `gpi_led_index_to_mask()`
	and provide `GPI_LED()` as a wrapper. It is up to the developer if she uses `GPI_LED(i)` or
	`gpi_led_index_to_mask(i)` (the latter appears more explicit). Different to the old versions,
	the new way removes the possibility to evaluate `GPI_LED()` expressions by the preprocessor
	(as in `#if (X == GPI_LED(1))`), which does not appear as an issue.

	@impdetails

	The number of (addressable) LEDs and buttons is limited by the width of the `int` datatype.
	If this is not enough, there are multiple options:
	
	1. Provide additional platform-specific functions.
	2. Make the datatype platform-dependent.
	3. Add an additional parameter to support LED groups.
	
	For the moment we prefer the first option if necessary. If there is significant demand
	for extensions, the strategy may be changed in the future.
	
	
	## Buttons {#gpi_gpio_buttons}
	
	The basic concept is the same as with LEDs (see [above](#gpi_gpio_leds)), with the major
	difference that the support of masks marking multiple buttons in `gpi_button_read()` is
	platform-specific. The return value when called with such masks is one of the following:
	
	- always 0 or invalid (= functionality not supported)
	- AND or OR combination of all requested button states
	- a bitfield marking the individual button states
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

/// @ingroup gpi_gpio
/// @{

/// @brief Convert LED index \a i to platform-specific LED mask.
/// @sa gpi_led_index_to_mask(), \ref gpi_gpio_leds_compatibility
//  internal: a pure macro implementation could look like this:
//  #define GPI_LED(x) (((1 == (x)) * GPI_LED_1) | ((2 == (x)) * GPI_LED_2) | ... )
#define GPI_LED(i)		gpi_led_index_to_mask(i)

/// @brief Convert button index \a i to platform-specific button mask.
/// @sa gpi_button_index_to_mask(), \ref gpi_gpio_leds_compatibility
#define GPI_BUTTON(i)	gpi_button_index_to_mask(i)

/// @}

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

/// @brief Initialize GPI.
/// @details
/// gpi_platform_init() must be called once before using any GPI functionality, e.g., during
/// system initialization. In many applications, a good place to call gpi_platform_init() is
/// at the beginning of the `main()` function. The function is not called automatically to
/// ensure that the user has full control over the right point in time.
///
/// gpi_platform_init() performs all internal initialization steps that are needed to bring
/// the system incl. GPI into a usable state. The meaning of the latter is platform-dependent,
/// on bare-metal microcontroller systems it typically includes initialization of the
/// CPU core (e.g. execution mode, FPU, exception handling, interrupt handling, etc.),
/// memory subsystem (e.g. caches), I/O ports, clock system (hardware oscillators, clocks.h),
/// stdio (e.g. via UART), and GPI's logging functionality (trace.h).
void			gpi_platform_init();

/// @ingroup gpi_gpio
/// @{

/// @brief Turn LED(s) on.
/// @details
/// \a mask is an OR combination of one or more platform-specific LED mask definitions,
/// see `GPI_LED_...`.
/// @sa \ref gpi_gpio_leds
void			gpi_led_on(int mask);

/// @brief Turn LED(s) off.
/// @copydetails gpi_led_on()
void			gpi_led_off(int mask);

/// @brief Toggle LED(s).
/// @copydetails gpi_led_on()
void			gpi_led_toggle(int mask);

/// @brief Convert LED index to platform-specific LED mask.
/// @details For details see \ref gpi_gpio_leds.
int				gpi_led_index_to_mask(int index);

/// @brief Read button(s).
/// @details
/// \a mask is an OR combination of one or more platform-specific button mask definitions,
/// see `GPI_BUTTON_...`.
/// @sa \ref gpi_gpio_buttons
uint_fast8_t	gpi_button_read(int mask);

/// @brief Convert button index to platform-specific button mask.
/// @details For details see \ref gpi_gpio_leds.
int				gpi_button_index_to_mask(int index);

/// @}

/// @brief Enter sleep mode.
/// @details
/// gpi_sleep() implements some "universal" sleep mode that can be used by platform-agnostic
/// applications. The precise meaning of sleep is platform-dependent. From an application point
/// of view, gpi_sleep() tells the system that there is nothing to do at the moment, and
/// execution will continue after the call when some wake-up event has been detected.
///
/// Since low-power and sleep modes are completely platform-dependent, the selected platform
/// may provide more platform-specific sleep functions, e.g. something like
/// `gpi_[<platform>]_enter_low_power_mode(...)`.
///
/// @todo In the Nordic branch we provide the variable `gpi_wakeup_event`, which can be used to
/// detect which interrupt/event has woken-up the CPU. Check if this concept can be generalized
/// and do so if possible.
void			gpi_sleep();

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
