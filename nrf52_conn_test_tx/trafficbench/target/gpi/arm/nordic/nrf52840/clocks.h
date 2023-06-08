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
 *	@file					gpi/arm/nordic/nrf52840/clocks.h
 *
 *	@brief					general-purpose slow, fast, and hybrid clock
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF52840_CLOCKS_H__
#define __GPI_ARM_nRF52840_CLOCKS_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/tools.h"

#include <nrf.h>

#ifdef GPI_SETUP_FILE
	#include STRINGIFY(GPI_SETUP_FILE)
#endif

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

#ifndef GPI_SLOW_CLOCK_RATE
	#define	GPI_SLOW_CLOCK_RATE		32768u
#endif

#ifndef GPI_FAST_CLOCK_RATE
	#define GPI_FAST_CLOCK_RATE		16000000u
#endif

#ifndef GPI_HYBRID_CLOCK_RATE
	#define GPI_HYBRID_CLOCK_RATE	GPI_FAST_CLOCK_RATE
#endif

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

#ifndef GPI_ARM_NRF_FAST_CLOCK_TIMER
	#define GPI_ARM_NRF_FAST_CLOCK_TIMER			0
#endif
#ifndef GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG
	#define GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG		0
#endif

#ifndef GPI_ARM_NRF_SLOW_CLOCK_RTC
	#define GPI_ARM_NRF_SLOW_CLOCK_RTC				0
#endif

#ifndef GPI_HYBRID_CLOCK_USE_VHT
	#define GPI_HYBRID_CLOCK_USE_VHT				0	// otherwise HYBRID_CLOCK === FAST_CLOCK
#endif
#ifndef GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL
	#define GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL	0	// needed only if GPI_HYBRID_CLOCK_USE_VHT is set
#endif
#ifndef GPI_ARM_NRF_HYBRID_CLOCK_CAPTURE_REG
	#define GPI_ARM_NRF_HYBRID_CLOCK_CAPTURE_REG	1	// needed only if GPI_HYBRID_CLOCK_USE_VHT is set
#endif

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

typedef uint16_t	Gpi_Slow_Tick_Native;			// machine word or smaller
typedef uint32_t	Gpi_Slow_Tick_Extended;			// for long intervals
typedef uint32_t	Gpi_Fast_Tick_Native;
typedef uint32_t	Gpi_Fast_Tick_Extended;
typedef uint32_t	Gpi_Hybrid_Tick;

typedef struct Gpi_Hybrid_Reference_tag
{
	Gpi_Hybrid_Tick			hybrid_tick;
	Gpi_Fast_Tick_Native	fast_capture;

} Gpi_Hybrid_Reference;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

static volatile typeof(*NRF_TIMER0) * const		_gpi_clocks_fast_timer =
	#if   (0 == GPI_ARM_NRF_FAST_CLOCK_TIMER)
		NRF_TIMER0;
	#elif (1 == GPI_ARM_NRF_FAST_CLOCK_TIMER)
		NRF_TIMER1;
	#elif (2 == GPI_ARM_NRF_FAST_CLOCK_TIMER)
		NRF_TIMER2;
	#elif (3 == GPI_ARM_NRF_FAST_CLOCK_TIMER)
		NRF_TIMER3;
	#elif (4 == GPI_ARM_NRF_FAST_CLOCK_TIMER)
		NRF_TIMER4;
	#else
		#error GPI_ARM_NRF_FAST_CLOCK_TIMER is invalid
	#endif

static volatile typeof(*NRF_RTC0) * const		_gpi_clocks_rtc =
	#if   (0 == GPI_ARM_NRF_SLOW_CLOCK_RTC)
		NRF_RTC0;
	#elif (1 == GPI_ARM_NRF_SLOW_CLOCK_RTC)
		NRF_RTC1;
	#elif (2 == GPI_ARM_NRF_SLOW_CLOCK_RTC)
		NRF_RTC2;
	#else
		#error GPI_ARM_NRF_SLOW_CLOCK_RTC is invalid
	#endif

