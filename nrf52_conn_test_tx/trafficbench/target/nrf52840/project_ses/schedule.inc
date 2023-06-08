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
 *	@file					schedule.inc
 *
 *	@brief					application-specific communication schedule
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	Do not compile this file directly, it is included in schedule_framework.s .

 **************************************************************************************************/
//***** Global Defines and Consts ******************************************************************

// following macros must be defined (they are used by the framework)

// position of checkpoint marker in a packet's payload.
// positive values specify offsets relative to payload[0],
// negative values can be used to specify offsets relative to payload[end]
TRX_CHECKPOINT_MARKER_POS = -1

// constant pre- and postprocessing delays of TRX instructions.
// virtual execution time of TRX = TRX_PRE_DELAY + specified timeout + TRX_POST_DELAY.
// values can be rather small (depending on the schedule, even 0 is possible),
// but they should be increased if late start delays > 0 appear in the results.
// values >= 500 are comfortable choices if there is no need to pack packets as dense as possible.
TRX_PRE_DELAY	= 500
TRX_POST_DELAY	= 500

// default values for RSSI sampling pre- and posttrigger times.
// these values are used if pre-/posttrigger time is not specified explicitly at TRX
RSSI_PRETRIGGER_TIME_DEFAULT	= 100
RSSI_POSTTRIGGER_TIME_DEFAULT	= 100

//**************************************************************************************************
//***** Local Macros *******************************************************************************

// It is possible to use assembly and preprocessor macros to simplify the schedule.
// If both are mixed, take care that parameters get resolved in the intended order.

//**************************************************************************************************
// node ID mapping
// for details see schedule_template.inc

#include "config.h"		// -> BUILD_CONFIG_IS(), config_flocklab.h

#if !BUILD_CONFIG_IS(Release_FlockLab)
	#define NODE(i)			i
#else
	// helper macros
	#define VA_ARGi(i, ...)			VA_ARG ## i (__VA_ARGS__)
	#define VA_ARG0(_0, ...)		_0
	#define VA_ARG1(_0, _1, ...)		_1
	#define VA_ARG2(_0, _1, _2, ...)		_2
	#define VA_ARG3(_0, _1, _2, _3, ...)		_3
	#define VA_ARG4(_0, _1, _2, _3, _4, ...)		_4
	#define VA_ARG5(_0, _1, _2, _3, _4, _5, ...)		_5
	#define VA_ARG6(_0, _1, _2, _3, _4, _5, _6, ...)		_6
	#define VA_ARG7(_0, _1, _2, _3, _4, _5, _6, _7, ...)		_7
	#define VA_ARG8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...)		_8
	#define VA_ARG9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...)		_9

	// specify physical node IDs
	#ifndef FLOCKLAB_NODES
		#define FLOCKLAB_NODES	FLOCKLAB_OBSERVERS
	#endif

	// translate logical ID to physical ID
	#define NODE(i)			VA_ARGi(i, unused_index_0, FLOCKLAB_NODES)
#endif

// translate list of logical IDs to list of physical IDs
#if 1
	#define NODES(...)			LIST(NODES1(__VA_ARGS__))
	#define NODES1(i, ...)		NODE(i) __VA_OPT__(, NODES2(__VA_ARGS__))
	#define NODES2(i, ...)		NODE(i) __VA_OPT__(, NODES3(__VA_ARGS__))
	#define NODES3(i, ...)		NODE(i) __VA_OPT__(, NODES4(__VA_ARGS__))
	#define NODES4(i, ...)		NODE(i) __VA_OPT__(, NODES5(__VA_ARGS__))
	#define NODES5(i, ...)		NODE(i) __VA_OPT__(, NODES6(__VA_ARGS__))
	#define NODES6(i, ...)		NODE(i) __VA_OPT__(, NODES7(__VA_ARGS__))
	#define NODES7(i, ...)		NODE(i) __VA_OPT__(, NODES8(__VA_ARGS__))
	#define NODES8(i, ...)		NODE(i) __VA_OPT__(, NODES9(__VA_ARGS__))
	#define NODES9(i, ...)		NODE(i) __VA_OPT__(, NODES10(__VA_ARGS__))
	#define NODES10(i, ...)		NODE(i) __VA_OPT__(, NODES11(__VA_ARGS__))
	#define NODES11(i, ...)		NODE(i) __VA_OPT__(, NODES12(__VA_ARGS__))
	#define NODES12(i, ...)		NODE(i) __VA_OPT__(, NODES13(__VA_ARGS__))
	#define NODES13(i, ...)		NODE(i) __VA_OPT__(, NODES14(__VA_ARGS__))
	#define NODES14(i, ...)		NODE(i) __VA_OPT__(, NODES15(__VA_ARGS__))
	#define NODES15(i, ...)		NODE(i) __VA_OPT__(, NODES16(__VA_ARGS__))
	#define NODES16(i, ...)		NODE(i) __VA_OPT__(, NODES17(__VA_ARGS__))
	#define NODES17(i, ...)		NODE(i) __VA_OPT__(, NODES18(__VA_ARGS__))
	#define NODES18(i, ...)		NODE(i) __VA_OPT__(, NODES19(__VA_ARGS__))
	#define NODES19(i, ...)		NODE(i) __VA_OPT__(, NODES20(__VA_ARGS__))
	#define NODES20(i, ...)		NODE(i) __VA_OPT__(_Pragma("GCC error \"NODES() size exceeded, macro needs extension (can be done easily)\""))
