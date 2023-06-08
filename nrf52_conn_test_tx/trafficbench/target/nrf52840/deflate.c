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
 *	@file					deflate.c
 *
 *	@brief					deflate-compatible compression routines
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
#define TRACE_INFO		GPI_TRACE_MSG_TYPE_INFO
#define TRACE_WARNING	GPI_TRACE_MSG_TYPE_WARNING
#define TRACE_ERROR		GPI_TRACE_MSG_TYPE_ERROR
#define TRACE_VERBOSE	GPI_TRACE_MSG_TYPE_VERBOSE

// select active message groups, i.e., the messages to be printed (others will be dropped)
#ifndef GPI_TRACE_BASE_SELECTION
	#define GPI_TRACE_BASE_SELECTION	GPI_TRACE_LOG_STANDARD /*| GPI_TRACE_LOG_PROGRAM_FLOW*/
#endif
#ifndef GPI_TRACE_USER_SELECTION
	#define GPI_TRACE_USER_SELECTION	GPI_TRACE_LOG_USER
#endif
GPI_TRACE_CONFIG(deflate, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION);

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "deflate.h"

#include "gpi/tools.h"
#include "gpi/olf.h"

#include <stdlib.h>
#include <stdint.h>
//#include <inttypes.h>
#include <string.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

// maximum search window length for C2_DIFFERENTIAL search mode.
// higher values enable better compression, but increase memory consumption and search time.
#ifndef DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH
	#define DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH	1024
#elif DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH > 32768
	#warning "truncating DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH to 32K"
	#undef DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH
	#define DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH	32768
#endif

//**************************************************************************************************
// fixed code and header used in BTYPE 01

const static uint16_t CODE_LL_FIXED[286] =
{
	// 0 - 143
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
	0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,
	0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,
	0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
	0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,

	// 144 - 255
	0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0197, 0x0198, 0x0199, 0x019A, 0x019B, 0x019C, 0x019D, 0x019E, 0x019F,
	0x01A0, 0x01A1, 0x01A2, 0x01A3, 0x01A4, 0x01A5, 0x01A6, 0x01A7, 0x01A8, 0x01A9, 0x01AA, 0x01AB, 0x01AC, 0x01AD, 0x01AE, 0x01AF,
	0x01B0, 0x01B1, 0x01B2, 0x01B3, 0x01B4, 0x01B5, 0x01B6, 0x01B7, 0x01B8, 0x01B9, 0x01BA, 0x01BB, 0x01BC, 0x01BD, 0x01BE, 0x01BF,
	0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C4, 0x01C5, 0x01C6, 0x01C7, 0x01C8, 0x01C9, 0x01CA, 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF,
	0x01D0, 0x01D1, 0x01D2, 0x01D3, 0x01D4, 0x01D5, 0x01D6, 0x01D7, 0x01D8, 0x01D9, 0x01DA, 0x01DB, 0x01DC, 0x01DD, 0x01DE, 0x01DF,
	0x01E0, 0x01E1, 0x01E2, 0x01E3, 0x01E4, 0x01E5, 0x01E6, 0x01E7, 0x01E8, 0x01E9, 0x01EA, 0x01EB, 0x01EC, 0x01ED, 0x01EE, 0x01EF,
	0x01F0, 0x01F1, 0x01F2, 0x01F3, 0x01F4, 0x01F5, 0x01F6, 0x01F7, 0x01F8, 0x01F9, 0x01FA, 0x01FB, 0x01FC, 0x01FD, 0x01FE, 0x01FF,

	// 256 - 279
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 

	// 280 - 285
	0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5
};

const static uint8_t CLEN_LL_FIXED[143] =
{
	// 0 - 143
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,

	// 144 - 255
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,

	// 256 - 279
	0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
	0x77, 0x77, 0x77, 0x77, 

	// 280 - 285
	0x88, 0x88, 0x88
};

const static uint16_t CODE_DIST_FIXED[30] =
{
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D
};

const static uint8_t CLEN_DIST_FIXED[15] =
{
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55
};

const static uint8_t CHDR_FIXED[] =
{
	// BFINAL = 0
	// BTYPE = 01
	0x02
};

const static uint16_t CHDR_FIXED_SIZE = 3;

//**************************************************************************************************
// code optimized for
// - almost constant data, stored in differential format (-> many 0s, some +/-1s, little other values)
// - C1 mode (-> no distance alphabet)

const static uint16_t CODE_LL_C1_1[257] =
{
	// 0 - 255
	0x0000, 0x0004, 0x0030, 0x0031, 0x0032, 0x0033, 0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0714, 0x0715, 0x0716, 0x0717, 0x0718, 
	0x0719, 0x071A, 0x071B, 0x071C, 0x071D, 0x071E, 0x071F, 0x0720, 0x0721, 0x0722, 0x0723, 0x0724, 0x0725, 0x0726, 0x0727, 0x0728, 
	0x0729, 0x072A, 0x072B, 0x072C, 0x072D, 0x072E, 0x072F, 0x0730, 0x0731, 0x0732, 0x0733, 0x0734, 0x0735, 0x0736, 0x0737, 0x0738, 
	0x0739, 0x073A, 0x073B, 0x073C, 0x073D, 0x073E, 0x073F, 0x0740, 0x0741, 0x0742, 0x0743, 0x0744, 0x0745, 0x0746, 0x0747, 0x0748, 
	0x0749, 0x074A, 0x074B, 0x074C, 0x074D, 0x074E, 0x074F, 0x0750, 0x0751, 0x0752, 0x0753, 0x0754, 0x0755, 0x0756, 0x0757, 0x0758, 
	0x0759, 0x075A, 0x075B, 0x075C, 0x075D, 0x075E, 0x075F, 0x0760, 0x0761, 0x0762, 0x0763, 0x0764, 0x0765, 0x0766, 0x0767, 0x0768, 
	0x0769, 0x076A, 0x076B, 0x076C, 0x076D, 0x076E, 0x076F, 0x0770, 0x0771, 0x0772, 0x0773, 0x0774, 0x0775, 0x0776, 0x0777, 0x0778, 
	0x0779, 0x077A, 0x077B, 0x077C, 0x077D, 0x077E, 0x077F, 0x0780, 0x0781, 0x0782, 0x0783, 0x0784, 0x0785, 0x0786, 0x0787, 0x0788, 
	0x0789, 0x078A, 0x078B, 0x078C, 0x078D, 0x078E, 0x078F, 0x0790, 0x0791, 0x0792, 0x0793, 0x0794, 0x0795, 0x0796, 0x0797, 0x0798, 
	0x0799, 0x079A, 0x079B, 0x079C, 0x079D, 0x079E, 0x079F, 0x07A0, 0x07A1, 0x07A2, 0x07A3, 0x07A4, 0x07A5, 0x07A6, 0x07A7, 0x07A8, 
	0x07A9, 0x07AA, 0x07AB, 0x07AC, 0x07AD, 0x07AE, 0x07AF, 0x07B0, 0x07B1, 0x07B2, 0x07B3, 0x07B4, 0x07B5, 0x07B6, 0x07B7, 0x07B8, 
	0x07B9, 0x07BA, 0x07BB, 0x07BC, 0x07BD, 0x07BE, 0x07BF, 0x07C0, 0x07C1, 0x07C2, 0x07C3, 0x07C4, 0x07C5, 0x07C6, 0x07C7, 0x07C8, 
	0x07C9, 0x07CA, 0x07CB, 0x07CC, 0x07CD, 0x07CE, 0x07CF, 0x07D0, 0x07D1, 0x07D2, 0x07D3, 0x07D4, 0x07D5, 0x07D6, 0x07D7, 0x07D8, 
	0x07D9, 0x07DA, 0x07DB, 0x07DC, 0x07DD, 0x07DE, 0x07DF, 0x07E0, 0x07E1, 0x07E2, 0x07E3, 0x07E4, 0x07E5, 0x07E6, 0x07E7, 0x07E8, 
	0x07E9, 0x07EA, 0x07EB, 0x07EC, 0x07ED, 0x07EE, 0x07EF, 0x07F0, 0x07F1, 0x07F2, 0x07F3, 0x07F4, 0x07F5, 0x07F6, 0x07F7, 0x07F8, 
	0x07F9, 0x07FA, 0x07FB, 0x07FC, 0x07FD, 0x07FE, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389, 0x0034, 0x0035, 0x0036, 0x0037, 0x0005, 

	// 256
	0x07FF
};

