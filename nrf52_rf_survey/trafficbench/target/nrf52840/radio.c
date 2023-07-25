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
 *	@file					radio.c
 *
 *	@brief					radio transmit and receive functions including RSSISpy
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
#define TRACE_INFO    GPI_TRACE_MSG_TYPE_INFO
#define TRACE_WARNING GPI_TRACE_MSG_TYPE_WARNING
#define TRACE_ERROR   GPI_TRACE_MSG_TYPE_ERROR
#define TRACE_VERBOSE GPI_TRACE_MSG_TYPE_VERBOSE

// select active message groups, i.e., the messages to be printed (others will be dropped)
#ifndef GPI_TRACE_BASE_SELECTION
  #define GPI_TRACE_BASE_SELECTION (GPI_TRACE_LOG_STANDARD | GPI_TRACE_LOG_PROGRAM_FLOW)
#endif
#ifndef GPI_TRACE_USER_SELECTION
  #define GPI_TRACE_USER_SELECTION GPI_TRACE_LOG_USER
#endif
#if (GPI_TRACE_USER_SELECTION & GPI_TRACE_MSG_TYPE_VERBOSE)
  #define TRACE_USER_SELECTION (GPI_TRACE_USER_SELECTION | GPI_TRACE_LOG_FUNCTION_RETURN_MSG)
#else
  #define TRACE_USER_SELECTION GPI_TRACE_USER_SELECTION
#endif
GPI_TRACE_CONFIG(radio, GPI_TRACE_BASE_SELECTION | TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "radio.h"

#include "gpi/clocks.h"
#include "gpi/interrupts.h"
#include "gpi/olf.h"
#include "gpi/platform.h"
#include "gpi/resource_check.h"
#include "gpi/tools.h"
#include GPI_PLATFORM_PATH(radio.h)

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

// DEBUG_RSSI can be used to debug the RSSI sampling subsystem.
// It reduces the sampling rate and additionally outputs internal variables to the sample buffer.
#define DEBUG_RSSI 0

// use DEBUG_GPIO to connect internal events to GPIO pins (allows external monitoring)
#define DEBUG_GPIO 1

// sampling period in timer ticks
#if DEBUG_RSSI
  #define RSSI_SAMPLING_PERIOD 4096
#else
  #define RSSI_SAMPLING_PERIOD 16
#endif

//**************************************************************************************************
// resource assignments
// TODO: maybe move to a header file to simplify application-specific adaptions

#define MAIN_TIMER_INDEX         GPI_ARM_NRF_FAST_CLOCK_TIMER
#define RSSI_TIMER_INDEX         0
#define RSSI_TIMER2_INDEX        1
#define RSSI_TIMER3_INDEX        2

#define RSSI_MWU_REGION          0

// NOTE: could check if any of the pre-programmed PPI channels can be used
#define PPI_START                0
#define PPI_READY                1
#define PPI_ADDRESS              2
//#define PPI_PAYLOAD					3
#define PPI_END                  4
#define PPI_RSSI_START           5
#define PPI_RSSI_END             6
#define PPI_RSSI_MWU             7
#define PPI_RSSI_COUNT           8
#define PPI_TX_CONTROL           9 // can be shared with PPI_RSSI_... if not enough channels

// CC regs (CCI_ = CC index, CCR_ = CC reg)
// NOTE: CC[0] = GPI_ARM_NRF_FAST_CLOCK_CAPTURE_REG
// if there is a lack of CC regs: radio events could use same CC with timestamps saved in the radio ISR
#define CCI_MAIN_COMPARE         1
#define CCI_MAIN_START_READY_END 2
#define CCI_MAIN_ADDRESS         3
#define CCI_MAIN_RSSI_START      4
#define CCI_MAIN_RSSI            5
//#define CCI_MAIN_PAYLOAD			4

#ifdef DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    #define LED_RADIO_ISR      GPI_LED_INT1
    #define LED_MAIN_TIMER_ISR GPI_LED_INT2
    #define LED_RSSI_TIMER     GPI_LED_1
    #define LED_RSSI_ACTIVE    GPI_LED_2
    #define PPI_DEBUG1         10
    #define PPI_DEBUG2         11
    #define GPIOTE_DEBUG1      0
    #define GPIOTE_DEBUG2      1
  #elif GPI_ARCH_IS_BOARD(nRF_PCA10056)
    #define LED_RADIO_ISR      GPI_LED_3
    #define LED_MAIN_TIMER_ISR GPI_LED_4
    #define GPIO_DEBUG1_PORT   1
    #define GPIO_DEBUG1_PIN    10
    #define GPIO_DEBUG1_Px     CONCAT(NRF_P, GPIO_DEBUG1_PORT)
    #define GPIOTE_DEBUG1      0
  #endif
  #ifndef LED_RADIO_ISR
    #define LED_RADIO_ISR GPI_LED_NONE
  #endif
  #ifndef LED_MAIN_TIMER_ISR
    #define LED_MAIN_TIMER_ISR GPI_LED_NONE
  #endif
  #ifndef LED_RSSI_TIMER
    #define LED_RSSI_TIMER GPI_LED_NONE
  #endif
  #ifndef LED_RSSI_ACTIVE
    #define LED_RSSI_ACTIVE GPI_LED_NONE
  #endif
#endif

//**************************************************************************************************
// derived resource macros and resource reservations
// (for details see gpi/resource_check.h)

// TIMER0...TIMER2 have only 4 CCs -> MAIN_TIMER must be TIMER3 or TIMER4
ASSERT_CT_STATIC(MAIN_TIMER_INDEX >= 3, MAIN_TIMER_INDEX_must_be_3_or_4);

#define MAIN_TIMER          CONCAT(NRF_TIMER, MAIN_TIMER_INDEX)
#define MAIN_TIMER_IRQ      CONCAT(TIMER, MAIN_TIMER_INDEX, _IRQn)
#define MAIN_TIMER_ISR_NAME CONCAT(TIMER, MAIN_TIMER_INDEX, _IRQHandler)

GPI_RESOURCE_RESERVE_SHARED(NRF_TIMER, MAIN_TIMER_INDEX);

#define RSSI_TIMER           CONCAT(NRF_TIMER, RSSI_TIMER_INDEX)
#define RSSI_TIMER2          CONCAT(NRF_TIMER, RSSI_TIMER2_INDEX)
#define RSSI_TIMER3          CONCAT(NRF_TIMER, RSSI_TIMER3_INDEX)
#define RSSI_IRQ             CONCAT(TIMER, RSSI_TIMER_INDEX, _IRQn)
#define RSSI_ISR_NAME        CONCAT(TIMER, RSSI_TIMER_INDEX, _IRQHandler)
#define RSSI_TIMER2_IRQ      CONCAT(TIMER, RSSI_TIMER2_INDEX, _IRQn)
#define RSSI_TIMER2_ISR_NAME CONCAT(TIMER, RSSI_TIMER2_INDEX, _IRQHandler)

GPI_RESOURCE_RESERVE(NRF_TIMER, RSSI_TIMER_INDEX);
GPI_RESOURCE_RESERVE(NRF_TIMER, RSSI_TIMER2_INDEX);
GPI_RESOURCE_RESERVE(NRF_TIMER, RSSI_TIMER3_INDEX);
GPI_RESOURCE_RESERVE_SHARED(NRF_MWU);
GPI_RESOURCE_RESERVE(NRF_MWU_REGION, RSSI_MWU_REGION);
GPI_RESOURCE_RESERVE(NRF_TEMP);

#define PPI_CHEN_TX_MASK (BV(PPI_ADDRESS) | BV(PPI_END))
//#define PPI_CHEN_TX_MASK			(BV(PPI_ADDRESS) | BV(PPI_PAYLOAD) | BV(PPI_END))

#if defined(PPI_DEBUG2)
  #define PPI_CHEN_RX_MASK_EXTRA (BV(PPI_DEBUG1) | BV(PPI_DEBUG2))
#elif defined(PPI_DEBUG1)
  #define PPI_CHEN_RX_MASK_EXTRA BV(PPI_DEBUG1)
#else
  #define PPI_CHEN_RX_MASK_EXTRA 0
#endif
#define PPI_CHEN_RX_MASK                                                                           \
    (PPI_CHEN_TX_MASK | PPI_CHEN_RX_MASK_EXTRA | BV(PPI_READY) | BV(PPI_RSSI_START) |              \
     BV(PPI_RSSI_END) | BV(PPI_RSSI_MWU) | BV(PPI_RSSI_COUNT))

GPI_RESOURCE_RESERVE_SHARED(NRF_PPI);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_START);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_READY);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_ADDRESS);
//GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_PAYLOAD);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_END);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_RSSI_START);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_RSSI_END);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_RSSI_MWU);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_RSSI_COUNT);
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_TX_CONTROL);
#ifdef PPI_DEBUG1
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_DEBUG1);
#endif
#ifdef PPI_DEBUG2
GPI_RESOURCE_RESERVE(NRF_PPI_CH, PPI_DEBUG2);
#endif

#define CCR_MAIN_COMPARE         (MAIN_TIMER->CC[CCI_MAIN_COMPARE])
#define CCR_MAIN_START_READY_END (MAIN_TIMER->CC[CCI_MAIN_START_READY_END])
#define CCR_MAIN_ADDRESS         (MAIN_TIMER->CC[CCI_MAIN_ADDRESS])
#define CCR_MAIN_RSSI_START      (MAIN_TIMER->CC[CCI_MAIN_RSSI_START])
#define CCR_MAIN_RSSI            (MAIN_TIMER->CC[CCI_MAIN_RSSI])
//#define CCR_MAIN_PAYLOAD			(MAIN_TIMER->CC[CCI_MAIN_PAYLOAD])

#define INTEN_MAIN_COMPARE       BV_BY_NAME_PREEXP(CONCAT(TIMER_INTENSET_COMPARE, CCI_MAIN_COMPARE), Set)

GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_COMPARE);
GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_START_READY_END);
GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_ADDRESS);
GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_RSSI_START);
GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_RSSI);
//GPI_RESOURCE_RESERVE(NRF_TIMER_CC, MAIN_TIMER_INDEX, CCI_MAIN_PAYLOAD);

#ifdef GPIOTE_DEBUG1
GPI_RESOURCE_RESERVE(NRF_GPIOTE_CH, GPIOTE_DEBUG1);
#endif
#ifdef GPIOTE_DEBUG2
GPI_RESOURCE_RESERVE(NRF_GPIOTE_CH, GPIOTE_DEBUG2);
#endif

//**************************************************************************************************

#ifdef DEBUG_GPIO
  #define LED_ISR(name, led)                                                                       \
      CONCAT(name, _)();                                                                           \
      void name()                                                                                  \
      {                                                                                            \
          gpi_led_toggle(led);                                                                     \
          CONCAT(name, _)();                                                                       \
          gpi_led_toggle(led);                                                                     \
      }                                                                                            \
      void CONCAT(name, _)()
#else
  #define LED_ISR(name, led) void name()
#endif

//**************************************************************************************************
// radio timing constants, in timer ticks (PCLK16M)

#define PPI_DELAY                  1

// nRF spec. states that TASKS_TXEN -> EVENTS_READY = 40...40us (t_TXEN,FAST), while at the same time
// it says that this delay has a typical jitter of 0.25us (t_READYJITTER) [4413_417 v1.2 6.20.15.8 and 6.20.15.10].
// Hence, for the sake of precise timing we avoid using the TXREADY->START shortcut and trigger
// TASKS_START manually RADIO_TX_RAMP_UP_TOLERANCE after the nominal RADIO_TX_RAMP_UP_TIME.
#define RADIO_TX_RAMP_UP_TIME      GPI_TICK_US_TO_FAST(40)
#define RADIO_TX_RAMP_UP_TOLERANCE GPI_TICK_US_TO_FAST(1)

// Rx ramp-up is less time critical than Tx ramp-up because some tolerance is needed anyhow
// (to compensate for clock drift)
#define RADIO_RX_RAMP_UP_TIME      GPI_TICK_US_TO_FAST(40)

// TASKS_START (from TXIDLE state) -> packet on air
// precise value is unknown so far
#define RADIO_TX_START_DELAY       0

// besides nRF spec., see Carsten's measurements and
// https://devzone.nordicsemi.com/f/nordic-q-a/83778/undocumented-tx---rx-radio-delay
#define RADIO_TX_EVENT_ADDRESS_DELAY                                                               \
    (-13) // surprise: it's negative (-> nRF spec. event desc. is not precise)
#define RADIO_RX_EVENT_ADDRESS_DELAY                                                               \
    155 // 152.1...156.5, mean 154.5, rounding up includes some air time
#define RADIO_TX_EVENT_END_DELAY 4
#define RADIO_RX_EVENT_END_DELAY                                                                   \
    156 // 154.1...157.2, mean 155.5, rounding up includes some air time

// RADIO_TX_DISABLE_DELAY can be used to fine-tune shutdown moment of power amplifier.
// nRF spec. defines TASKS_DISABLE -> EVENTS_DISABLED delay (6us for BLE 1M), but it is
// unclear at which point in this period the power amp. shuts down. [4413_417 v1.2 6.20.15.8]
#define RADIO_TX_DISABLE_DELAY 0

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************

typedef enum Radio_State
{
    // bit fields
    RS_RAMP_UP           = 0x01,
    RS_RUNNING           = 0x02,
    RS_BITCOUNTER_ACTIVE = 0x04,
    RS_RX_ACTIVE         = 0x40,
    RS_TX_ACTIVE         = 0x80,

    // state patterns
    RS_IDLE              = 0x00,
    RS_RX_RAMP_UP        = 0x41, // ATTENTION: without RS_BITCOUNTER_ACTIVE
    //RS_RX_RUNNING			= 0x42,		// ATTENTION: without RS_BITCOUNTER_ACTIVE
    RS_TX_RAMP_UP        = 0x81,
    //RS_TX_RUNNING			= 0x82,

} Radio_State;

//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************

static Radio_State    radio_state;
static uint32_t       timestamp_ready;
static uint32_t       tx_ccr_disable;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

uint8_t               rssi_space[NUM_ELEMENTS(rssi_space)];
volatile uint32_t     rssi_space_num_writing;
volatile uint32_t     rssi_space_num_written_radio;

Rx_Queue_Entry        rx_queue[NUM_ELEMENTS(rx_queue)];
volatile uint32_t     rx_queue_num_writing;
volatile uint32_t     rx_queue_num_written_radio;

volatile uint_fast8_t rx_intermediate_trigger_event;

Tx_Ack                tx_ack;

//**************************************************************************************************
//***** Local Functions ****************************************************************************

// RSSI sampling ISR
// ATTENTION: this function is very time-critical and designed with greatest care
void __attribute__((naked, section(".fast"))) RSSI_ISR_NAME()
{
    // ATTENTION: Instructions marked with (**) will be updated at runtime by adopt_rssi_isr().
    // Do not change their positions without updating adopt_rssi_isr()!
    __asm__ volatile(
            "mov.w	r0, #0x40000000				\n"
            "add.w	r3, r0, %[TA]				\n" // r3 = &RSSI_TIMER
            "movw.w	r2, #0						\n" // (**)
            "str.w	sp, [r3, %[TA_E]]			\n" // RSSI_TIMER->EVENTS_COMPARE[x] = 0
            "movt.w	r2, #0						\n" // r2 = &rssi_buffer.samples (**)
            "add.w	r0, r0, %[RADIO]			\n" // r0 = &RADIO
            "ldr.w	r3, [r2, %[nw_offset]]		\n" // r3 = num_written
#if !(DEBUG_RSSI)
            "add.w	r12, r3, #1					\n"
#else
            "add.w	r12, r3, #16				\n"
#endif
            "str.w	r12, [r2, %[nw_offset]]		\n" // num_written++
            "bfc.w	r3, #0, #1					\n" // r3 %= NUM_ELEMENTS(rssi_buffer.samples) (**)
#if !(DEBUG_RSSI)
            "ldr	r0, [r0, %[RADIO_RSSI]]		\n"
  #if 0 // store buffer index instead of RSSISAMPLE
		"strb	r3, [r2, r3, lsl #0]		\n"	// this generates sawtooth signals, which is helpful for debugging
  #else
            "strb	r0, [r2, r3, lsl #0]		\n" // rssi_buffer.samples[r3] = RADIO->RSSISAMPLE
  #endif
#else
            // if DEBUG_RSSI is enabled: dump more information to support debugging
            // record format (fields):
            //		RADIO_RSSI (uint8)
            //		RSSI_TIMER2->EVENTS_COMPARE[0] (uint8)
            //		num_written (uint16)
            //		RSSI_TIMER2->CC[3] (uint32)
            //		CCR_MAIN_RSSI_START (uint32)
            //		CCR_MAIN_RSSI (uint32)
            "mov	r1, #0x40000000				\n"
            "add	r1, r1, %[TB]				\n"
            "mov	r12, #1						\n"
            "str	r12, [r1, %[TB_T3]]			\n"
            "add	r2, r2, r3, lsl #0			\n"
            "ldr	r12, [r1, %[TB_CC3]]		\n"
            "ldr	r0, [r0, %[RADIO_RSSI]]		\n"
            "strb	r0, [r2], #2				\n"
            "strh	r3, [r2], #2				\n"
            "ldr	r0, [r1, %[TB_E0]]			\n"
            "str	sp, [r1, %[TB_E0]]			\n"
            "strb	r0, [r2, #-3]				\n"
            "str	r12, [r2], #4				\n"
            "sub	r3, r1, %[TB]				\n"
            "add	r1, r3, %[TM]				\n"
            "ldr	r0, [r1, %[TM_CCA]]			\n"
            "str	r0, [r2], #4				\n"
            "ldr	r0, [r1, %[TM_CCB]]			\n"
            "str	r0, [r2], #4				\n"
#endif
            "bx		lr							\n"
            :
            :
            // ATTENTION: all assignments must be purely constant
            // (as this is a naked function, and time-critical moreover)
            [nw_offset] "J"(offsetof(Rssi_Buffer, num_written) - offsetof(Rssi_Buffer, samples)),
            [RADIO] "I"((uintptr_t) NRF_RADIO - 0x40000000),
            [TA] "I"((uintptr_t) RSSI_TIMER - 0x40000000),
            [TB] "I"((uintptr_t) RSSI_TIMER2 - 0x40000000),
            [TM] "I"((uintptr_t) MAIN_TIMER - 0x40000000),
            //[RADIO_E] "J"((uintptr_t)&(NRF_RADIO->EVENTS_RSSIEND) - (uintptr_t)NRF_RADIO),
            [RADIO_RSSI] "J"((uintptr_t) & (NRF_RADIO->RSSISAMPLE) - (uintptr_t) NRF_RADIO),
            [TA_E] "J"((uintptr_t) & (RSSI_TIMER->EVENTS_COMPARE[1]) - (uintptr_t) RSSI_TIMER),
            [TB_E0] "J"((uintptr_t) & (RSSI_TIMER2->EVENTS_COMPARE[0]) - (uintptr_t) RSSI_TIMER2),
            [TB_T3] "J"((uintptr_t) & (RSSI_TIMER2->TASKS_CAPTURE[3]) - (uintptr_t) RSSI_TIMER2),
            [TB_CC3] "J"((uintptr_t) & (RSSI_TIMER2->CC[3]) - (uintptr_t) RSSI_TIMER2),
            [TM_CCA] "J"((uintptr_t) &CCR_MAIN_RSSI_START - (uintptr_t) MAIN_TIMER),
            [TM_CCB] "J"((uintptr_t) &CCR_MAIN_RSSI - (uintptr_t) MAIN_TIMER));

    // execution time (!DEBUG_RSSI):
    //
    // best-case (due to PCLK16M phase):
    // PCLK16M	 0  1  1  1  1  2  2  2  2  3  3  3  3  4  4  4  4  5  5  5  5  6  6  6  6  7  7  7  7  8  8  8  8  9  9  9
    // mov		 x
    // add		    x
    // movw		       x
    // str		          b  a  s                       d
    // movt		             x
    // add		                x
    // ldr		                                           a  d
    // add		                                                 x
    // str		                                                    a  d
    // bfc		                                                          x
    // ldr		                                                             a  s                       d
    // str		                                                                                           b
    // bx		                                                                                              ...
    // HCLK64M	 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
    //
    // worst-case (due to PCLK16M phase):
    // PCLK16M	 0  0  0  0  1  1  1  1  2  2  2  2  3  3  3  3  4  4  4  4  5  5  5  5  6  6  6  6  7  7  7  7  8  8  8  8
    // mov		 x
    // add		    x
    // movw		       x
    // str		          b  a           s                       d
    // movt		             x
    // add		                x
    // ldr		                                                    a  d
    // add		                                                          x
    // str		                                                             a  d
    // bfc		                                                                   x
    // ldr		                                                                      a  s                       d
    // str		                                                                                                    b
    // bx		                                                                                                       ...
    // HCLK64M	 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
    //
    // (legend: x = execute, b = store in write buffer, a = address phase, d = data phase / done, s = PCLK16M sync stage)
}

