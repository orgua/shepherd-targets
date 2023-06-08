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
 *	@file					schedule_framework.s
 *
 *	@brief					assembler macros and code embedding the application-specific communication schedule
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
//***** Local Defines and Macros *******************************************************************

// size of checkpoint data
// ATTENTION: must match sizeof(Checkpoint_Data)
TRX_CHECKPOINT_SIZE = 12

// timer clock rate / resolution
TICKS_PER_US = 16

//**************************************************************************************************
// print macros for compile-time debugging

#define DEBUG_PRINT_HEX(x)	\
	.if ((x) & 8);	\
		.if ((x) & 4);	\
			.if ((x) & 2);	\
				.if ((x) & 1); .print "f"; .else; .print "e"; .endif;	\
			.else;	\
				.if ((x) & 1); .print "d"; .else; .print "c"; .endif;	\
			.endif;	\
		.else;	\
			.if ((x) & 2);	\
				.if ((x) & 1); .print "b"; .else; .print "a"; .endif;	\
			.else;	\
				.if ((x) & 1); .print "9"; .else; .print "8"; .endif;	\
			.endif;	\
		.endif;	\
	.else;	\
		.if ((x) & 4);	\
			.if ((x) & 2);	\
				.if ((x) & 1); .print "7"; .else; .print "6"; .endif;	\
			.else;	\
				.if ((x) & 1); .print "5"; .else; .print "4"; .endif;	\
			.endif;	\
		.else;	\
			.if ((x) & 2);	\
				.if ((x) & 1); .print "3"; .else; .print "2"; .endif;	\
			.else;	\
				.if ((x) & 1); .print "1"; .else; .print "0"; .endif;	\
			.endif;	\
		.endif;	\
	.endif;

#define DEBUG_PRINT(x)	\
	.print "DEBUG: "; .print #x; .print "= 0x...";	\
	DEBUG_PRINT_HEX((x) >> 28);	\
	DEBUG_PRINT_HEX((x) >> 24);	\
	DEBUG_PRINT_HEX((x) >> 20);	\
	DEBUG_PRINT_HEX((x) >> 16);	\
	DEBUG_PRINT_HEX((x) >> 12);	\
	DEBUG_PRINT_HEX((x) >>  8);	\
	DEBUG_PRINT_HEX((x) >>  4);	\
	DEBUG_PRINT_HEX((x) >>  0);

//**************************************************************************************************

// test if specified scope is open, i.e. if we are between corresponding start and end labels
.macro ensure_scope scope=0, or_scope:vararg
	.subsection 0
	.if (\scope != 3)
		.ifge 3000b - 3999b
			.ifb \or_scope
				.error "instruction not allowed inside TRX_GROUP"
			.else
				ensure_scope \or_scope
			.endif
		.endif
	.endif
.endm

//**************************************************************************************************
//***** Schedule Instructions **********************************************************************

// see traffic_bench.h for details on the instruction formats

// used sections:
//	.rodata.schedule:
//		subsection 0:	instruction words
//		subsection 1:	instruction params
//	dummy:				packet contents (dropped by the linker), used to count lengths etc.

//**************************************************************************************************

.macro TERMINATE
	ensure_scope 0
	.subsection 0
	.byte	0		// opcode
	.zero	3		// reserved
.endm

//**************************************************************************************************

.macro SLEEP period:req
	ensure_scope 0
	.subsection 0
	.byte	2						// opcode
	.zero	1						// reserved
	.2byte	SLEEP_\@ - schedule		// params_ptr
	.subsection 1
	.balign 4
	SLEEP_\@\():
	.4byte	\period
	.subsection 0
.endm

//**************************************************************************************************

.macro BRANCH destination:req
	ensure_scope 0
	.subsection 0
	.byte	200								// opcode
	.zero	1								// reserved
	.2byte	(\destination - (. - 2)) / 4	// target offset
.endm

//**************************************************************************************************

