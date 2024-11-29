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
 *	@file					gpi/arm/nordic/nrf528xx/platform.c
 *
 *	@brief					common nRF528xx platform interface functions
 *
 *	@version				$Id: 0928760904161f0b6ee5b7fc6283a0b44666592b $
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/
//***** Trace Settings *****************************************************************************



//**************************************************************************************************
//**** Includes ************************************************************************************

#include "gpi/tools.h"
#include "gpi/platform.h"
#include "gpi/interrupts.h"

#include "platform_internal.h"

#include <nrf.h>

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



//**************************************************************************************************
//***** Global Functions ***************************************************************************

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