const static uint8_t CLEN_LL_C1_1[129] =
{
	// 0 - 11
	0x31, 0x66, 0x66, 0xAA, 0xAA, 0xBA,
	
	// 12 - 245
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	
	// 246 - 255
	0xAA, 0xAA, 0x6A, 0x66, 0x36, 
	
	// 256
	0x0B
};

const static uint8_t CHDR_C1_1[] =
{
	// BFINAL = 0
	// BTYPE = 2
	
	// HLIT = 0 (257)
	// HDIST = 0 (1)
	// HCLEN = 14 (18)

	// used code length code:
	// symbol	length	code
	// ---------------------
	// 16		1		0
	// 10		3		100
	// 11		3		101
	//  0		4		1100
	//  1		4		1101
	//  3		4		1110
	//  6		4		1111
	
	// code lengths for the code length alphabet in the order 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
	// 1, 0, 0, 4, 0, 0, 0, 4, 3, 0, 3, 0, 0, 4, 0, 0, 0, 4

	// code lengths for the literal/length code
	// 1, 3, 6, 16/3, 10, 16/4, 11, 16/6 ... 16/6 (39 times), 10, 16/4, 6, 16/3, 3, 11

	// code lengths for the distance alphabet
	// 0

	// raw content (binary):
	// 0 01 00000 00000 0111
	// 100 000 000 001 000 000 000 001 110 000 110 000 000 001 000 000 000 001
	// 1101 1110 1111 000 100 010 101
	// 011 011 011 011 011 011 011 011 011 011
	// 011 011 011 011 011 011 011 011 011 011
	// 011 011 011 011 011 011 011 011 011 011
	// 011 011 011 011 011 011 011 011 011 
	// 100 010 1111 000 1110 101
	// 1100
	
	0x20, 0x03, 0xC0, 0x08, 0x00, 0xE1, 0x80, 0x20, 
	0x03, 0xBD, 0xE2, 0x2A, 0xDB, 0x6D, 0xB6, 0xDB, 
	0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 
	0xDB, 0x6D, 0xB8, 0xBC, 0x75, 0x0C	// 4 bits unused in the last byte
};

const static uint16_t CHDR_C1_1_SIZE = sizeof(CHDR_C1_1) * 8 - 4;

//**************************************************************************************************
// code optimized for
// - almost constant data, stored in differential format (-> many 0s, some +/-1s, little other values)
// - C1 mode (-> no distance alphabet)

const static uint16_t CODE_LL_C1_2[257] =
{
	// 0 - 255
	0x0000, 0x0001, 0x0018, 0x0019, 0x0380, 0x0381, 0x0382, 0x070C, 0x070D, 0x070E, 0x070F, 0x0710, 0x0711, 0x0712, 0x0713, 0x0714, 
	0x0715, 0x0716, 0x0717, 0x0718, 0x0719, 0x071A, 0x071B, 0x071C, 0x071D, 0x071E, 0x071F, 0x0720, 0x0721, 0x0722, 0x0723, 0x0724,
	0x0725, 0x0726, 0x0727, 0x0728, 0x0729, 0x072A, 0x072B, 0x072C, 0x072D, 0x072E, 0x072F, 0x0730, 0x0731, 0x0732, 0x0733, 0x0734, 
	0x0735, 0x0736, 0x0737, 0x0738, 0x0739, 0x073A, 0x073B, 0x073C, 0x073D, 0x073E, 0x073F, 0x0740, 0x0741, 0x0742, 0x0743, 0x0744, 
	0x0745, 0x0746, 0x0747, 0x0748, 0x0749, 0x074A, 0x074B, 0x074C, 0x074D, 0x074E, 0x074F, 0x0750, 0x0751, 0x0752, 0x0753, 0x0754, 
	0x0755, 0x0756, 0x0757, 0x0758, 0x0759, 0x075A, 0x075B, 0x075C, 0x075D, 0x075E, 0x075F, 0x0760, 0x0761, 0x0762, 0x0763, 0x0764, 
	0x0765, 0x0766, 0x0767, 0x0768, 0x0769, 0x076A, 0x076B, 0x076C, 0x076D, 0x076E, 0x076F, 0x0770, 0x0771, 0x0772, 0x0773, 0x0774, 
	0x0775, 0x0776, 0x0777, 0x0778, 0x0779, 0x077A, 0x077B, 0x077C, 0x077D, 0x077E, 0x077F, 0x0780, 0x0781, 0x0782, 0x0783, 0x0784, 
	0x0785, 0x0786, 0x0787, 0x0788, 0x0789, 0x078A, 0x078B, 0x078C, 0x078D, 0x078E, 0x078F, 0x0790, 0x0791, 0x0792, 0x0793, 0x0794, 
	0x0795, 0x0796, 0x0797, 0x0798, 0x0799, 0x079A, 0x079B, 0x079C, 0x079D, 0x079E, 0x079F, 0x07A0, 0x07A1, 0x07A2, 0x07A3, 0x07A4, 
	0x07A5, 0x07A6, 0x07A7, 0x07A8, 0x07A9, 0x07AA, 0x07AB, 0x07AC, 0x07AD, 0x07AE, 0x07AF, 0x07B0, 0x07B1, 0x07B2, 0x07B3, 0x07B4, 
	0x07B5, 0x07B6, 0x07B7, 0x07B8, 0x07B9, 0x07BA, 0x07BB, 0x07BC, 0x07BD, 0x07BE, 0x07BF, 0x07C0, 0x07C1, 0x07C2, 0x07C3, 0x07C4, 
	0x07C5, 0x07C6, 0x07C7, 0x07C8, 0x07C9, 0x07CA, 0x07CB, 0x07CC, 0x07CD, 0x07CE, 0x07CF, 0x07D0, 0x07D1, 0x07D2, 0x07D3, 0x07D4, 
	0x07D5, 0x07D6, 0x07D7, 0x07D8, 0x07D9, 0x07DA, 0x07DB, 0x07DC, 0x07DD, 0x07DE, 0x07DF, 0x07E0, 0x07E1, 0x07E2, 0x07E3, 0x07E4, 
	0x07E5, 0x07E6, 0x07E7, 0x07E8, 0x07E9, 0x07EA, 0x07EB, 0x07EC, 0x07ED, 0x07EE, 0x07EF, 0x07F0, 0x07F1, 0x07F2, 0x07F3, 0x07F4, 
	0x07F5, 0x07F6, 0x07F7, 0x07F8, 0x07F9, 0x07FA, 0x07FB, 0x07FC, 0x07FD, 0x07FE, 0x0383, 0x0384, 0x0385, 0x001A, 0x001B, 0x0002, 
	
	// 256
	0x07FF
};