// open TRX instruction (with one or more transmitters)
.macro TRX_SYNC_begin transmitter:req, timeout=0, tx_delay:req, tx_carrier_period_1=0, tx_carrier_period_2=0, rssi_pretrigger_time=0, rssi_posttrigger_time=0, rssi_buffer_size=0, rng_offset=0

	ensure_scope 0, 3

	// if outside TRX_GROUP: adopt parameter values
	// NOTE: .subsection 0 is required (otherwise label diffs will not be absolute)
	.subsection 0
	.if ((3000b - 3999b) < 0)
		.set .LTRX_timeout, \timeout
		.set .LTRX_rssi_buffer_size, \rssi_buffer_size
		.set .LTRX_rssi_pretrigger_time, \rssi_pretrigger_time
		.set .LTRX_rssi_posttrigger_time, \rssi_posttrigger_time

	// if first instruction inside TRX_GROUP: adopt parameter values not provided at TRX_GROUP_begin
	// NOTE: this is provided for compatibility and will be removed in the future
	// (in prior versions, timeout and others were specified at first group member, not at TRX_GROUP_begin)
	.elseif ((. - 3000b) == 0)
		.if (.LTRX_timeout == 0)
			.set .LTRX_timeout, \timeout
		.endif
		.if (.LTRX_rssi_buffer_size == 0)
			.set .LTRX_rssi_buffer_size, \rssi_buffer_size
		.endif
		.if (.LTRX_rssi_pretrigger_time == 0)
			.set .LTRX_rssi_pretrigger_time, \rssi_pretrigger_time
		.endif
		.if (.LTRX_rssi_posttrigger_time == 0)
			.set .LTRX_rssi_posttrigger_time, \rssi_posttrigger_time
		.endif
	.endif

	// if inside TRX_GROUP
	.if ((3000b - 3999b) >= 0)
		// ensure that timeout has been specified
		.if (.LTRX_timeout == 0)
			.error "(group) timeout not specified"
		.endif
		// redundant parameter specifications should be avoided
		// ATTENTION: do not warn if value matches, it may be the first instruction of the group (see above)
		.if ((\timeout != 0) && (\timeout != .LTRX_timeout))
			.warning "timeout setting ignored (using group timeout)"
		.endif
		.if ((\rssi_buffer_size != 0) && (\rssi_buffer_size != .LTRX_rssi_buffer_size))
			.warning "rssi_buffer_size setting ignored (using group value)"
		.endif
		.if ((\rssi_pretrigger_time != 0) && (\rssi_pretrigger_time != .LTRX_rssi_pretrigger_time))
			.warning "rssi_pretrigger_time setting ignored (using group value)"
		.endif
		.if ((\rssi_posttrigger_time != 0) && (\rssi_posttrigger_time != .LTRX_rssi_posttrigger_time))
			.warning "rssi_posttrigger_time setting ignored (using group value)"
		.endif
	.endif

	// check and update parameter values
	.if (.LTRX_rssi_buffer_size > 16)
		.error "rssi_buffer_size overflow"
	.endif
	.if (.LTRX_rssi_pretrigger_time == 0)
		.set .LTRX_rssi_pretrigger_time, RSSI_PRETRIGGER_TIME_DEFAULT
	.endif
	.if (.LTRX_rssi_posttrigger_time == 0)
		.set .LTRX_rssi_posttrigger_time, RSSI_POSTTRIGGER_TIME_DEFAULT
	.endif

	.subsection 0
	.byte	1							// opcode
	.if ((3999b - 3000b) <= 0)			// if inside TRX_GROUP
		.if ((. - 3000b) < 4)			// if first instruction
			.byte	(3999f - .) / 4		// group_offset -> group end
		.else
			.byte	(3000b - .) / 4		// group_offset -> anchor (first instruction)
		.endif
	.else
		.byte	0						// group_offset -> group end / anchor (no group)
	.endif
	.2byte	TRX_\@ - schedule			// params_ptr

	.subsection 1
	.balign 4
	TRX_\@\():
	.4byte	.LTRX_timeout
	.4byte	\tx_delay
	.2byte	\tx_carrier_period_1
	.2byte	\tx_carrier_period_2
	.2byte	.LTRX_rssi_pretrigger_time
	.2byte	.LTRX_rssi_posttrigger_time
	.2byte	\rng_offset

	.section dummy
	.set .LTRX_\@_cp_offset, (1250f - 1000f)
	.previous

	.byte 	1999f - 1000f				// payload_length
	.byte 	.LTRX_rssi_buffer_size		// rssi_buffer_size_msb
	.byte	.LTRX_\@_cp_offset			// checkpoint_offset
	.byte	.LTRX_\@ - (. + 1)			// num_transmitters
	.byte	\transmitter
	.LTRX_\@\():
	//.2byte	1900f - (. + 2)			// payload descriptor list size

	// define default labels (outside of 1000 ... 1999)
	// each of them ensures that label exists and allows TRX_SYNC_end to check if corresponding component has been used
	.section dummy
	1255:								// TRX_data_no_packet
	1256:								// TRX_data_checkpoint_marker
	.zero	1
	1000:								// payload begin
	.previous

.endm

//**************************************************************************************************

