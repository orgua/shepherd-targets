/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2024, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/nrf528xx/platform_internal.h
 *
 *	@brief					internal nRF528xx platform functions
 *
 *	@version				$Id: de20daccc233eb492af35c36706759f6fe901534 $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_nRF528xx_PLATFORM_INTERNAL_H__
#define __GPI_ARM_nRF528xx_PLATFORM_INTERNAL_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "gpi/platform_spec.h"

#include "gpi/tools.h"
#include "gpi/platform.h"		// get internal settings
#include "gpi/interrupts.h"

#include <nrf.h>

#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// bitfield macros for CMSIS register definitions

#define BV_BY_NAME(field, value)	((field ## _ ## value << field ## _Pos) & field ## _Msk)
#define BV_BY_VALUE(field, value)	(((value) << field ## _Pos) & field ## _Msk)
//#define BV_BY_NAME(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)
//#define BV_BY_VALUE(field, value)	ASSERT_CT_EVAL(LSB(field ## _Msk) == field ## _Pos)

// with intermediate macro expansion
#define BV_BY_NAME_PREEXP(field, value)		BV_BY_NAME(field, value)
#define BV_BY_VALUE_PREEXP(field, value)	BV_BY_VALUE(field, value)

#define BV_TEST_BY_NAME(reg, field, value)	(BV_BY_NAME(field, value) == ((reg) & field ## _Msk))
#define BV_TEST_BY_VALUE(reg, field, value)	(BV_BY_VALUE(field, value) == ((reg) & field ## _Msk))

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************



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

// init (reset) CPU core to defined state
// this function can be moved to generic ARM code if helpful
static inline void core_init()
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
	// NOTE: UART gets initialized even if no external pins are used
	// because other functions may rely on it
	{
		__typeof__(NRF_P0) port;

		// TXD
		#ifdef _GPI_ARM_nRF_UART_TXD_PORT
			port = (_GPI_ARM_nRF_UART_TXD_PORT) ? NRF_P1 : NRF_P0;
			port->OUTSET = BV(_GPI_ARM_nRF_UART_TXD_PIN);
			port->PIN_CNF[_GPI_ARM_nRF_UART_TXD_PIN] =
				BV_BY_NAME(GPIO_PIN_CNF_DIR, Output)		|
				BV_BY_NAME(GPIO_PIN_CNF_INPUT, Disconnect)	|
				BV_BY_NAME(GPIO_PIN_CNF_PULL, Disabled)		|
				BV_BY_NAME(GPIO_PIN_CNF_DRIVE, S0S1)		|
				BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			NRF_UARTE0->PSEL.TXD =
				BV_BY_VALUE(UARTE_PSEL_TXD_PORT, _GPI_ARM_nRF_UART_TXD_PORT)	|
				BV_BY_VALUE(UARTE_PSEL_TXD_PIN,  _GPI_ARM_nRF_UART_TXD_PIN)		|
				BV_BY_NAME(UARTE_PSEL_TXD_CONNECT, Connected);
		#else
			NRF_UARTE0->PSEL.TXD =
				BV_BY_NAME(UARTE_PSEL_TXD_CONNECT, Disconnected);
		#endif

		// RXD
		#ifdef _GPI_ARM_nRF_UART_RXD_PORT
			port = (_GPI_ARM_nRF_UART_RXD_PORT) ? NRF_P1 : NRF_P0;
			NRF_P0->PIN_CNF[_GPI_ARM_nRF_UART_RXD_PIN] =
				BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
				BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
				BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)		|
				BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			NRF_UARTE0->PSEL.RXD =
				BV_BY_VALUE(UARTE_PSEL_RXD_PORT, _GPI_ARM_nRF_UART_RXD_PORT)	|
				BV_BY_VALUE(UARTE_PSEL_RXD_PIN,  _GPI_ARM_nRF_UART_RXD_PIN)		|
				BV_BY_NAME(UARTE_PSEL_RXD_CONNECT, Connected);
		#else
			NRF_UARTE0->PSEL.RXD =
				BV_BY_NAME(UARTE_PSEL_RXD_CONNECT, Disconnected);
		#endif
		
		// RTS
		// So far, we do not support flow control in receive direction (= stdin). But:
		// ATTENTION: Interface MCU on PCA10056 uses RTS to perform dynamic flow control detection
		// (see Dev. Kit User Guide 4440_050 v1.1 section 7.2.1 for details).
		// Pull RTS low / high to signal that flow control is used / unused.
		#if GPI_ARCH_IS_BOARD(nRF_PCA10056)
			port = (_GPI_ARM_nRF_UART_RTS_PORT) ? NRF_P1 : NRF_P0;
			#if GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE
				port->OUTCLR = BV(_GPI_ARM_nRF_UART_RTS_PIN);
				port->PIN_CNF[_GPI_ARM_nRF_UART_RTS_PIN] =
					BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
					BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
					BV_BY_NAME(GPIO_PIN_CNF_PULL, Pulldown)		|
					BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			#else
				port->OUTSET = BV(_GPI_ARM_nRF_UART_RTS_PIN);
				port->PIN_CNF[_GPI_ARM_nRF_UART_RTS_PIN] =
					BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
					BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
					BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)		|
					BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			#endif
		#endif
		NRF_UARTE0->PSEL.RTS = BV_BY_NAME(UARTE_PSEL_RTS_CONNECT, Disconnected);
		
		// CTS
		#if GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE
			port = (_GPI_ARM_nRF_UART_CTS_PORT) ? NRF_P1 : NRF_P0;
			port->PIN_CNF[_GPI_ARM_nRF_UART_CTS_PIN] =
				BV_BY_NAME(GPIO_PIN_CNF_DIR, Input)			|
				BV_BY_NAME(GPIO_PIN_CNF_INPUT, Connect)		|
				#if (GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE & 2)
					BV_BY_NAME(GPIO_PIN_CNF_PULL, Pullup)	|
				#else
					BV_BY_NAME(GPIO_PIN_CNF_PULL, Pulldown)	|
				#endif
				BV_BY_NAME(GPIO_PIN_CNF_SENSE, Disabled);
			NRF_UARTE0->PSEL.CTS = 
				BV_BY_VALUE(UARTE_PSEL_CTS_PORT, _GPI_ARM_nRF_UART_CTS_PORT)	|
				BV_BY_VALUE(UARTE_PSEL_CTS_PIN,  _GPI_ARM_nRF_UART_CTS_PIN)		|
				BV_BY_NAME(UARTE_PSEL_CTS_CONNECT, Connected);
		#else
			NRF_UARTE0->PSEL.CTS = BV_BY_NAME(UARTE_PSEL_CTS_CONNECT, Disconnected);
		#endif
	}
	
	// set UART mode: 8 data bits, 1 stop bit, no parity
	#if GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE
		NRF_UARTE0->CONFIG =
			BV_BY_NAME(UARTE_CONFIG_HWFC, Enabled)		|
			BV_BY_NAME(UARTE_CONFIG_PARITY, Excluded)	|
			BV_BY_NAME(UARTE_CONFIG_STOP, One);
	#else
		NRF_UARTE0->CONFIG =
			BV_BY_NAME(UARTE_CONFIG_HWFC, Disabled)		|
			BV_BY_NAME(UARTE_CONFIG_PARITY, Excluded)	|
			BV_BY_NAME(UARTE_CONFIG_STOP, One);
	#endif

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

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_ARM_nRF528xx_PLATFORM_INTERNAL_H__
