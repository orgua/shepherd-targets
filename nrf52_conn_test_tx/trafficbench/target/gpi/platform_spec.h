/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2018 - 2021, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/platform_spec.h
 *
 *	@brief					defines platform specific attributes and settings
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *	@author					Fabian Mager
 *
 ***************************************************************************************************

 	@details

	TODO

	@internal

	Intervals defined by <name> ... <name>_END are half open, i.e., <name>_END represents the
	first value outside the interval (it is the same concept as used with C++ STL containers).

	# Architecture Names
	
	There can be a huge variety of platforms, so it is important to choose macro names carefully.
	
	## Board Names
	
	Board names should (roughly) follow the scheme <vendor>_<board>. Here, 
	
		* <vendor> should be some unique vendor identification (can be abbreviated as long as it
		  is unique, e.g. using common vendor codes like TI (Texas Instruments), ST(M) (ST Micro) 
		  and the like). 
		 
		* <board> should be some *unique* board identification, e.g. a product number. 
		  Do not use informal names that are not unique or might change.

	This scheme should also be followed in case of custom boards, where <vendor> and <board>
	can be some	"less official" identifiers, but again they must be unique.

	In case of a "standard" board connected to a custom environment (e.g. with application specific
	GPIO connections) it is prefered to use the scheme <vendor>_<board>_<customization> with 
	<vendor> and <board> as above and <customization> identifying the application specific usage.
	If there is a need to distinguish such customizations, there should also be a PURE variant
	(i.e., <vendor>_<board>_PURE) that identifies the base board used in a stand-alone manner.

	It may be convenient to identify a family of boards from a different perspective, e.g.
	plug-in cards for a specific hardware system or from a functionality point of view. If such
	naming should be used, then it should not replace the <vendor>_<board>[_<customization>]
	baseline. Instead, names following a different taxonomy should be added as aliases refering
	to the standard names.
	
	Example:
	
		GPI_ARCH_BOARD_nRF_PCA10059
			<vendor> = nRF, <board> = PCA10059
			
		GPI_ARCH_BOARD_nRF_PCA10059_PURE
			nRF_PCA10059 used stand-alone
			
		GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB
			nRF_PCA10059 used as FlockLab target (with custom GPIO connections)
			
		GPI_ARCH_BOARD_FLOCKLAB_nRF5
			alias for nRF_PCA10059_FLOCKLAB
			Here, FLOCKLAB is used as a unique "vendor" code for FlockLab targets, while nRF5 
			is the board identifier. The latter is not just a simple name shot from the hip, 
			it is the name used to identify the board in FlockLab XML files, which can be 
			expected to be a unique identifier (in the context of FlockLab).

 **************************************************************************************************/

#ifndef __GPI_PLATFORM_SPEC_H__
#define __GPI_PLATFORM_SPEC_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/tools.h"		// STRINGIFY(), LSB(), ASSERT_CT()

#include <stdint.h>			// UINTxx_C()

// include project-specific setup file (if defined)
// NOTE: As a side effect, this "activates" GPI_SETUP_FILE in every file that includes platform_spec.h
// (i.e. almost everywhere), which is less error-prone than including it manually in every relevant place.
#ifdef GPI_SETUP_FILE
	#include STRINGIFY(GPI_SETUP_FILE)
#endif

//**************************************************************************************************
//***** Global Defines and Consts ******************************************************************

#define GPI_PLATFORM_PATH(file)				GPI_PLATFORM_PATH_2(GPI_PLATFORM_DIR, file)
#define GPI_PLATFORM_PATH_2(dir, file)		STRINGIFY(gpi/dir/file)

//**************************************************************************************************
// detect and adopt used platform specification method

