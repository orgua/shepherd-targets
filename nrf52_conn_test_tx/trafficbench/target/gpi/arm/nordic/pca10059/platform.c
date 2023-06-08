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
 *	@file					gpi/arm/nordic/pca10059/platform.c
 *
 *	@brief					platform interface functions
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Fabian Mager
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/
//***** Trace Settings *****************************************************************************
/*
#include <gpi/trace.h>

// message groups for TRACE messages (used in GPI_TRACE_MSG() calls)
// define groups appropriate for your needs, assign one bit per group
// values > GPI_TRACE_LOG_USER (i.e. upper 8 bits) are reserved
#define TRACE_GROUP1		0x00000001
#define TRACE_GROUP2		0x00000002

// select active message groups, i.e., the messages to be printed (others will be dropped)
GPI_TRACE_CONFIG(<TODO: module name>, TRACE_BASE_SELECTION |  GPI_TRACE_LOG_USER);
*/
//**************************************************************************************************
//**** Includes ************************************************************************************

#include "gpi/tools.h"
#include "gpi/platform_spec.h"
#include "gpi/platform.h"
#include "gpi/interrupts.h"
#include "gpi/clocks.h"
#include "gpi/trace.h"

#include <nrf.h>

#include "gpi/resource_check.h"

GPI_RESOURCE_RESERVE_SHARED(NRF_UARTE, 0);

// main clock resources are reserved in ../nrf52840/clocks.c

//#if ((GPI_TRACE_MODE & GPI_TRACE_MODE_TRACE) && GPI_TRACE_USE_DSR)
//	GPI_RESOURCE_RESERVE(TODO);		// GPI_TRACE_DSR_IRQ
//#endif

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

#define WARNING(msg)	WARNING2(GCC warning msg)
#define WARNING2(msg)	_Pragma (#msg)
	
// issue default value warnings (see platform.h for details)
#ifdef _GPI_STDOUT_UART_BAUDRATE_DEFAULT_WARNING
	WARNING(_GPI_STDOUT_UART_BAUDRATE_DEFAULT_WARNING)
#endif
#ifdef _GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY_DEFAULT_WARNING
	WARNING(_GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY_DEFAULT_WARNING)
#endif
#ifdef _GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS_DEFAULT_WARNING
	WARNING(_GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS_DEFAULT_WARNING)
#endif
#ifdef _GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE_DEFAULT_WARNING
	WARNING(_GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE_DEFAULT_WARNING)
#endif

#ifdef _GPI_ARM_nRF_PCA10059_UART_TXD_PORT
	#define ENABLE_UART		1
#else
	#define ENABLE_UART		0
#endif

#define PCLK16_RATE			16000000u

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************



//**************************************************************************************************
//***** Forward Declarations ***********************************************************************



//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************



//**************************************************************************************************
//***** Global Variables ***************************************************************************

uint_fast8_t		gpi_wakeup_event = 0;

//**************************************************************************************************
//***** Local Functions ****************************************************************************

// init (reset) CPU core to defined state
// this function can be moved to generic ARM code if helpful
static void core_init()
{
	// NOTE: some of the regs are already initialized for sure (since program arrived here)

	gpi_int_disable();
	__set_BASEPRI(0);
	__set_FAULTMASK(0);
	__set_CONTROL(0);		// no floating point-context, use MSP, privileged level
	__DSB();
	__ISB();

	// disable MPU
	MPU->CTRL = 0;

	// TODO: enable FPU if requested

	// TODO: setup Traps and Fault Exception Handlers (if requested)
	// -> regs. in System Control Block

	// TODO: setup SysTick timer if requested
}

//**************************************************************************************************
#if ENABLE_UART