const static uint8_t CLEN_LL_C1_2[129] =
{
	// 0 - 7
	0x22, 0x55, 0xAA, 0xBA,
	
	// 8 - 247
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
	
	// 248 - 255
	0xBB, 0xAA, 0x5A, 0x25, 
	
	// 256
	0x0B
};

const static uint8_t CHDR_C1_2[] =
{
	// BFINAL = 0
	// BTYPE = 2
	
	// HLIT = 0 (257)
	// HDIST = 0 (1)
	// HCLEN = 12 (16)

	// used code length code:
	// symbol	length	code
	// ---------------------
	// 16		1		0
	//  2		3		100
	//  5		3		101
	// 10		3		110
	//  0		4		1110
	// 11		4		1111
	
	// code lengths for the code length alphabet in the order 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
	// 1, 0, 0, 4, 0, 0, 0, 0, 3, 3, 4, 0, 0, 0, 0, 3

	// code lengths for the literal/length code
	// 2, 2, 5, 5, 10, 10, 10, 11, 16/6 ... 16/6 (39 times), 16/5, 16/3, 10, 10, 10, 5, 5, 2, 11

	// code lengths for the distance alphabet
	// 0

	// raw content (binary):
	// 0 01 00000 00000 0011
	// 100 000 000 001 000 000 000 000 110 110 001 000 000 000 000 110
	// 100 100 101 101 110 110 110 1111 
	// 011 011 011 011 011 011 011 011 011 011 
	// 011 011 011 011 011 011 011 011 011 011
	// 011 011 011 011 011 011 011 011 011 011 
	// 011 011 011 011 011 011 011 011 011
	// 001 000 110 110 110 101 101 100 1111
	// 1110
	
	0x20, 0x01, 0xC0, 0x08, 0x00, 0x6C, 0x40, 0x03, 
	0x49, 0x6E, 0xDB, 0xDB, 0x6D, 0xB6, 0xDB, 0x6D, 
	0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 
	0x6D, 0xB6, 0x46, 0xDA, 0xD9, 0x7E  // 1 bit unused in the last byte
};

const static uint16_t CHDR_C1_2_SIZE = sizeof(CHDR_C1_2) * 8 - 1;

//**************************************************************************************************
// code optimized for
// - almost constant data, stored in differential format (-> many 0s, some +/-1s, little other values)
// - C2 mode

const static uint16_t CODE_LL_C2_1[286] =
{
	// 0 - 255
	0x0000, 0x0001, 0x0018, 0x0019, 0x01E0, 0x01E1, 0x01E2, 0x01E3, 0x01E4, 0x01E5, 0x01E6, 0x1F80, 0x3F06, 0x3F07, 0x3F08, 0x3F09, 
	0x3F0A, 0x3F0B, 0x3F0C, 0x3F0D, 0x3F0E, 0x3F0F, 0x3F10, 0x3F11, 0x3F12, 0x3F13, 0x3F14, 0x3F15, 0x3F16, 0x3F17, 0x3F18, 0x3F19, 
	0x3F1A, 0x3F1B, 0x3F1C, 0x3F1D, 0x3F1E, 0x3F1F, 0x3F20, 0x3F21, 0x3F22, 0x3F23, 0x3F24, 0x3F25, 0x3F26, 0x3F27, 0x3F28, 0x3F29, 
	0x3F2A, 0x3F2B, 0x3F2C, 0x3F2D, 0x3F2E, 0x3F2F, 0x3F30, 0x3F31, 0x3F32, 0x3F33, 0x3F34, 0x3F35, 0x3F36, 0x3F37, 0x3F38, 0x3F39, 
	0x3F3A, 0x3F3B, 0x3F3C, 0x3F3D, 0x3F3E, 0x3F3F, 0x3F40, 0x3F41, 0x3F42, 0x3F43, 0x3F44, 0x3F45, 0x3F46, 0x3F47, 0x3F48, 0x3F49, 
	0x3F4A, 0x3F4B, 0x3F4C, 0x3F4D, 0x3F4E, 0x3F4F, 0x3F50, 0x3F51, 0x3F52, 0x3F53, 0x3F54, 0x3F55, 0x3F56, 0x3F57, 0x3F58, 0x3F59, 
	0x3F5A, 0x3F5B, 0x3F5C, 0x3F5D, 0x3F5E, 0x3F5F, 0x3F60, 0x3F61, 0x3F62, 0x3F63, 0x3F64, 0x3F65, 0x3F66, 0x3F67, 0x3F68, 0x3F69, 
	0x3F6A, 0x3F6B, 0x3F6C, 0x3F6D, 0x3F6E, 0x3F6F, 0x3F70, 0x3F71, 0x3F72, 0x3F73, 0x3F74, 0x3F75, 0x3F76, 0x3F77, 0x3F78, 0x3F79, 
	0x3F7A, 0x3F7B, 0x3F7C, 0x3F7D, 0x3F7E, 0x3F7F, 0x3F80, 0x3F81, 0x3F82, 0x3F83, 0x3F84, 0x3F85, 0x3F86, 0x3F87, 0x3F88, 0x3F89, 
	0x3F8A, 0x3F8B, 0x3F8C, 0x3F8D, 0x3F8E, 0x3F8F, 0x3F90, 0x3F91, 0x3F92, 0x3F93, 0x3F94, 0x3F95, 0x3F96, 0x3F97, 0x3F98, 0x3F99, 
	0x3F9A, 0x3F9B, 0x3F9C, 0x3F9D, 0x3F9E, 0x3F9F, 0x3FA0, 0x3FA1, 0x3FA2, 0x3FA3, 0x3FA4, 0x3FA5, 0x3FA6, 0x3FA7, 0x3FA8, 0x3FA9, 
	0x3FAA, 0x3FAB, 0x3FAC, 0x3FAD, 0x3FAE, 0x3FAF, 0x3FB0, 0x3FB1, 0x3FB2, 0x3FB3, 0x3FB4, 0x3FB5, 0x3FB6, 0x3FB7, 0x3FB8, 0x3FB9, 
	0x3FBA, 0x3FBB, 0x3FBC, 0x3FBD, 0x3FBE, 0x3FBF, 0x3FC0, 0x3FC1, 0x3FC2, 0x3FC3, 0x3FC4, 0x3FC5, 0x3FC6, 0x3FC7, 0x3FC8, 0x3FC9, 
	0x3FCA, 0x3FCB, 0x3FCC, 0x3FCD, 0x3FCE, 0x3FCF, 0x3FD0, 0x3FD1, 0x3FD2, 0x3FD3, 0x3FD4, 0x3FD5, 0x3FD6, 0x3FD7, 0x3FD8, 0x3FD9, 
	0x3FDA, 0x3FDB, 0x3FDC, 0x3FDD, 0x3FDE, 0x3FDF, 0x3FE0, 0x3FE1, 0x3FE2, 0x3FE3, 0x3FE4, 0x3FE5, 0x3FE6, 0x3FE7, 0x3FE8, 0x3FE9, 
	0x3FEA, 0x3FEB, 0x3FEC, 0x3FED, 0x3FEE, 0x1F81, 0x01E7, 0x01E8, 0x01E9, 0x01EA, 0x01EB, 0x01EC, 0x01ED, 0x001A, 0x001B, 0x0002, 

	// 256 - 285
	0x1F82, 0x001C, 0x001D, 0x01EE, 0x01EF, 0x01F0, 0x01F1, 0x01F2, 0x01F3, 0x01F4, 0x01F5, 0x01F6, 0x01F7, 0x3FEF, 0x3FF0, 0x3FF1, 
	0x3FF2, 0x3FF3, 0x3FF4, 0x3FF5, 0x3FF6, 0x3FF7, 0x3FF8, 0x3FF9, 0x3FFA, 0x3FFB, 0x3FFC, 0x3FFD, 0x3FFE, 0x3FFF
};