// variant 1: GPI_ARCH_<attribute>_IS_<value>
// example:
//		#define GPI_ARCH_CORE_IS_MSP430
//		#define GPI_ARCH_DEVICE_IS_MSP430F16x
//		#define GPI_ARCH_BOARD_IS_TMOTE
//		#define GPI_ARCH_OS_IS_NONE
// This variant is simple, but relatively unsafe and error-prone.
// It is provided primarily as a fallback in case other methods cause problems for some reason.
//
#if (!defined(GPI_ARCH_PLATFORM) && !defined(GPI_ARCH_DEVICE))

	#define GPI_ARCH_IS_CORE(x)			defined(GPI_ARCH_CORE_IS_ ## x)
	#define GPI_ARCH_IS_DEVICE(x)		defined(GPI_ARCH_DEVICE_IS_ ## x)
	#define GPI_ARCH_IS_BOARD(x)		defined(GPI_ARCH_BOARD_IS_ ## x)
	#define GPI_ARCH_IS_OS(x)			defined(GPI_ARCH_OS_IS_ ## x)
	#define GPI_ARCH_IS_CRT(x)			defined(GPI_ARCH_CRT_IS_ ## x)
	#define GPI_ARCH_IS_SDK(x)			defined(GPI_ARCH_SDK_IS_ ## x)

