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
 *	@file					radio_queues.h
 *
 *	@brief					select implementation of radio queue structures
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details


 **************************************************************************************************/

#ifndef __RADIO_QUEUES_H__
#define __RADIO_QUEUES_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/tools.h"

// include base implementation if there is no need for application-specific extensions.
// otherwise include customized version and ensure that all structures include at least
// the fields defined in radio_queues_base.h.
#ifdef RADIO_QUEUES_CUSTOM_HEADER
  #include STRINGIFY(RADIO_QUEUES_CUSTOM_HEADER)
#else
  #include "radio_queues_base.h"
#endif

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// check if required fields are present and aligned

// Radio_Packet
ASSERT_CT_STATIC(0 == offsetof(Radio_Packet, raw_payload) % sizeof(uint32_t));
ASSERT_CT_STATIC(0 == offsetof(Radio_Packet, trx_status) % sizeof(uint32_t));

// Rx_Queue_Entry
ASSERT_CT_STATIC(0 == offsetof(Rx_Queue_Entry, packet) % sizeof(uint32_t));
ASSERT_CT_STATIC(0 == offsetof(Rx_Queue_Entry, timestamp_ref) % sizeof(uint32_t));
ASSERT_CT_STATIC(0 == offsetof(Rx_Queue_Entry, timestamp_end) % sizeof(uint32_t));
ASSERT_CT_STATIC(0 == offsetof(Rx_Queue_Entry, rssi_space_num_written_begin) % sizeof(uint32_t));

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

#endif // __RADIO_QUEUES_H__