// init UART
// TODO: maybe make it a public function in platform.h (params: baudrate, flags (like HW flow control))
// NOTE: if function is inlined and baudrate is constant then it gets well optimized
static inline void uart_init(uint32_t baudrate)
{
	assert(baudrate <= 1000000);		// see spec. UARTE features

	// TODO: if enabled: STOPTX/RX

	// disable UART during reconfiguration
	NRF_UARTE0->ENABLE = BV_BY_NAME(UARTE_ENABLE_ENABLE, Disabled);

	// configure pins

	NRF_UARTE0->PSEL.RTS = BV_BY_NAME(UARTE_PSEL_RTS_CONNECT, Disconnected);
	NRF_UARTE0->PSEL.CTS = BV_BY_NAME(UARTE_PSEL_CTS_CONNECT, Disconnected);

	NRF_UARTE0->PSEL.TXD =
		BV_BY_VALUE(UARTE_PSEL_TXD_PORT, _GPI_ARM_nRF_PCA10059_UART_TXD_PORT)	|
		BV_BY_VALUE(UARTE_PSEL_TXD_PIN,  _GPI_ARM_nRF_PCA10059_UART_TXD_PIN)	|
		BV_BY_NAME(UARTE_PSEL_TXD_CONNECT, Connected);

	NRF_UARTE0->PSEL.RXD =
		BV_BY_VALUE(UARTE_PSEL_RXD_PORT, _GPI_ARM_nRF_PCA10059_UART_RXD_PORT)	|
		BV_BY_VALUE(UARTE_PSEL_RXD_PIN,  _GPI_ARM_nRF_PCA10059_UART_RXD_PIN)	|
		BV_BY_NAME(UARTE_PSEL_RXD_CONNECT, Connected);

	// set UART mode: 8 data bits, 1 stop bit, no parity
	NRF_UARTE0->CONFIG =
		BV_BY_NAME(UARTE_CONFIG_HWFC, Disabled)		|
		BV_BY_NAME(UARTE_CONFIG_PARITY, Excluded)	|
		BV_BY_NAME(UARTE_CONFIG_STOP, One);

	// set baudrate
	// Unfortunately, the documentation for the register value is very meager.
	// It seems that the baudrate is generated from PCLK16M by an up-counter issuing one tick
	// per overflow and the BAUDRATE register contains the increment value of that counter.
	// The increment can be approximated as BAUDRATE (>)= baudrate * 2^32 / 16000000.
	// It seems that the counter is 20 bit wide (i.e. only the upper bits of BAUDRATE are used).
	// The following posts confirm the observations:
	// https://devzone.nordicsemi.com/f/nordic-q-a/391/uart-baudrate-register-values#post-id-1194
	// https://devzone.nordicsemi.com/f/nordic-q-a/27666/uart-baudrate-nrf52
	switch (baudrate)
	{
		// use official values for common baudrates
		case   1200:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud1200;		break;
		case   2400:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud2400;		break;
		case   4800:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud4800;		break;
		case   9600:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud9600;		break;
		case  14400:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud14400;	break;
		case  19200:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud19200;	break;
		case  28800:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud28800;	break;
		case  38400:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud38400;	break;
		case  56000:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud56000;	break;
		case  57600:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud57600;	break;
		case  76800:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud76800;	break;
		case 115200:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200;	break;
		case 230400:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud230400;	break;
		case 460800:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud460800;	break;
		case 921600:	NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud921600;	break;

		// approximate other baudrates
		// NOTE: The computation is exact for power-of-two dividers, so we do not need to
		// provide explicit values for baudrates like 31250, 250000, or 1000000.
		default:
		{
			NRF_UARTE0->BAUDRATE = ((UINT64_C(0x100000000) * baudrate) + 8000000) / 16000000;
			break;
		}
	}

	// (un)mask interrupts
	#if GPI_STDOUT_INTERRUPT_ENABLED
		NRF_UARTE0->INTEN = BV_BY_NAME(UARTE_INTEN_ENDTX, Enabled);
		NVIC_SetPriority(UARTE0_UART0_IRQn, GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY);
		NVIC_ClearPendingIRQ(UARTE0_UART0_IRQn);
		NVIC_EnableIRQ(UARTE0_UART0_IRQn);
	#else
		NRF_UARTE0->INTEN = 0;
	#endif
	
	// start UART
	NRF_UARTE0->ENABLE = BV_BY_NAME(UARTE_ENABLE_ENABLE, Enabled);
}

#endif	// ENABLE_UART

//**************************************************************************************************
//***** Global Functions ***************************************************************************