const static uint8_t CLEN_LL_C2_1[143] =
{
	// 0 - 11
	0x22, 0x55, 0x99, 0x99, 0x99, 0xD9,

	// 12 - 243
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xEE, 0xEE, 0xEE, 0xEE,

	// 244 - 255
	0xDE, 0x99, 0x99, 0x99, 0x59, 0x25,
	
	// 256 - 269
	0x5D, 0x95, 0x99, 0x99, 0x99, 0x99,	0xE9,
	
	// 270 - 285
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE
};

const static uint16_t CODE_DIST_C2_1[30] =
{
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x0070, 0x0071, 
	0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F
};

const static uint8_t CLEN_DIST_C2_1[15] =
{
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77
};

const static uint8_t CHDR_C2_1[] =
{
	// BFINAL = 0
	// BTYPE = 2
	
	// HLIT = 29 (286)
	// HDIST = 29 (30)
	// HCLEN = 13 (17)

	// used code length code:
	// symbol	length	code
	// ---------------------
	// 16		1		0
	//  5		3		100
	// 13		3		101
	//  2		4		1100
	//  9		4		1101
	// 14		4		1110
	//  4		5		11110
	//	7		5		11111
	
	// code lengths for the code length alphabet in the order 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
	// 1, 0, 0, 0, 0, 5, 4, 0, 0, 3, 0, 5, 0, 0, 3, 4, 4

	// code lengths for the literal/length code
	// 2, 2, 5, 5, 9, 16/6, 13, 14, 16/6 ... 16/6 (38 times), 16/4, 13, 9, 16/6, 5, 5, 2, 13, 5, 5, 9, 16/6, 16/3, 14, 16/6, 16/6, 16/4
	
	// code lengths for the distance alphabet
	// 4, 16/6, 16/4, 16/3, 7, 16/6, 16/6, 16/3

	// raw content (binary):
	// 0 01 10111 10111 1011
	// 100 000 000 000 000 101 001 000 000 110 000 101 000 000 110 001 001
	// 1100 1100 100 100 1101 011 101 1110
	// 011 011 011 011 011 011 011 011 011 011 
	// 011 011 011 011 011 011 011 011 011 011 
	// 011 011 011 011 011 011 011 011 011 011 
	// 011 011 011 011 011 011 011 011 
	// 010 101 1101 011 100 100 1100 101 100 100 1101 011 000 1110 011 011 010
	// 11110 011 010 000 11111 011 011 000

	0x37, 0xBD, 0xC0, 0x00, 0xA4, 0x0C, 0x28, 0x18, 
	0x9C, 0xC9, 0x35, 0xDE, 0x6D, 0xB6, 0xDB, 0x6D, 
	0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 
	0x6D, 0xB6, 0xD5, 0xD7, 0x26, 0x59, 0x35, 0x8E, 
	0x6D, 0x79, 0xA1, 0xF6, 0x18  // 3 bits unused in the last byte
};

const static uint16_t CHDR_C2_1_SIZE = sizeof(CHDR_C2_1) * 8 - 3;

//**************************************************************************************************
// code optimized for
// - almost constant data, stored in differential format (-> many 0s, some +/-1s, little other values)
// - C2 mode

