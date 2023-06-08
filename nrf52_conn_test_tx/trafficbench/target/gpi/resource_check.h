/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2021, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/resource_check.h
 *
 *	@brief					helper macros for avoiding resource conflicts
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details
	
	Usage (in a nutshell):
	
		* declare resources with GPI_RESOURCE_DECLARE(<type> [, <numbers>]);
		
		* reserve resources with GPI_RESOURCE_RESERVE(<type> [, <numbers>]);
		
		* if a resource is used by multiple partners, reserve it with GPI_RESOURCE_RESERVE_SHARED()
		  (instead of GPI_RESOURCE_RESERVE()) at each partner
		  
		* Syntactically, <type> must be a valid identifier. <numbers> is a comma-separated list of
		  up to five numbers. If <numbers> is provided, then it holds:
		  
			* preprocessor macros in <numbers> are expanded
			
			* each <number> must resolve to a literal number that can be part of an identifier
			  (may be relaxed in the future)

	Background

	Basic idea: Each software module marks used (occupied) hardware resources. Based on these 
	markers, automatic checks ensure that there are no resource conflicts between different 
	software modules. Specifically,	if two or more modules mark the same resource, the check 
	generates some kind of error (e.g. compilation error, linker error, runtime assertion).

	To avoid undetected conflicts due to typos, existing resources should be explicitly declared.
	Resources are identified by the combination of <type> and up to five <numbers>, where <numbers>
	can be left out if <type> provides a unique identification on its own. The separate handling
	of <type> and <numbers> (instead of just writing <type>_<numbers>) enables macro expansion
	on <numbers>, which has some advantages in practice.

	Deciding about what is a single resource, i.e. the granularity of declarations, is a difficult 
	issue in general. Coarse declarations hinder usage of subcomponents in different modules, 
	while fine-grained declarations hardly cover higher-level dependencies. For example, think
	of a hardware timer unit with multiple capture/compare (CC) blocks. Defining the whole timer 
	as one resource hinders usage of individual CC blocks in different modules. On the other hand, 
	defining the CC blocks as individual resources hides the fact that all of them depend on the
	same counter, prescaler, etc.

	GPI_RESOURCE_RESERVE_SHARED() can be used to handle such interrelations in a smart way.
	The macro allows to mark a resource in multiple modules, but triggers an error if the same
	resource is marked as non-SHARED in any module. Semantically, GPI_RESOURCE_RESERVE_SHARED
	should express that the specific usage of the resource is compatible with the usage of the
	same resource at other places where it has been reserved SHARED (it states that other uses
	are explicitly considered). 
	With this definition in mind, the timer example could be handled as follows:
	* Declare resources for both, the timer as a whole and the CC blocks.
	* Reserve CC blocks with GPI_RESOURCE_RESERVE(), i.e. non-SHARED.
	* Additionally, reserve the timer with GPI_RESOURCE_RESERVE_SHARED().
	The last point implies that it has been checked that all places where the timer is used do
	not disturb each other. If anybody adds a new software module and tries to reserve the same
	timer with GPI_RESOURCE_RESERVE(), then an error appears, telling the author that the timer
	is already in use. The author can then check if the new module uses the timer in a compatible
	way. If so, she can replace GPI_RESOURCE_RESERVE by GPI_RESOURCE_RESERVE_SHARED in the new 
	module, otherwise she must not use this timer instance.

 **************************************************************************************************/

#ifndef __GPI_RESOURCE_CHECK_H__
#define __GPI_RESOURCE_CHECK_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/tools.h"		// STRINGIFY(), CONCAT()

#include "gpi/platform_spec.h"
#include GPI_PLATFORM_PATH(resource_check_pre_include.h)

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************

// settings

// implement resource check yes/no
#ifndef GPI_RESOURCE_CHECK
	#define GPI_RESOURCE_CHECK					0
#endif

// test if reserved resources have been declared
// This is useful to avoid typos, which could lead to undetected conflicts.
// Settings:
//	0: no check, resources need not be explicitly declared
//	1: check performed by compiler
//		DECLARE() must be visible to RESERVE() (e.g. from header file).
//	2: check performed by linker
//		DECLARE() need not be visible to RESERVE().
//		section GPI_RESOURCE_CHECK_SECTION (see below) must be kept for sure to work reliable
//		(e.g. using linker flags like --keep-section=GPI_RESOURCE_CHECK_SECTION)
#ifndef GPI_RESOURCE_CHECK_DECLARATION
	#define GPI_RESOURCE_CHECK_DECLARATION		2