void gpi_platform_init()
{
	// GPI_TRACE_FUNCTION -> don't TRACE because HW not ready

	int	i;

	// we assume bare-metal programming
	// If there is an underlying OS, the init code needs to be adapted.
	ASSERT_CT(GPI_ARCH_IS_OS(NONE));

	// NOTE: We assume that gpi_platform_init() is called in the init process after a reset event,
	// i.e., most of the registers are assumed to have their reset values. To perform a full system
	// init from an arbitrary state, reset the device manually (e.g. use NVIC_SystemReset() from CMSIS).


	// init (reset) CPU core to defined state
	core_init();

	// enable instruction cache
	// TODO: make that configurable, disable if program runs from RAM
	// NOTE: benefit of cache is application dependent
	// - decreases latency on hit (0 ws.), but increases latency on miss (3 vs. 2 wait states)
	// - can decrease or increase power consumption (with high and low hit rate, respectively)
	// NOTE: it is possible to profile the hit rate, see spec. for details
	NRF_NVMC->ICACHECNF =
		BV_BY_NAME(NVMC_ICACHECNF_CACHEEN, Enabled)	|
		BV_BY_NAME(NVMC_ICACHECNF_CACHEPROFEN, Disabled);

	// check UICR settings
	// - the settings may be application (not just board) specific -> do not touch them here
	// - PSELRESET is handled in nRF startup code (see CONFIG_NFCT_PINS_AS_GPIOS)
	// - NFCPINS is handled in nRF startup code (see CONFIG_NFCT_PINS_AS_GPIOS)

	// (re)init POWER settings
	NRF_POWER->INTENCLR = -1u;
	NRF_POWER->POFCON = BV_BY_NAME(POWER_POFCON_POF, Disabled);
	NRF_POWER->DCDCEN = BV_BY_NAME(POWER_DCDCEN_DCDCEN, Enabled);		// set REG1 to DC/DC mode
	NRF_POWER->DCDCEN0 = BV_BY_NAME(POWER_DCDCEN0_DCDCEN, Disabled);	// set REG0 to DC/DC mode (if enabled)
	for (i = 0; i <= 8; ++i)
		NRF_POWER->RAM[i].POWER = 0x0000FFFF;	// all RAM sections enabled, no retention during System OFF

	// disable watchdog
	// -> not possible if it is running already

	// disable all PPI channels
	NRF_PPI->CHEN = 0;


	// init I/O ports
	// NOTE: We do this before clock init because the latter takes some time. The goal is to
	// configure all pins into a compatible state as fast as possible to avoid (or at least shorten)
	// any high-current situations.

	// stop HFXO (if running), switch HFCLK to HFINT
	// NOTE: by doing so, we (explicitly) ensure that the CPU runs independent from external
	// signals, which is important while reconfiguring the I/O ports
//	if (NRF_CLOCK->HFCLKSTAT & CLOCK_HFCLKSTAT_STATE_Msk)
		NRF_CLOCK->TASKS_HFCLKSTOP = 1;

	// set default GPIO config: input, enable pullup or pulldown (for unconnected pins)
	// NOTE: enable pullup or pulldown on unconnected pins to ensure defined logic levels
	// (floating pins can increase power consumption)
	// NOTE: Considering the nRF52840 specification (4413_417 v1.0 Figure 43) it is not clear
	// if the pullup/down is effective / needed when the pad is disconnected (PIN_CNF.INPUT = 0).
	// We enable it for sure.
	// NOTE: PIN_CNF[i].DIR and DIR.PIN[i] reflect the same setting
	for (i = 0; i < 32; ++i)
	{
		NRF_P0->PIN_CNF[i] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Pulldown)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	}

	for (i = 0; i < 16; ++i)
	{
		NRF_P1->PIN_CNF[i] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Pulldown)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	}

	// configure used pins (others use default config from above)
	// n.c. = not connected, a.s. = application specific (connected to pin header)

	// P0.00 / XL1 (D2): used as XL1 (LFXO in, connected to X2)
	NRF_P0->PIN_CNF[0] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.01 / XL2 (F2): used as XL2 (LFXO out, connected to X2)
	NRF_P0->PIN_CNF[1] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.02 / AIN0 (A12): a.s.
	// P0.03 / AIN1 (B13): n.c.
	// P0.04 / AIN2 (J1) : a.s.
	// P0.05 / AIN3 (K2) : n.c.

	// P0.06 (L1): LED1
	NRF_P0->PIN_CNF[6] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	NRF_P0->OUTSET = BV(6); // active low

	// P0.07 (M2) : n.c.
	
	// P0.08 (N1): LED2_R
	NRF_P0->PIN_CNF[8] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	NRF_P0->OUTSET = BV(8); // active low

	// P0.09 / NFC1 (L24): a.s.
	// P0.10 / NFC2 (J24): a.s.
	// P0.11 (T2): a.s. / TRACEDATA2

	// P0.12 (U1): LED2_B / TRACEDATA1
	NRF_P0->PIN_CNF[12] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	NRF_P0->OUTSET = BV(12); // active low

	// P0.13 (AD8) : a.s.
	// P0.14 (AC9) : a.s.
	// P0.15 (AD10): a.s.
	// P0.16 (AC11): n.c.
	// P0.17 (AD12): a.s.

	// P0.18 / nRESET (AC13): used as RESET (connected to SW2)
	NRF_P0->PIN_CNF[18] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.19 (AC15): connected to RESET (SW2)
	NRF_P0->PIN_CNF[19] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.20 (AD16): a.s.

	// P0.21 (AC17): connected to RESET (SW2)
	NRF_P0->PIN_CNF[21] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.22 (AD18): a.s.

	// P0.23 (AC19): connected to RESET (SW2)
	NRF_P0->PIN_CNF[23] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.24 (AD20): a.s.

	// P0.25 (AC21): connected to RESET (SW2)
	NRF_P0->PIN_CNF[25] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P0.26 (G1): a.s.
	// P0.27 (H2): n.c.
	// P0.28 / AIN4 (B11): n.c.
	// P0.29 / AIN5 (A10): a.s.
	// P0.30 / AIN6 (B9) : n.c.
	// P0.31 / AIN7 (A8) : a.s.
	
	// P1.00 (AD22): a.s. / TRACEDATA0
	// P1.01 (Y23) : a.s.
	// P1.02 (W24) : a.s.
	// P1.03 (V23) : n.c.
	// P1.04 (U24) : a.s.
	// P1.05 (T23) : n.c.

	// P1.06 (R24): button SW1
	NRF_P1->PIN_CNF[6] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	// P1.07 (P23): a.s.
	// P1.08 (P2) : n.c.

	// P1.09 (R1): LED2_G / TRACEDATA3
	NRF_P1->PIN_CNF[9] =
		BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
		BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
		BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
		BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
		BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
	NRF_P1->OUTSET = BV(9); // active low

	// P1.10 (A20): a.s.
	// P1.11 (B19): a.s.
	// P1.12 (B17): n.c.
	// P1.13 (A16): a.s.
	// P1.14 (B15): n.c. (board revision 1.x.x) / GND (board revision 2.0.0)
	// P1.15 (A14): a.s.

	// application specific connections of PC10059 based FlockLab target
	#if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
	
		// P0.13 (AD8): LED1 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[13] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		NRF_P0->OUTCLR = BV(13);
		
		// P0.15 (AD10): LED2 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[15] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		NRF_P0->OUTCLR = BV(15);
		
		// P0.17 (AD12): LED3 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[17] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		NRF_P0->OUTCLR = BV(17);
		
		// P0.20 (AD16): INT1 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[20] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		NRF_P0->OUTCLR = BV(20);
		
		// P0.22 (AD18): INT2 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[22] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		NRF_P0->OUTCLR = BV(22);
		
		// P0.24 (AD20): UART RXD
		NRF_P0->PIN_CNF[24] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
		
		// P0.29 / AIN5 (A10): SIG2 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[29] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			
		// P0.31 / AIN7 (A8): SIG1 (FlockLab GPIO signal name)
		NRF_P0->PIN_CNF[31] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

		// P1.10 (A20): UART TXD
		NRF_P1->OUTSET = BV(10);
		NRF_P1->PIN_CNF[10] =
			BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
			BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
			BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
			BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
			BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);

	#endif	// GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
	

	// init clock system
	// NOTE: this should be done before initializing other peripherals

	// setup:
	// HFCLK: 64MHz from XO (XO running with 32MHz)
	// LFCLK: 32768Hz from XO
	// TIMERx (fast clock): 16MHz from PCLK16M, 32-bit timer
	// RTCx (slow clock): 32768Hz from LFCLK

	// ATTENTION: the CPU is running, so some valid configuration is already there. When we change
	// the settings, we must take care that the CPU keeps running for sure after every single step.
	// Hence, the order of changes has to be designed with care.

	// stop HFXO (if running), implicitly switch HFCLK to HFINT
