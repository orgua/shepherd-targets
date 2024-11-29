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
 *	@file					gpi/clocks.h
 *
 *	@brief					General-purpose slow (lo-res), fast (hi-res), and hybrid clock.
 *
 * @internal
 *	@version				\$Id: 4514afebca504ea938abcb2051c386f626b9a931 $
 *	@noop @date				git log -1 <filename>
 *
 *	@author					Carsten Herrmann
 * @endinternal
 *
 ***************************************************************************************************

 	@details

	This module provides basic clock functionality, which is useful in many projects.

	The common API supports three clocks, namely a *fast clock*, a *slow clock*, and
	a *hybrid clock*. Depending on the platform, not each of these clocks may be independent,
	but the user can expect that there is a clock behind each interface (e.g., the fast clock and
	hybrid clock functions may access the same fast internal clock, while the slow clock functions
	access a slower real-time clock).
	Beyond the common API defined here, the platform-specific clocks.h may provide additional
	functionality that is specific for the concrete platform, e.g. special synchronization routines.
	It also contains platform-specific configuration settings, e.g., clock rates,
	used hardware resources (e.g., timer instances), etc..

	# Clock Types

	In a typical setting, the *fast clock* represents an everyday clock with a clock rate in the
	MHz range that can be used for time measurements of all kinds. Often, it is also the source
	clock for peripheral modules and hardware-based timer capture functionality. The accuracy
	of the fast clock is heavily platform-dependent and can range from tens of ppm (e.g., from a
	crystal oscillator) to multiple percent (e.g., from an uncompensated internal oscillator).

	The *slow clock* usually stands for a real-time clock with a clock rate of some kHz.
	It is interesting in situations where longer time periods should be monitored and the high
	resolution of the fast clock is not necessary. Depending on the platform, there may also be
	differences between the fast and slow clock regarding power consumption and low-power modes.
	A slow clock driven by a typical low-speed clock crystal often provides a pretty accurate
	frequency (up to some ppm).

	The *hybrid clock* is intended to combine the best of both worlds, i.e., high resolution and
	frequency stability as well as power effiency. Its implementation is heavily platform-dependent.
	In the simplest case it can be just an alias for the fast clock if the latter is driven by an
	accurate crystal oscillator and not stopped during sleep mode. Advanced implementations use
	the hybrid clock to provide so-called *Virtual High-resolution Time (VHT)*, which extends the
	capabilities of an accurate slow clock via an edge-coupled fast clock. The details of this
	concept are discussed in [here](https://dl.acm.org/doi/10.1145/1791212.1791231).

	@sa GPI_FAST_CLOCK_RATE, GPI_SLOW_CLOCK_RATE, GPI_HYBRID_CLOCK_RATE

	# Data Types {#gpi-clocks-datatypes}

	Clock tick values are stored in unsigned integer variables with platform-dependent width.
	The API provides the following datatypes, which should be used whenever possible to avoid
	hard-coded dependencies.

	Datatype               | Usage
	-----------------------|--------------------------------------------------
	Gpi_Fast_Tick_Native   | Fast clock native datatype (machine word or smaller).
	Gpi_Fast_Tick_Extended | Fast clock extended datatype (for long intervals).
	Gpi_Slow_Tick_Native   | Slow clock native datatype (machine word or smaller).
	Gpi_Slow_Tick_Extended | Slow clock extended datatype (for long intervals).
	Gpi_Hybrid_Tick        | Hybrid clock datatype.

	Usually @noop (except for, e.g., 8-bit MCUs)
	the *native* datatypes match the width of underlying hardware timers and / or machine words
	(often 16 or 32 bit). They represent the exchange format between hardware (e.g., timer
	capture units) and software and enable most efficient handling (without the need for computing
	format extensions and the like).
	Hence, they should be preferred whenever their width is sufficient for the application (i.e.,
	if wrap-arounds are detected for sure or missed wrap-arounds do not cause critical issues).

	The *extended* datatypes (often 32 or 64 bit) are provided for use cases that require to
	handle longer time intervals. To this end, the underlying datatype may be larger than the
	native timer and / or machine width, making it somewhat more expensive than its native
	counterpart. Most important,
	@attention To work correctly, format extensions beyond the width of
	hardware timers require that no wrap-arounds of the underlying native timers are missed.
	To this end, the application must ensure that it calls `gpi_tick_fast/slow_extended()`
	at least once per native wrap-around interval.

	In many applications this comes for free because the function is called anyhow once in a while
	(that's what the extended datatype is needed for). Beyond that, it could be called periodically
	in a main loop or an interrupt service routine.

	The hybrid clock does not provide an explicit native datatype, as the handling of
	`Gpi_Hybrid_Tick` is always special if the hybrid clock is not just an alias for another clock.

	@todo Rename datatypes to `Gpi_Tick_...` and mark current names as deprecated.

	@sa
	GPI_TICK_FAST_MAX, GPI_TICK_SLOW_MAX, GPI_TICK_HYBRID_MAX
	\ref gpi-clocks-compare

	# Comparing Timestamps {#gpi-clocks-compare}

	Since tick values have limited width and overflow after a specific period of time, the
	comparison of tick values must be handled in a way that is aware of potential wrap-arounds.
	For example, to compare if `uint16_t t1` represents an earlier point in time than `uint16_t t2`
	it is normally not a good idea to evaluate `t1 < t2` (e.g., think of the case `t1 = 0xfffe`
	and `t2 = 0x0001`). In many cases, it is better to evaluate `t2 - t1` and test if the result
	is positive or negative, as in `(int16_t)(t2 - t1) > 0`. Unfortunately the cast to the signed
	datatype requires knowledge about the timestamp datatype (`uint16_t` in the example), which
	is not directly available when using GPI tick datatypes. Much worse, the program would have to
	handle multiple alternative type definitions if the source code shall be platform-independent.

	To address this problem, the GPI provides explicit helper functions for timestamp comparisons.
	They are named `gpi_tick_compare_<clock-type>(a, b)` and return
	-1 if \a a is earlier than \a b (i.e., \a a - \a b < 0),
	+1 if \a a is later than \a b (i.e., \a a - \a b > 0),
	and 0 if \a a equals \a b.

 **************************************************************************************************/

#ifndef __GPI_CLOCKS_H__
#define __GPI_CLOCKS_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"       // GPI_PLATFORM_PATH
#include GPI_PLATFORM_PATH(clocks.h) // platform specific functionality

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

/// @name Clock Rates
//  The following definitions are platform-specific, but mandatory.
/// @{

/// @def GPI_FAST_CLOCK_RATE
/// @brief Clock frequency of fast clock in ticks per second.

/// @def GPI_SLOW_CLOCK_RATE
/// @brief Clock frequency of slow clock in ticks per second.

/// @def GPI_HYBRID_CLOCK_RATE
/// @brief Clock frequency of hybrid clock in ticks per second.

#ifdef __DOXYGEN__
  // provide dummy definitions if necessary to avoid incomplete documentation
  #ifndef GPI_FAST_CLOCK_RATE
    #define GPI_FAST_CLOCK_RATE
  #endif
  #ifndef GPI_SLOW_CLOCK_RATE
    #define GPI_SLOW_CLOCK_RATE
  #endif
  #ifndef GPI_HYBRID_CLOCK_RATE
    #define GPI_HYBRID_CLOCK_RATE
  #endif
#endif

/// @}

/// @name Clock Value Ranges
/// The following macros determine the value ranges of the different clock types (fast, slow, hyrid).
/// They mark the highest possible value, i.e., the value one tick before the clock value wraps
/// around to zero.
/// Note that these values can be smaller than the corresponding datatype's maxima (for example,
/// the tick datatype could be uint32_t while the clock is a 24 bit timer with
/// `GPI_TICK_..._MAX = 0xffffff`).
/// @todo Add equivalent macros for native datatypes
/// @{

/// @brief Maximum fast clock (extended) tick value.
#ifndef GPI_TICK_FAST_MAX
  #define GPI_TICK_FAST_MAX ((Gpi_Fast_Tick_Extended) (UINT64_C(0xFFFFFFFFFFFFFFFF)))
#endif

/// @brief Maximum slow clock (extended) tick value.
#ifndef GPI_TICK_SLOW_MAX
  #define GPI_TICK_SLOW_MAX ((Gpi_Slow_Tick_Extended) (UINT64_C(0xFFFFFFFFFFFFFFFF)))
#endif

/// @brief Maximum hybrid clock tick value.
#ifndef GPI_TICK_HYBRID_MAX
  #define GPI_TICK_HYBRID_MAX ((Gpi_Hybrid_Tick) (UINT64_C(0xFFFFFFFFFFFFFFFF)))
#endif

/// @}

/// @name Time Period to Clock Ticks Conversion Macros
/// The following macros can be used to convert time periods represented in seconds, milliseconds,
/// or microseconds to the corresponding tick values (i.e., translate to the selected clock's rate).
/// The macros implement careful rounding and overflow protection.
/// They are intended to be used with constant arguments.
/// @{

/// Convert microseconds to fast clock ticks.
#define GPI_TICK_US_TO_FAST(us) _GPI_TICK_T_TO_X(us, 1000000, FAST)

/// Convert milliseconds to fast clock ticks.
#define GPI_TICK_MS_TO_FAST(ms) _GPI_TICK_T_TO_X(ms, 1000, FAST)

/// Convert seconds to fast clock ticks.
#define GPI_TICK_S_TO_FAST(s)   _GPI_TICK_T_TO_X(s, 1, FAST)

/// @brief Convert milliseconds to fast clock ticks with second split.
/// @details
/// This macro can be used if \a ms is too large for GPI_TICK_MS_TO_FAST().
/// With GPI_TICK_MS_TO_FAST2(), the value is split into a seconds (\a ms / 1000) and a milliseconds
/// (\a ms % 1000) part and then converted separately. This allows for larger value ranges, but
/// the result may be less accurate than that from GPI_TICK_MS_TO_FAST().
#define GPI_TICK_MS_TO_FAST2(ms)                                                                   \
    (GPI_TICK_S_TO_FAST((ms) / 1000) + GPI_TICK_MS_TO_FAST((ms) % 1000))

/// @brief Convert microseconds to fast clock ticks with millisecond split.
/// @details
/// This macro can be used if \a us is too large for GPI_TICK_US_TO_FAST().
/// With GPI_TICK_US_TO_FAST2(), the value is split into a milliseconds (\a us / 1000) and a
/// microseconds (\a us % 1000) part and then converted separately. This allows for larger value
/// ranges, but the result may be less accurate than that from GPI_TICK_US_TO_FAST().
#define GPI_TICK_US_TO_FAST2(us)                                                                   \
    (GPI_TICK_MS_TO_FAST2((us) / 1000) + GPI_TICK_US_TO_FAST((us) % 1000))

/// Convert milliseconds to slow clock ticks.
#define GPI_TICK_MS_TO_SLOW(ms)   _GPI_TICK_T_TO_X(ms, 1000, SLOW)

/// Convert seconds to slow clock ticks.
#define GPI_TICK_S_TO_SLOW(s)     _GPI_TICK_T_TO_X(s, 1, SLOW)

/// Convert microseconds to hybrid clock ticks.
#define GPI_TICK_US_TO_HYBRID(us) _GPI_TICK_T_TO_X(us, 1000000, HYBRID)

/// Convert milliseconds to hybrid clock ticks.
#define GPI_TICK_MS_TO_HYBRID(ms) _GPI_TICK_T_TO_X(ms, 1000, HYBRID)

/// Convert seconds to hybrid clock ticks.
#define GPI_TICK_S_TO_HYBRID(s)   _GPI_TICK_T_TO_X(s, 1, HYBRID)

/// @brief Convert milliseconds to hybrid clock ticks with second split.
/// @details
/// This macro can be used if \a ms is too large for GPI_TICK_MS_TO_HYBRID().
/// With GPI_TICK_MS_TO_HYBRID2(), the value is split into a seconds (\a ms / 1000) and a milliseconds
/// (\a ms % 1000) part and then converted separately. This allows for larger value ranges, but
/// the result may be less accurate than that from GPI_TICK_MS_TO_HYBRID().
#define GPI_TICK_MS_TO_HYBRID2(ms)                                                                 \
    (GPI_TICK_S_TO_HYBRID((ms) / 1000) + GPI_TICK_MS_TO_HYBRID((ms) % 1000))

/// @brief Convert microseconds to hybrid clock ticks with millisecond split.
/// @details
/// This macro can be used if \a us is too large for GPI_TICK_US_TO_HYBRID().
/// With GPI_TICK_US_TO_HYBRID2(), the value is split into a milliseconds (\a us / 1000) and a
/// microseconds (\a us % 1000) part and then converted separately. This allows for larger value
/// ranges, but the result may be less accurate than that from GPI_TICK_US_TO_HYBRID().
#define GPI_TICK_US_TO_HYBRID2(us)                                                                 \
    (GPI_TICK_MS_TO_HYBRID2((us) / 1000) + GPI_TICK_US_TO_HYBRID((us) % 1000))

/// @}

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

#define _GPI_TICK_T_TO_X(x, m, t)                                                                  \
    (((GPI_##t##_CLOCK_RATE % m) ? (((x) * GPI_##t##_CLOCK_RATE) / m + ((m > 1) ? 1 : 0))          \
                                 : ((x) * (GPI_##t##_CLOCK_RATE / m))) +                           \
     ASSERT_CT_EVAL((x) <= (GPI_TICK_##t##_MAX / GPI_##t##_CLOCK_RATE) ||                          \
                            !(GPI_##t##_CLOCK_RATE % m),                                           \
                    GPI_TICK_TO_##t##_overflow))

// helper function for timestamp comparisons
// return value indicates a in relation to b: </> 0 : a is earlier/later than b (== 0 : a equals b)
#define _GPI_TICK_COMPARE_FUNCTION(name, type)                                                     \
    static inline                                                                                  \
            __attribute__((always_inline)) int_fast8_t gpi_tick_compare_##name(type a, type b)     \
    {                                                                                              \
        ASSERT_CT(sizeof(a) <= 8, gpi_tick_compare_##name##_overflow);                             \
        a -= b;                                                                                    \
        switch (sizeof(a))                                                                         \
        {                                                                                          \
            case 2: return ((int16_t) a < 0) ? -1 : !!(a);                                         \
            case 4: return ((int32_t) a < 0) ? -1 : !!(a);                                         \
            case 8: return ((int64_t) a < 0) ? -1 : !!(a);                                         \
            default: return 0; /* must not happen (catch with ASSERT_CT) */                        \
        }                                                                                          \
    }

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

/// @name Tick Datatypes.
/// See \ref gpi-clocks-datatypes for details.
/// @{

/// @typedef Gpi_Slow_Tick_Native
/// @brief Slow clock native datatype.

/// @typedef Gpi_Slow_Tick_Extended
/// @brief Slow clock extended datatype.

/// @typedef Gpi_Fast_Tick_Native
/// @brief Fast clock native datatype.

/// @typedef Gpi_Fast_Tick_Extended
/// @brief Fast clock extended datatype.

/// @typedef Gpi_Hybrid_Tick
/// @brief Hybrid clock datatype.

/// @struct Gpi_Hybrid_Reference
/// @brief Reference value that marks relationship between fast and hybrid clock.
/// @sa gpi_tick_hybrid_reference()

/// @}

//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif

/// @name Get Time Functions
/// @{

/// @brief Get current time (tick value) of slow clock with native datatype.
Gpi_Slow_Tick_Native      gpi_tick_slow_native(void);

/// @brief Get current time (tick value) of slow clock with extended datatype.
Gpi_Slow_Tick_Extended    gpi_tick_slow_extended(void);

// provide these functions if they would be helpful, decide later
//uint16_t					gpi_tick_slow_16();
//uint32_t					gpi_tick_slow_32();

/// @brief Get current time (tick value) of fast clock with native datatype.
Gpi_Fast_Tick_Native      gpi_tick_fast_native(void);

/// @brief Get current time (tick value) of fast clock with extended datatype.
Gpi_Fast_Tick_Extended    gpi_tick_fast_extended(void);

// provide these functions if they would be helpful (and if they are available), decide later
//uint16_t					gpi_tick_fast_16();
//uint32_t					gpi_tick_fast_32();
//uint64_t					gpi_tick_fast_64();

/// @brief Get current time (tick value) of hybrid clock.
Gpi_Hybrid_Tick           gpi_tick_hybrid(void);

/// @}

/// @name Timestamp Conversion Functions
/// @{

/// @brief Get reference value needed to compute relationship between fast and hybrid clock.
/// @details
/// The result contains a fast and a hybrid timestamp, which both belong to the same point in time.
/// They stem from the near past and can be used to compute the relationship for other timestamps
/// by evaluating the differences between the timestamps of interest and the reference timestamps.
Gpi_Hybrid_Reference      gpi_tick_hybrid_reference(void);

/// @brief Convert a fast tick value from the near past to hybrid ticks.
/// @details
/// This function can be used to convert a native fast clock timestamp to the corresponding
/// hybrid time. A typical use case is the conversion of a timestamp that has been captured
/// automatically in response to some hardware event (e.g., using timer capture functionality).
///
/// To work correctly, the function must be called not more than GPI_TICK_FAST_MAX ticks
/// after the fast timestamp has been captured. Otherwise, the fast tick datatype overflow
/// leads to a wrong interpretation and result.
///
/// @sa gpi_tick_hybrid_reference()
Gpi_Hybrid_Tick           gpi_tick_fast_to_hybrid(Gpi_Fast_Tick_Native fast_tick);

/// @brief Convert fast clock timestamp to microseconds.
/// @details
/// While the mathematical operation is rather simple, the GPI provides this explicit function
/// to ensure an efficient implementation. The latter is particularly important for log / trace
/// messages (which typically contain timestamps) and profiling purposes.
uint32_t                  gpi_tick_fast_to_us(Gpi_Fast_Tick_Extended ticks);

/// @brief Convert slow clock timestamp to microseconds.
/// @copydetails gpi_tick_fast_to_us()
uint32_t                  gpi_tick_slow_to_us(Gpi_Slow_Tick_Extended ticks);

/// @brief Convert hybrid clock timestamp to microseconds.
/// @copydetails gpi_tick_fast_to_us()
uint32_t                  gpi_tick_hybrid_to_us(Gpi_Hybrid_Tick ticks);

/// @}

/// @name Miscellaneous Functions

/// @brief Sleep \a ms milliseconds.
/// @details
/// The function is designed carefully to guarantee that the effective delay is *at least*
/// as long as specified, which is important if, for instance, the function is used to wait
/// for some critical time constant specified in a datasheet.
///
/// @sa gpi_micro_sleep()
void                      gpi_milli_sleep(uint16_t ms);

/// @brief Sleep \a us microseconds.
/// @details
/// The function is designed carefully to guarantee that the effective delay is *at least*
/// as long as specified, which is important if, for instance, the function is used to wait
/// for some critical time constant specified in a datasheet.
///
/// Compared to gpi_milli_sleep(), gpi_micro_sleep() is explicitly tuned to be fast
/// beyond the specified sleep period and to make the effective delay as accurate as possible.
///
/// @sa gpi_milli_sleep()
void                      gpi_micro_sleep(uint16_t us);

/// @}

/// @name Timestamp Comparison Functions
/// See \ref gpi-clocks-compare for details.
/// @{

/// @brief Test if \a a is earlier, equal, or later than \a b.
/// @details For details see \ref gpi-clocks-compare.
static inline int_fast8_t gpi_tick_compare_slow_native(Gpi_Slow_Tick_Native a,
                                                       Gpi_Slow_Tick_Native b);

/// @copydoc gpi_tick_compare_slow_native()
static inline int_fast8_t gpi_tick_compare_slow_extended(Gpi_Slow_Tick_Extended a,
                                                         Gpi_Slow_Tick_Extended b);

/// @copydoc gpi_tick_compare_slow_native()
static inline int_fast8_t gpi_tick_compare_fast_native(Gpi_Fast_Tick_Native a,
                                                       Gpi_Fast_Tick_Native b);

/// @copydoc gpi_tick_compare_slow_native()
static inline int_fast8_t gpi_tick_compare_fast_extended(Gpi_Fast_Tick_Extended a,
                                                         Gpi_Fast_Tick_Extended b);

/// @copydoc gpi_tick_compare_slow_native()
static inline int_fast8_t gpi_tick_compare_hybrid(Gpi_Hybrid_Tick a, Gpi_Hybrid_Tick b);

/// @}

#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

_GPI_TICK_COMPARE_FUNCTION(slow_native, Gpi_Slow_Tick_Native)
_GPI_TICK_COMPARE_FUNCTION(slow_extended, Gpi_Slow_Tick_Extended)
_GPI_TICK_COMPARE_FUNCTION(fast_native, Gpi_Fast_Tick_Native)
_GPI_TICK_COMPARE_FUNCTION(fast_extended, Gpi_Fast_Tick_Extended)
_GPI_TICK_COMPARE_FUNCTION(hybrid, Gpi_Hybrid_Tick)

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_CLOCKS_H__