#endif

// With GPI_RESOURCE_CHECK_DECLARATION = 2 it is important to ensure that resource reservations
// do not get optimized away by the linker. To support this, we put the relevant output in a 
// special section, which can be explicitly marked as "keep" in the build environment.
// Background: If a reservation is optimized away, then the linker will not try to resolve
// the contained reference to the resource declaration. That is to say, it will not be checked
// if the referenced resource exists (or if the reservation contains a typo, for instance).
#ifndef GPI_RESOURCE_CHECK_SECTION
	#define GPI_RESOURCE_CHECK_SECTION			.rodata.gpi_resource_check
#endif

//**************************************************************************************************
// resource reservation commands

// Resource instances are identified by the combination of a type and up to five numbers.
// The numbers are optional at the public interface. Internally we add X zeros to the argument
// list, which effectively provides a default value of 0 for the first X numbers.
// (Maybe this feature becomes important for future enhancements.)
// The following macros implement the default values and combine the type and all numbers
// into one composite identifier for each resource.

// ATTENTION: The most simple implementation is
//
//		#define GPI_RESOURCE_<operation>(...)	_GPI_RESOURCE_<operation>(__VA_ARGS__, 0)
//
// This variant has a significant drawback: If one of the arguments matches a macro name,
// then this macro gets expanded in the intermediate step. This is a critical issue because
// it is not unlikely that chosen type names interfere with definitions from other
// hardware-related header files (e.g. CMSIS <device.h> in case of ARM-based platforms).
// Indeed, using the same names may be intentional.
// For this reason, we use the following concept, which avoids macro expansion:
//
//		#define GPI_RESOURCE_<operation>(...)	_HELPER(dummy, ## __VA_ARGS__, 0)
//		#define _HELPER(dummy, a1, a2, ...)		_GPI_RESOURCE_<operation>(_ ## a1, a2)
//
// Here, the concatenation operator avoids macro expansion. Note that it is used in a very
// special (and GNU specific) way in the first line, and it decorates a1 with a preceding
// underscore in the second line (which is not critical in our use case).
// Instead of wasting the dummy argument, we use it to select the operation, which finally
// leads to the code below. Note how _GPI_RESOURCE_X5() "dynamically" assembles a macro call,
// which gets evaluated by successive macro expansion.

#define _GPI_RESOURCE_X(op, id, ...)			_GPI_RESOURCE_X1(op, _ ## id, __VA_ARGS__)
#define _GPI_RESOURCE_X1(op, id, n1, ...)		_GPI_RESOURCE_X2(op, id ## _ ## n1, __VA_ARGS__)
#define _GPI_RESOURCE_X2(op, id, n2, ...)		_GPI_RESOURCE_X3(op, id ## _ ## n2, __VA_ARGS__)
#define _GPI_RESOURCE_X3(op, id, n3, ...)		_GPI_RESOURCE_X4(op, id ## _ ## n3, __VA_ARGS__)
#define _GPI_RESOURCE_X4(op, id, n4, ...)		_GPI_RESOURCE_X5(op, id ## _ ## n4, __VA_ARGS__)
#define _GPI_RESOURCE_X5(op, id, n5, ...)		_GPI_RESOURCE_ ## op (id ## _ ## n5)

#define GPI_RESOURCE_DECLARE(...)				_GPI_RESOURCE_X(DECLARE, ## __VA_ARGS__, 0)
#define GPI_RESOURCE_RESERVE(...)				_GPI_RESOURCE_X(RESERVE, ## __VA_ARGS__, 0)
#define GPI_RESOURCE_RESERVE_SHARED(...)		_GPI_RESOURCE_X(RESERVE_SHARED, ## __VA_ARGS__, 0)

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

#define _GPI_RESOURCE_SECTION_DECL	 __attribute__((section(STRINGIFY(GPI_RESOURCE_CHECK_SECTION))))

#if !GPI_RESOURCE_CHECK

	// use a typedef to bind the semicolon
	// ATTENTION: do not use while (0), as macros are typically used on file scope
	#define _GPI_RESOURCE_DECLARE(...)				typedef int Gpi_Resource_Dummy_Type
	#define _GPI_RESOURCE_RESERVE(...)				typedef int Gpi_Resource_Dummy_Type
	#define _GPI_RESOURCE_RESERVE_SHARED(...)		typedef int Gpi_Resource_Dummy_Type