//	if (NRF_CLOCK->HFCLKSTAT & CLOCK_HFCLKSTAT_STATE_Msk)
		NRF_CLOCK->TASKS_HFCLKSTOP = 1;

	// stop LFXO (if running)
//	if (NRF_CLOCK->LFCLKSTAT & CLOCK_LFCLKSTAT_STATE_Msk)
		NRF_CLOCK->TASKS_LFCLKSTOP = 1;

	// init CLOCK module
	NRF_CLOCK->INTENCLR = -1u;
	NRF_CLOCK->LFCLKSRC =
		BV_BY_NAME(CLOCK_LFCLKSRC_SRC, Xtal)		|
		BV_BY_NAME(CLOCK_LFCLKSRC_BYPASS, Disabled)	|
		BV_BY_NAME(CLOCK_LFCLKSRC_EXTERNAL, Disabled);
	NRF_CLOCK->HFXODEBOUNCE =
		BV_BY_VALUE(CLOCK_HFXODEBOUNCE_HFXODEBOUNCE, 0x40);

	// start HFXO
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
	NRF_CLOCK->TASKS_HFCLKSTART = 1;

	// start LFXO
	NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
	NRF_CLOCK->TASKS_LFCLKSTART = 1;

	// init fast-clock timer
	{
		_gpi_clocks_fast_timer->TASKS_STOP = 1;

		// wait a bit to make sure that STOP gets processed
		// (see spec. 4413_417 v1.0 page 422 "Task delays")
		// ATTENTION: since we stopped the timer, we cannot use it to measure time.
		// Therefore we use some nops here.
		for (i = 4; i-- > 0;)
			__NOP();

		_gpi_clocks_fast_timer->SHORTS 		= 0;
		_gpi_clocks_fast_timer->INTENCLR 	= -1u;
		_gpi_clocks_fast_timer->MODE 		= BV_BY_NAME(TIMER_MODE_MODE, Timer);
		_gpi_clocks_fast_timer->BITMODE 	= BV_BY_NAME(TIMER_BITMODE_BITMODE, 32Bit);

		ASSERT_CT(PCLK16_RATE == (PCLK16_RATE / GPI_FAST_CLOCK_RATE) * GPI_FAST_CLOCK_RATE, GPI_FAST_CLOCK_RATE_invalid);
		ASSERT_CT(IS_POWER_OF_2(PCLK16_RATE / GPI_FAST_CLOCK_RATE), GPI_FAST_CLOCK_RATE_invalid);
		ASSERT_CT(MSB(PCLK16_RATE / GPI_FAST_CLOCK_RATE) <= 9, GPI_FAST_CLOCK_RATE_invalid);

		_gpi_clocks_fast_timer->PRESCALER 	=
			BV_BY_VALUE(TIMER_PRESCALER_PRESCALER, MSB(PCLK16_RATE / GPI_FAST_CLOCK_RATE));

		_gpi_clocks_fast_timer->TASKS_START = 1;
	}

	// init RTC (slow clock)
	{
		_gpi_clocks_rtc->TASKS_STOP = 1;

		// NOTE: The spec. does not mention anything that we have to wait a bit after STOP.
		// If there are any troubles, check again.

		_gpi_clocks_rtc->INTENCLR	= -1u;
		_gpi_clocks_rtc->EVTEN		= BV_BY_VALUE(RTC_EVTENSET_TICK, 1);
			// EVENTS_TICK is needed for ready-polling below and (optionally) VHT

		ASSERT_CT(32768 == (32768 / GPI_SLOW_CLOCK_RATE) * GPI_SLOW_CLOCK_RATE, GPI_SLOW_CLOCK_RATE_invalid);
		ASSERT_CT((32768 / GPI_SLOW_CLOCK_RATE) <= 0x1000, GPI_SLOW_CLOCK_RATE_too_low);

		_gpi_clocks_rtc->PRESCALER	= (32768 / GPI_SLOW_CLOCK_RATE) - 1;

		_gpi_clocks_rtc->TASKS_START = 1;
	}

	// if VHT: use PPI to connect RTC->EVENTS_TICK to TIMER->TASKS_CAPTURE
	#if GPI_HYBRID_CLOCK_USE_VHT

		NRF_PPI->CH[GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL].EEP =
			(uintptr_t)&(_gpi_clocks_rtc->EVENTS_TICK);

		NRF_PPI->CH[GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL].TEP =
			(uintptr_t)&(_gpi_clocks_fast_timer->TASKS_CAPTURE[GPI_ARM_NRF_HYBRID_CLOCK_CAPTURE_REG]);

		NRF_PPI->CHENSET = BV(GPI_ARM_NRF_HYBRID_CLOCK_PPI_CHANNEL);

	#endif


	// init UART
	// ATTENTION: before using the UART HFCLK must be stable too
	#if ENABLE_UART
		uart_init(GPI_STDOUT_UART_BAUDRATE);
	#endif


	// wait until clocks are stable
	// ATTENTION: The clocks are not reliable before. However, we can interleave all init tasks
	// that do not rely on clock accuracy.
	// ATTENTION: Since LFCLK may have been unstable when we initialized the RTC (see above),
	// we wait until RTC started up for sure (see spec. 4413_417 v1.0 page 339 START task delay)
	while (!(NRF_CLOCK->EVENTS_HFCLKSTARTED && NRF_CLOCK->EVENTS_LFCLKSTARTED));
	_gpi_clocks_rtc->EVENTS_TICK = 0;
	while (!(_gpi_clocks_rtc->EVENTS_TICK));

	// if !VHT: disable RTC->EVENTS_TICK (not needed anymore)
	#if !GPI_HYBRID_CLOCK_USE_VHT
		_gpi_clocks_rtc->EVTENCLR = BV_BY_VALUE(RTC_EVTENSET_TICK, 1);
	#endif


	// init TRACE DSR
	#if (GPI_TRACE_MODE_IS_TRACE && GPI_TRACE_USE_DSR)
		NVIC_SetPriority(GPI_TRACE_DSR_IRQ, 0xff);
		NVIC_ClearPendingIRQ(GPI_TRACE_DSR_IRQ);
		NVIC_EnableIRQ(GPI_TRACE_DSR_IRQ);
	#endif


	// GPI_TRACE_RETURN();
}

