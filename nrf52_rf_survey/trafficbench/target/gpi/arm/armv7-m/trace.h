/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2019 - 2022, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/armv7-m/trace.h
 *
 *	@brief					ARM specific TRACE settings
 *
 *	@version				$Id: 9537b7ee70bb1f4b7c1c4ecd55938f0b1204108a $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARMv7M_TRACE_H__
#define __GPI_ARMv7M_TRACE_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/clocks.h"
#include "gpi/tools.h"

#include <stdint.h>

//**************************************************************************************************
//***** Global Defines and Consts ******************************************************************


//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// needed to provide compile-time assertions within TRACE macros
#define GPI_TRACE_VA_SIZE_MAX FIELD_SIZEOF(Gpi_Trace_Msg, var_args)

// size of TRACE buffer (number of elements)
#ifndef GPI_TRACE_BUFFER_NUM_ENTRIES
  #define GPI_TRACE_BUFFER_NUM_ENTRIES 16
#endif

// TRACE buffer entry size
// implicitly determines number/size of possible var_args when using GPI_TRACE_MSG() and
// GPI_TRACE_RETURN_MSG() (and their ..._FAST() variants)
#ifndef GPI_TRACE_BUFFER_ENTRY_SIZE
  #define GPI_TRACE_BUFFER_ENTRY_SIZE 64
#endif

// select whether TRACE functions internally use a DSR (delayed service routine)
// pro: better timing when using TRACE on interrupt level
// con: uses an interrupt (interrupts must be enabled, "asynchronous" execution)
#ifndef GPI_TRACE_USE_DSR
  #define GPI_TRACE_USE_DSR 0
#endif

// select whether TRACE buffer overflow detection is done on read or write side
#define GPI_TRACE_OVERFLOW_ON_WRITE 0

// maximum number of messages flushed by a single GPI_TRACE_FLUSH() call, 0 = unlimited
// @details
// In a single-threaded environment, each GPI_TRACE_FLUSH() call flushes at most
// GPI_TRACE_BUFFER_NUM_ENTRIES messages, as this is the maximum number of messages in the
// buffer (older messages get lost in case). In a multi-threaded environment, it is possible
// that new messages arrive while GPI_TRACE_FLUSH() is running, which can lead to the situation
// that a single GPI_TRACE_FLUSH() call outputs more than GPI_TRACE_BUFFER_NUM_ENTRIES messages
// (in the extreme case, GPI_TRACE_FLUSH() can run forever). This is critical as it can render
// it impossible to estimate the runtime of GPI_TRACE_FLUSH().
// To overcome this problem, GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL can be used to limit the
// maximum number of messages that are output by a single GPI_TRACE_FLUSH() call. Further,
// if GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL is set to a negative value -N then it limits the
// number of messages to N and, additionally, processes only those messages that have already
// been in the buffer when GPI_TRACE_FLUSH() was entered (so messages arriving in parallel to
// GPI_TRACE_FLUSH() are not handled in the current call).
// NOTE: GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL is not considered if GPI_TRACE_OVERFLOW_ON_WRITE
// is active (TODO: change this).
// TODO: this macro may be of interest for multiple platforms, so maybe move it to gpi/trace.h
#ifndef GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL
  #define GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL GPI_TRACE_BUFFER_NUM_ENTRIES
#endif

// select if and how path part gets filtered out from file names
#ifndef GPI_TRACE_FILTER_PATH
  #define GPI_TRACE_FILTER_PATH 1
#endif

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

typedef struct Gpi_Trace_Msg_tag
{
    Gpi_Hybrid_Tick timestamp;
    const char     *msg;

    // use int64_t to ensure 8-byte-alignment (as defined in ARM ABI, document ARM IHI 0042F)
    int64_t         var_args[(GPI_TRACE_BUFFER_ENTRY_SIZE - sizeof(Gpi_Hybrid_Tick) -
                      sizeof(const char *)) /
                     sizeof(int64_t)];

} Gpi_Trace_Msg;

ASSERT_CT_STATIC(sizeof(Gpi_Trace_Msg) == GPI_TRACE_BUFFER_ENTRY_SIZE);

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

#endif // __GPI_ARMv7M_TRACE_H__
