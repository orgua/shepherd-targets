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
 *	@file					gpi/arm/nordic/nrf52840/clocks.c
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
//***** Trace Settings *****************************************************************************



//**************************************************************************************************
//**** Includes ************************************************************************************

#include "gpi/tools.h"
#include "gpi/clocks.h"
#include "gpi/interrupts.h"
#include "gpi/olf.h"

#include "gpi/resource_check.h"

GPI_RESOURCE_RESERVE_SHARED(NRF_TIMER, GPI_ARM_NRF_FAST_CLOCK_TIMER);
GPI_RESOURCE_RESERVE(NRF_TIMER_CC, GPI_ARM_NRF_FAST_CLOCK_TIMER, GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG);

#if GPI_HYBRID_CLOCK_USE_VHT
	GPI_RESOURCE_RESERVE(NRF_PPI_CH, GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL);
	GPI_RESOURCE_RESERVE(NRF_TIMER_CC, GPI_ARM_NRF_FAST_CLOCK_TIMER, GPI_ARM_NRF_HYBRID_CLOCK_CAPTURE_REG);
#endif

GPI_RESOURCE_RESERVE_SHARED(NRF_RTC, GPI_ARM_NRF_SLOW_CLOCK_RTC);

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

// remove int locks in hybrid clock functions
// Setting this define avoids some int locks and improves performance a bit. On the other hand,
// it makes (some of) the hybrid clock functions non-reentrant. Since this is dangerous if
// enabled without care, the option is disabled by default.
#define GPI_CLOCKS_HYBRID_FRAGILE	0

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************



//**************************************************************************************************
//***** Forward Declarations ***********************************************************************



//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************



//**************************************************************************************************
//***** Global Variables ***************************************************************************



//**************************************************************************************************
//***** Local Functions ****************************************************************************



//**************************************************************************************************
//***** Global Functions ***************************************************************************

Gpi_Slow_Tick_Extended gpi_tick_slow_extended()
{
	ASSERT_CT(sizeof(Gpi_Slow_Tick_Extended) == sizeof(uint32_t));

	static struct
	{
		uint16_t	high;
	} s	=
	{0};

	register Generic32	o;

	// TODO: check how the function is used and decide if we can remove the int-lock or
	// provide and unlocked version (using the same static variables)
	// ATTENTION: int-lock makes the function reentrant; it is not without the int-lock.
	// Alternatively, maybe it is possible to use a marker to avoid nested updates.

	int ie = gpi_int_lock();

	// read 24-bit value directly from COUNTER
	// NOTE: gpi_tick_slow_native() returns 16-bit
	o.u32 = _gpi_clocks_rtc->COUNTER;

	// extend format
	// update high part using the 8 upper bits of the 24-bit value
	// ATTENTION: function has to be called periodically at least once per 0xFFFFFF ticks,
	// otherwise it will loose ticks in high part
	s.high += (uint8_t)(o.u8_hl - s.high);
	o.u16_h = s.high;

	gpi_int_unlock(ie);

	return o.u32;
}

//*************************************************************************************************
#if GPI_HYBRID_CLOCK_USE_VHT