//**************************************************************************************************

void gpi_sleep()
{
	// disable interrupts, set PRIMASK = 1
	gpi_int_disable();

	// mark that CPU comes from power-down
	// this flag can be evaluated by the application
	// NOTE: to be meaningful, the first ISR taken after power-up should clear it
	gpi_wakeup_event = 1;

	// set control registers such that CPU will wake-up but not enter ISR, i.e., program returns here
	// (see ARM Cortex-M4 Generic User Guide (DUI 0553A ID121610) "2.5.2 Wakeup from sleep mode" for details)
	// NOTE: PRIMASK has already been set to 1 by gpi_int_disable() above
//	__set_FAULTMASK(0);
//	__set_PRIMASK(1);

	// enter power-down (if no IRQ pending)
	// NOTE: enabled interrupts work as wake-up events even if PRIMASK = 0
	// NOTE: SCR settings are assumed to be configured by the application (fitting her needs)
	__WFI();

	// sleep...

	// restore standard behavior
	// NOTE: PRIMASK = 0 reenables interrupts. In consequence, pending IRQ(s) will be taken.
	__set_PRIMASK(0);
}

//**************************************************************************************************

void gpi_nrf_uicr_erase()
{
	// set erase-enable mode
	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
	NRF_NVMC->CONFIG = BV_BY_NAME(NVMC_CONFIG_WEN, Een);

	// erase UICR
	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
	NRF_NVMC->ERASEUICR = BV_BY_NAME(NVMC_ERASEUICR_ERASEUICR, Erase);

	// go back to read-only mode
	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
	NRF_NVMC->CONFIG = BV_BY_NAME(NVMC_CONFIG_WEN, Ren);

	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
}

