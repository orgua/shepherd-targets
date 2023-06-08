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
 *	@file					traffic_bench.h
 *
 *	@brief					entry point and internal declarations
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

#ifndef __TRAFFIC_BENCH_H__
#define __TRAFFIC_BENCH_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "radio.h" // RSSISpy radio interface

#include "gpi/interrupts.h"
#include "gpi/protothreads.h"

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

#define POSTPROC_SWI_INDEX 0

#define POSTPROC_IRQ       CONCAT(SWI, POSTPROC_SWI_INDEX, _EGU, POSTPROC_SWI_INDEX, _IRQn)
#define POSTPROC_ISR_NAME  CONCAT(SWI, POSTPROC_SWI_INDEX, _EGU, POSTPROC_SWI_INDEX, _IRQHandler)

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// checkpoint data (in packets containing checkpoints)
typedef struct __attribute__((packed)) Checkpoint_Data
{
    uint8_t  transmitter_id;
    uint8_t  transmitter_hop;
    uint16_t schedule_pc;
    uint32_t schedule_clock;
    uint32_t schedule_rng_state;

} Checkpoint_Data;

//**************************************************************************************************
// comm. scheduler instructions

typedef enum Opcode
{
    opTERMINATE = 0,
    opTRX,
    opSLEEP,
    //	opCHANGE_RADIO_MODE,
    opBRANCH = 200,

} Opcode;

typedef struct /*__attribute__((packed))*/ Params_SLEEP
{
    uint32_t delay;

} Params_SLEEP;

typedef enum Params_TRX_Desc_Type
{
    TRX_DATA_END        = 0, // end of list
    TRX_DATA_FIXED      = 1,
    TRX_DATA_RANDOM     = 2,
    TRX_DATA_CHECKPOINT = 250,
    TRX_DATA_NO_PACKET  = 255

} Params_TRX_Desc_Type;

typedef struct /*__attribute__((packed))*/ Params_TRX
{
    uint32_t timeout;
    uint32_t tx_delay;
    uint16_t tx_carrier_period_1;
    uint16_t tx_carrier_period_2;
    uint16_t rssi_pretrigger_time;
    uint16_t rssi_posttrigger_time;
    uint16_t rng_offset;
    uint8_t  payload_length;
    uint8_t  rssi_buffer_size_msb; // 0 = auto from payload_length
    uint8_t  checkpoint_offset;    // 0xFF = no checkpoint
    uint8_t  num_transmitters;
    uint8_t  transmitter_ids[0];
    //uint16_t		payload_descriptor_list_size;

    struct __attribute__((packed))
    {
        uint8_t size; // size of descriptor (not of corresponding payload chunk)
        uint8_t type; // see Params_TRX_Desc_Type
        union
        {
            struct __attribute__((packed))
            {
                uint8_t data[0];

            } fixed;

            struct __attribute__((packed))
            {
                uint8_t num_bytes;

            } random;
        };
    } payload_descriptors[0];

} Params_TRX;

typedef union Instruction_Params
{
    Params_SLEEP SLEEP;
    Params_TRX   TRX;

} Instruction_Params;

// 32-bit machine instruction
typedef struct Schedule_Entry
{
    uint8_t opcode;

    // immediate parameters
    union __attribute__((packed))
    {
        //uint8_t  		params_raw[3];

        struct __attribute__((packed))
        {
            uint8_t  __padding__; // for alignment
            uint16_t params_ptr;
        };

        struct __attribute__((packed))
        {
            uint8_t __reserved__;
            int16_t offset;

        } BRANCH;

        struct __attribute__((packed))
        {
            int8_t   group_offset;
            uint16_t params_ptr;

        } TRX;

        //struct __attribute__((packed))
        //{
        //	uint8_t		num_entries;
        //	uint16_t	__reserved__;

        //} TRX_GROUP;
    };

} Schedule_Entry;

// static options provided in the schedule
typedef struct Schedule_Options
{
    uint16_t TRX_pre_delay;  // between schedule tick and start of packet
    uint16_t TRX_post_delay; // between end of timeout and next instruction
    int16_t  TRX_checkpoint_marker_pos;

} Schedule_Options;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

extern uint8_t                my_node_id;

// the following symbols are defined in schedule_framework.s
extern const Schedule_Entry   schedule[];
extern const Schedule_Entry   schedule_end;
extern const Schedule_Options schedule_options;

// protothread contexts
extern struct pt              pt_context[3];
static struct pt *const       pt_scheduler   = &pt_context[0];
static struct pt *const       pt_postprocess = &pt_context[1];
static struct pt *const       pt_log         = &pt_context[2];

//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// main task scheduler
void scheduler_start(uint8_t my_node_id);

// thread entry functions (used internally)
PT_THREAD(execution_thread());
PT_THREAD(postproc_thread());
PT_THREAD(log_thread());

#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

static inline void scheduler_wake_at(Gpi_Fast_Tick_Native tick)
{
    radio_wake_at(tick);

    // in response, trigger_radio_event() triggers the scheduler (see there)
}

//**************************************************************************************************

static inline void trigger_postprocessing() { NVIC_SetPendingIRQ(POSTPROC_IRQ); }

//**************************************************************************************************
//**************************************************************************************************

#endif // __TRAFFIC_BENCH_H__