#else 
	// alternative implementation (if __VA_OPT__() is not available)

	#define Nstop(...)			__VA_ARGS__
	#define N1(...)				__VA_ARGS__, NODE(1)
	#define N2(...)				__VA_ARGS__, NODE(2)
	#define N3(...)				__VA_ARGS__, NODE(3)
	#define N4(...)				__VA_ARGS__, NODE(4)
	#define N5(...)				__VA_ARGS__, NODE(5)

	#define LIST2(...)				_LIST2(__VA_ARGS__)
	#define _LIST2(unused, ...)		LIST(__VA_ARGS__)

	#define NODES(...)			_NODES(dummy, ## __VA_ARGS__, stop, stop, stop, stop, stop)
	#define _NODES(dummy, _1, _2, _3, _4, _5, ...)	LIST2(N ## _5(N ## _4(N ## _3(N ## _2(N ## _1())))))
#endif

//**************************************************************************************************
//***** Schedule Program ***************************************************************************

main_loop:

	// This is just an example schedule provided to demonstrate the usage of the instructions.
	// Replace it with your own schedule program. For details, see schedule_template.inc.

	// transmit a packet from node 1
	// NOTE: time values are in microseconds
	TRX_begin			transmitter=NODE(1), tx_delay=2000, timeout=10000
		// payload content:
		TRX_data_fixed			0x01, 0x02, 0x03, 0x04		// 4 bytes with fixed content
		TRX_data_random			len=4						// 4 bytes with random content
		TRX_data_checkpoint									// checkpoint
		TRX_data_fixed			0x05, 0x06, 0x07, 0x08		// some more content
		TRX_data_checkpoint_marker							// checkpoint marker
		// ATTENTION: TRX_data_checkpoint_marker is mandatory and must match
		// TRX_CHECKPOINT_MARKER_POS (also if packet does not contain a checkpoint)
	TRX_end

	// packets from nodes 2 and 3
	TRX_begin			transmitter=NODE(2), tx_delay=2000, timeout=10000
		TRX_data_fixed			0x21, 0x22, 0x23, 0x24
		TRX_data_checkpoint
		TRX_data_checkpoint_marker
	TRX_end
	TRX_begin			transmitter=NODE(3), tx_delay=2000, timeout=10000
		TRX_data_fixed			0x31, 0x32, 0x33, 0x34
		TRX_data_checkpoint
		TRX_data_checkpoint_marker
	TRX_end
	
	// sleep a second
	SLEEP		1000000
	
	// another packet from node 1
	TRX_begin			transmitter=NODE(1), tx_delay=2000, timeout=10000
		TRX_data_fixed			0x11, 0x12, 0x13, 0x14
		TRX_data_checkpoint_marker	// also if packet does not contain a checkpoint
	TRX_end

	// synchronous packets from nodes 2 and 3
	TRX_SYNC_begin			transmitter=NODES(2,3), tx_delay=2000, timeout=10000
		TRX_data_fixed		1,2,3,4
		TRX_data_random		len=4
		TRX_data_checkpoint_marker
	TRX_SYNC_end

	// concurrent and individually time-shifted packets from multiple nodes
	// ATTENTION: make sure that packets inside a TRX_GROUP do not contain different amounts
	// of random bytes, otherwise the RNG synchronization will get lost
	TRX_GROUP_begin			timeout=10000
		TRX_SYNC_begin			transmitter=NODE(1), tx_delay=1000, rng_offset=0x01
			TRX_data_fixed		1,2,3,4
			TRX_data_random		len=4
			TRX_data_checkpoint_marker
		TRX_SYNC_end
		TRX_SYNC_begin			transmitter=NODE(2), tx_delay=1000, rng_offset=0x01
			TRX_data_fixed		1,2,3,4
			TRX_data_random		len=4
			TRX_data_checkpoint_marker
		TRX_SYNC_end
		TRX_SYNC_begin			transmitter=NODE(3), tx_delay=2000, rng_offset=0x02
			TRX_data_fixed		5,6,7,8
			TRX_data_random		len=4
			TRX_data_checkpoint_marker
		TRX_SYNC_end
	TRX_GROUP_end

	// sleep 3s
	SLEEP		3000000

	// next loop iteration
	BRANCH		main_loop

	// never reached because of endless loop above
	TERMINATE

//**************************************************************************************************
//**************************************************************************************************