//**************************************************************************************************

void gpi_nrf_uicr_write(uintptr_t dest, const void *src, size_t size)
{
	dest = MAX(dest, sizeof(NRF_UICR->CUSTOMER));
	size = MAX(size, sizeof(NRF_UICR->CUSTOMER) - dest);

	if (0 == size)
		return;

	// set write-enable mode
	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
	NRF_NVMC->CONFIG = BV_BY_NAME(NVMC_CONFIG_WEN, Wen);

	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));

	// write UICR words
	while (size > 0)
	{
		uint_fast8_t	n = dest & 0x3;
		uint32_t		t;

		// assemble aligned 32-bit data word
		t = 0xffffffff;
		memcpy((uint8_t*)&t + n, src, MIN(4 - n, size));
		n = MIN(4 - n, size);

		// write data word
		// ATTENTION: there seems to be some timing issue with READYNEXT (observed with
		// optimization level 3 enabled). We add a tiny sleep period to circumvent that.
		// The sleep does not hurt because writing a single word takes much more time
		// anyhow (4413_417 v1.0: typ. 41us).
		while (!BV_TEST_BY_NAME(NRF_NVMC->READYNEXT, NVMC_READYNEXT_READYNEXT, Ready));
		NRF_UICR->CUSTOMER[dest >> 2] = t;
		gpi_micro_sleep(2);

		src = (const uint8_t*)src + n;
		dest += n;
		size -= n;
	}

	// go back to read-only mode
	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
	NRF_NVMC->CONFIG = BV_BY_NAME(NVMC_CONFIG_WEN, Ren);

	while (!BV_TEST_BY_NAME(NRF_NVMC->READY, NVMC_READY_READY, Ready));
}

//**************************************************************************************************
//**************************************************************************************************