// place assertions outside of naked function
// ASSERT_CT_STATIC(IS_POWER_OF_2(NUM_ELEMENTS(rssi_buffer.samples)));

// adopt RSSI sampling ISR machine code to a given buffer
// ATTENTION: this requires that the ISR is placed in RAM
static void adopt_rssi_isr(void *samples, uint_fast8_t size_msb /*uint_fast32_t size*/)
{
    GPI_TRACE_FUNCTION();

    //// check if size is a power of 2
    //assert((size & -size) == size);

    uint16_t *const        isr = (uint16_t *) ((uintptr_t) &RSSI_ISR_NAME & ~UINT32_C(1));
    uintptr_t              blo = (uintptr_t) samples & 0xffff;
    uintptr_t              bhi = (uintptr_t) samples >> 16;
    //uint_fast8_t		size_msb = gpi_get_msb(size);

    // check if ISR is placed in code RAM
    // NOTE: cannot use ASSERT_CT() because ISR address is unknown at compile time (defined by the linker)
    // NOTE: do not use symbols that are specific for the build environment (e.g.
    // __RAM_segment_start__ and __RAM_segment_end__). Testing if some address is in RAM or not
    // is a pure hardware decision and independent of software semantics.
    static uint16_t *const RAM_SEGMENT_START = (void *) 0x00800000;
    static uint16_t *const RAM_SEGMENT_END   = (void *) 0x00840000;
    assert((RAM_SEGMENT_START <= isr) && (isr < RAM_SEGMENT_END));

    // movw r2, #blo
    isr[4]  = 0xf240 | ((blo & 0x0800) >> 1) | ((blo & 0xf000) >> 12);
    isr[5]  = 0x0200 | ((blo & 0x0700) << 4) | ((blo & 0x00ff) << 0);

    // movt r2, #bhi
    isr[8]  = 0xf2c0 | ((bhi & 0x0800) >> 1) | ((bhi & 0xf000) >> 12);
    isr[9]  = 0x0200 | ((bhi & 0x0700) << 4) | ((bhi & 0x00ff) << 0);

    // bfc r3, #lsb, #32-lsb
    isr[18] = 0xf36f;
    isr[19] = 0x031f | ((size_msb & 0x1c) << 10) | ((size_msb & 0x03) << 6);

    // synchronize memory
    // NOTE: implicitly contains REORDER_BARRIER()
    __DSB();
    __ISB();

    GPI_TRACE_RETURN();
}

//**************************************************************************************************

// radio ISR
void LED_ISR(RADIO_IRQHandler, LED_RADIO_ISR)
{
    GPI_TRACE_FUNCTION_FAST();

    // disable PPI_START
    if (radio_state & RS_RAMP_UP)
    //if (BV_TEST_BY_NAME(NRF_RADIO->INTENSET, RADIO_INTENSET_READY, Enabled))
    {
        NRF_RADIO->INTENCLR = BV_BY_VALUE(RADIO_INTENCLR_READY, 1);
        NRF_PPI->CHENCLR    = BV(PPI_START);
        // NOTE: INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")

        timestamp_ready     = CCR_MAIN_START_READY_END - PPI_DELAY;

        radio_state += RS_RUNNING - RS_RAMP_UP;

        GPI_TRACE_RETURN_MSG_FAST(, "radio ready (ramped up)");
    }

    //assert(radio_state & RS_RUNNING);
    //assert(radio_state & (RS_TX_ACTIVE | RS_RX_ACTIVE));

    // if Tx active
    if (radio_state & RS_TX_ACTIVE)
    {
        //assert(BV_TEST_BY_NAME(NRF_RADIO->STATE, RADIO_STATE_STATE, Disabled));

        GPI_TRACE_MSG_FAST(TRACE_VERBOSE, "Tx done, disabling radio");

        // disable radio
        // NOTE: Although the radio subsystem is inactive hereafter, it is important to disable
        // specific shortcuts and PPI channels to ensure a clean state for the next radio operation.
        // NRF_RADIO->TASKS_DISABLE	= 1;	// already triggered via shortcut or PPI
        NRF_RADIO->INTENCLR = -1u;
        NRF_RADIO->SHORTS &= ~(BV_BY_VALUE(RADIO_SHORTS_TXREADY_START, 1) |
                               BV_BY_VALUE(RADIO_SHORTS_END_DISABLE, 1));
        NRF_PPI->CHENCLR = PPI_CHEN_TX_MASK | BV(PPI_TX_CONTROL) | BV(PPI_START);
        // NOTE: INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")

#if (DEBUG_GPIO && GPI_ARCH_IS_BOARD(nRF_PCA10056))
        NRF_GPIOTE->TASKS_CLR[GPIOTE_DEBUG1] = 1;
#endif

        // finalize Tx ack entry
        if (tx_ack.packet->is_tx_no_packet)
        {
            tx_ack.timestamp_ref = timestamp_ready;
            tx_ack.timestamp_end = tx_ccr_disable + PPI_DELAY; // PPI_DELAY: timer -> TASKS_DISABLE
        }
        else
        {
            tx_ack.timestamp_ref = CCR_MAIN_ADDRESS - PPI_DELAY - RADIO_TX_EVENT_ADDRESS_DELAY;
            tx_ack.timestamp_end = CCR_MAIN_START_READY_END - PPI_DELAY - RADIO_TX_EVENT_END_DELAY;
        }
        tx_ack.done = 1;

        // done
        radio_state = RS_IDLE;
        trigger_radio_event();
    }

    // if Rx active
    else
    {
        // if bit counter triggered
        if (radio_state & RS_BITCOUNTER_ACTIVE)
        //if (BV_TEST_BY_NAME(NRF_RADIO->INTENSET, RADIO_INTENSET_BCMATCH, Enabled))
        {
            if (NRF_RADIO->EVENTS_BCMATCH)
            {
                NRF_RADIO->INTENCLR = BV_BY_VALUE(RADIO_INTENCLR_BCMATCH, 1);
                // NOTE: INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")

                radio_state &= ~RS_BITCOUNTER_ACTIVE;

                // trigger event
                rx_intermediate_trigger_event = 1;
                trigger_radio_event();

                GPI_TRACE_RETURN_MSG_FAST(, "bit counter match");
            }
        }

        //assert(BV_TEST_BY_NAME(NRF_RADIO->STATE, RADIO_STATE_STATE, RxIdle));

        GPI_TRACE_MSG_FAST(TRACE_INFO, "packet received");

        // disable radio IRQ
        NRF_RADIO->INTENCLR  = -1u;

        Rx_Queue_Entry *q    = &rx_queue[rx_queue_num_written_radio % NUM_ELEMENTS(rx_queue)];
        Rssi_Buffer    *rssi = (Rssi_Buffer *) &rssi_space[q->rssi_space_num_written_begin %
                                                        NUM_ELEMENTS(rssi_space)];

        // arm delay timer (continue RSSI sampling for post-trigger time)
        {
            // 2 * PPI_DELAY: END -> CAPTURE, COMPARE -> DISABLE
            uint32_t stop_time = CCR_MAIN_START_READY_END - (2 * PPI_DELAY) -
                                 RADIO_RX_EVENT_END_DELAY + rssi->posttrigger_time;

            uint_fast32_t timeout = MAIN_TIMER->INTENSET & INTEN_MAIN_COMPARE;

            // if timeout enabled: restrict stop_time to timeout
            // (-> don't touch timeout timer if stop_time would exceed timeout)
            if (!timeout || (gpi_tick_compare_fast_native(stop_time, CCR_MAIN_COMPARE) < 0))
            {
                CCR_MAIN_COMPARE                             = stop_time;
                MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_COMPARE] = 0;
                MAIN_TIMER->INTENSET                         = INTEN_MAIN_COMPARE;

                if (gpi_tick_compare_fast_native(gpi_tick_fast_native(), stop_time) >= 0)
                {
                    NVIC_SetPendingIRQ(MAIN_TIMER_IRQ);

                    if (timeout)
                        GPI_TRACE_MSG_FAST(TRACE_WARNING,
                                           "ISR is late (%uus, extends RSSI posttrigger interval)",
                                           gpi_tick_fast_to_us(gpi_tick_fast_native() - stop_time));
                }
            }
        }

        // update packet status
        q->packet.timeout_triggered = 0;
    }

    GPI_TRACE_RETURN_FAST();
}

//**************************************************************************************************

