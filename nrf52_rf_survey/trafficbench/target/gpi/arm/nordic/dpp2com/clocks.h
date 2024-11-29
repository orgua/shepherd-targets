/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2019, Networked Embedded Systems Lab, TU Dresden
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
 *	@file					gpi/arm/nordic/dpp2com/clocks.h
 *
 *	@brief					general-purpose slow, fast, and hybrid clock
 *
 *	@version				$Id: 30e35eeb818af1c7a767d64261fc0b8c47f06f74 $
 *	@date					TODO
 *
 *	@author					Fabian Mager
 *
 ***************************************************************************************************

 	@details

	TODO

 **************************************************************************************************/

#ifndef __GPI_ARM_DPP2_COM_CLOCKS_H__
#define __GPI_ARM_DPP2_COM_CLOCKS_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "../nrf52840/clocks.h" // wrapper

//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

#ifndef GPI_LFRC_CAL_TIMER_PPI_CHANNEL
	#define GPI_LFRC_CAL_TIMER_PPI_CHANNEL	1	// start calibration timer after LFRC has been calibrated
#endif
#ifndef GPI_LFRC_CAL_TASK_PPI_CHANNEL
	#define GPI_LFRC_CAL_TASK_PPI_CHANNEL	2	// start calibration after calibration timer reached 0 (EVENTS_CTTO)
#endif

#endif // __GPI_ARM_DPP2_COM_CLOCKS_H__