// advanced schemes
#else

	// variant 2: GPI_ARCH_<attribute> = ...
	// example:
	//		#define GPI_ARCH_DEVICE		GPI_ARCH_DEVICE_MSP430F16x
	//		#define GPI_ARCH_BOARD		GPI_ARCH_BOARD_TMOTE
	//		#define GPI_ARCH_OS			GPI_ARCH_OS_NONE
	// This variant is experimental. Do not use it if not required.
	//
	#if (!defined(GPI_ARCH_PLATFORM))

		#define _GPI_ARCH_GET(field)			GPI_ARCH_ ## field
		#define _GPI_ARCH_ENCODE(field, x)		UINT32_C(x)

	// variant 3: GPI_ARCH_PLATFORM = ...
	// example:
	//		#define GPI_ARCH_PLATFORM	(GPI_ARCH_BOARD_TMOTE | GPI_ARCH_OS_NONE)
	// This is the preferred method (currently).
	//
	#else

		// information is encoded in a single 32 bit value

		// Software Platform / Runtime Environment (RTE)
		#define GPI_ARCH_OS_MASK				UINT32_C(0xF0000000)
		#define GPI_ARCH_CRT_MASK				UINT32_C(0x0E000000)
		#define GPI_ARCH_SDK_MASK				UINT32_C(0x01000000)

		// Hardware Platform
		#define GPI_ARCH_DEVICE_MASK			UINT32_C(0x00FFF000)
		#define GPI_ARCH_BOARD_MASK				UINT32_C(0x00FFF00F)

		#define GPI_ARCH_OS_SHIFT				28
		#define GPI_ARCH_CRT_SHIFT				25
		#define GPI_ARCH_SDK_SHIFT				24
		#define GPI_ARCH_DEVICE_SHIFT			12
		#define GPI_ARCH_BOARD_SHIFT			0
		//#define GPI_ARCH_<field>_SHIFT		LSB(GPI_ARCH_<field>_MASK)

		#define _GPI_ARCH_GET(field)			(GPI_ARCH_PLATFORM & GPI_ARCH_ ## field ## _MASK)
		#define _GPI_ARCH_ENCODE(field, x)		((UINT32_C(x) << GPI_ARCH_ ## field ## _SHIFT) & GPI_ARCH_ ## field ## _MASK)

	#endif

	// internal: test if attr lies inside interval
	// ATTENTION: Due to the half-open intervals, _END may lie outside the range of _MASK,
	// i.e., _END & _MASK could be 0. Hence, do not compare < _END, do <= _END - 1 instead.
	// NOTE: A single value version (without interval) could be provided easily too, but we do not need it.
	#define _GPI_ARCH_TEST_INTERVAL(field, attr, interval)	\
		((_GPI_ARCH_GET(field) >= GPI_ARCH_ ## attr ## _ ## interval) &&	\
		 (_GPI_ARCH_GET(field) <= (GPI_ARCH_ ## attr ## _ ## interval ## _END - _GPI_ARCH_ENCODE(field, 1))))

	// internal: test optional extra conditions provided by _COND
	#define _GPI_ARCH_TEST_EXTRA(...)			_GPI_ARCH_TEST_EXTRA_(__VA_ARGS__, 1)
	#define _GPI_ARCH_TEST_EXTRA_(a, b, ...)	(b)

	// internal: test interval and optional extra conditions
	// ATTENTION: preprocessor does not expand self-referential macros (also indirect self-reference),
	// so _COND has limited nesting capabilities and must be used with care
	#define _GPI_ARCH_IS_X1(field, attr, x)		_GPI_ARCH_TEST_INTERVAL(field, attr, x)
	#define _GPI_ARCH_IS_X2(field, attr, x)		\
		(_GPI_ARCH_TEST_INTERVAL(field, attr, x) && _GPI_ARCH_TEST_EXTRA(GPI_ARCH_ ## attr ## _ ## x ## _COND))

	#define GPI_ARCH_IS_CORE(x)				_GPI_ARCH_IS_X1(DEVICE, CORE, x)
//	#define GPI_ARCH_IS_DEVICE_FAMILY(x)	_GPI_ARCH_IS_X1(DEVICE, DEVICE_FAMILY, x)
	#define GPI_ARCH_IS_DEVICE(x)			_GPI_ARCH_IS_X1(DEVICE, DEVICE, x)
	#define GPI_ARCH_IS_BOARD(x)			_GPI_ARCH_IS_X1(BOARD, BOARD, x)
	#define GPI_ARCH_IS_OS(x)				_GPI_ARCH_IS_X1(OS, OS, x)
	#define GPI_ARCH_IS_CRT(x)				_GPI_ARCH_IS_X2(CRT, CRT, x)
	#define GPI_ARCH_IS_SDK(x)				_GPI_ARCH_IS_X1(SDK, SDK, x)

#endif

//**************************************************************************************************
//***** Platform Identifiers and Handling **********************************************************

// abbr. for conversions (for internal use only)
#define _GPI_ARCH_CORE(x)				_GPI_ARCH_ENCODE(DEVICE, x)
#define _GPI_ARCH_DEVICE(x)				_GPI_ARCH_ENCODE(DEVICE, x)
#define _GPI_ARCH_BOARD(x)				_GPI_ARCH_ENCODE(BOARD, x)
#define _GPI_ARCH_OS(x)					_GPI_ARCH_ENCODE(OS, x)
#define _GPI_ARCH_CRT(x)				_GPI_ARCH_ENCODE(CRT, x)
#define _GPI_ARCH_SDK(x)				_GPI_ARCH_ENCODE(SDK, x)

//**************************************************************************************************
// Runtime Environments (RTEs)

// operating systems
// NOTE: We distinguish operating systems as they have major influence on GPI implementation
// (hardware access, stdio, etc.). A specific OS may support multiple (hardware) platforms.
#define GPI_ARCH_OS_NONE						_GPI_ARCH_OS(0)
#define GPI_ARCH_OS_NONE_END					_GPI_ARCH_OS(1)
#define GPI_ARCH_OS_ANY							_GPI_ARCH_OS(1)
	#define GPI_ARCH_OS_FREERTOS					_GPI_ARCH_OS(1)
	#define GPI_ARCH_OS_FREERTOS_END				_GPI_ARCH_OS(2)
#define GPI_ARCH_OS_ANY_END						_GPI_ARCH_OS(16)

// C runtime libraries
// NOTE: We distinguish runtime libraries as they can have influence on GPI implementation (e.g. stdio).
// NOTE: CRTs are typically OS-dependent, but one OS can come with multiple CRT options
// (e.g. single-threaded vs. multi-threaded, device-specific subset of functions, etc.).
// Hence, distinguishing OSes only is not enough.
#define GPI_ARCH_CRT_ANY						_GPI_ARCH_CRT(0)

	// GENERIC is used for libraries that do not require any special handling (from GPI side).
	// Candidates are glibc, newlib, newlib-nano for instance.
	// NOTE: Typical examples for potential special handling are elementary stdio functions
	// like putchar(), getchar() etc. Their implementations may rely on non-standard internal
	// functions that must be provided by the system integrator (i.e., the GPI).
	#define GPI_ARCH_CRT_GENERIC					_GPI_ARCH_CRT(0)
	#define GPI_ARCH_CRT_GENERIC_END				_GPI_ARCH_CRT(1)

	// Typically the CRT is OS dependent (coming as part of the OS, or depending on OS == NONE
	// in case of bare metal CRTs). Hence, we can overlay the CRT codes if (and only if!) we ensure
	// that GPI_ARCH_IS_CRT() implicitly tests the OS. This is realized with additional _COND macros.
	// ATTENTION: For internal reasons, _COND macros must begin with 1, ... (they will not work otherwise).
	//#define GPI_ARCH_CRT_OS_SPEC					_GPI_ARCH_CRT(1)
	//#define GPI_ARCH_CRT_OS_NONE					_GPI_ARCH_CRT(1)
		#define GPI_ARCH_CRT_SEGGER1					_GPI_ARCH_CRT(1)
		#define GPI_ARCH_CRT_SEGGER1_END				_GPI_ARCH_CRT(2)
		#define GPI_ARCH_CRT_SEGGER1_COND				1, GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CORE(ARM)
			// aka. "Embedded Studio Library"
			// identification needed because of stdio implementation details (putchar()...)
			// NOTE: likely not ARM specific, but we inspected it only for ARM so far
		#define GPI_ARCH_CRT_SEGGER2					_GPI_ARCH_CRT(2)
		#define GPI_ARCH_CRT_SEGGER2_END				_GPI_ARCH_CRT(3)
		#define GPI_ARCH_CRT_SEGGER2_COND				1, GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CORE(ARM)
			// aka. "SEGGER", "SEGGER RTL", "SEGGER Runtime Library"
			// identification needed because of stdio implementation details (putchar()...)
			// NOTE: likely not ARM specific, but we inspected it only for ARM so far
	//#define GPI_ARCH_CRT_OS_NONE_END				_GPI_ARCH_CRT(7)
	//#define GPI_ARCH_CRT_OS_SPEC_END				_GPI_ARCH_CRT(7)

	//#define GPI_ARCH_CRT_DEVICE_SPEC				_GPI_ARCH_CRT(TODO)
	//#define GPI_ARCH_CRT_DEVICE_SPEC_END			_GPI_ARCH_CRT(TODO)

#define GPI_ARCH_CRT_ANY_END					_GPI_ARCH_CRT(7)

// vendor SDK
// NOTE: We distinguish SDK yes/no as this can have influence on GPI implementation
// (e.g. bare metal hardware access vs. using SDK functions).
// NOTE: Differentiating SDKs and other middleware could easily get messy: There could be
// a huge variety of (potentially very platform-specific) variants, and trying to handle them
// in a platform-independent GPI fashion may not make sense. For this reason we distinguish
// only one option that appears often in embedded programming: The usage of some vendor-provided SDK.
// Other (maybe more fine-grained) options may be implemented in a platform-dependent manner.
// Always remember that we have no need to regard RTE components in GPI_ARCH_...
// that have no influence on GPI implementation (app can distinguish them itself if necessary).
// NOTE: Some vendor SDKs contain support for multiple OSes (incl. OS == NONE). Hence, it is
// meaningful to mark SDK usage independent of OS/CRT.
#define GPI_ARCH_SDK_NONE						_GPI_ARCH_SDK(0)
#define GPI_ARCH_SDK_NONE_END					_GPI_ARCH_SDK(1)
#define GPI_ARCH_SDK_VENDOR						_GPI_ARCH_SDK(1)
#define GPI_ARCH_SDK_VENDOR_END					_GPI_ARCH_SDK(2)

// It may be advantageous to combine OS, CRT, and SDK settings to common runtime environments
// and introduce GPI_ARCH_RTE_... macros. However, this seems likely platform-specific, so the
// place to provide such macros may be in specific GPI platform branches.

//**************************************************************************************************
// Texas Instruments MSP430
// see here for part numbering scheme:
// http://www.ti-msp430.com/en/overview/naming-rules-0002.html
// https://en.wikipedia.org/wiki/TI_MSP430#MSP430_part_numbering

#define GPI_ARCH_CORE_MSP430					_GPI_ARCH_CORE(1)		// don't use 0 as a valid value
#define GPI_ARCH_CORE_MSP430_END				(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_CORE(99))	// = 100

// generation 0
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x0xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE( 0))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x0xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(10))

// generation 1
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x1xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(10))
#define GPI_ARCH_DEVICE_MSP430x1xx				(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(10))
	#define GPI_ARCH_DEVICE_MSP430F15x				(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(15))
	#define GPI_ARCH_DEVICE_MSP430F15x_END			(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(16))
	#define GPI_ARCH_DEVICE_MSP430F16x				(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(16))
	#define GPI_ARCH_DEVICE_MSP430F16x_END			(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(17))
#define GPI_ARCH_DEVICE_MSP430x1xx_END			(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(20))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x1xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(20))

// generation 1 boards
#define GPI_ARCH_BOARD_TMOTE					(GPI_ARCH_DEVICE_MSP430F16x + _GPI_ARCH_BOARD(1))
	#define GPI_ARCH_BOARD_TMOTE_PURE				(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(0))
	#define GPI_ARCH_BOARD_TMOTE_PURE_END			(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(1))
	#define GPI_ARCH_BOARD_TMOTE_FLOCKLAB			(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(1))
	#define GPI_ARCH_BOARD_TMOTE_FLOCKLAB_END		(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(2))
	#define GPI_ARCH_BOARD_TMOTE_INDRIYA			(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(2))
	#define GPI_ARCH_BOARD_TMOTE_INDRIYA_END		(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(3))
#define GPI_ARCH_BOARD_TMOTE_END				(GPI_ARCH_BOARD_TMOTE + _GPI_ARCH_BOARD(3))

// ...
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x2xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(20))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x2xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(30))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x3xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(30))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x3xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(40))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x4xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(40))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x4xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(50))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x5xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(50))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x5xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(60))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x6xx		(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(60))
//#define GPI_ARCH_DEVICE_FAMILY_MSP430x6xx_END	(GPI_ARCH_CORE_MSP430 + _GPI_ARCH_DEVICE(70))