// main timer ISR
void LED_ISR(MAIN_TIMER_ISR_NAME, LED_MAIN_TIMER_ISR)
{
    GPI_TRACE_FUNCTION_FAST();

    // if radio is idle and timer activated by radio_wake_at()
    if (RS_IDLE == radio_state)
    {
        MAIN_TIMER->INTENCLR = -1u;
        // INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")

        trigger_radio_event();
        GPI_TRACE_RETURN_FAST();
    }

    // if Tx active
    if (radio_state & RS_TX_ACTIVE)
    {
        // timer ISR is used to arm carrier_period_2
        // after carrier_period_1 is complete (and TASKS_START has been triggered)

        MAIN_TIMER->INTENCLR            = -1u;

        NRF_PPI->CHENCLR                = BV(PPI_TX_CONTROL);
        CCR_MAIN_COMPARE                = tx_ccr_disable;
        NRF_PPI->CH[PPI_TX_CONTROL].TEP = (uintptr_t) & (NRF_RADIO->TASKS_DISABLE);
        NRF_PPI->CHENSET                = BV(PPI_TX_CONTROL);

        GPI_TRACE_MSG(TRACE_VERBOSE,
                      "carrier period 1 passed, arming carrier period 2 (shutdown timer)");

        // check timeout
        Gpi_Fast_Tick_Native now = gpi_tick_fast_native();
        if (gpi_tick_compare_fast_native(now, tx_ccr_disable) >= 0)
        {
            NRF_RADIO->TASKS_DISABLE = 1;

            GPI_TRACE_MSG_FAST(TRACE_WARNING, "ISR is late (%uus), triggered DISABLE manually",
                               gpi_tick_fast_to_us(now - tx_ccr_disable));

            // NOTE: it is not critical if TASKS_DISABLE gets triggered twice
        }
    }

    // if Rx active
    else
    {
        assert(radio_state & RS_RX_ACTIVE);

// stop RSSI sampling
// ATTENTION: It is important to do this "gracefully" (i.e. do not break a sampling cycle)
// to ensure that number of trigger events and IRQs is consistent. We realize it as follows:
// * use CC[2] to generate a compare event when timer reaches an uncritical value
//   (outside of the potential event / IRQ pending range)
// * use a shortcut from CC[2] to TASKS_STOP
// As a prerequisite, CC[2] is set to an unreachable value in radio_start_rx(),
// so we know that the compare event will not trigger before we update CC[2].
#if DEBUG_RSSI
        RSSI_TIMER->CC[2] = 100;
#else
        RSSI_TIMER->CC[2] = 3;
#endif
        while (!(RSSI_TIMER->EVENTS_COMPARE[2]))
            ;

        // stop radio subsystem
        // NOTE: RSSI_TIMER is stopped (from above). RSSI_TIMER2 is also stopped because we are
        // outside of sampling activity (note that sampling IRQ has higher priority). Anyhow,
        // we add an explicit STOP command to be absolutely safe.
        // NOTE: Although the radio subsystem is inactive hereafter, it is important to deactivate
        // the PPI channels to ensure a clean state for the next radio operation (Rx or Tx).
        NRF_RADIO->TASKS_DISABLE      = 1;
        RSSI_TIMER2->TASKS_STOP       = 1;
        NRF_RADIO->INTENCLR           = -1u;
        MAIN_TIMER->INTENCLR          = -1u;
        RSSI_TIMER->INTENCLR          = -1u;
        NRF_PPI->CHENCLR              = PPI_CHEN_RX_MASK | BV(PPI_START);
        // RSSI_TIMER2_IRQ is not needed for the application.
        // It can be helpful for debugging purposes.
        //RSSI_TIMER2->INTENCLR		= -1u;
        // NOTE: INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")

        // prepare readout of RSSI_TIMER3
        RSSI_TIMER3->TASKS_CAPTURE[0] = 1;

#if (DEBUG_GPIO && GPI_ARCH_IS_BOARD(nRF_PCA10056))
        NRF_GPIOTE->TASKS_CLR[GPIOTE_DEBUG1] = 1;
#endif

        GPI_TRACE_MSG_FAST(TRACE_VERBOSE, "Rx done, disabling radio");

        // finalize Rx queue entry
        // ATTENTION: do not rely on rssi_space_num_written_radio because it may get updated in between by radio_drop_rssi_space()
        uint32_t        nw        = rx_queue_num_written_radio;
        Rx_Queue_Entry *q         = &rx_queue[nw % NUM_ELEMENTS(rx_queue)];
        Rssi_Buffer    *rssi      = (Rssi_Buffer *) &rssi_space[q->rssi_space_num_written_begin %
                                                        NUM_ELEMENTS(rssi_space)];

        q->packet.crc             = NRF_RADIO->RXCRC;
        q->packet.header_detected = NRF_RADIO->EVENTS_ADDRESS;
        q->packet.crc_ok          = q->packet.header_detected && NRF_RADIO->CRCSTATUS;
        q->timestamp_ref          = CCR_MAIN_ADDRESS - PPI_DELAY - RADIO_RX_EVENT_ADDRESS_DELAY;
        q->timestamp_end          = CCR_MAIN_START_READY_END - PPI_DELAY - RADIO_RX_EVENT_END_DELAY;

        rssi->timestamp_rssi_end  = CCR_MAIN_RSSI - PPI_DELAY;

        // ATTENTION: following computation must not produce rounding errors, i.e. ensure
        // that the timestamp's distance is an integer multiple of RSSI_SAMPLING_PERIOD
        // (otherwise ensure correct rounding or add the corresponding offset before division)
        uint32_t num_expected = (rssi->timestamp_rssi_end - timestamp_ready) / RSSI_SAMPLING_PERIOD;
        ASSERT_CT_WARN(IS_POWER_OF_2(RSSI_SAMPLING_PERIOD), slow_division_operation);

        rssi->num_missed             = num_expected - rssi->num_written;
        rssi->status                 = 0;
        rssi->early_readout_detected = (RSSI_TIMER3->CC[0] != num_expected);
        rssi->late_readout_detected  = RSSI_TIMER2->EVENTS_COMPARE[1];
        rssi->temperature            = (NRF_TEMP->EVENTS_DATARDY) ? NRF_TEMP->TEMP : INT16_MIN;
        rssi_space_num_written_radio = rssi_space_num_writing;

        rx_queue_num_written_radio   = ++nw;

        GPI_TRACE_MSG_FAST(TRACE_VERBOSE,
                           "RSSI ISR monitoring #expected = %u, #written = %u, TIMER3 = %u",
                           num_expected, rssi->num_written, RSSI_TIMER3->CC[0]);
        GPI_TRACE_MSG_FAST(TRACE_VERBOSE, "RSSI ISR monitoring CC = %3u %3u %3u %3u",
                           RSSI_TIMER2->CC[0], RSSI_TIMER2->CC[1], RSSI_TIMER2->CC[2],
                           RSSI_TIMER2->CC[3]);
        GPI_TRACE_MSG_FAST(TRACE_VERBOSE, "RSSI ISR monitoring EV = %3u %3u %3u %3u",
                           RSSI_TIMER2->EVENTS_COMPARE[0], RSSI_TIMER2->EVENTS_COMPARE[1],
                           RSSI_TIMER2->EVENTS_COMPARE[2], RSSI_TIMER2->EVENTS_COMPARE[3]);

        // done
        radio_state = RS_IDLE;
        trigger_radio_event();
    }

    GPI_TRACE_RETURN_FAST();
}

//**************************************************************************************************
/*
// RSSI_TIMER2_IRQ is not needed for the application.
// It can be helpful for debugging purposes to set a breakpoint or to log interesting information.
void RSSI_TIMER2_ISR_NAME()
{
	GPI_TRACE_FUNCTION_FAST();

	RSSI_TIMER2->INTENCLR = -1u;

	GPI_TRACE_MSG_FAST(1, "main CC: %08x %08x %08x", MAIN_TIMER->CC[2], MAIN_TIMER->CC[3], MAIN_TIMER->CC[4]);

	RSSI_TIMER2->TASKS_CAPTURE[3] = 1;
	GPI_TRACE_MSG_FAST(1, "RSSI_TIMER2 value: %u", RSSI_TIMER2->CC[3]);

	GPI_TRACE_MSG_FAST(1, "samples_num_written: %u", rssi_buffer.samples_num_written);

	GPI_TRACE_RETURN_FAST();
}
*/
//**************************************************************************************************