const static uint16_t CODE_LL_C2_2[286] =
{
	// 0 - 255
	0x01E0, 0x01E1, 0x01E2, 0x01E3, 0x01E4, 0x1F80, 0x1F81, 0x1F82, 0x3F06, 0x3F07, 0x3F08, 0x3F09, 0x3F0A, 0x3F0B, 0x3F0C, 0x3F0D, 
	0x3F0E, 0x3F0F, 0x3F10, 0x3F11, 0x3F12, 0x3F13, 0x3F14, 0x3F15, 0x3F16, 0x3F17, 0x3F18, 0x3F19, 0x3F1A, 0x3F1B, 0x3F1C, 0x3F1D, 
	0x3F1E, 0x3F1F, 0x3F20, 0x3F21, 0x3F22, 0x3F23, 0x3F24, 0x3F25, 0x3F26, 0x3F27, 0x3F28, 0x3F29, 0x3F2A, 0x3F2B, 0x3F2C, 0x3F2D, 
	0x3F2E, 0x3F2F, 0x3F30, 0x3F31, 0x3F32, 0x3F33, 0x3F34, 0x3F35, 0x3F36, 0x3F37, 0x3F38, 0x3F39, 0x3F3A, 0x3F3B, 0x3F3C, 0x3F3D, 
	0x3F3E, 0x3F3F, 0x3F40, 0x3F41, 0x3F42, 0x3F43, 0x3F44, 0x3F45, 0x3F46, 0x3F47, 0x3F48, 0x3F49, 0x3F4A, 0x3F4B, 0x3F4C, 0x3F4D, 
	0x3F4E, 0x3F4F, 0x3F50, 0x3F51, 0x3F52, 0x3F53, 0x3F54, 0x3F55, 0x3F56, 0x3F57, 0x3F58, 0x3F59, 0x3F5A, 0x3F5B, 0x3F5C, 0x3F5D, 
	0x3F5E, 0x3F5F, 0x3F60, 0x3F61, 0x3F62, 0x3F63, 0x3F64, 0x3F65, 0x3F66, 0x3F67, 0x3F68, 0x3F69, 0x3F6A, 0x3F6B, 0x3F6C, 0x3F6D, 
	0x3F6E, 0x3F6F, 0x3F70, 0x3F71, 0x3F72, 0x3F73, 0x3F74, 0x3F75, 0x3F76, 0x3F77, 0x3F78, 0x3F79, 0x3F7A, 0x3F7B, 0x3F7C, 0x3F7D, 
	0x3F7E, 0x3F7F, 0x3F80, 0x3F81, 0x3F82, 0x3F83, 0x3F84, 0x3F85, 0x3F86, 0x3F87, 0x3F88, 0x3F89, 0x3F8A, 0x3F8B, 0x3F8C, 0x3F8D, 
	0x3F8E, 0x3F8F, 0x3F90, 0x3F91, 0x3F92, 0x3F93, 0x3F94, 0x3F95, 0x3F96, 0x3F97, 0x3F98, 0x3F99, 0x3F9A, 0x3F9B, 0x3F9C, 0x3F9D, 
	0x3F9E, 0x3F9F, 0x3FA0, 0x3FA1, 0x3FA2, 0x3FA3, 0x3FA4, 0x3FA5, 0x3FA6, 0x3FA7, 0x3FA8, 0x3FA9, 0x3FAA, 0x3FAB, 0x3FAC, 0x3FAD, 
	0x3FAE, 0x3FAF, 0x3FB0, 0x3FB1, 0x3FB2, 0x3FB3, 0x3FB4, 0x3FB5, 0x3FB6, 0x3FB7, 0x3FB8, 0x3FB9, 0x3FBA, 0x3FBB, 0x3FBC, 0x3FBD, 
	0x3FBE, 0x3FBF, 0x3FC0, 0x3FC1, 0x3FC2, 0x3FC3, 0x3FC4, 0x3FC5, 0x3FC6, 0x3FC7, 0x3FC8, 0x3FC9, 0x3FCA, 0x3FCB, 0x3FCC, 0x3FCD, 
	0x3FCE, 0x3FCF, 0x3FD0, 0x3FD1, 0x3FD2, 0x3FD3, 0x3FD4, 0x3FD5, 0x3FD6, 0x3FD7, 0x3FD8, 0x3FD9, 0x3FDA, 0x3FDB, 0x3FDC, 0x3FDD, 
	0x3FDE, 0x3FDF, 0x3FE0, 0x3FE1, 0x3FE2, 0x3FE3, 0x3FE4, 0x3FE5, 0x3FE6, 0x3FE7, 0x3FE8, 0x3FE9, 0x3FEA, 0x3FEB, 0x3FEC, 0x3FED, 
	0x3FEE, 0x3FEF, 0x3FF0, 0x3FF1, 0x3FF2, 0x3FF3, 0x3FF4, 0x3FF5, 0x3FF6, 0x3FF7, 0x3FF8, 0x3FF9, 0x01E5, 0x01E6, 0x01E7, 0x01E8, 

	// 256 - 285
	0x3FFA, 0x01E9, 0x01EA, 0x01EB, 0x01EC, 0x0018, 0x0019, 0x001A, 0x001B, 0x0000, 0x0001, 0x0002, 0x001C, 0x001D, 0x01ED, 0x01EE, 
	0x01EF, 0x01F0, 0x01F1, 0x01F2, 0x01F3, 0x01F4, 0x01F5, 0x01F6, 0x01F7, 0x3FFB, 0x3FFC, 0x3FFD, 0x3FFE, 0x3FFF
};

const static uint8_t CLEN_LL_C2_2[143] =
{
	// 0 - 7
	0x99, 0x99, 0xd9, 0xdd, 
	
	// 8 - 251
	0xee, 0xee, 0xee, 0xee,	0xee, 0xee, 0xee, 0xee, 
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	0xee, 0xee, 0xee, 0xee,	0xee, 0xee, 0xee, 0xee, 
	0xee, 0xee, 
	
	// 252 - 255
	0x99, 0x99,

	// 256 - 285
	0x9e, 0x99, 0x59, 0x55, 0x25, 0x22, 0x55, 0x99,
	0x99, 0x99, 0x99, 0x99, 0xe9, 0xee, 0xee
};

const static uint8_t CHDR_C2_2[] =
{
	// BFINAL = 0
	// BTYPE = 2
	
	// HLIT = 29 (286)
	// HDIST = 29 (30)
	// HCLEN = 13 (17)

	// used code length code:
	// symbol	length	code
	// ---------------------
	// 16		1		0
	//  9		3		100
	// 14		3		101
	//  2		4		1100
	//  5		4		1101
	// 13		4		1110
	//  4		5		11110
	//  7		5		11111
	
	// code lengths for the code length alphabet in the order 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
	// 1, 0, 0,	0, 0, 5, 3, 0, 0, 4, 0, 5, 0, 0, 4, 4, 3

	// code lengths for the literal/length code
	// 9, 16/4, 13, 13, 13, 14, 16/6 ... (40 times), 16/3, 9, 16/3, 14, 9, 16/3, 5, 16/3, 2, 2, 2, 5, 5, 9, 16/6, 16/4, 14, 16/4

	// code lengths for the distance alphabet
	// 4, 16/6, 16/4, 16/3, 7, 16/6, 16/6, 16/3

	// raw content (binary):
	// 0 01 10111 10111 1011
	// 100 000 000 000 000 101 110 000 000 001 000 101 000 000 001 001 110
	// 100 0 10 1110 1110 1110 101
	// 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11
	// 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11
	// 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11
	// 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11 0 11
	// 0 00 100 0 00 101 100 0 00 1101 0 00 1100 1100 1100 1101 1101 100 0 11 0 10 101 0 10
	// 11110 0 11 0 10 0 00 11111 0 11 0 11 0 00

	0x37, 0xBD, 0xC0, 0x00, 0xB8, 0x02, 0x28, 0x04, 
	0xE8, 0xBB, 0xBA, 0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 
	0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 0xDB, 0x6D, 0xB6, 
	0xDB, 0x6D, 0x88, 0x2C, 0x1A, 0x33, 0x33, 0x76, 
	0x35, 0x57, 0x9A, 0x1F, 0x6C, 0x00  // 7 bits unused in the last byte
};

