/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2021, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/nrf52840/resource_declarations.h
 *
 *	@brief					nRF52840 resource definitions (see resource_check.h)
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

#ifndef __GPI_ARM_NRF52840_RESOURCE_DECLARATIONS_H__
#define __GPI_ARM_NRF52840_RESOURCE_DECLARATIONS_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************



//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************



//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************



//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************



//**************************************************************************************************
//***** Global Variables ***************************************************************************

// nRF52840 resources
// NOTE: peripheral names are equal to those from nrf.h, besides that indexes are split up

// TODO: break down subblocks as needed (gather some experience before). Consider the background
// infos about shared resources provided in top-level resource_check.h.

GPI_RESOURCE_DECLARE(NRF_FICR);
GPI_RESOURCE_DECLARE(NRF_UICR);

GPI_RESOURCE_DECLARE(NRF_CLOCK);
GPI_RESOURCE_DECLARE(NRF_POWER);

GPI_RESOURCE_DECLARE(NRF_P, 0);
GPI_RESOURCE_DECLARE(NRF_P, 1);

GPI_RESOURCE_DECLARE(NRF_RADIO);

GPI_RESOURCE_DECLARE(NRF_UARTE, 0);
GPI_RESOURCE_DECLARE(NRF_UARTE, 1);

// would be nice to have a mechanism that allows to
// split up mutually exclusive resources without losing the dependencies
GPI_RESOURCE_DECLARE(NRF_SPIM0_SPIS0_TWIM0_TWIS0);
GPI_RESOURCE_DECLARE(NRF_SPIM1_SPIS1_TWIM1_TWIS1);
GPI_RESOURCE_DECLARE(NRF_SPIM2_SPIS2);
GPI_RESOURCE_DECLARE(NRF_SPIM3);

GPI_RESOURCE_DECLARE(NRF_NFCT);

GPI_RESOURCE_DECLARE(NRF_GPIOTE);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 0);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 1);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 2);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 3);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 4);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 5);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 6);
GPI_RESOURCE_DECLARE(NRF_GPIOTE_CH, 7);

GPI_RESOURCE_DECLARE(NRF_SAADC);

GPI_RESOURCE_DECLARE(NRF_TIMER, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 0, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 0, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 0, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 0, 3);

GPI_RESOURCE_DECLARE(NRF_TIMER, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 1, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 1, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 1, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 1, 3);

GPI_RESOURCE_DECLARE(NRF_TIMER, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 2, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 2, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 2, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 2, 3);

GPI_RESOURCE_DECLARE(NRF_TIMER, 3);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 3);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 4);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 3, 5);

GPI_RESOURCE_DECLARE(NRF_TIMER, 4);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 0);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 1);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 2);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 3);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 4);
GPI_RESOURCE_DECLARE(NRF_TIMER_CC, 4, 5);

GPI_RESOURCE_DECLARE(NRF_RTC, 0);
GPI_RESOURCE_DECLARE(NRF_RTC, 1);
GPI_RESOURCE_DECLARE(NRF_RTC, 2);

GPI_RESOURCE_DECLARE(NRF_TEMP);

GPI_RESOURCE_DECLARE(NRF_RNG);

GPI_RESOURCE_DECLARE(NRF_ECB);

GPI_RESOURCE_DECLARE(NRF_AAR_CCM);

GPI_RESOURCE_DECLARE(NRF_WDT);

GPI_RESOURCE_DECLARE(NRF_QDEC);

GPI_RESOURCE_DECLARE(NRF_COMP_LPCOMP);

GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 0);
GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 1);
GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 2);
GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 3);
GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 4);
GPI_RESOURCE_DECLARE(NRF_EGU_SWI, 5);

GPI_RESOURCE_DECLARE(NRF_PWM, 0);
GPI_RESOURCE_DECLARE(NRF_PWM, 1);
GPI_RESOURCE_DECLARE(NRF_PWM, 2);
GPI_RESOURCE_DECLARE(NRF_PWM, 3);

GPI_RESOURCE_DECLARE(NRF_PDM);

GPI_RESOURCE_DECLARE(NRF_ACL_NVMC);

GPI_RESOURCE_DECLARE(NRF_PPI);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  0);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  1);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  2);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  3);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  4);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  5);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  6);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  7);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  8);
GPI_RESOURCE_DECLARE(NRF_PPI_CH,  9);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 10);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 11);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 12);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 13);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 14);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 15);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 16);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 17);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 18);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 19);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 20);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 21);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 22);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 23);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 24);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 25);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 26);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 27);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 28);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 29);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 30);
GPI_RESOURCE_DECLARE(NRF_PPI_CH, 31);

GPI_RESOURCE_DECLARE(NRF_MWU);
GPI_RESOURCE_DECLARE(NRF_MWU_REGION, 0);
GPI_RESOURCE_DECLARE(NRF_MWU_REGION, 1);
GPI_RESOURCE_DECLARE(NRF_MWU_REGION, 2);
GPI_RESOURCE_DECLARE(NRF_MWU_REGION, 3);
GPI_RESOURCE_DECLARE(NRF_MWU_PREGION, 0);
GPI_RESOURCE_DECLARE(NRF_MWU_PREGION, 1);

GPI_RESOURCE_DECLARE(NRF_I2S);

GPI_RESOURCE_DECLARE(NRF_FPU);

GPI_RESOURCE_DECLARE(NRF_USBD);

GPI_RESOURCE_DECLARE(NRF_QSPI);

GPI_RESOURCE_DECLARE(NRF_CC_HOST_RGF_CRYPTOCELL);

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

#endif // __GPI_ARM_NRF52840_RESOURCE_DECLARATIONS_H__