// start radio gracefully
static Gpi_Fast_Tick_Native radio_start(Gpi_Fast_Tick_Native start_tick,
                                        volatile uint32_t   *start_task)
{
    GPI_TRACE_FUNCTION();

    Gpi_Fast_Tick_Native delay = 0;
    Gpi_Fast_Tick_Native now;

    REORDER_BARRIER();

    // this part is time-critical
    // ATTENTION: do not set breakpoints directly on start instructions,
    // it can disturb the timing (delay in the break handler between
    // executing the instruction and releasing exceptions / interrupts)

    // enable PPI channel that starts the radio (time-triggered)
    NRF_PPI->CHENSET = BV(PPI_START);

    // if start tick is in the past and radio not started: do it manually
    // NOTE: this can happen if we were late with enabling PPI_START
    now              = gpi_tick_fast_native();
    if (gpi_tick_compare_fast_native(now, start_tick) >= 0)
    {
        // wait a bit before evaluating state (maybe we are very close behind successful PPI start)
        gpi_micro_sleep(1);

        // if radio still off: start it manually
        if (BV_TEST_BY_NAME(NRF_RADIO->STATE, RADIO_STATE_STATE, Disabled))
        //if ((NRF_RADIO->STATE & RADIO_STATE_STATE_Msk) != ramp_up_state)
        {
            register Gpi_Fast_Tick_Native t1, t2;

            t1          = gpi_tick_fast_native();
            *start_task = 1;
            t2          = gpi_tick_fast_native();

            // t1 = (t1 + t2) / 2 (= mean(t1,t2)) with wrap-around handling
            t1 >>= 1;
            t2 >>= 1;
            if (t2 < t1) t2 |= 1 << (sizeof(Gpi_Fast_Tick_Native) * 8 - 1);
            t1 += t2;

            delay = t1 - start_tick;

            GPI_TRACE_MSG(TRACE_WARNING, "missed radio start time, started manually (%uus delayed)",
                          gpi_tick_fast_to_us(delay));
        }
    }
    else
        GPI_TRACE_MSG(TRACE_VERBOSE, "armed radio, start time buffer: %uus",
                      gpi_tick_fast_to_us(start_tick - now));

    GPI_TRACE_RETURN(delay);
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

void radio_init()
{
    GPI_TRACE_FUNCTION();

// We expect that this function is called once during system init, with peripherals
// in reset state (more or less). The following block demonstrates our assumptions.
#if 1
    NRF_RADIO->TASKS_DISABLE = 1;
    RSSI_TIMER->TASKS_STOP   = 1;
    RSSI_TIMER2->TASKS_STOP  = 1;
    RSSI_TIMER3->TASKS_STOP  = 1;
    NRF_MWU->REGIONENCLR =
            BV_BY_NAME_PREEXP(CONCAT(MWU_REGIONENCLR_RGN, RSSI_MWU_REGION, RA), Clear);
    NRF_PPI->CHENCLR      = PPI_CHEN_TX_MASK | PPI_CHEN_RX_MASK | BV(PPI_START);
    // NOTE: STOP takes	effect within one PCLK16M cycle	(4413_417 v1.2 6.3.30)
    NRF_RADIO->INTENCLR   = -1u;
    MAIN_TIMER->INTENCLR  = -1u;
    RSSI_TIMER->INTENCLR  = -1u;
    RSSI_TIMER2->INTENCLR = -1u;
    RSSI_TIMER3->INTENCLR = -1u;
    NRF_MWU->INTENCLR = BV_BY_NAME_PREEXP(CONCAT(MWU_INTENCLR_PREGION, RSSI_MWU_REGION, RA), Clear);
    NRF_TEMP->INTENCLR = -1u;
    // NOTE: INTENCLR takes effect within 4 CPU clock cycles (4413_417 v1.2 p. 100 "Interrupt clearing")
#endif

    rx_queue_num_writing         = 0;
    rx_queue_num_written_radio   = 0;
    rssi_space_num_writing       = 0;
    rssi_space_num_written_radio = 0;

    radio_state                  = RS_IDLE;

    assert(BV_TEST_BY_NAME(NRF_RADIO->MODECNF0, RADIO_MODECNF0_RU, Fast));

    // disable FPU context preservation
    // ATTENTION: Automatic FPU context preservation may increase ISR latency to a value that
    // is too high for the time critical RSSI sampling routine. It should work with lazy stacking
    // because this seems interruptible (https://developer.arm.com/documentation/ka001321/latest)
    // and the RSSI ISR does not use the FPU. If lazy stacking is not interruptible, it can cause
    // trouble even without using the FPU in the RSSI ISR (if the FPU is used in other ISRs).
    // (I don't see any reason to doubt https://developer.arm.com/documentation/ka001321/latest,
    // but it should be tested for sure).
    // NOTE: We do not rely on __FPU_USED (a compiler generated macro) because different objects
    // may have been compiled with different settings.
    if (SCB->CPACR & (0xF << 20))
    {
        GPI_TRACE_MSG(TRACE_WARNING, "warning: FPU enabled, disabling FP context preservation");
        FPU->FPCCR &= ~(FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk);
        //__DSB();
        //__ISB();
    }

    // connect RADIO shortcuts (those which can stay active all the time)
    NRF_RADIO->SHORTS = BV_BY_NAME(RADIO_SHORTS_RXREADY_START, Enabled) |
                        BV_BY_NAME(RADIO_SHORTS_ADDRESS_BCSTART, Enabled);

    // set MAXLEN to avoid buffer overruns
    NRF_RADIO->PCNF1 = (NRF_RADIO->PCNF1 & ~RADIO_PCNF1_MAXLEN_Msk) |
                       BV_BY_VALUE(RADIO_PCNF1_MAXLEN, sizeof_field(Radio_Packet, raw_payload));


    // configure RSSI sample clock
    // NOTE: The nRF52840 Product Specification is unclear regarding the timing of the COMPARE->CLEAR
    // shortcut. In particular, it is unclear if there is a delay between the moment when the timer
    // reaches the CC value and CLEAR taking effect (in other words: does the timer indeed reach CC
    // and have this value for > 0 PCLK cycles, or does it flip from CC - 1 to 0). We conducted a
    // small experiment (routing the COMPARE event via PPI to a GPIO pin and measuring the frequency)
    // and found that the shortcut takes effect without delay (i.e. count sequence = CC-2, CC-1, 0, ...).
    RSSI_TIMER->MODE        = BV_BY_NAME(TIMER_MODE_MODE, Timer);
    RSSI_TIMER->PRESCALER   = BV_BY_VALUE(TIMER_PRESCALER_PRESCALER, 0); // 16MHz
    RSSI_TIMER->BITMODE     = BV_BY_NAME(TIMER_BITMODE_BITMODE, 16Bit);
    RSSI_TIMER->TASKS_CLEAR = 1;
#if DEBUG_RSSI
    RSSI_TIMER->CC[1] = RSSI_SAMPLING_PERIOD;
    RSSI_TIMER->CC[0] = RSSI_SAMPLING_PERIOD - 10;
#else
    RSSI_TIMER->CC[1] = RSSI_SAMPLING_PERIOD;     // triggers IRQ
    RSSI_TIMER->CC[0] = RSSI_SAMPLING_PERIOD - 0; // triggers RSSISTART
#endif
    //RSSI_TIMER->CC[2]		= -1u;		// -> radio_start_rx()
    RSSI_TIMER->SHORTS = BV_BY_NAME(TIMER_SHORTS_COMPARE1_CLEAR, Enabled) |
                         BV_BY_NAME(TIMER_SHORTS_COMPARE2_STOP, Enabled);

    // configure RSSI ISR monitoring
    RSSI_TIMER2->MODE      = BV_BY_NAME(TIMER_MODE_MODE, Timer);
    RSSI_TIMER2->PRESCALER = BV_BY_VALUE(TIMER_PRESCALER_PRESCALER, 0); // 16MHz
    RSSI_TIMER2->BITMODE   = BV_BY_NAME(TIMER_BITMODE_BITMODE, 08Bit);
    //RSSI_TIMER2->BITMODE	= BV_BY_NAME(TIMER_BITMODE_BITMODE, 32Bit);
    RSSI_TIMER2->SHORTS    = 0; // BV_BY_NAME(TIMER_SHORTS_COMPARE1_STOP, Enabled);
    RSSI_TIMER2->CC[0] =
            3; // minimum margin (must be reached), event routed to RSSI_TIMER3->TASKS_COUNT
    RSSI_TIMER2->CC[1]                     = 14; // deadline (must not be reached)
    RSSI_TIMER2->CC[2]                     = 11; // optional, can be used for profiling / debugging
    RSSI_TIMER2->CC[3]                     = 15; // optional, can be used for profiling / debugging
    RSSI_TIMER3->MODE                      = BV_BY_NAME(TIMER_MODE_MODE, Counter);
    RSSI_TIMER3->BITMODE                   = BV_BY_NAME(TIMER_BITMODE_BITMODE, 32Bit);
    RSSI_TIMER3->SHORTS                    = 0;
    RSSI_TIMER3->TASKS_START               = 1;
    NRF_MWU->REGION[RSSI_MWU_REGION].START = (uintptr_t) & (NRF_RADIO->RSSISAMPLE);
    NRF_MWU->REGION[RSSI_MWU_REGION].END =
            (uintptr_t) & (NRF_RADIO->RSSISAMPLE) + sizeof(NRF_RADIO->RSSISAMPLE) - 1;
    NRF_MWU->REGIONENSET = BV_BY_NAME_PREEXP(CONCAT(MWU_REGIONENSET_RGN, RSSI_MWU_REGION, RA), Set);

// configure temperature sensor -> nothing to do
// NOTE: erratum [66] is handled in SystemInit()


// configure debug/trace GPIOs
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    NRF_GPIOTE->CONFIG[GPIOTE_DEBUG1] = BV_BY_NAME(GPIOTE_CONFIG_MODE, Task) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PSEL, LSB(LED_RSSI_TIMER)) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PORT, 0) |
                                        BV_BY_NAME(GPIOTE_CONFIG_POLARITY, Toggle) |
                                        BV_BY_NAME(GPIOTE_CONFIG_OUTINIT, Low);
    NRF_GPIOTE->CONFIG[GPIOTE_DEBUG2] = BV_BY_NAME(GPIOTE_CONFIG_MODE, Task) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PSEL, LSB(LED_RSSI_ACTIVE)) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PORT, 0) |
                                        BV_BY_NAME(GPIOTE_CONFIG_POLARITY, Toggle) |
                                        BV_BY_NAME(GPIOTE_CONFIG_OUTINIT, Low);
  #elif GPI_ARCH_IS_BOARD(nRF_PCA10056)
    //GPIO_DEBUG1_Px->OUTCLR = BV(GPIO_DEBUG1_PIN);
    //GPIO_DEBUG1_Px->PIN_CNF[GPIO_DEBUG1_PIN] =
    //	BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)	|
    //	BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)	|
    //	BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)	|
    //	BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)	|
    //	BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
    NRF_GPIOTE->CONFIG[GPIOTE_DEBUG1] = BV_BY_NAME(GPIOTE_CONFIG_MODE, Task) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PSEL, GPIO_DEBUG1_PIN) |
                                        BV_BY_VALUE(GPIOTE_CONFIG_PORT, GPIO_DEBUG1_PORT) |
                                        BV_BY_NAME(GPIOTE_CONFIG_POLARITY, Toggle) |
                                        BV_BY_NAME(GPIOTE_CONFIG_OUTINIT, Low);
  #endif