#if (MSP430 || __MSP430__)

	// ATTENTION: the macro MSP430 breaks things like GPI_ARCH_IS_CORE(MSP430),
	// therefore we undefine it here (in favor of __MSP430__)
	#undef MSP430
	#ifndef __MSP430__
		#define __MSP430__
	#endif

	#if !GPI_ARCH_IS_CORE(MSP430)
		#warning GPI_ARCH_PLATFORM not specified or mismatch; assuming GPI_ARCH_CORE_IS_MSP430
		#define GPI_ARCH_CORE_IS_MSP430
	#endif

	#if GPI_ARCH_IS_BOARD(TMOTE)
		#define GPI_PLATFORM_DIR	msp430/tmote
	#else
		#define GPI_PLATFORM_DIR	msp430/msp430_common
	#endif

	#define VA_SIZE_GRANULARITY		2

	// safety-check
	ASSERT_CT_STATIC(ALIGNMENT == 2, alignment_mismatch);

#elif GPI_ARCH_IS_CORE(MSP430)
	#error platform mismatch
#endif

//**************************************************************************************************
// ARM

#define GPI_ARCH_CORE_ARM					GPI_ARCH_CORE_MSP430_END
#define GPI_ARCH_CORE_ARM_END				(GPI_ARCH_CORE_ARM + _GPI_ARCH_CORE(1000))

