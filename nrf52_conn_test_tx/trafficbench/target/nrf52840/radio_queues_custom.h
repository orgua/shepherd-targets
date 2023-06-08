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
 *	@file					radio_queues_custom.h
 *
 *	@brief					application-specific implementation of radio queue structures
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details


 **************************************************************************************************/

#ifndef __RADIO_QUEUES_CUSTOM_H__
#define __RADIO_QUEUES_CUSTOM_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform.h"

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// radio packet format
typedef struct /*__attribute__((packed))*/ Radio_Packet
{
	uint8_t		_padding_1[2];			// for alignment (payload should be word-aligned)
	
	uint8_t		ble_header;				// S0 (see nRF doc. for details)
	uint8_t		raw_payload_length;		// BLE length field

	union __attribute__((packed))
	{
		uint8_t			raw_payload[255];
		
		// application specific packet format
		//struct
		//{
		//	...
		//	uint8_t		payload[255 - x];
		//};
	};

	uint32_t	_padding_2[0];			// align trx_status
	
	union
	{
		uint32_t		trx_status;

		// always
		struct
		{
			// with little endian byteorder
			uint32_t	crc					: 24;
			uint32_t						:  7;
			uint32_t	is_tx				:  1;	// this is a transmitted packet
		};
		
		// if this is a receive packet
		struct
		{
			// with little endian byteorder
			uint32_t						: 24;	// crc
			uint32_t						:  3;
			uint32_t	timeout_triggered	:  1;
			uint32_t	header_detected		:  1;
			uint32_t	crc_ok				:  1;	// valid packet
			uint32_t	content_ok			:  1;	// trustworthy packet
			uint32_t						:  1;	// is_tx
		};

		// if this is a transmit packet
		struct
		{
			// with little endian byteorder
			uint32_t						: 24;	// crc
			uint32_t						:  2;
			uint32_t	is_tx_no_packet		:  1;	// Tx without packet (i.e. only carrier signal)
			uint32_t						:  4;
			uint32_t						:  1;	// is_tx
		};
	};
	
} Radio_Packet;

//**************************************************************************************************

typedef struct Rx_Queue_Entry
{
	Radio_Packet	packet;
	uint32_t		timestamp_schedule_global;		// -1 = invalid (out of sync)
	uint32_t		timestamp_schedule_local;
	uint32_t		timestamp_ref;					// ADDRESS, SFD, etc.
	uint32_t		timestamp_end;
	int16_t			timestamp_ref_deviation;
	uint16_t		late_start_delay;
	union
	{
		uint32_t	rssi_space_num_written_begin;	// in case of Rx
		uint32_t	tx_delay;						// in case of Tx
	};

	// NOTE: timestamp_schedule_global == -1 is reserved as out-of-sync marker. It does not
	// appear in a sync'd schedule because the scheduler explicitly skips this value when in 
	// sync. The latter is a matter of taste, because if the value would appear in sync'd state,
	// it just declares a single sync'd entry as out-of-sync, which is not that critical.
	// (We assume that such entries are typically skipped during evaluation).
	// That said, in general it is not a bad idea to avoid schedules that run for so long to
	// prevent wrap-around issues / uncertainties when interpreting the results.
	
} Rx_Queue_Entry;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

// Rx queue
extern Rx_Queue_Entry			rx_queue[RX_QUEUE_SIZE];
extern volatile uint32_t		rx_queue_num_writing;
extern volatile uint32_t		rx_queue_num_written_radio;
extern volatile uint32_t		rx_queue_num_written_trx;
extern volatile uint32_t		rx_queue_num_written_postproc;

//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
	extern "C" {
#endif

// callback function that signals interesting radio events (e.g. finished transmission).
// can be used to trigger application-specific event processing.
// ATTENTION: function is called from radio ISR, so execution can be time-critical.
// typically it is best to trigger deferred processing instead of handling events directly.
static inline void	trigger_radio_event();

#ifdef __cplusplus
	}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

static inline void trigger_scheduler()
{
	// trigger comm. scheduler interrupt
	SCB->ICSR = BV_BY_VALUE(SCB_ICSR_PENDSVSET, 1);
	__DSB();	// ensures immediate exception entry when called from lower priority context
}

static inline void trigger_radio_event()
{
	trigger_scheduler();
}

//**************************************************************************************************
//**************************************************************************************************

#endif // __RADIO_QUEUES_CUSTOM_H__