#endif


    // make PPI connections

    // MAIN_TIMER.COMPARE[START] -> RADIO.ENABLE etc. (on demand)
    // MAIN_TIMER.COMPARE[START] -> TEMP.START
    NRF_PPI->CH[PPI_START].EEP =
            (uintptr_t) & (MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_START_READY_END]);
    // NRF_PPI->CH[PPI_START].TEP = ...	-> radio_start_rx(), radio_start_tx()
    NRF_PPI->FORK[PPI_START].TEP = (uintptr_t) & (NRF_TEMP->TASKS_START);

    // RADIO.READY -> RSSI_TIMER.START
    // RADIO.READY -> MAIN_TIMER.CAPTURE[READY]
    NRF_PPI->CH[PPI_READY].EEP   = (uintptr_t) & (NRF_RADIO->EVENTS_READY);
    NRF_PPI->CH[PPI_READY].TEP   = (uintptr_t) & (RSSI_TIMER->TASKS_START);
    NRF_PPI->FORK[PPI_READY].TEP =
            (uintptr_t) & (MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_START_READY_END]);

    // RADIO.ADDRESS -> MAIN_TIMER.CAPTURE[ADDRESS]
    NRF_PPI->CH[PPI_ADDRESS].EEP = (uintptr_t) & (NRF_RADIO->EVENTS_ADDRESS);
    NRF_PPI->CH[PPI_ADDRESS].TEP = (uintptr_t) & (MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_ADDRESS]);
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(nRF_PCA10056)
    NRF_PPI->FORK[PPI_ADDRESS].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_OUT[GPIOTE_DEBUG1]);
  #endif
#endif

    //	// RADIO.PAYLOAD -> MAIN_TIMER.CAPTURE[PAYLOAD]
    //	NRF_PPI->CH[PPI_PAYLOAD].EEP = (uintptr_t)&(NRF_RADIO->EVENTS_PAYLOAD);
    //	NRF_PPI->CH[PPI_PAYLOAD].TEP = (uintptr_t)&(MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_PAYLOAD]);

    // RADIO.END -> MAIN_TIMER.CAPTURE[END]
    NRF_PPI->CH[PPI_END].EEP = (uintptr_t) & (NRF_RADIO->EVENTS_END);
    NRF_PPI->CH[PPI_END].TEP = (uintptr_t) & (MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_START_READY_END]);
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(nRF_PCA10056)
    NRF_PPI->FORK[PPI_END].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_OUT[GPIOTE_DEBUG1]);
  #endif
#endif

    // MAIN_TIMER.COMPARE[COMPARE] -> RADIO.START etc. (on demand)
    NRF_PPI->CH[PPI_TX_CONTROL].EEP = (uintptr_t) & (MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_COMPARE]);
// NRF_PPI->CH[PPI_TX_CONTROL].TEP = ... -> radio_start_tx()
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(nRF_PCA10056)
    NRF_PPI->FORK[PPI_TX_CONTROL].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_OUT[GPIOTE_DEBUG1]);
  #endif
#endif

    // RSSI_TIMER.COMPARE[0] -> RADIO.RSSISTART
    // RSSI_TIMER.COMPARE[0] -> MAIN_TIMER.CAPTURE[RSSI_START]
    NRF_PPI->CH[PPI_RSSI_START].EEP = (uintptr_t) & (RSSI_TIMER->EVENTS_COMPARE[0]);
    NRF_PPI->CH[PPI_RSSI_START].TEP = (uintptr_t) & (NRF_RADIO->TASKS_RSSISTART);
#if DEBUG_RSSI
    NRF_PPI->FORK[PPI_RSSI_START].TEP =
            (uintptr_t) & (MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_RSSI_START]);
#endif
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    NRF_PPI->CH[PPI_DEBUG1].EEP   = (uintptr_t) & (RSSI_TIMER->EVENTS_COMPARE[0]);
    NRF_PPI->CH[PPI_DEBUG1].TEP   = (uintptr_t) & (NRF_GPIOTE->TASKS_SET[GPIOTE_DEBUG1]);
    NRF_PPI->FORK[PPI_DEBUG1].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_SET[GPIOTE_DEBUG2]);
  #endif
#endif

    // RADIO.RSSIEND -> RSSI_TIMER2.START
    // RADIO.RSSIEND -> MAIN_TIMER.CAPTURE[RSSI]
    NRF_PPI->CH[PPI_RSSI_END].EEP   = (uintptr_t) & (NRF_RADIO->EVENTS_RSSIEND);
    NRF_PPI->CH[PPI_RSSI_END].TEP   = (uintptr_t) & (RSSI_TIMER2->TASKS_START);
    NRF_PPI->FORK[PPI_RSSI_END].TEP = (uintptr_t) & (MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_RSSI]);

    // RSSI_TIMER2.COMPARE[0] -> RSSI_TIMER3.COUNT
    NRF_PPI->CH[PPI_RSSI_COUNT].EEP = (uintptr_t) & (RSSI_TIMER2->EVENTS_COMPARE[0]);
    NRF_PPI->CH[PPI_RSSI_COUNT].TEP = (uintptr_t) & (RSSI_TIMER3->TASKS_COUNT);
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    NRF_PPI->FORK[PPI_RSSI_COUNT].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_CLR[GPIOTE_DEBUG1]);
  #endif
#endif

    // MWU.RSSISAMPLE -> RSSI_TIMER2.STOP+CLEAR
    NRF_PPI->CH[PPI_RSSI_MWU].EEP   = (uintptr_t) & (NRF_MWU->EVENTS_REGION[RSSI_MWU_REGION].RA);
    NRF_PPI->CH[PPI_RSSI_MWU].TEP   = (uintptr_t) & (RSSI_TIMER2->TASKS_STOP);
    NRF_PPI->FORK[PPI_RSSI_MWU].TEP = (uintptr_t) & (RSSI_TIMER2->TASKS_CLEAR);
#if DEBUG_GPIO
  #if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
    NRF_PPI->CH[PPI_DEBUG2].EEP = (uintptr_t) & (NRF_MWU->EVENTS_REGION[RSSI_MWU_REGION].RA);
    NRF_PPI->CH[PPI_DEBUG2].TEP = (uintptr_t) & (NRF_GPIOTE->TASKS_CLR[GPIOTE_DEBUG2]);
  #endif
#endif

// for debugging / profiling: capture RSSI timestamps (instead of radio events)
#if 0
		NRF_PPI->CH[PPI_ADDRESS].EEP = (uintptr_t)&(RSSI_TIMER->EVENTS_COMPARE[0]);
		NRF_PPI->CH[PPI_PAYLOAD].EEP = (uintptr_t)&(NRF_MWU->EVENTS_REGION[RSSI_MWU_REGION].RA);
#endif

    // enable PPI channels -> radio_start_rx() / radio_start_tx()
    //NRF_PPI->CHENSET = ...;


    // arm IRQs

    ASSERT_CT(GPI_ARM_INTLOCK_PRIORITY >= 1);

    NVIC_SetPriority(RADIO_IRQn, 1);
    NVIC_ClearPendingIRQ(RADIO_IRQn);
    NVIC_EnableIRQ(RADIO_IRQn);

    NVIC_SetPriority(MAIN_TIMER_IRQ, 1);
    NVIC_ClearPendingIRQ(MAIN_TIMER_IRQ);
    NVIC_EnableIRQ(MAIN_TIMER_IRQ);

    NVIC_SetPriority(RSSI_IRQ, 0);
    NVIC_ClearPendingIRQ(RSSI_IRQ);
    NVIC_EnableIRQ(RSSI_IRQ);

    // RSSI_TIMER2_IRQ is not needed for the application.
    // It can be helpful for debugging purposes.
    //NVIC_SetPriority(RSSI_TIMER2_IRQ, 1);
    //NVIC_ClearPendingIRQ(RSSI_TIMER2_IRQ);
    //NVIC_EnableIRQ(RSSI_TIMER2_IRQ);


    GPI_TRACE_RETURN();
}

//**************************************************************************************************

