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
 *	@file					radio.h
 *
 *	@brief					RSSISpy API and internal declarations
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

#ifndef __RADIO_H__
#define __RADIO_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "radio_queues.h"

#include "gpi/platform.h"
#include GPI_PLATFORM_PATH(radio.h)

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// transmit acknowledgement marker
typedef struct Tx_Ack
{
    const Radio_Packet   *packet;
    uint32_t              timestamp_ref; // ADDRESS, SFD, etc.
    uint32_t              timestamp_end;
    volatile uint_fast8_t done;

} Tx_Ack;

//**************************************************************************************************

// sample buffer of one RSSI recording
typedef struct Rssi_Buffer
{
    // NOTE: members are ordered such that struct is packed
    // (to save space in rssi_space, which can contain quite a few header entries)

    uint32_t timestamp_rssi_end; // timestamp of last sample
    uint32_t num_written;
    uint32_t num_missed;
    uint32_t pretrigger_time;  // stored as info for postprocessing
    uint32_t posttrigger_time; // stored as info for postprocessing
    uint8_t  size_msb;
    union
    {
        uint8_t status;
        struct
        {
            uint8_t early_readout_detected : 1;
            uint8_t late_readout_detected : 1;
        };
    };
    int16_t  temperature; // stored to enable temperature compensation

    uint32_t _padding_[0]; // word-align samples[]

    uint8_t  samples[0]; // size follows from size_msb

} Rssi_Buffer;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

// transmit acknowledgement marker
extern Tx_Ack                tx_ack;

// Rx intermediate trigger event marker
extern volatile uint_fast8_t rx_intermediate_trigger_event;

// rssi_space = circular buffer of Rssi_Buffer entries
extern uint8_t               rssi_space[RSSI_SPACE_SIZE];
extern volatile uint32_t     rssi_space_num_writing;
extern volatile uint32_t     rssi_space_num_written_radio;

// NOTE: Theoretically, the last bytes of rssi_space (sizeof(Rssi_Buffer) + min. buffer size - 1
// if min. buffer size > sizeof(Rssi_Buffer)) could be used for something different (e.g. scratch
// buffer for postprocessing) because this space gets never used by rssi sampling (it is always
// skipped).

// test buffer sizes
// should be power of 2 to enable fast computation of x % NUM_ELEMENTS(buffer)
// must be power of 2 to ensure that num_written wrap-around works right
ASSERT_CT_STATIC(IS_POWER_OF_2(NUM_ELEMENTS(rx_queue)), size_of_rx_queue_must_be_power_of_2)
ASSERT_CT_STATIC(IS_POWER_OF_2(NUM_ELEMENTS(rssi_space)), size_of_rssi_space_must_be_power_of_2)

//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif

void                 radio_init();

Gpi_Fast_Tick_Native radio_start_tx(Gpi_Fast_Tick_Native start_tick,
                                    Gpi_Fast_Tick_Native carrier_period_1,
                                    Gpi_Fast_Tick_Native carrier_period_2,
                                    const Radio_Packet  *packet);

Gpi_Fast_Tick_Native radio_start_rx(Gpi_Fast_Tick_Native start_tick, Gpi_Fast_Tick_Native timeout,
                                    int_fast16_t         intermediate_trigger_pos,
                                    uint8_t              intermediate_trigger_preset_content,
                                    uint_fast32_t        min_rssi_buffer_size,
                                    Gpi_Fast_Tick_Native rssi_pretrigger_time,
                                    Gpi_Fast_Tick_Native rssi_posttrigger_time);

// useful helper functions

// update rssi_space_num_written_radio from the outside in a safe way,
// e.g. to regain buffer space after postprocessing has finished
void                 radio_update_rssi_num_written(uint32_t rx_queue_num_read,
                                                   uint32_t rssi_space_num_written_radio);

// drop all rssi data,
// e.g. because data has been damaged (potentially) by postprocessing
// ATTENTION: this function must not interrupt radio_start_rx()
void                 radio_drop_rssi_space();

// generate event (-> trigger_radio_event()) at specified time.
// can be used to utilize the timer IRQ occupied by radio.c for other purposes
// while the radio is inactive.
void                 radio_wake_at(Gpi_Fast_Tick_Native tick);

// compute theoretical timestamp of reference event (-> timestamp_ref) relative to start of packet
Gpi_Fast_Tick_Native radio_get_ref_timestamp_offset(Gpi_Radio_Mode mode);

// compute nominal packet airtime
Gpi_Fast_Tick_Native radio_get_packet_airtime(Gpi_Radio_Mode mode, uint_fast8_t payload_length);

#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************


//**************************************************************************************************
//**************************************************************************************************

#endif // __RADIO_H__