Gpi_Hybrid_Reference gpi_tick_hybrid_reference()
{
	ASSERT_CT(sizeof(Gpi_Slow_Tick_Native) == sizeof(uint16_t));
	ASSERT_CT(sizeof(Gpi_Fast_Tick_Native) == sizeof(uint32_t));
	ASSERT_CT(sizeof(Gpi_Slow_Tick_Extended) == sizeof(uint32_t));
	ASSERT_CT(sizeof(Gpi_Hybrid_Tick) == sizeof(uint32_t));

	Gpi_Hybrid_Reference	r;
	register uint16_t		slow;
	register uint32_t		fast;
	register Generic32		t;

	// lock interrupts
	// NOTE: due to the active use of EVENTS_TICK, the code is not reentrant without ints locked
	#if (!GPI_CLOCKS_HYBRID_FRAGILE)
		register int ie = gpi_int_lock();
	#endif

	// get edge ticks
	do
	{
		// clear event register
		_gpi_clocks_rtc->EVENTS_TICK = 0;	

		// read slow tick
		// NOTE: see gpi_tick_slow_native() for details regarding asynchronous clock issues
		slow = _gpi_clocks_rtc->COUNTER;
	
		// ATTENTION: The RTC tick event is routed through the PPI which introduces a delay of one
		// PCLK16 cycle. Additionally the RTC runs with an asynchronous clock (LFCLK), so there is
		// a good chance that there is some synchronization stage at the event generator introducing
		// an additional delay. Therefore we delay a bit before reading the capture value to ensure
		// that it is impossible that an event generated before we reset EVENTS_TICK did not arrive
		// yet. With a potential delay of two PCLK16 cycles and the CPU running 4x faster (fed
		// from HCLK64M), 8 nops plus the execution time of the COUNTER read should be save.
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

		fast = _gpi_clocks_fast_timer->CC[GPI_ARM_NRF_HYBRID_CLOCK_CAPTURE_REG];
    }
	while (_gpi_clocks_rtc->EVENTS_TICK);
	
	// unlock interrupts
	#if (!GPI_CLOCKS_HYBRID_FRAGILE)
		gpi_int_unlock(ie);
	#endif

	// extent slow value
	// NOTE: we do not call gpi_tick_slow_extended() within the loop directly because it is
	// expensive in comparison to the loop
	// ATTENTION: It must be guaranteed that the delay between the loop and the
	// gpi_tick_slow_extended() call is less than 0x10000 slow ticks. Since this is a large
	// amount of time in a typical configuration (in the range of seconds) we do not implement
	// any locks here.
	t.u32 = gpi_tick_slow_extended();
	if (t.u16_l < slow)
		t.u16_h--;
	t.u16_l = slow;

	// convert edge ticks to hybrid timebase
	{
		// conversion: hybrid_ticks = slow_ticks * hybrid_slow_ratio
		// NOTE: In general hybrid_slow_ratio is not an integer, but it holds
		// 16000000 = 15625 * 1024 = 15625 * 32768 / 32 -> ticks_16M = ticks_32k * 15625 / 32
		// with HYBRID_CLOCK_RATE = 16M / 2^x and SLOW_CLOCK_RATE = 32768:
		// hybrid_ticks = slow_ticks * 15625 / (512M / HYBRID_CLOCK_RATE)

		ASSERT_CT(32768 == GPI_SLOW_CLOCK_RATE, GPI_SLOW_CLOCK_RATE_unsupported);
		ASSERT_CT((512000000u == (512000000u / GPI_HYBRID_CLOCK_RATE) * GPI_HYBRID_CLOCK_RATE) &&
			IS_POWER_OF_2(512000000u / GPI_HYBRID_CLOCK_RATE),
			hybrid_slow_ratio_unsupported);
	
		t.u32 = gpi_mulu_32x16to64(t.u32, 15625) >> MSB(512000000u / GPI_HYBRID_CLOCK_RATE);
    }
	
	r.hybrid_tick = t.u32;
	r.fast_capture = fast;

	return r;
}

#endif	// GPI_HYBRID_CLOCK_USE_VHT
//**************************************************************************************************
#if GPI_HYBRID_CLOCK_USE_VHT

// convert a fast tick value from the near past (e.g. timer capture) to hybrid ticks
// ATTENTION: the call has to follow within <= 0xF...F fast ticks (max. Gpi_Fast_Tick_Native),
// otherwise the result will be wrong
Gpi_Hybrid_Tick gpi_tick_fast_to_hybrid(Gpi_Fast_Tick_Native fast_tick)
{
	register Gpi_Hybrid_Reference	r;
	register Gpi_Fast_Tick_Native	delta;

	// get last edge ticks
	// ATTENTION: this must happen <= 0xF...F fast ticks after the interesting point in time
	r = gpi_tick_hybrid_reference();

	ASSERT_CT(IS_POWER_OF_2(GPI_FAST_CLOCK_RATE / GPI_HYBRID_CLOCK_RATE), fast_hybrid_ratio_must_be_power_of_2);

	// compute delta between edge capture and past value
	// ATTENTION: We expect that fast_tick is before edge tick in the typical case. But the edge is
	// from the (near) past, so it is also possible that fast_tick stems from a period < 1 slow
	// clock cycles after the edge. In this case, -delta < GPI_FAST_CLOCK_RATE / GPI_SLOW_CLOCK_RATE
	// (+ some tolerance if fast clock is asynchronous to slow clock). Hence we split the
	// interpretation of delta at this value.
	delta = r.fast_capture - fast_tick;

	// compute hybrid tick:
	// if fast_tick is behind edge for sure: sub delta with respect to datatypes
	// ATTENTION: we add a safety margin that compensates for clock drift (i.e. delta may be
	// > GPI_FAST_CLOCK_RATE / GPI_SLOW_CLOCK_RATE even if fast_tick is between edge and next edge)
	if (-delta < ((GPI_FAST_CLOCK_RATE / GPI_SLOW_CLOCK_RATE) * 103) / 100)
		r.hybrid_tick += -delta / (GPI_FAST_CLOCK_RATE / GPI_HYBRID_CLOCK_RATE);

	// else sub delta in standard way
	else
		r.hybrid_tick -= delta / (GPI_FAST_CLOCK_RATE / GPI_HYBRID_CLOCK_RATE);

	return r.hybrid_tick;
}