Gpi_Fast_Tick_Native radio_start_rx(Gpi_Fast_Tick_Native start_tick, Gpi_Fast_Tick_Native timeout,
                                    int_fast16_t         intermediate_trigger_pos,
                                    uint8_t              intermediate_trigger_preset_content,
                                    uint_fast32_t        min_rssi_buffer_size,
                                    Gpi_Fast_Tick_Native rssi_pretrigger_time,
                                    Gpi_Fast_Tick_Native rssi_posttrigger_time)
{
    GPI_TRACE_FUNCTION();

    // assumed state (radio subsystem): initialized, idle (prior Rx/Tx finished)

    assert(RS_IDLE == radio_state);
    radio_state = RS_RX_RAMP_UP;

    Gpi_Fast_Tick_Native start_tick_internal, timeout_tick, delay;

    // account for ramp-up time + PPI delay
    start_tick_internal            = start_tick - PPI_DELAY - RADIO_RX_RAMP_UP_TIME;
    timeout_tick                   = start_tick + timeout - PPI_DELAY;

    // allocate rx queue destination slot
    Rx_Queue_Entry *q              = &rx_queue[rx_queue_num_written_radio % NUM_ELEMENTS(rx_queue)];
    NRF_RADIO->PACKETPTR           = (uintptr_t) & (q->packet.ble_header);
    rx_queue_num_writing           = rx_queue_num_written_radio + 1;

    // init packet status
    q->packet.trx_status           = 0;
    q->packet.timeout_triggered    = 1;

    // prepare RSSI sampling
    // NOTE: RSSI_TIMER2->EVENTS_COMPARE[0,2,3] need not be reset to ensure functionality.
    // They are reset only for the TRACE/log messages printed after Rx has finished.
    // Do not reset them if you prefer cumulated information.
    RSSI_TIMER->TASKS_CLEAR        = 1;
    RSSI_TIMER2->TASKS_CLEAR       = 1;
    RSSI_TIMER3->TASKS_CLEAR       = 1;
    RSSI_TIMER->CC[2]              = -1u;
    RSSI_TIMER->EVENTS_COMPARE[2]  = 0;
    RSSI_TIMER2->EVENTS_COMPARE[0] = 0; // see NOTE
    RSSI_TIMER2->EVENTS_COMPARE[1] = 0;
    RSSI_TIMER2->EVENTS_COMPARE[2] = 0; // see NOTE
    RSSI_TIMER2->EVENTS_COMPARE[3] = 0; // see NOTE
    {
        int_fast8_t size_msb;
        uint32_t    sample_buffer_size;

#if DEBUG_RSSI
        min_rssi_buffer_size = MAX(min_rssi_buffer_size, 64);
#else
        min_rssi_buffer_size = MAX(min_rssi_buffer_size, 1);
#endif

        size_msb = gpi_get_msb(min_rssi_buffer_size);
        size_msb += ((1 << size_msb) != min_rssi_buffer_size) ? 1 : 0;
        size_msb           = MAX(size_msb, 2); // use word-aligned buffers
        size_msb           = MIN(size_msb, MSB(sizeof(rssi_space) - sizeof(Rssi_Buffer)));
        sample_buffer_size = 1 << size_msb;

        uint32_t nw        = rssi_space_num_written_radio;
        uint32_t size      = sizeof(Rssi_Buffer) + sample_buffer_size;
        uint32_t space     = sizeof(rssi_space) - (nw % sizeof(rssi_space));

        if (size > space)
        {
            GPI_TRACE_MSG(TRACE_VERBOSE, "RSSI buffer skipping %u bytes", space);
            nw += space;
            rssi_space_num_written_radio = nw;
        }

        if ((int32_t) (rssi_space_num_writing - nw) < (int32_t) size)
            rssi_space_num_writing = nw + size;

        assert(!(nw % 4));
        assert(!(rssi_space_num_writing % 4));
        assert(!(size % 4));

        GPI_TRACE_MSG(TRACE_VERBOSE, "RSSI buffer: size 0x%x, nw_buf 0x%08x, nw_hot 0x%08x",
                      sample_buffer_size, nw, rssi_space_num_writing);

        q->rssi_space_num_written_begin = nw;

        Rssi_Buffer *rssi      = (Rssi_Buffer *) &rssi_space[nw % NUM_ELEMENTS(rssi_space)];

        rssi->size_msb         = size_msb;
        rssi->pretrigger_time  = rssi_pretrigger_time;
        rssi->posttrigger_time = rssi_posttrigger_time;
        rssi->num_written      = 0;

        adopt_rssi_isr(rssi->samples, size_msb);
    }

    // prepare temperature measurement (needed for RSSI temperature compensation)
    NRF_TEMP->EVENTS_DATARDY      = 0;

    // arm timeout timer
    CCR_MAIN_COMPARE              = timeout_tick;

    // use CCR_MAIN_START_READY_END to start radio via PPI
    CCR_MAIN_START_READY_END      = start_tick_internal;
    NRF_PPI->CH[PPI_START].TEP    = (uintptr_t) & (NRF_RADIO->TASKS_RXEN);

    // enable PPI channels (except for PPI_START)
    NRF_PPI->CHENSET              = PPI_CHEN_RX_MASK;

    // arm bitcounter
    // intermediate_trigger_pos is defined as byte offset relative to raw_payload[0]
    // TODO: test if CI and TERM1 are counted in 125k and 500k modes
    rx_intermediate_trigger_event = 0;
    if (intermediate_trigger_pos >= 0)
    {
        // 16 = S0, LEN; +1 to trigger *after* the field has been received
        NRF_RADIO->BCC                                  = 16 + ((intermediate_trigger_pos + 1) * 8);
        q->packet.raw_payload[intermediate_trigger_pos] = intermediate_trigger_preset_content;
        radio_state |= RS_BITCOUNTER_ACTIVE;
    }
    else NRF_RADIO->BCC = -1u; // far beyond end of packet

    // clear interrupt events and unmask IRQs
    NRF_RADIO->EVENTS_READY   = 0;
    NRF_RADIO->EVENTS_ADDRESS = 0;
    NRF_RADIO->EVENTS_PAYLOAD = 0;
    NRF_RADIO->EVENTS_END     = 0;
    NRF_RADIO->EVENTS_BCMATCH = 0;
    NRF_RADIO->INTENSET =
            BV_BY_VALUE(RADIO_INTENSET_READY, 1) | // used to disable PPI_START
            BV_BY_VALUE(RADIO_INTENSET_END, 1) |
            ((intermediate_trigger_pos >= 0) ? BV_BY_VALUE(RADIO_INTENSET_BCMATCH, 1) : 0);
    //BV_BY_VALUE(RADIO_INTENSET_ADDRESS, 1) |
    RSSI_TIMER->EVENTS_COMPARE[1] = 0;
    RSSI_TIMER->INTENSET          = BV_BY_VALUE(TIMER_INTENSET_COMPARE1, 1);

    // RSSI_TIMER2_IRQ is not needed for the application.
    // It can be helpful for debugging purposes.
    //RSSI_TIMER2->EVENTS_COMPARE[3] = 0;
    //RSSI_TIMER2->INTENSET = BV_BY_VALUE(TIMER_INTENSET_COMPARE3, 1);

    REORDER_BARRIER();

    // start
    // this part is time-critical
    // ATTENTION: do not set breakpoints directly on start instructions,
    // it can disturb the timing (delay in the break handler between
    // executing the instruction and releasing exceptions / interrupts)

    if (timeout > 0)
    {
        // trigger timeout immediately if timeout_tick is in the past or too close in the future
        Gpi_Fast_Tick_Native now = gpi_tick_fast_native();
        if (gpi_tick_compare_fast_native(now + RADIO_RX_RAMP_UP_TIME, timeout_tick) >= 0)
        {
            // start RSSI timer (normally done by NRF_RADIO->EVENTS_READY)
            // ATTENTION: without doing so the ISR would run into an endless loop
            // (waiting for the graceful stop event)
            // NOTE: also capture the timestamp of our fake READY event (again, normally triggered
            // by NRF_RADIO->EVENTS_READY). This is necessary to compute the number of expected
            // RSSI samples (see ISR). The inaccurate timing due to manual activation may cause
            // a little hickup in this regard (together with the fact that we disable the RSSI IRQ,
            // i.e. num samples written = 0), which is acceptable in the situation we are here.
            RSSI_TIMER->INTENCLR                                = -1u;
            RSSI_TIMER->TASKS_START                             = 1;
            timestamp_ready                                     = now;
            MAIN_TIMER->TASKS_CAPTURE[CCI_MAIN_START_READY_END] = 1;

            NVIC_SetPendingIRQ(MAIN_TIMER_IRQ);
            GPI_TRACE_MSG(TRACE_WARNING, "timeout triggered immediately");

            if (gpi_tick_compare_fast_native(now, start_tick) >= 0) start_tick = now;

            GPI_TRACE_RETURN(start_tick);
        }

        // unmask timeout IRQ
        MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_COMPARE] = 0;
        MAIN_TIMER->INTENSET                         = INTEN_MAIN_COMPARE;
    }

    // start radio gracefully
    delay = radio_start(start_tick_internal, &(NRF_RADIO->TASKS_RXEN));
    if (delay)
    {
        NRF_TEMP->TASKS_START = 1;
        start_tick += delay;
    }

    GPI_TRACE_RETURN(start_tick);
}

//**************************************************************************************************

