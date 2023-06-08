/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2021 - 2022, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					deflate.h
 *
 *	@brief					deflate-compatible compression routines
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

#ifndef __DEFLATE_H__
#define __DEFLATE_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include <stdlib.h>
#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// compression method descriptor
typedef struct Deflate_Method
{
	enum
	{
		NONE = 0,
		
		// C0 = no compression (just storage)
		C0_FIXED,			// uncoded blocks with 16-bit LEN fields
		C0_STREAM,			// coded blocks (think of C-strings with escape sequences)
		
		// C1 = symbol coding only (using code_ll, which is typically a Huffman code)
		C1,
		
		// C2 = duplicate string elimination + symbol coding (standard deflate).
		// different string search methods are optimized for different kinds of data
		C2_DIFFERENTIAL,
		
	}					mode;
	
	const uint16_t		*code_ll;
	const uint8_t		*clen_ll;
	const uint16_t		*code_dist;
	const uint8_t		*clen_dist;
	const uint8_t		*header;
	uint16_t			header_size;	// in bits (not bytes)
	
} Deflate_Method;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

// predefined compression method descriptors
extern const Deflate_Method		DEFLATE_FLUSH_;
extern const Deflate_Method		DEFLATE_C0_FIXED_;
extern const Deflate_Method		DEFLATE_C0_STREAM_;
extern const Deflate_Method		DEFLATE_C1_DIFF1_;
extern const Deflate_Method		DEFLATE_C2_DIFF0_;
extern const Deflate_Method		DEFLATE_C2_DIFF1_;
extern const Deflate_Method		DEFLATE_C2_DIFF2_;

// these values can be directly used as method parameter when calling deflate()
static const Deflate_Method * const		DEFLATE_FLUSH		= &DEFLATE_FLUSH_;
static const Deflate_Method * const		DEFLATE_C0_FIXED	= &DEFLATE_C0_FIXED_;
static const Deflate_Method * const		DEFLATE_C0_STREAM	= &DEFLATE_C0_STREAM_;
static const Deflate_Method * const		DEFLATE_C1_DIFF1	= &DEFLATE_C1_DIFF1_;
static const Deflate_Method * const		DEFLATE_C2_DIFF0	= &DEFLATE_C2_DIFF0_;
static const Deflate_Method * const		DEFLATE_C2_DIFF1	= &DEFLATE_C2_DIFF1_;
static const Deflate_Method * const		DEFLATE_C2_DIFF2	= &DEFLATE_C2_DIFF2_;
			
//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
	extern "C" {
#endif

// deflate input data
// call with dest = NULL to reset/init internal state (drops anything pending)
// call with method = NULL to continue open block
// call with method = DEFLATE_FLUSH to close open block and flush output buffer
size_t		deflate(
				void*					dest, 
				size_t					dest_size, 
				const void*				src, 
				size_t					len, 
				const Deflate_Method*	method,
				const void*				window, 
				size_t*					nwritten, 
				size_t*					nread);

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************



//**************************************************************************************************
//**************************************************************************************************

#endif // __DEFLATE_H__