// close TRX instruction
.macro TRX_SYNC_end

	.subsection 1
	.byte	2, 0			// end of list
	//1900:					// descriptor list end marker

	.section dummy
	1999:					// payload end marker

	// if TRX_data_no_packet is used
	.if (1255b - 1000b >= 0)

		.if (. - 1000b > 0)
			.error "TRX_data_no_packet can only be used stand-alone (rules out any packet content)"
		.endif

	.else

		// trigger error if payload exceeds max. size
		.if (. - 1000b) > 255
			.error "payload length overrun"
		.endif

		// trigger error if TRX_CHECKPOINT_MARKER_POS is out of range
		.if (TRX_CHECKPOINT_MARKER_POS >= 0)
			.if ((. - 1000b) <= TRX_CHECKPOINT_MARKER_POS)
				.error "payload has no space for checkpoint marker (payload is to small for TRX_CHECKPOINT_MARKER_POS)"
			.endif
		.else
			.if ((. + TRX_CHECKPOINT_MARKER_POS - 1000b) < 0)
				.error "payload has no space for checkpoint marker (payload is to small for TRX_CHECKPOINT_MARKER_POS)"
			.endif
		.endif
		.if (1256b - 1000b < 0)
			.error "missing checkpoint marker"
		.endif

		// if TRX_data_checkpoint_marker used
		//.if (1256b - 1000b >= 0)
			// trigger error if TRX_CHECKPOINT_MARKER_POS does not match
			.if (TRX_CHECKPOINT_MARKER_POS >= 0)
				.if ((1256b - 1000b) != TRX_CHECKPOINT_MARKER_POS)
					.error "checkpoint marker placement does not match TRX_CHECKPOINT_MARKER_POS"
				.endif
			.else
				.if ((1999b - 1256b) != -TRX_CHECKPOINT_MARKER_POS)
					.error "checkpoint marker placement does not match TRX_CHECKPOINT_MARKER_POS"
				.endif
			.endif
		//.endif

	.endif

	.zero	255 - (. - 1000b)
	1250:	// dummy checkpoint data, used to establish checkpoint_offset = 255 if there is no cp data
	.previous
	.subsection 0

.endm

//**************************************************************************************************

// open TRX group with multiple TRX instructions
// ATTENTION: use of default timeout is deprecated, it is provided for compatibility reasons
// (in prior versions, the timeout was specified at the first group member, not at TRX_GROUP_begin)
.macro TRX_GROUP_begin timeout=0, rssi_pretrigger_time=0, rssi_posttrigger_time=0, rssi_buffer_size=0
	.subsection 0
	//.byte	2
	//.byte	(3999f - 3000f) / 4
	//.zero	2
	3000:
	// store parameters for following group members
	.set .LTRX_timeout, \timeout
	.set .LTRX_rssi_buffer_size, \rssi_buffer_size
	.set .LTRX_rssi_pretrigger_time, \rssi_pretrigger_time
	.set .LTRX_rssi_posttrigger_time, \rssi_posttrigger_time
.endm

// close TRX group
.macro TRX_GROUP_end
	.subsection 0
	3999:
	.if	(3999b - 3000b) < 4
		.error "TRX_GROUP must not be empty"
	.elseif (3999b - 3000b) > 128 * 4
		.error "TRX_GROUP size overflow (max. 128 entries allowed)"
	.endif
.endm

//**************************************************************************************************

// TRX_begin/end are just abbreviations for TRX_sync_begin/end
// (can be used to avoid confusion with "sync" if only a single transmitter is specified)

.macro TRX_begin transmitter:req, timeout=0, tx_delay:req, tx_carrier_period_1=0, tx_carrier_period_2=0, rssi_pretrigger_time=0, rssi_posttrigger_time=0, rssi_buffer_size=0
	TRX_SYNC_begin transmitter=\transmitter, timeout=\timeout, tx_delay=\tx_delay, tx_carrier_period_1=\tx_carrier_period_1, tx_carrier_period_2=\tx_carrier_period_2, rssi_pretrigger_time=\rssi_pretrigger_time, rssi_posttrigger_time=\rssi_posttrigger_time, rssi_buffer_size=\rssi_buffer_size
.endm

.macro TRX_end
	TRX_SYNC_end
.endm

//**************************************************************************************************

// TRX is a short form to specify TRX instructions on a single line (with limited flexibility)
// maybe it should be avoided
.macro TRX transmitter:req, timeout:req, tx_delay:req, type=fixed, options:vararg
	.ifc "\type", "fixed"; .else; .ifc "\type", "random"
	.else
		.error "type \"\type\" is invalid"
	.endif; .endif
	.if ((TRX_CHECKPOINT_MARKER_POS != 0) && (TRX_CHECKPOINT_MARKER_POS != -1))
		.error "current TRX_CHECKPOINT_MARKER_POS is not supported by TRX (can be used with 0 and -1)"
	.endif
	TRX_begin	transmitter=\transmitter, tx_delay=\tx_delay, timeout=\timeout
		.if (0 == TRX_CHECKPOINT_MARKER_POS)
			TRX_data_checkpoint_marker
		.endif
		TRX_data_\type	\options
		TRX_data_checkpoint
		.if (-1 == TRX_CHECKPOINT_MARKER_POS)
			TRX_data_checkpoint_marker
		.endif
	TRX_end