// ARM architectures
// ARMv1 ... ARMv5: unsupported (obsolete)

// ARMv6 (e.g. Cortex-M0(+))
#define GPI_ARCH_CORE_ARMv6					(GPI_ARCH_CORE_ARM   + _GPI_ARCH_CORE(  0))
	#define GPI_ARCH_CORE_ARM_M0				(GPI_ARCH_CORE_ARMv6 + _GPI_ARCH_CORE(  0))
	#define GPI_ARCH_CORE_ARM_M0_END			(GPI_ARCH_CORE_ARMv6 + _GPI_ARCH_CORE(100))
#define GPI_ARCH_CORE_ARMv6_END				(GPI_ARCH_CORE_ARMv6 + _GPI_ARCH_CORE(100))

// ARMv7
// ARMv7-M = microcontroller profile  (e.g. Cortex-M3, Cortex-M4)
// ARMv7E-M = ARMv7-M + SIMD instructions (-> Cortex-M4)
// ARMv7-R = realtime profile (e.g. Cortex-R4)
// ARMv7-A = application profile (e.g. Cortex-A8)
#define GPI_ARCH_CORE_ARMv7					(GPI_ARCH_CORE_ARMv6_END)
	#define GPI_ARCH_CORE_ARMv7M				(GPI_ARCH_CORE_ARMv7  + _GPI_ARCH_CORE(  0))
		#define GPI_ARCH_CORE_ARM_M3				(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(  0))
		#define GPI_ARCH_CORE_ARM_M3_END			(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(100))
		#define GPI_ARCH_CORE_ARM_M4				(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(100))
			#define GPI_ARCH_CORE_ARM_M4F				(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(150))	// incl. FPU
			#define GPI_ARCH_CORE_ARM_M4F_END			(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(200))
		#define GPI_ARCH_CORE_ARM_M4_END			(GPI_ARCH_CORE_ARMv7M + _GPI_ARCH_CORE(200))
	#define GPI_ARCH_CORE_ARMv7M_END			(GPI_ARCH_CORE_ARMv7  + _GPI_ARCH_CORE(200))
	#define GPI_ARCH_CORE_ARMv7A				(GPI_ARCH_CORE_ARMv7M_END + _GPI_ARCH_CORE(0))
	#define GPI_ARCH_CORE_ARMv7A_END			(GPI_ARCH_CORE_ARMv7M_END + _GPI_ARCH_CORE(1))
	#define GPI_ARCH_CORE_ARMv7R				(GPI_ARCH_CORE_ARMv7M_END + _GPI_ARCH_CORE(1))
	#define GPI_ARCH_CORE_ARMv7R_END			(GPI_ARCH_CORE_ARMv7M_END + _GPI_ARCH_CORE(2))