#endif	// GPI_HYBRID_CLOCK_USE_VHT
//**************************************************************************************************

// convert timestamp from slow ticks to microseconds
uint32_t gpi_tick_slow_to_us(Gpi_Slow_Tick_Extended ticks)
{
	ASSERT_CT(sizeof(Gpi_Slow_Tick_Extended) == sizeof(uint32_t));
	ASSERT_CT(GPI_SLOW_CLOCK_RATE >= 64, GPI_SLOW_CLOCK_RATE_too_small);
	ASSERT_CT(IS_POWER_OF_2(GPI_SLOW_CLOCK_RATE), GPI_SLOW_CLOCK_RATE_must_be_power_of_2);
		// to make sure that div gets replaced by shift

	// result = ticks * 1000000 / GPI_SLOW_CLOCK_RATE
	// observe that 1000000 = 15625 * 64 ->
	// result = ticks * 15625 * 64 / GPI_SLOW_CLOCK_RATE = ticks * 15625 / (GPI_SLOW_CLOCK_RATE / 64)

	uint64_t temp;
	
	temp = gpi_mulu_32x16to64(ticks, 15625);
	return temp / (GPI_SLOW_CLOCK_RATE / 64);
}

//*************************************************************************************************

#if !(__OPTIMIZE__)
	// enable constant propagation to avoid errors with ASSERT_CT()
	__attribute__((optimize("Og")))
#endif
void gpi_milli_sleep(uint16_t ms)
{
	const uint16_t			TICKS_PER_MS = GPI_FAST_CLOCK_RATE / 1000u;
	Gpi_Fast_Tick_Native	tick;

	ASSERT_CT(GPI_FAST_CLOCK_RATE == TICKS_PER_MS * 1000u, GPI_FAST_CLOCK_RATE_unsupported);
	ASSERT_CT(sizeof(tick) >= sizeof(uint32_t));

	// ensure that ms * TICKS_PER_MS < INT32_MAX (signed)
	ASSERT_CT(TICKS_PER_MS < 0x8000);

	tick = gpi_tick_fast_native();

	tick += (Gpi_Fast_Tick_Native)ms * TICKS_PER_MS;

	while (gpi_tick_compare_fast_native(gpi_tick_fast_native(), tick) <= 0);
}

//*************************************************************************************************

#if !(__OPTIMIZE__)
	// enable constant propagation to avoid errors with ASSERT_CT()
	__attribute__((optimize("Og")))
#endif
void gpi_micro_sleep(uint16_t us)
{
	// ATTENTION: gpi_micro_sleep() should be fast

	const uint16_t			TICKS_PER_US = GPI_FAST_CLOCK_RATE / 1000000u;
	Gpi_Fast_Tick_Native	tick;

	ASSERT_CT(GPI_FAST_CLOCK_RATE == TICKS_PER_US * 1000000u, GPI_FAST_CLOCK_RATE_unsupported);
	ASSERT_CT(sizeof(tick) >= sizeof(uint32_t));

	// ensure that us * TICKS_PER_US < INT32_MAX (signed)
	ASSERT_CT(TICKS_PER_US < 0x8000);

	tick = gpi_tick_fast_native();

	tick += (Gpi_Fast_Tick_Native)us * TICKS_PER_US;

	while (gpi_tick_compare_fast_native(gpi_tick_fast_native(), tick) <= 0);
}

//**************************************************************************************************
//**************************************************************************************************