.endm

//**************************************************************************************************
// TRX content macros

// fixed content
.macro TRX_data_fixed data:vararg
	.subsection 1			// descriptor
	.byte	.LTRX_\@ - .	// size
	.byte	1				// type
	.byte	\data			// content
	.LTRX_\@\():
	.section dummy
	.byte	\data			// dummy data of right size
	.previous
.endm

//**************************************************************************************************

// random bytes
.macro TRX_data_random len:req
	.if \len % 4
		.error "len must be a multiple of 4"	// for the moment
	.endif
	.subsection 1
	.byte	.LTRX_\@ - .
	.byte	2, \len
	.LTRX_\@\():
	.section dummy
	.zero	\len
	.previous
.endm

//**************************************************************************************************

// checkpoint (dynamic data is inserted at runtime)
.macro TRX_data_checkpoint
	//.section dummy
	//.if ((. - 1000b) > 0)
	//	.error "checkpoint is allowed only at start of packet"		// for the moment
	//.endif
	//.previous
	.subsection 1
	.byte	2, 250
	.section dummy
	1250:	// checkpoint data
	.zero	TRX_CHECKPOINT_SIZE
	.previous
.endm

//**************************************************************************************************

// checkpoint marker (indicates if packet contains a checkpoint)
// ATTENTION: must be placed at TRX_CHECKPOINT_MARKER_POS
.macro TRX_data_checkpoint_marker
	.section dummy
	1256:	// checkpoint marker
	.previous
	TRX_data_fixed	0		// will be initialized at runtime
.endm

//**************************************************************************************************

// do not send a packet, only activate tx_carrier_period_1/2
.macro TRX_data_no_packet
	.subsection 1
	.byte	2, 255
	.section dummy
	1255:	// no_packet marker (can be checked in TRX_SYNC_end)
	.previous
.endm

//**************************************************************************************************
//***** Public Helper Macros ***********************************************************************

// passing a list (containing comma characters) to an asm macro parameter
// is possible by quoting it as a string. We provide a macro for this.
#define LIST(...)			_STRINGIFY(__VA_ARGS__)
#define _STRINGIFY(...)		#__VA_ARGS__

//**************************************************************************************************
//***** Schedule Specification *********************************************************************

// these symbols must be provided
	.global schedule, schedule_end, schedule_options

// enter target section
	.section .rodata.schedule
	.subsection 0
	.balign 4

// dummy TRX_GROUP (labels needed for checks)
3000:
	.fill	4
3999:

//.subsection 1
//schedule_1_begin:	// used for size check
//.subsection 0

// application-specific schedule
schedule:

#ifndef SCHEDULE_FILE
	#warning "SCHEDULE_FILE is not defined, nodes will do nothing (just terminate with empty schedule)"
#else
	#include LIST(SCHEDULE_FILE)
#endif

	// in case schedule runs through
	TERMINATE

	.subsection 1
	.balign		4

schedule_end:

	// check if schedule defines all mandatory constants

	.ifndef	TRX_PRE_DELAY
		.error	"TRX_PRE_DELAY is undefined"
	.elseif	((TRX_PRE_DELAY * TICKS_PER_US) > 0xffff)
		.error	"TRX_PRE_DELAY exceeds upper limit"
	.endif

	.ifndef	TRX_POST_DELAY
		.error	"TRX_POST_DELAY is undefined"
	.elseif	((TRX_POST_DELAY * TICKS_PER_US) > 0xffff)
		.error	"TRX_POST_DELAY exceeds upper limit"
	.endif

	.ifndef	TRX_CHECKPOINT_MARKER_POS
		.error	"TRX_CHECKPOINT_MARKER_POS is undefined"
	.endif

	TRX_PRE_DELAY  = TRX_PRE_DELAY * TICKS_PER_US
	TRX_POST_DELAY = TRX_POST_DELAY * TICKS_PER_US

	// for some reason SCHEDULE_SIZE_1 (= label difference in subsection 1 with subsections switched in between)
	// is interpreted as non-constant
	//.subsection 0
	//SCHEDULE_SIZE_0 = . - schedule
	//.subsection 1
	//SCHEDULE_SIZE_1 = . - schedule_1_begin
	//.if ((SCHEDULE_SIZE_0 + SCHEDULE_SIZE_1) > 0x10000)
	//	.error "schedule size exceed (must not be > 0x10000)"
	//.endif

schedule_options:

	// layout = struct Schedule_Options
	.2byte		TRX_PRE_DELAY
	.2byte		TRX_POST_DELAY
	.2byte		TRX_CHECKPOINT_MARKER_POS

//**************************************************************************************************
//**************************************************************************************************