#define GPI_ARCH_CORE_ARMv7_END				(GPI_ARCH_CORE_ARMv7  + _GPI_ARCH_CORE(202))

// ARM devices and boards
// Typically we use the following format: GPI_ARCH_BOARD_<vendor>_<product-code>

// Nordic Semiconductor nRF52840
#define GPI_ARCH_DEVICE_nRF52840				(GPI_ARCH_CORE_ARM_M4F + _GPI_ARCH_DEVICE(0))
#define GPI_ARCH_DEVICE_nRF52840_END			(GPI_ARCH_CORE_ARM_M4F + _GPI_ARCH_DEVICE(1))

// NOTE: PCA... is the reliable way to refer to a specific Nordic board. Names like nRF52840DK
// stand for kits (board + accessories) and may change.
#define GPI_ARCH_BOARD_nRF_PCA10056					(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(1))		// = nRF52840 DK
#define GPI_ARCH_BOARD_nRF_PCA10056_END				(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(2))
#define GPI_ARCH_BOARD_nRF_PCA10059					(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(2))		// = nRF52840 USB Dongle
	#define GPI_ARCH_BOARD_nRF_PCA10059_PURE			(GPI_ARCH_BOARD_nRF_PCA10059 + _GPI_ARCH_BOARD(0))
	#define GPI_ARCH_BOARD_nRF_PCA10059_PURE_END		(GPI_ARCH_BOARD_nRF_PCA10059 + _GPI_ARCH_BOARD(1))
	#define GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB		(GPI_ARCH_BOARD_nRF_PCA10059 + _GPI_ARCH_BOARD(1))	// = PCA10059 FlockLab target
	#define GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB_END	(GPI_ARCH_BOARD_nRF_PCA10059 + _GPI_ARCH_BOARD(2))
	#define GPI_ARCH_BOARD_FLOCKLAB_nRF5				 GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB			// alias for FlockLab oriented naming
	#define GPI_ARCH_BOARD_FLOCKLAB_nRF5_END			 GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB_END
	// GPI_ARCH_BOARD_nRF5_FLOCKLAB is deprecated, use GPI_ARCH_BOARD_FLOCKLAB_nRF5 instead
	// (for reasons see comments about board names at the beginning of this file)
	//#define GPI_ARCH_BOARD_nRF5_FLOCKLAB				 GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB
	//#define GPI_ARCH_BOARD_nRF5_FLOCKLAB_END			 GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB_END