//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
	extern "C" {
#endif

// forward declarations (needed below)
#if GPI_HYBRID_CLOCK_USE_VHT
	Gpi_Hybrid_Tick			gpi_tick_fast_to_hybrid(Gpi_Fast_Tick_Native fast_tick);
#endif

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

static ALWAYS_INLINE Gpi_Slow_Tick_Native gpi_tick_slow_native(void)
{
	// ATTENTION: counter register is asynchronous to the CPU clock, but the RTC peripheral
	// synchronizes reads by itself (see spec. 4413_417 v1.0 page 340 "Reading the COUNTER
	// register" for details)

	return _gpi_clocks_rtc->COUNTER;
}

//**************************************************************************************************

static ALWAYS_INLINE Gpi_Fast_Tick_Native gpi_tick_fast_native(void)
{
	// the counter register is not directly accessible
	// -> we trigger a capture event and read the value from the capture register
	//
	// ATTENTION: Exactly speaking, this procedure is not reentrant without additional locking.
	// However, if the caller's context is interruptable, it does not matter if the returned
	// timestamp is taken before, during, or after the interrupt as long as it stems from the
	// interval between function entry and return. Hence, we do not need a locking mechanism.

	_gpi_clocks_fast_timer->TASKS_CAPTURE[GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG] = 1;
	return _gpi_clocks_fast_timer->CC[GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG];
}

//**************************************************************************************************

static ALWAYS_INLINE Gpi_Fast_Tick_Extended gpi_tick_fast_extended(void)
{
	ASSERT_CT(sizeof(Gpi_Fast_Tick_Extended) == sizeof(Gpi_Fast_Tick_Native));
	
	return gpi_tick_fast_native();
}

//**************************************************************************************************
#if !GPI_HYBRID_CLOCK_USE_VHT

static ALWAYS_INLINE Gpi_Hybrid_Tick gpi_tick_fast_to_hybrid(Gpi_Fast_Tick_Native fast_tick)
{
	// use the full function(ality) if format extension/conversion is necessary
	ASSERT_CT(sizeof(Gpi_Hybrid_Tick) == sizeof(Gpi_Fast_Tick_Native));
	ASSERT_CT(GPI_HYBRID_CLOCK_RATE == GPI_FAST_CLOCK_RATE);
	
	return fast_tick;
}

#endif	// GPI_HYBRID_CLOCK_USE_VHT
//**************************************************************************************************
#if !GPI_HYBRID_CLOCK_USE_VHT

static ALWAYS_INLINE Gpi_Hybrid_Reference gpi_tick_hybrid_reference(void)
{
	// use the full function(ality) if format extension/conversion is necessary
//	ASSERT_CT(sizeof(Gpi_Hybrid_Tick) == sizeof(Gpi_Fast_Tick_Native));
//	ASSERT_CT(GPI_HYBRID_CLOCK_RATE == GPI_FAST_CLOCK_RATE);

	Gpi_Hybrid_Reference	r;

	r.fast_capture = gpi_tick_fast_native();
	r.hybrid_tick = r.fast_capture;

	return r;
}

#endif	// GPI_HYBRID_CLOCK_USE_VHT
//**************************************************************************************************

static ALWAYS_INLINE Gpi_Hybrid_Tick gpi_tick_hybrid(void)
{
	return gpi_tick_fast_to_hybrid(gpi_tick_fast_native());
}

//**************************************************************************************************

// convert timestamp from hybrid ticks to microseconds
// NOTE: providing an efficient implementation of this functionality is advantageous
// for debug messages and profiling purposes
static ALWAYS_INLINE uint32_t gpi_tick_hybrid_to_us(Gpi_Hybrid_Tick ticks)
{
	#if (GPI_HYBRID_CLOCK_RATE >= 1000000)

		ASSERT_CT(
			(GPI_HYBRID_CLOCK_RATE == (GPI_HYBRID_CLOCK_RATE / 1000000) * 1000000) &&
			IS_POWER_OF_2(GPI_HYBRID_CLOCK_RATE / 1000000),
			GPI_HYBRID_CLOCK_RATE_unsupported);

		return ticks / (GPI_HYBRID_CLOCK_RATE / 1000000);
	
	#else

		ASSERT_CT(
			1000000 == (1000000 / GPI_HYBRID_CLOCK_RATE) * GPI_HYBRID_CLOCK_RATE,
			GPI_HYBRID_CLOCK_RATE_unsupported);

		return ticks * (1000000 / GPI_HYBRID_CLOCK_RATE);

	#endif

	return ticks;
}

//**************************************************************************************************

static ALWAYS_INLINE uint32_t gpi_tick_fast_to_us(Gpi_Fast_Tick_Extended ticks)
{
	ASSERT_CT(sizeof(Gpi_Hybrid_Tick) == sizeof(Gpi_Fast_Tick_Extended));
	ASSERT_CT(GPI_FAST_CLOCK_RATE == GPI_HYBRID_CLOCK_RATE);

	return gpi_tick_hybrid_to_us(ticks);

	// could be extended as follows, but take care with all the value ranges:
	// return gpi_tick_hybrid_to_us(ticks / (GPI_FAST_CLOCK_RATE / GPI_HYBRID_CLOCK_RATE));
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF52840_CLOCKS_H__
