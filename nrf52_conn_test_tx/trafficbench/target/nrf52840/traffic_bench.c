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
 *	@file					traffic_bench.c
 *
 *	@brief					main entry point and task scheduler
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

#include "gpi/trace.h"

// message groups for TRACE messages (used in GPI_TRACE_MSG() calls)
// define groups appropriate for your needs, assign one bit per group
// values > GPI_TRACE_LOG_USER (i.e. upper bits) are reserved
#define TRACE_INFO GPI_TRACE_MSG_TYPE_INFO

// select active message groups, i.e., the messages to be printed (others will be dropped)
#ifndef GPI_TRACE_BASE_SELECTION
  #define GPI_TRACE_BASE_SELECTION (GPI_TRACE_LOG_STANDARD | GPI_TRACE_LOG_PROGRAM_FLOW)
#endif
#ifndef GPI_TRACE_USER_SELECTION
  #define GPI_TRACE_USER_SELECTION GPI_TRACE_LOG_USER
#endif
GPI_TRACE_CONFIG(traffic_bench, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "traffic_bench.h"

#include "gpi/protothreads.h"
#include "gpi/resource_check.h"
#include "gpi/tools.h"

#include <stdint.h>
#include <stdio.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

GPI_RESOURCE_RESERVE_SHARED(NRF_EGU_SWI, POSTPROC_SWI_INDEX);

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************


//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************


//**************************************************************************************************
//***** Global Variables ***************************************************************************

uint8_t           my_node_id;

volatile uint32_t rx_queue_num_written_trx;
volatile uint32_t rx_queue_num_written_postproc;

// protothread contexts
struct pt         pt_context[3];

//**************************************************************************************************
//***** Local Functions ****************************************************************************

// communication scheduler ISR
void              PendSV_Handler()
{
    GPI_TRACE_FUNCTION_FAST();

    PT_SCHEDULE(execution_thread());

    GPI_TRACE_RETURN_FAST();
}

//**************************************************************************************************

// postprocessing ISR
void POSTPROC_ISR_NAME()
{
    GPI_TRACE_FUNCTION_FAST();

    PT_SCHEDULE(postproc_thread());

    GPI_TRACE_RETURN_FAST();
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

// main task scheduler
void scheduler_start(uint8_t node_id)
{
    GPI_TRACE_FUNCTION();

    Gpi_Fast_Tick_Native t1;

    // init global data
    my_node_id                    = node_id;
    rx_queue_num_written_trx      = rx_queue_num_written_radio;
    rx_queue_num_written_postproc = rx_queue_num_written_trx;

    // ensure that GPI_TRACE_MODE_FLUSH != AUTO (would disturb timing and logging otherwise)
    ASSERT_CT(GPI_TRACE_MODE_IS_NO_TRACE || GPI_TRACE_MODE_IS_FLUSH_NOAUTO,
              GPI_TRACE_MODE_FLUSH_AUTO_would_disturb_timing);

    // prepare PendSV exception
    // NOTE: don't NVIC_EnableIRQ(), PendSV is always enabled (PendSV is a system exception, not an IRQ)
    ASSERT_CT(__NVIC_PRIO_BITS >= 3);
    NVIC_SetPriority(PendSV_IRQn, 5);

    // prepare postprocessing interrupt
    NVIC_SetPriority(POSTPROC_IRQ, 6);
    NVIC_ClearPendingIRQ(POSTPROC_IRQ);
    NVIC_EnableIRQ(POSTPROC_IRQ);

    // init threads
    PT_INIT(pt_scheduler);
    PT_INIT(pt_postprocess);
    PT_INIT(pt_log);

    //// start threads to allow thread-internal initialization
    trigger_scheduler();
    trigger_postprocessing();
    PT_SCHEDULE(log_thread());

    // start communication scheduler (which operates self-driven from this point)
    trigger_scheduler();

    // main loop
    t1 = gpi_tick_fast_native();
    while (1)
    {
        // flush TRACE buffer
        GPI_TRACE_FLUSH();

        // schedule threads
        PT_SCHEDULE(log_thread());

        // show sign of life once in a while
        if (gpi_tick_compare_fast_native(gpi_tick_fast_native(), t1) >= 0)
        {
            t1 += GPI_TICK_MS_TO_FAST(500);

            printf("Hello from main scheduler...\n");
#if GPI_ARCH_IS_BOARD(nRF_PCA10056)
            gpi_led_toggle(GPI_LED_2);
#endif
        }

        //if (PT_WAITING == PT_SCHEDULE_STATE(log_thread()))
        //{
        //}
    }

    GPI_TRACE_RETURN();
}

//**************************************************************************************************
//**************************************************************************************************