#define GPI_ARCH_BOARD_nRF_PCA10059_END				(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(4))
#define GPI_ARCH_BOARD_RIGADO_BMD340				(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(4))
	#define GPI_ARCH_BOARD_TUDNES_DPP2COM				(GPI_ARCH_BOARD_RIGADO_BMD340 + _GPI_ARCH_BOARD(0))
	#define GPI_ARCH_BOARD_TUDNES_DPP2COM_END			(GPI_ARCH_BOARD_RIGADO_BMD340 + _GPI_ARCH_BOARD(1))
#define GPI_ARCH_BOARD_RIGADO_BMD340_END			(GPI_ARCH_DEVICE_nRF52840 + _GPI_ARCH_BOARD(5))

#if (__ARM_ARCH)

	#if !GPI_ARCH_IS_CORE(ARM)
		#warning GPI_ARCH_PLATFORM not specified or mismatch; assuming GPI_ARCH_CORE_IS_ARM
		#define GPI_ARCH_CORE_IS_ARM
	#endif

	#if GPI_ARCH_IS_BOARD(nRF_PCA10056)
		#define GPI_PLATFORM_DIR	arm/nordic/pca10056
	#elif GPI_ARCH_IS_BOARD(nRF_PCA10059)
		#define GPI_PLATFORM_DIR	arm/nordic/pca10059
	#elif GPI_ARCH_IS_BOARD(TUDNES_DPP2COM)
		#define GPI_PLATFORM_DIR	arm/nordic/dpp2com
	#else
		#error unknown board
//		#define GPI_PLATFORM_DIR	arm/TODO
	#endif

	#if __ARM_32BIT_STATE

		// ATTENTION: VA_SIZE handling on 32-bit ARM is tricky for two reasons:
		// 1) While the granularity is 4, the alignment is defined as 8.
		// 2) Variadic arguments of type float are casted to double.
		// (defined in ABI specification, document ARM IHI 0042F)
		// These definitions make exact size determination complicated. As a compromise, we set
		// VA_SIZE_GRANULARITY to 8, leading to overestimated results. This wastes a bit of memory
		// (in some sense, e.g., size checks may fail although there is enough space), but it is
		// more safe than the other way around. If memory is an issue then VA_SIZE_GRANULARITY can
		// be set to 4, but with adequate care regarding the mentioned points (e.g., it is safe if
		// the program never uses floating point or 64-bit values as variadic arguments).
		#ifdef VA_SIZE_GRANULARITY
			#if ((VA_SIZE_GRANULARITY < 4) || (VA_SIZE_GRANULARITY & 3))
				#error VA_SIZE_GRANULARITY is invalid
			#endif
		#else
			#define VA_SIZE_GRANULARITY		8
		#endif

		// safety-check
		ASSERT_CT_STATIC(ALIGNMENT == 8, alignment_mismatch);

	#else

		#error unsupported architecture
		// TODO: add support for 64 bit cores

	#endif

#elif GPI_ARCH_IS_CORE(ARM)
	#error platform mismatch
#endif

//**************************************************************************************************
// future architectures