const static uint16_t CHDR_C2_2_SIZE = sizeof(CHDR_C2_2) * 8 - 7;

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************



//**************************************************************************************************
//***** Forward Declarations ***********************************************************************



//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************

// internal state
// ATTENTION: deflate() is not reentrant
static struct
{
	uint8_t					*dest_end;
	size_t					noverflow;
	
	uint32_t				buffer;
	uint_fast8_t			npending;

	struct
	{
		const void			*src;
		void				*dest;
		uint32_t			buffer;
		uint_fast8_t		npending;
		
	} checkpoint;
	
	uint16_t				tail;
	uint8_t					tail_size;
	
	Deflate_Method			method;

	// algorithm / block_type dependent state data
	union
	{
		struct
		{
			const uint8_t	*window;

			// NOTE: Strictly, length and datatype need not match. The length defines the size
			// of the whole window, while the datatype defines the maximum distance between two
			// entries of a chain. However, we do not distinguish that here.
			#if (DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH <= 0x100)
				uint8_t			hash_chain[DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH];
			#elif (DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH <= 0x10000)
				uint16_t		hash_chain[DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH];
			#else
				#error "DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH invalid"
			#endif

			int16_t			hash_anchor[27];
			
		} differential;
	};
	
} state;

//**************************************************************************************************
//***** Global Variables ***************************************************************************

// predefined compression method descriptors
const Deflate_Method	DEFLATE_FLUSH_ = {NONE, NULL, NULL, NULL, NULL, NULL, 0};
const Deflate_Method	DEFLATE_C0_FIXED_ = {C0_FIXED, NULL, NULL, NULL, NULL, NULL, 0};
const Deflate_Method	DEFLATE_C0_STREAM_ = {C0_STREAM, NULL, NULL, NULL, NULL, NULL, 0};
const Deflate_Method	DEFLATE_C1_DIFF1_ = {C1, CODE_LL_C1_1, CLEN_LL_C1_1, NULL, NULL, CHDR_C1_1, CHDR_C1_1_SIZE};
const Deflate_Method	DEFLATE_C2_DIFF0_ = {C2_DIFFERENTIAL, CODE_LL_FIXED, CLEN_LL_FIXED, CODE_DIST_FIXED, CLEN_DIST_FIXED, CHDR_FIXED, CHDR_FIXED_SIZE};
const Deflate_Method	DEFLATE_C2_DIFF1_ = {C2_DIFFERENTIAL, CODE_LL_C2_1, CLEN_LL_C2_1, CODE_DIST_C2_1, CLEN_DIST_C2_1, CHDR_C2_1, CHDR_C2_1_SIZE};
const Deflate_Method	DEFLATE_C2_DIFF2_ = {C2_DIFFERENTIAL, CODE_LL_C2_2, CLEN_LL_C2_2, CODE_DIST_C2_1, CLEN_DIST_C2_1, CHDR_C2_2, CHDR_C2_2_SIZE};

//**************************************************************************************************
//***** Local Functions ****************************************************************************

// set a checkpoint.
// going back to a checkpoint allows to emit consistent output in case a full block cannot be
// processed completely due to insufficient buffer size
static inline void set_checkpoint(void *dest, const void *src)
{
	assert(!state.noverflow);
	
	state.checkpoint.src		= src;
	state.checkpoint.dest		= dest;
	state.checkpoint.npending	= state.npending;
	state.checkpoint.buffer		= state.buffer;
}

//**************************************************************************************************

// suggest to set a checkpoint
// (set one if dest buffer is almost full, otherwise skip the effort (to improve performance)
// because not having a checkpoint at the current place is uncritical)
static inline void suggest_checkpoint(void *dest, const void *src)
{
	if (!state.noverflow && (state.dest_end - (uint8_t*)dest < 8))
		set_checkpoint(dest, src);
}

//**************************************************************************************************

// flush output buffer (shift register)
static uint8_t* flush(uint8_t *dest)
{
	uint_fast8_t	nbytes = MIN(state.npending / 8, state.dest_end - dest);
	uint32_t		b;
	
	if (nbytes > 0)
	{
		b = gpi_bitswap(state.buffer);
		b >>= 32 - state.npending;

		switch (nbytes)
		{
			case 4:	*dest++ = b; b >>= 8;	// don't break
			case 3:	*dest++ = b; b >>= 8;	// don't break
			case 2:	*dest++ = b; b >>= 8;	// don't break
			case 1:	*dest++ = b;			// don't break
		}

		state.npending -= nbytes * 8;
	}
	
	return dest;
}

//**************************************************************************************************

// push bits to output buffer (shift register)
static inline uint8_t* push(uint8_t *dest, uint_fast32_t data, uint_fast8_t num_bits)
{
	if (state.noverflow)
		state.noverflow += num_bits;
		
	else
	{
		if (state.npending + num_bits > 32)
			dest = flush(dest);
			
		if (state.npending + num_bits > 32)
			state.noverflow = num_bits;

		else
		{
			state.buffer <<= num_bits;
			state.buffer |= data;
			state.npending += num_bits;

			// ATTENTION: data is not masked (for performance reasons), i.e. data is expected to be well-formed
			// state.buffer |= data & (UINT32_MAX >> (32 - num_bits));
		}
	}

	return dest;
}

//**************************************************************************************************