#elif (1 == GPI_RESOURCE_CHECK_DECLARATION)

	#define _GPI_RESOURCE_DECLARE(id)					\
		typedef char gpi_resource_declaration_ ## id

	// We use a special common variable to (a) enable the coexistence of multiple SHARED
	// reservations, but (b) prohibit mixed SHARED and non-SHARED reservations.
	// The additional typedef is necessary to catch the case of some resource being reserved 
	// first SHARED and afterwards non-SHARED in the same file while not being reserved
	// anywhere else. In this case, the variable declaration in RESERVE() overwrites the
	// attributes of the declaration in RESERVE_SHARED(), which avoids the common/non-common
	// conflict. We catch this case with a type conflict in the additional typedef
	// (which has no effect for reservations in different modules).
	// NOTE: Catching the special case discussed above is important when using gpi.c (for instance).
	//
	// Background: (global) common variables can be defined multiple times (with the same name),
	// where all definitions refer to the same instance in memory (this is resolved by the linker).
	// Doing this with normal (non-common) variables would throw compiler or linker errors
	// (if the linker is configured to do so, which is typically the case in embedded development).
	// Note that this concept is different from weak symbols.
	
	#define _GPI_RESOURCE_RESERVE_SHARED(id)					\
		/* global marker variable, declared as common */		\
		const gpi_resource_declaration_ ## id __attribute__((common))	\
			gpi_resource_reservation_ ## id;					\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef char gpi_resource_reservation_ ## id ## _
	
	#define _GPI_RESOURCE_RESERVE(id)							\
		/* global marker variable, declared as non-common */	\
		const gpi_resource_declaration_ ## id _GPI_RESOURCE_SECTION_DECL	\
			gpi_resource_reservation_ ## id = 1;				\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef long gpi_resource_reservation_ ## id ## _
	
#elif (2 == GPI_RESOURCE_CHECK_DECLARATION)

	#define _GPI_RESOURCE_DECLARE(id)							\
		const char __attribute__((common)) gpi_resource_declaration_ ## id [0]

	// NOTE: In the implementation below, each reservation stores a pointer to the corresponding
	// declaration. To save memory, we could store only one byte instead of the whole pointer.
	// However, we save the effort for two reasons:
	// (1) Storing the full pointer simplifies debugging (in case this is necessary).
	// (2) We assume that memory consumption is not an issue (typically). On one hand,
	//     resource checks do not use much memory (and only flash ROM if configured right),
	//     on the other hand they can be deactivated in the release build.
		
	#define _GPI_RESOURCE_RESERVE_SHARED(id)					\
		extern const char gpi_resource_declaration_ ## id [];	\
		/* local marker, throws error if resource declaration is missing */	\
		static const char * const _GPI_RESOURCE_SECTION_DECL	\
			CONCAT(gpi_resource_reservation_ ## id ## _ref, __COUNTER__) =	\
			&gpi_resource_declaration_ ## id [0];				\
		/* global marker variable, declared as common */		\
		const char * const __attribute__((common))				\
			gpi_resource_reservation_ ## id;					\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef char gpi_resource_reservation_ ## id ## _
	
	#define _GPI_RESOURCE_RESERVE(id)							\
		extern const char gpi_resource_declaration_ ## id [];	\
		/* global marker variable, declared as non-common */	\
		const char * const _GPI_RESOURCE_SECTION_DECL			\
			gpi_resource_reservation_ ## id =					\
			&gpi_resource_declaration_ ## id [0];				\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef long gpi_resource_reservation_ ## id ## _

#else

	#define _GPI_RESOURCE_DECLARE(id)		typedef int Gpi_Resource_Dummy_Type

	#define _GPI_RESOURCE_RESERVE_SHARED(id)					\
		/* global marker variable, declared as common */		\
		const char __attribute__((common))						\
			gpi_resource_reservation_ ## id;					\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef char gpi_resource_reservation_ ## id ## _
	
	#define _GPI_RESOURCE_RESERVE(id)							\
		/* global marker variable, declared as non-common */	\
		const char _GPI_RESOURCE_SECTION_DECL					\
			gpi_resource_reservation_ ## id = 1;				\
		/* additional typedef used to catch SHARED and non-SHARED in same module */	\
		typedef long gpi_resource_reservation_ ## id ## _
	
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



//**************************************************************************************************
//***** Includes ***********************************************************************************

#include GPI_PLATFORM_PATH(resource_check.h)

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_RESOURCE_CHECK_H__