#define GPI_ARCH_CORE_TODO					GPI_ARCH_CORE_ARM_END
#define GPI_ARCH_CORE_TODO_END				(GPI_ARCH_CORE_TODO + _GPI_ARCH_CORE(100))

//**************************************************************************************************
//***** RTE Auto Detection *************************************************************************

// try to detect runtime environment if not fully specified
// NOTE: This feature will not always be able to "guess" everything relevant (in a compatible way,
// e.g. without including header files that are not present in every situation). It is thought
// more as a helping hand for the developer. For this reason, we throw warnings in case we
// adapt something to support the developer in making the right settings explicitly.
// We provide GPI_ARCH_RTE_AUTO to enforce the other way, but consider this as incomplete
// and use it with care.

#if GPI_ARCH_RTE_AUTO
	#define _GPI_ARCH_RTE_AUTO_WARN(x)
#else
	#define _GPI_ARCH_RTE_AUTO_WARN(...)	_GPI_ARCH_RTE_AUTO_WARN_1(	\
		GPI RTE detection: __VA_ARGS__ (please update GPI_ARCH_PLATFORM setting))
	#define _GPI_ARCH_RTE_AUTO_WARN_1(...)	_GPI_ARCH_RTE_AUTO_WARN_2(#__VA_ARGS__)
	#define _GPI_ARCH_RTE_AUTO_WARN_2(x)	_GPI_ARCH_RTE_AUTO_WARN_3(GCC warning #x)
	#define _GPI_ARCH_RTE_AUTO_WARN_3(x)	_Pragma(#x)
#endif

#if (GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(GENERIC))

	#if (GPI_ARCH_IS_CORE(ARM))

		// detect SEGGER RTL

		// older "Embedded Studio" variant
		#include <stdio.h>						// -> __PRINTF_TAG_PTR_DEFINED
		#ifdef __PRINTF_TAG_PTR_DEFINED

			_GPI_ARCH_RTE_AUTO_WARN(changed CRT to SEGGER1)

			#ifndef _GPI_ARCH_GET				// spec. method 1 (see above)
				#undef GPI_ARCH_CRT_IS_GENERIC
				#define GPI_ARCH_CRT_IS_SEGGER1
			#elif !defined(GPI_ARCH_PLATFORM)	// spec. method 2 (see above)
				#undef GPI_ARCH_CRT
				#define GPI_ARCH_CRT	GPI_ARCH_CRT_SEGGER1
			#else								// spec. method 3 (see above)
				#undef _GPI_ARCH_GET
				#define _GPI_ARCH_GET(field)	\
					((GPI_ARCH_PLATFORM & ~GPI_ARCH_CRT_MASK | GPI_ARCH_CRT_SEGGER1) & GPI_ARCH_ ## field ## _MASK)
			#endif

		// SEGGER RTL (available since SES 5.10, version 2.4.2 in SES 5.42)
		// https://studio.segger.com/arm_segger_studio_release_notes.htm
		#elif (__SEGGER_RTL_VERSION >= 24201)

			_GPI_ARCH_RTE_AUTO_WARN(changed CRT to SEGGER2)

			#ifndef _GPI_ARCH_GET				// spec. method 1 (see above)
				#undef GPI_ARCH_CRT_IS_GENERIC
				#define GPI_ARCH_CRT_IS_SEGGER2
			#elif !defined(GPI_ARCH_PLATFORM)	// spec. method 2 (see above)
				#undef GPI_ARCH_CRT
				#define GPI_ARCH_CRT	GPI_ARCH_CRT_SEGGER2
			#else								// spec. method 3 (see above)
				#undef _GPI_ARCH_GET
				#define _GPI_ARCH_GET(field)	\
					((GPI_ARCH_PLATFORM & ~GPI_ARCH_CRT_MASK | GPI_ARCH_CRT_SEGGER2) & GPI_ARCH_ ## field ## _MASK)
			#endif

		#endif

	#endif

#endif	// GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(GENERIC)

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



//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_PLATFORM_SPEC_H__