// push code symbol to output buffer (shift register)
static inline uint8_t* push_symbol(uint8_t *dest, uint_fast16_t symbol, const uint16_t *code, const uint8_t *clen)
{
	uint_fast8_t n = clen[symbol / 2];
	if (symbol & 1)
		n >>= 4;
	else n &= 0x0F;

	return push(dest, code[symbol], n);
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

// deflate input data
size_t deflate(
				void*					dest, 
				size_t					dest_size, 
				const void*				src, 
				size_t					len, 
				const Deflate_Method*	method,
				const void*				window, 
				size_t*					nwritten, 
				size_t*					nread)
{
	GPI_TRACE_FUNCTION();

	const uint8_t		*s = src;
	uint8_t				*d = dest;

	state.dest_end = &d[dest_size];
	state.noverflow = 0;
	set_checkpoint(d, s);

	// init
	if (NULL == dest)
	{
		state.method.mode = NONE;
		state.npending = 0;
		state.tail_size = 0;
		
		GPI_TRACE_RETURN(0);
	}

	assert(dest_size >= 8);
	
	// if new block: close open block
	if (NULL != method)
	{
		if (state.tail_size > 0)
		{
			GPI_TRACE_MSG(TRACE_VERBOSE, "close block");
			
			d = push(d, state.tail, state.tail_size);
			assert(!state.noverflow);
			
			state.tail_size = 0;

			set_checkpoint(d, s);
		}
		
		state.method.mode = NONE;
	}
	else method = &state.method;

	// encode data
	switch (method->mode)
	{
		// NONE is used to finalize current data chunk and flush buffer
		case NONE:
		{
			// finalize data chunk
			// NOTE: this could be made optional, e.g. depending on src or len
			GPI_TRACE_MSG(TRACE_VERBOSE, "finalize chunk");
			d = push(d, 0x300, 10);		// new block, BFINAL = 1, BTYPE = 01 | end-of-block marker

			// flush buffer
			GPI_TRACE_MSG(TRACE_VERBOSE, "flush buffer");
			d = push(d, 0, (32 - state.npending) % 8);
			d = flush(d);
			
			// state.method.mode = NONE; (follows from above)
			break;
		}
		
		case C0_FIXED:
		{
			assert(NULL == method->header);
			
			while (len > 0)
			{
				d = push(d, 0x0, 3);	// new block, BFINAL = 0, BTYPE = 00 (LSB first)
				d = push(d, 0, (32 - state.npending) % 8);
				d = flush(d);

				size_t l = MIN(len, 0x7fff);
				
				if (state.npending || state.noverflow || (l > state.dest_end - d - 4))
					break;
					
				*d++ = l;
				*d++ = l >> 8;
				*d++ = ~l;
				*d++ = ~l >> 8;
	
				memcpy(d, s, l);
				d += l;
				s += l;

				set_checkpoint(d, s);

				len -= l;
			}
			
			// state.method.mode = NONE; (follows from above)
			break;
		}

		case C0_STREAM:
		{
			assert(NULL == method->header);
			
			// open new block if necessary
			if (NONE == state.method.mode)
			{
				d = push(d, 0x2, 3);	// new block, BFINAL = 0, BTYPE = 01 (LSB first)
				
				if (state.noverflow)
					break;
					
				set_checkpoint(d, s);
					
				state.method = *method;
				
				// end-of-block marker
				state.tail = 0x00;
				state.tail_size = 7;
			}
			
			while ((len-- > 0) && !state.noverflow)
			{
				uint_fast8_t	x = *s++;
	
				if (x < 144)
					d = push(d, 0x30 + x, 8);
				else d = push(d, 0x190 - 144 + x, 9);
				
				suggest_checkpoint(d, s);
			}
			
			break;
		}

		case C1:
		{
			// open new block if necessary
			if (NONE == state.method.mode)
			{
				state.method = *method;
				
				assert(NULL != state.method.code_ll);
				assert(NULL != state.method.clen_ll);

				// dump header
				if (NULL != state.method.header)
				{
					uint_fast16_t	nbits = state.method.header_size;
					const uint8_t	*h = state.method.header;
				
					for (; nbits >= 8; nbits -= 8)
						d = push(d, *h++, 8);
					
					if (nbits > 0)
						d = push(d, *h++, nbits);
				}
					
				if (state.noverflow)
				{
					state.method.mode = NONE;
					break;
				}
						
				set_checkpoint(d, s);
				
				// end-of-block marker
				state.tail = state.method.code_ll[256];
				state.tail_size = state.method.clen_ll[256 / 2] & 0x0f;
			}
			
			while ((len-- > 0) && !state.noverflow)
			{
				d = push_symbol(d, *s++, state.method.code_ll, state.method.clen_ll);
				suggest_checkpoint(d, s);
			}
			
			break;
		}			
		
		// compression optimized for slowly changing data stored in differential format.
		// string search considers strings that start with 3 bytes from {0x00, 0x01, 0xff},
		// which is the vast majority with the described kind of data.
		// restricting the search to such strings (i.e. 27 possible start patterns overall)
		// allows us to implement compact hash data structures and make the search very efficient.
		case C2_DIFFERENTIAL:
		{
			const int_fast32_t		HINVALID = 0xfa000000;		// * 3 = 0xee000000; * 9 = 0xca000000; * 27 = 0x5e000000
			int_fast32_t			hash_scan = HINVALID, hash_match = HINVALID;
			const uint8_t			*match_begin = NULL;
			const uint8_t			*match_ref; 
			uint32_t				buffer;
			uint_fast8_t			npending = 0;

			if (NULL == window)
				window = src;
			else
			{
				assert(window <= src);

				// the following comes into play when the assertion below is replaced by a loop
				//if (src - window >= 0x8000)
				//	window = src - 0x8000;
			}
			
			// open new block if necessary
			if (NONE == state.method.mode)
			{
				state.method = *method;
				
				assert(NULL != state.method.code_ll);
				assert(NULL != state.method.clen_ll);
				assert(NULL != state.method.code_dist);
				assert(NULL != state.method.clen_dist);

				// dump header
				if (NULL != state.method.header)
				{
					uint_fast16_t	nbits = state.method.header_size;
					const uint8_t	*h = state.method.header;
				
					for (; nbits >= 8; nbits -= 8)
						d = push(d, *h++, 8);
					
					if (nbits > 0)
						d = push(d, *h++, nbits);
				}				

				if (state.noverflow)
				{
					state.method.mode = NONE;
					break;
				}
					
				set_checkpoint(d, s);
					
				// end-of-block marker
				state.tail = state.method.code_ll[256];
				state.tail_size = state.method.clen_ll[256 / 2] & 0x0f;
				
				// init state
				state.differential.window = s;
				memset(state.differential.hash_anchor, -1u, sizeof(state.differential.hash_anchor));
			}
			
			// reduce window if requested
			// NOTE: we do not utilize enlarged windows
			else if ((const uint8_t*)window > state.differential.window)
			{
				intptr_t diff = (const uint8_t*)window - state.differential.window;
				
				for (uint_fast32_t i = 0; i < NUM_ELEMENTS(state.differential.hash_anchor); i++)
				{
					if (diff > state.differential.hash_anchor[i])
						state.differential.hash_anchor[i] = -1;
					else state.differential.hash_anchor[i] -= diff;
				}

				state.differential.window = window;
			}

			// state here: hash_anchor[i] >= -1

			// ensure that hash_anchor[] is valid after processing
			// TODO: this should be improved by splitting the data block into slices
			// and updating the window after each slice
			assert(s + len - state.differential.window < 0x8000);
			// TODO: while (...) deflate(d, dest_size, s, len_TODO, block_type, window_TODO, window_size, nwritten, nread);

			// process data
			while ((len-- > 0) && !state.noverflow)
			{
				uint8_t			x = *s++;
				const uint8_t	*ph = s - 3;
				uint_fast16_t	distance;

				// update current hash registers.
				// computation ensures that
				// * 3 consecutive bytes from {0x00, 0x01, 0xff} make the hash value non-negative 
				//   (enables fast testing if 3 consecutive elements from the set have been found)
				// * lower bits of hash value determine which of the 27 possible sequences has
				//   been found (enables fast indexing)
				switch (x)
				{
					case 0x00:
					case 0x01:
					case 0xff:
						hash_scan *= 3;
						hash_scan += (x ^ (x >> 7)) & 3;
						hash_match *= 3;
						hash_match += (x ^ (x >> 7)) & 3;
						break;
				
					default:
						hash_scan = HINVALID;
						hash_match = HINVALID;
						break;
				}

				// if scan hash is valid: update hash chains
				if (hash_scan >= 0)
				{
					uint8_t h = hash_scan & 0xff;

					distance = ph - (state.differential.window + state.differential.hash_anchor[h]);
					if (distance > (typeof(state.differential.hash_chain[0]))-1u)
						distance = 0;

					ASSERT_CT(IS_POWER_OF_2(NUM_ELEMENTS(state.differential.hash_chain)), inefficient_hash_chain_length);
					
					state.differential.hash_chain[(uintptr_t)ph % NUM_ELEMENTS(state.differential.hash_chain)] = distance;
					state.differential.hash_anchor[h] = ph - state.differential.window;

					hash_scan = (9 * HINVALID) + h % 9;
				}

				// if a backward reference is open
				if (NULL != match_begin)
				{
					uint_fast16_t	match_len = s - match_begin;
					uint_fast8_t	close = 0;

					// if current byte does not match
					if (x != match_ref[match_len - 1])
					{
						const uint8_t *new_ref = NULL, *r = match_ref;
						
						distance = match_begin - match_ref;

						// look for another segment that matches the full string (incl. current byte)
						while (ph - r < NUM_ELEMENTS(state.differential.hash_chain))
						{
							uint_fast16_t d = state.differential.hash_chain[(uintptr_t)r % NUM_ELEMENTS(state.differential.hash_chain)];
							if (0 == d)
								break;
								
							distance += d;
							r = match_begin - distance;
							if (r < state.differential.window)
								break;
							
							if (!memcmp(match_begin, r, match_len))
							{
								new_ref = r;
								break;
							}
						}

						// if there is one: use it, otherwise finalize reference entry
						if (NULL != new_ref)
							match_ref = new_ref;
						else
						{
							match_len -= 1;
							close = 1;
						}
					}

					// also finalize if max. match len or end of input data reached
					// NOTE: we do not keep open references across multiple deflate() calls
					if ((258 == match_len) || (0 == len))
						close = 1;
					
					if (!close)
						continue;

					// finalize reference entry
					// see RFC 1951 section 3.2.5 for details
						
					distance = match_begin - match_ref;
					
					GPI_TRACE_MSG(TRACE_VERBOSE, "backward ref. at %u: len = %u, distance = %u", 
						match_begin - (const uint8_t*)src, match_len, distance);

					switch (match_len)
					{
						case 3 ... 10:
						{
							uint_fast16_t c = 254 + match_len;
							d = push_symbol(d, c, state.method.code_ll, state.method.clen_ll);
							break;
						}
						
						case 11 ... 257:
						{
							uint_fast16_t len = match_len - 3;
							int_fast8_t	n = gpi_get_msb(len) - 2;
							uint_fast16_t c = 257 + 4 * n + (len >> n);
							d = push_symbol(d, c, state.method.code_ll, state.method.clen_ll);
							c = len & ~(-1u << n);
							c = gpi_bitswap_16(c) >> (16 - n);		// LSB first (here)
							d = push(d, c, n);
							break;
						}
							
						case 258:
						{
							uint_fast16_t c = 285;
							d = push_symbol(d, c, state.method.code_ll, state.method.clen_ll);
							break;
						}
						
						default:
							assert(0);
					}
					
					switch (distance)
					{
						case 1 ... 4:
						{
							uint_fast16_t c = distance - 1;
							d = push_symbol(d, c, state.method.code_dist, state.method.clen_dist);
							break;
						}
						
						case 5 ... 32768:
						{
							distance -= 1;
							int_fast8_t	n = gpi_get_msb(distance) - 1;
							uint_fast16_t c = 2 * n + (distance >> n);
							d = push_symbol(d, c, state.method.code_dist, state.method.clen_dist);
							c = distance & ~(-1u << n);
							c = gpi_bitswap_16(c) >> (16 - n);		// LSB first (here)
							d = push(d, c, n);
							break;
						}
						
						default:
							assert(0);
					}

					npending = 0;

					// if full match (incl. current input byte)
					if (match_begin + match_len == s)
					{
						suggest_checkpoint(d, s);
						hash_match = HINVALID;
						match_begin = NULL;
						continue;
					}

					suggest_checkpoint(d, s - 1);
					
					// else warm-start hash
					if (HINVALID != hash_scan)
						hash_match = (3 * HINVALID) + (uint8_t)hash_scan % 3;
						
					match_begin = NULL;
				}

				// NOTE: At this place we know that there is no open backward reference.
				
				// store current byte in intermediate buffer
				// (do not dump it before we know if it gets replaced by a backward reference)
				buffer <<= 8;
				buffer |= x;

				// a hash coincides with 3 bytes, so dump all but the last 3 bytes
				if (3 == npending)
				{
					d = push_symbol(d, buffer >> 24, state.method.code_ll, state.method.clen_ll);
					suggest_checkpoint(d, s - 3);
				}
				else npending += 1;

				// if hash is invalid: move on
				if (hash_match < 0)
					continue;

				// otherwise look-up the most recent segment starting with the associated content
				// ATTENTION: do not link to the input data itself (could happen as hash_chains
				// have been updated already, see above)
				uint8_t h = hash_match & 0xff;
				match_ref = state.differential.window + state.differential.hash_anchor[h];
				if (match_ref == ph)
				{
					// distance is valid from above
					// distance = state.differential.hash_chain[(uintptr_t)ph % NUM_ELEMENTS(state.differential.hash_chain)];
					
					if (0 == distance)
						match_ref = state.differential.window - 1;
					else match_ref -= distance;
				}

				// if found segment is inside the history window: open a reference,
				// else warm-start hash
				if (match_ref < state.differential.window)
					hash_match = (9 * HINVALID) + h % 9;
				else match_begin = ph;
			}

			// flush intermediate buffer
			buffer <<= 32 - (8 * npending);
			while (npending-- > 0)
			{
				d = push_symbol(d, buffer >> 24, state.method.code_ll, state.method.clen_ll);
				buffer <<= 8;
			}
			suggest_checkpoint(d, s);
			
			break;
		}
		
		default:
			assert(0);
	}

	// if output buffer would overflow: go back to last checkpoint and stop there
	if (state.noverflow)
	{
		s				= state.checkpoint.src;
		d				= state.checkpoint.dest;
		state.npending	= state.checkpoint.npending;
		state.buffer	= state.checkpoint.buffer;
	}

	if (NULL != nwritten)
		*nwritten = d - (uint8_t*)dest;
		
	if (NULL != nread)
		*nread = s - (const uint8_t*)src;
	
	GPI_TRACE_RETURN((state.noverflow + 7) / 8);
}	
		
//**************************************************************************************************
//**************************************************************************************************