Gpi_Fast_Tick_Native radio_start_tx(Gpi_Fast_Tick_Native start_tick,
                                    Gpi_Fast_Tick_Native carrier_period_1,
                                    Gpi_Fast_Tick_Native carrier_period_2,
                                    const Radio_Packet  *packet)
{
    GPI_TRACE_FUNCTION();

    Gpi_Fast_Tick_Native air_time;
    Gpi_Fast_Tick_Native start_tick_internal, cp1_internal;
    Gpi_Fast_Tick_Native x;

    // assumed state (radio subsystem): initialized, idle (prior Rx/Tx finished)
    assert(RS_IDLE == radio_state);

    // init ack status
    tx_ack.packet = packet;
    tx_ack.done   = 0;

    air_time      = (packet->is_tx_no_packet)
                            ? 0
                            : radio_get_packet_airtime(gpi_radio_get_mode(), packet->raw_payload_length);

    // catch potential timer overruns
    x             = carrier_period_1 + carrier_period_2;
    assert((x >= carrier_period_1) && (x < (-10000u - air_time)));

    // if there is no frame to send
    if (packet->is_tx_no_packet)
    {
        // merge carrier periods
        carrier_period_2 += carrier_period_1;
        carrier_period_1 = 0;

        // skip activation of radio if nothing to do
        if (!carrier_period_2)
        {
            tx_ack.timestamp_ref = start_tick;
            tx_ack.timestamp_end = start_tick;
            tx_ack.done          = 1;

            // NOTE: depending on the caller, trigger_radio_event() may not be necessary here
            // (if caller checks tx_ack.done anyhow after return). however, we don't rely on
            // such application-specific behavior
            trigger_radio_event();

            GPI_TRACE_RETURN(start_tick);
        }
    }

    // ensure minimum carrier periods to avoid race conditions
    // NOTE: oscillator drift is not an issue because transmitter is in sync with itself
    // ATTENTION: do not change carrier_period_1 (catch only), as this would impact timestamp_ref
    // and disturb scheduler synchronization
    x = GPI_TICK_US_TO_FAST(5);
    assert(!(carrier_period_1 && (carrier_period_1 < x)));
    if (carrier_period_1 && (carrier_period_1 < x))
    {
        GPI_TRACE_MSG(TRACE_ERROR, "carrier period 1 < min. (%u < %u = %uus)", carrier_period_1, x,
                      gpi_tick_fast_to_us(x));
    }
    if (carrier_period_2 && (carrier_period_2 < x))
    {
        GPI_TRACE_MSG(TRACE_WARNING, "extending carrier period 2 from %u to %u (%uus)",
                      carrier_period_2, x, gpi_tick_fast_to_us(x));
        carrier_period_2 = x;
    }

    radio_state          = RS_TX_RAMP_UP;

    // account for ramp-up time + PPI delay
    start_tick_internal  = start_tick - PPI_DELAY - RADIO_TX_RAMP_UP_TIME;
    cp1_internal         = carrier_period_1;

    // init DMA data pointer
    NRF_RADIO->PACKETPTR = (uintptr_t) & (packet->ble_header);

    // connect shortcuts and PPI channels (those used only with Tx)
    // NOTE: we use shortcuts or PPI to ensure that turn-on and turn-off delays
    // are not influenced by software runtime
    if (!(packet->is_tx_no_packet))
    {
        // nRF spec. states that TASKS_TXEN -> EVENTS_READY has a typical jitter of 0.25us
        // [t_READYJITTER in 4413_417 v1.2 6.20.15.10].
        // Hence, for the sake of precise timing we avoid using the TXREADY->START shortcut and
        // trigger TASKS_START manually RADIO_TX_RAMP_UP_TOLERANCE after the nominal ramp-up time.
        // At the same time we adjust start_tick_internal to compensate the delay (so
        // RADIO_TX_RAMP_UP_TOLERANCE is visible in an early ramp-up, but it does not shift start_tick).
        // NOTE: We keep the source code using the shortcut for testing purposes.
        if (!carrier_period_1)
        {
            cp1_internal = RADIO_TX_RAMP_UP_TOLERANCE;
            start_tick_internal -= RADIO_TX_RAMP_UP_TOLERANCE;
        }

        if (cp1_internal) NRF_PPI->CH[PPI_TX_CONTROL].TEP = (uintptr_t) & (NRF_RADIO->TASKS_START);
        else NRF_RADIO->SHORTS |= BV_BY_NAME(RADIO_SHORTS_TXREADY_START, Enabled);
    }
    if (carrier_period_2)
    {
        // + start_tick follows below
        tx_ccr_disable =
                carrier_period_1 + air_time + carrier_period_2 - PPI_DELAY - RADIO_TX_DISABLE_DELAY;

        if (!cp1_internal)
            NRF_PPI->CH[PPI_TX_CONTROL].TEP = (uintptr_t) & (NRF_RADIO->TASKS_DISABLE);
        // else done in timer ISR

        // NOTE: In contrast to READY->START, we allow using the shortcut for END->DISABLE
        // since this is less critical (has no impact on important timestamps).
    }
    else NRF_RADIO->SHORTS |= BV_BY_NAME(RADIO_SHORTS_END_DISABLE, Enabled);

    // use CCR_MAIN_START_READY_END to start radio via PPI
    CCR_MAIN_START_READY_END   = start_tick_internal;
    NRF_PPI->CH[PPI_START].TEP = (uintptr_t) & (NRF_RADIO->TASKS_TXEN);

    // enable PPI channels (except for PPI_START and PPI_TX_CONTROL)
    NRF_PPI->CHENSET           = PPI_CHEN_TX_MASK;

    // clear interrupt events and unmask IRQs
    NRF_RADIO->EVENTS_READY    = 0;
    //NRF_RADIO->EVENTS_ADDRESS		= 0;
    //NRF_RADIO->EVENTS_PAYLOAD		= 0;
    //NRF_RADIO->EVENTS_END			= 0;
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->INTENSET        = BV_BY_VALUE(RADIO_INTENSET_READY, 1) | // used to disable PPI_START
                          BV_BY_VALUE(RADIO_INTENSET_DISABLED, 1);

    REORDER_BARRIER();

    // start
    // ATTENTION: this part is time-critical
    // NOTE: after start we have about 40us (ramp-up delay) to complete the following instructions

    start_tick += radio_start(start_tick_internal, &(NRF_RADIO->TASKS_TXEN));

    // NOTE: tx_ccr_disable is used whenever carrier_period_2 > 0
    tx_ccr_disable += start_tick;

    if (cp1_internal)
    {
        // timer -> PPI_TX_CONTROL -> TASKS_START
        CCR_MAIN_COMPARE = start_tick + carrier_period_1 - PPI_DELAY - RADIO_TX_START_DELAY;
        NRF_PPI->CHENSET = BV(PPI_TX_CONTROL);

        // enable timer IRQ to arm carrier_period_2 in timer ISR
        if (carrier_period_2)
        {
            MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_COMPARE] = 0;
            MAIN_TIMER->INTENSET                         = INTEN_MAIN_COMPARE;
        }
    }

    else if (carrier_period_2) // && !carrier_period_1 (from else)
    {
        // timer -> PPI_TX_CONTROL -> TASKS_DISABLE
        CCR_MAIN_COMPARE = tx_ccr_disable;
        NRF_PPI->CHENSET = BV(PPI_TX_CONTROL);
    }

    // catch timeout
    // ATTENTION: avoid that radio transmits carrier forever
    x = gpi_tick_fast_native();
    if (gpi_tick_compare_fast_native(x, start_tick) >= 0)
    {
        MAIN_TIMER->INTENCLR     = -1u;
        NRF_PPI->CHENCLR         = BV(PPI_TX_CONTROL);
        NRF_RADIO->TASKS_DISABLE = 1;

        assert((x < start_tick, 0));
        while (0)
            ;
    }

    GPI_TRACE_RETURN(start_tick);
}

//**************************************************************************************************

// compute theoretical timestamp of reference event (= EVENTS_ADDRESS in case of BLE)
// relative to start of packet (TASKS_START)
Gpi_Fast_Tick_Native radio_get_ref_timestamp_offset(Gpi_Radio_Mode mode)
{
    GPI_TRACE_FUNCTION();

    Gpi_Fast_Tick_Native ref_delay;

    switch (mode)
    {
        // PREAMBLE + ADDRESS
        case BLE_1M: ref_delay = GPI_TICK_US_TO_FAST(8 + 32); break;
        case BLE_2M: ref_delay = GPI_TICK_US_TO_FAST(8 + 16); break;
        case BLE_125k:
        case BLE_500k: ref_delay = GPI_TICK_US_TO_FAST(80 + 256); break;
        default: GPI_TRACE_MSG(TRACE_ERROR, "invalid radio mode: %d!!!", mode); assert(0);
    }

    GPI_TRACE_RETURN(ref_delay);
}

//**************************************************************************************************

// compute nominal packet airtime
Gpi_Fast_Tick_Native radio_get_packet_airtime(Gpi_Radio_Mode mode, uint_fast8_t payload_length)
{
    GPI_TRACE_FUNCTION();

    Gpi_Fast_Tick_Native airtime;

    switch (mode)
    {
            // field lengths:	PREAMBLE	ADDRESS		CI		TERM1		PDU			CRC		TERM2
            // always [bit]:				 32							(2...258)*8		24
            // 1M:				 8, 8us		 32us		0		0						 24us	0
            // 2M:				16, 8us		 16us		0		0						 12us	0
            // 125k:			80,80us		256us		2,16us	3,24us					192us	3,24us
            // 500k:			80,80us		256us		2,16us	3,24us					 48us	3, 6us
            //
            // PDU:				S0			LENGTH		S1		PAYLOAD
            // always [bit]:	8			8			0		(0...255)*8
            // (S1 = 8 bit if Constant Tone Extension is used)

        case BLE_1M:
            airtime = GPI_TICK_US_TO_FAST(8 + 32 + 0 + 0 + 16 + 24 + 0) +
                      (GPI_TICK_US_TO_FAST(8) * payload_length);
            break;
        case BLE_2M:
            airtime = GPI_TICK_US_TO_FAST(8 + 16 + 0 + 0 + 8 + 12 + 0) +
                      (GPI_TICK_US_TO_FAST(4) * payload_length);
            break;
        case BLE_125k:
            airtime = GPI_TICK_US_TO_FAST(80 + 256 + 16 + 24 + 128 + 192 + 24) +
                      (GPI_TICK_US_TO_FAST(64) * payload_length);
            break;
        case BLE_500k:
            airtime = GPI_TICK_US_TO_FAST(80 + 256 + 16 + 24 + 32 + 48 + 6) +
                      (GPI_TICK_US_TO_FAST(16) * payload_length);
            break;
        default: GPI_TRACE_MSG(TRACE_ERROR, "invalid radio mode: %d!!!", mode); assert(0);
    }

    GPI_TRACE_RETURN(airtime);
}

//**************************************************************************************************

// update rssi_space_num_written_radio from the outside in a safe way,
void radio_update_rssi_num_written(uint32_t rx_queue_nr, uint32_t rssi_space_nw)
{
    GPI_TRACE_FUNCTION();

    register int ie = gpi_int_lock();

    if (!(radio_state & RS_RX_ACTIVE) && (rx_queue_nr == rx_queue_num_written_radio))
        rssi_space_num_written_radio = rssi_space_nw;

    gpi_int_unlock(ie);

    GPI_TRACE_RETURN();
}

//**************************************************************************************************

// drop all rssi data
void radio_drop_rssi_space()
{
    GPI_TRACE_FUNCTION();

    register uint32_t nw;

    // ATTENTION: this function must not interrupt radio_start_rx()
    // (if this is required then use gpi_int_lock() in radio_start_rx() too)

    register int      ie         = gpi_int_lock();

    nw                           = rssi_space_num_writing + NUM_ELEMENTS(rssi_space);
    rssi_space_num_writing       = nw;
    rssi_space_num_written_radio = nw;

    gpi_int_unlock(ie);

    GPI_TRACE_RETURN();
}

//**************************************************************************************************

// generate event at specified time
void radio_wake_at(Gpi_Fast_Tick_Native tick)
{
    GPI_TRACE_FUNCTION();

    assert(RS_IDLE == radio_state);
    while (RS_IDLE != radio_state)
        ;

    CCR_MAIN_COMPARE                             = tick;
    MAIN_TIMER->EVENTS_COMPARE[CCI_MAIN_COMPARE] = 0;

    int ie                                       = gpi_int_lock();

    MAIN_TIMER->INTENSET                         = INTEN_MAIN_COMPARE;
    if (gpi_tick_compare_fast_native(gpi_tick_fast_native(), tick) >= 0)
        NVIC_SetPendingIRQ(MAIN_TIMER_IRQ);

    gpi_int_unlock(ie);

    GPI_TRACE_RETURN();
}

//**************************************************************************************************
//**************************************************************************************************
