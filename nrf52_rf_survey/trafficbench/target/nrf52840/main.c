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
 *	@file					main.c
 *
 *	@brief					main entry point
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
GPI_TRACE_CONFIG(main, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "traffic_bench.h"

#include "gpi/interrupts.h"
#include "gpi/platform.h"
#include "gpi/tools.h"
#include GPI_PLATFORM_PATH(radio.h)

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h> // atoi()

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************


//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************


//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************


//**************************************************************************************************
//***** Global Variables ***************************************************************************

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

//**************************************************************************************************
//***** Local Functions ****************************************************************************


//**************************************************************************************************
//***** Global Functions ***************************************************************************

int                   main()
{
    // don't TRACE before gpi_platform_init()
    // GPI_TRACE_FUNCTION();

    uint16_t physical_node_id;
    uint8_t  node_id;

    // init platform
    gpi_platform_init();
    gpi_int_enable();

#if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    // wait until FlockLab observer is ready (GPIO tracing, UART, ...)
    // we use SIG1 as start signal
    // NOTE: The start offset of GPIO tracing can be controlled via the XML file, see
    // <https://gitlab.ethz.ch/tec/public/flocklab/wiki/-/wikis/Man/XmlConfig#gpio-tracing-service-configuration>
    // Besides that, it seems that the UART receiver has also a start delay.
    // Waiting for SIG1 ensures that everything is ready.
    while (!gpi_button_read(GPI_BUTTON_SIG1))
        ;
#endif

    GPI_TRACE_FLUSH();
    printf("main.c __DATE__ __TIME__ = " __DATE__ " " __TIME__ "\n");

    // init RF transceiver
    // perform standard GPI radio initialization
    // TODO: could be moved to radio_init(), and maybe the latter into TrafficBench's init
    gpi_radio_init(BLE_1M);
    gpi_radio_set_tx_power(gpi_radio_dbm_to_power_level(8));
    gpi_radio_set_channel(BLE_RADIO_CHANNEL);
    gpi_radio_ble_set_access_address(~0x8E89BED6); // TODO
    // perform application specific radio init
    radio_init();

    GPI_TRACE_FLUSH();
    printf("System started.\n");

    // get physical_node_id
    physical_node_id = SHEPHERD_NODE_ID;
    GPI_TRACE_MSG(TRACE_INFO, "SHEPHERD_NODE_ID = %u", physical_node_id);
    GPI_TRACE_FLUSH();
    printf("starting node %u ...\n", physical_node_id);

// translate physical_node_id to logical node id
// can be used to implement testbed-specific mappings
#if 1
    node_id = physical_node_id;
#else
    for (node_id = 0; node_id < NUM_ELEMENTS(nodes); ++node_id)
    {
        if (nodes[node_id] == physical_node_id) break;
    }
    if (node_id >= NUM_ELEMENTS(nodes))
    {
        printf("!!! PANIC: node mapping not found for node %u !!!\n", physical_node_id);
        while (1)
            ;
    }
#endif
    printf("mapped physical node %u to logical id %u\n", physical_node_id, node_id);

    // start TrafficBench's task scheduler
    scheduler_start(node_id);

    // the following is never reached
    while (1)
    {
        GPI_TRACE_FLUSH();
        printf("scheduler returned to main() !!!\n");
#if GPI_ARCH_IS_BOARD(nRF_PCA10056)
        gpi_led_toggle(GPI_LED_2);
#endif
        gpi_milli_sleep(200);
    }

    GPI_TRACE_RETURN(0);
}

//**************************************************************************************************
//**************************************************************************************************
