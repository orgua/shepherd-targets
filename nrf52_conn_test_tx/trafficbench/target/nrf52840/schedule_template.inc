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

// The following macros are optional and can be used to implement an arbitrary mapping between
// logical and physical node IDs. This is helpful if the same schedule should run on different
// sets of nodes. In this case, the schedule can refer to logical node IDs (e.g., used nodes
// just enumerated as 1, 2, ...), which get then mapped to a selected set of physical node IDs
// via a mapping function. With this concept, a different set of nodes can be selected by adapting
// the mapping function instead of the schedule, which is typically faster and less error-prone.

// The mapping concept provides two macros:
// * NODE(i), which translates a single logical ID <i> to the corresponding physical ID, and
// * NODES(i, j, k, ...), which translates a whole list of IDs.
// Both macros can be used in TRX -> transmitter.
// NODE(i) implements the actual mapping function.
// For debugging purposes, one can test the result using .error NODES(...).

// specify mapping
#if 1
	// direct mapping: physical ID = logical ID (i.e., mapping function = identity)
	#define NODE(i)			i
#else
	// arbitrary mapping (example)
	#if 1
		// specify mapping by defining a macro N<i> for each logical ID <i>
		#define N1			3
		#define N2			7
		#define N3			9
		#define N4			20
		#define N5			24
		// translate logical ID (<i> -> N<i> -> physical ID)
		#define	NODE(i)			_NODE(N ## i)
		#define _NODE(x)		x
	#else
		// specify mapping by defining a list
		#define NODE_IDs		unused_index_0, 3, 7, 9, 20, 24
		// translate logical ID
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
		#define NODE(i)			VA_ARG ## i (NODE_IDs)
	#endif
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
	// Replace it with your own schedule program.
	// Note that the schedule is handled as a (VM) assembly language program behind the scenes,
	// so you can make use of generic language features like labels and macros.

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
/* available instructions and parameters

(m) = mandatory, (o) = optional parameter


TERMINATE
terminate schedule program


SLEEP
pause execution for specified amount of time

- period (m): sleep for that long [us]


BRANCH
branch to specified label and continue execution from there

- destination (m): branch target


TRX_SYNC_begin, TRX_SYNC_end
transmit or receive a packet.
Each transmit/receive (TRX) operation is written as a block delimited by TRX_SYNC_begin and TRX_SYNC_end.
Control parameters are provided together with TRX_SYNC_begin, while the body of the block specifies
the packet payload(s).
All nodes perform the operation synchronously respecting their individual roles (transmitter or receiver).

basic parameters:

- transmitter (m): ID(s) of transmitting node(s).
	Single transmitters can be specified directly, multiple transmitters can be specified using LIST()
	(use NODE() or NODES() in case node ID mapping is to be used).
	All transmitters start at the same time and transmit the specified packet.
	All nodes not listed as transmitter enter receive mode.

- timeout (m): listening timeout [us] to be used at receiver nodes (i.e. at all non-transmitters).
	The timeout also determines the execution time of the TRX instruction (together with 
	TRX_PRE_DELAY and TRX_POST_DELAY).

- tx_delay (m): delay [us] from nominal start time to start of transmission.
	If tx_delay > 0, then receivers start listening right before the start of the packet on air,
	which introduces some clock drift tolerance and avoids misleading race conditions.

advanced parameters:
	
- rng_offset (o): random number generator (RNG) offset. default = 0 (i.e. no offset).
	The synchronous execution of the schedule on all nodes also includes the RNGs, so at
	the same step in a schedule all nodes generate the same random numbers. While this is
	beneficial for some purposes (e.g., to synchronously transmit random but identical packets), 
	it may not be appropriate for others.
	rng_offset > 0 can be used to generate differing random payloads at different transmitters
	even from synchronized RNGs. To this end, it applies x = transmitter_index * rng_offset to the 
	RNG output,	where the meaning of "apply" is implementation-specific (currently it just adds x
	to the results, but it could, for instance, also temporarily shift the internal RNG states by x).
	
- tx_carrier_period_1, tx_carrier_period_2 (o): length [us] of pure carrier period 
	before (1) and after (2) the packet. default = 0 (i.e. no pure carrier period).
	This feature is provided for deep inspection and special purposes.
	Do not use it if you are unsure about it.

RSSI sampling control:

- rssi_buffer_size (o): amount of space reserved as RSSI sample buffer for this TRX operation.
	reserved space = 2 ^ <provided value>. default = 0 (use internal minimum).
	
- rssi_pretrigger_time (o): extra sampling time [us] before start of packet, 
	i.e. time before packet for which RSSI samples should be kept. default = 0.
	For internal reasons, the number of stored pretrigger samples can be a little bit (< 5) higher 
	than specified. More important, it can be significantly lower if the received packet started 
	before the pretrigger time has passed or if the reserved buffer is too small to keep all samples.
	
- rssi_posttrigger_time (o): extra sampling time [us] after end of packet. default = 0.
	For internal reasons, the number of stored posttrigger samples can be a little bit (< 5) higher 
	than specified. More important, it can be significantly lower if the specified timeout is reached
	before the posttrigger time has passed (note that rssi_posttrigger_time > 0 requires to keep the 
	receiver active for some extra time after the end of a received packet) or if the reserved buffer 
	is too small to keep all samples.

packet content commands and parameters (used between TRX_SYNC_begin and TRX_SYNC_end):

- TRX_data_fixed: fixed content.
	- data (m): comma-separated list of byte values. 
	  The length of the data block is determined automatically.
	  The identifier 'data=' can be left out, so one can just write 'TRX_data_fixed 1,2,3,4'
	
- TRX_data_random: random data of fixed length.
	- len (m): length of data block, i.e. number of random bytes.
	  Currently, the length is required to be a multiple of 4.

- TRX_data_checkpoint: a checkpoint data block containing the node's internal program state.
	Checkpoints can be used by receiving nodes to synchronize their clocks and schedule
	execution states, which is most important during network startup. Besides that, clock 
	synchronization is a continuous process, so transmitted packets should include checkpoints
	at least once in a while.
	The content of a checkpoint is generated automatically at runtime.
	The size of a checkpoint, TRX_CHECKPOINT_SIZE, is defined internally (currently it is 12 byte).

- TRX_data_checkpoint_marker: 
  marker that determines the availability and position of a checkpoint inside the packet.
	Checkpoints can be placed at arbitrary positions inside packets, so receiving nodes 
	need to know if and in case where a packet contains a checkpoint. This information
	is provided by a checkpoint marker, which must be placed at a predefined position in
	each packet, namely at the statically configurable TRX_CHECKPOINT_MARKER_POS (see above).
	The marker has a size of one byte, and it's content is generated automatically.

- TRX_data_no_packet: do not send a packet.
	This special content type causes the transmission of the packet to be skipped.
	It can be used to generate stand-alone pure carrier periods (with tx_carrier_period_1 + 
	tx_carrier_period_2 > 0).
	Do not use it together with other content types.


TRX_begin, TRX_end
plain abbreviations for TRX_SYNC_begin and TRX_SYNC_end, respectively.
Can be used to avoid confusion with the meaning of SYNC in case of a single transmitter.
However, we recommend to use TRX_SYNC_...  whenever multiple transmitters are specified.


TRX_GROUP_begin, TRX_GROUP_end
transmit multiple overlapping packets with different contents and/or time-shifted to each other.
A TRX group allows to implement multiple TRX_SYNC operations that overlap each other in time.
It can be used to transmit overlapping packets from different nodes with fine-grained start time
offsets.
For the included TRX_SYNC blocks, there are two restrictions:
(1) A single node cannot transmit multiple packets. Hence, if a node is listed as transmitter 
    in multiple TRX_SYNC blocks, then all but the first one are ignored for that node.
(2) All TRX_SYNC blocks have the same timeout, which is specified at TRX_GROUP_begin (instead of 
    TRX_SYNC_begin). This is necessary because a receiving node cannot know in advance which of the 
	packets (or if any at all) it will receive. The global timeout enables synchronous schedule
	execution independent of the received packets.
	For the same reason, the RSSI sampling control parameters are defined for the whole group
	because a receiving node has to reserve the RSSI destination buffer before sampling starts.

- timeout (m): listening timeout [us] to be used at receiver nodes (i.e. at all non-transmitters).
	The timeout also determines the execution time of the TRX instruction (together with 
	TRX_PRE_DELAY and TRX_POST_DELAY).

- rssi_buffer_size (o): amount of space reserved as RSSI sample buffer for this TRX operation.
	reserved space = 2 ^ <provided value>. default = 0 (use internal minimum).
	
- rssi_pretrigger_time (o): extra sampling time [us] before start of packet, 
	i.e. time before packet for which RSSI samples should be kept. default = 0.
	For internal reasons, the number of stored pretrigger samples can be a little bit (< 5) higher 
	than specified. More important, it can be significantly lower if the received packet started 
	before the pretrigger time has passed or if the reserved buffer is too small to keep all samples.
	
- rssi_posttrigger_time (o): extra sampling time [us] after end of packet. default = 0.
	For internal reasons, the number of stored posttrigger samples can be a little bit (< 5) higher 
	than specified. More important, it can be significantly lower if the specified timeout is reached
	before the posttrigger time has passed (note that rssi_posttrigger_time > 0 requires to keep the 
	receiver active for some extra time after the end of a received packet) or if the reserved buffer 
	is too small to keep all samples.

*/
//**************************************************************************************************
//**************************************************************************************************
