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
 *	@file					cbor.h
 *
 *	@brief					CBOR data types and lightweight encoding functions
 *
 *	@version				$Id$
 *	@date					TODO
 *
 *	@author					Carsten Herrmann
 *
 ***************************************************************************************************

 	@details

	For details of CBOR see <https://en.wikipedia.org/wiki/CBOR>.

 **************************************************************************************************/

#ifndef __CBOR_H__
#define __CBOR_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include "traffic_bench.h"
#include <stdint.h>

//**************************************************************************************************
//***** Global (Public) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************


//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// CBOR datatypes

typedef struct __attribute__((packed)) cbor_uint_tiny_t
{
    uint8_t hdr;
} cbor_uint_tiny_t;
typedef struct __attribute__((packed)) cbor_uint8_t
{
    uint8_t hdr;
    uint8_t val;
} cbor_uint8_t;
typedef struct __attribute__((packed)) cbor_uint16_t
{
    uint8_t  hdr;
    uint16_t val;
} cbor_uint16_t;
typedef struct __attribute__((packed)) cbor_uint32_t
{
    uint8_t  hdr;
    uint32_t val;
} cbor_uint32_t;

typedef cbor_uint_tiny_t cbor_int_tiny_t;
typedef cbor_uint8_t     cbor_int8_t;
typedef cbor_uint16_t    cbor_int16_t;
typedef cbor_uint32_t    cbor_int32_t;

typedef cbor_uint_tiny_t cbor_break;
typedef cbor_uint_tiny_t cbor_bstr_envelope_t;

typedef struct __attribute__((packed)) cbor_bstr_tiny_t
{
    uint8_t hdr;
    uint8_t data[0];
} cbor_bstr_tiny_t;
typedef struct __attribute__((packed)) cbor_bstr8_t
{
    uint8_t hdr;
    uint8_t len;
    uint8_t data[0];
} cbor_bstr8_t;
typedef struct __attribute__((packed)) cbor_bstr16_t
{
    uint8_t  hdr;
    uint16_t len;
    uint8_t  data[0];
} cbor_bstr16_t;
typedef struct __attribute__((packed)) cbor_bstr32_t
{
    uint8_t  hdr;
    uint32_t len;
    uint8_t  data[0];
} cbor_bstr32_t;

typedef cbor_bstr_tiny_t cbor_array_tiny_t;
typedef cbor_bstr8_t     cbor_array8_t;
typedef cbor_bstr16_t    cbor_array16_t;
typedef cbor_bstr32_t    cbor_array32_t;

//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// TODO: replace item by pointer and afterwards macros by inline functions

#define cbor_encode_break(item)         cbor_encode_marker_(&(item), 0xff)
#define cbor_encode_bstr_envelope(item) cbor_encode_marker_(&(item), 0x40 | 0x1f)

#define cbor_encode_uint(item, value)   cbor_encode_uint_(&(item), sizeof(item), (value))
#define cbor_encode_uint_tiny(item, value)                                                         \
  cbor_encode_uint_(&(item), sizeof(cbor_uint_tiny_t), (value))
#define cbor_encode_uint8(item, value)         cbor_encode_uint_(&(item), sizeof(cbor_uint8_t), (value))
#define cbor_encode_uint16(item, value)        cbor_encode_uint_(&(item), sizeof(cbor_uint16_t), (value))
#define cbor_encode_uint32(item, value)        cbor_encode_uint_(&(item), sizeof(cbor_uint32_t), (value))
#define cbor_encode_uint_by_value(item, value) cbor_encode_uint_by_value_(&(item), (value))

#define cbor_encode_int(item, value)           cbor_encode_int_(&(item), sizeof(item), (value))
#define cbor_encode_int_tiny(item, value)                                                          \
  cbor_encode_int_(&(item), sizeof(cbor_int_tiny_t), (value))
#define cbor_encode_int8(item, value)    cbor_encode_int_(&(item), sizeof(cbor_int8_t), (value))
#define cbor_encode_int16(item, value)   cbor_encode_int_(&(item), sizeof(cbor_int16_t), (value))
#define cbor_encode_int32(item, value)   cbor_encode_int_(&(item), sizeof(cbor_int32_t), (value))

#define cbor_encode_bstr(item, src, len) cbor_encode_bstr_(&(item), sizeof(item), (src), (len))
#define cbor_encode_bstr_tiny(item, src, len)                                                      \
  cbor_encode_bstr_(&(item), sizeof(cbor_bstr_tiny_t), (src), (len))
#define cbor_encode_bstr8(item, src, len)                                                          \
  cbor_encode_bstr_(&(item), sizeof(cbor_bstr8_t), (src), (len))
#define cbor_encode_bstr16(item, src, len)                                                         \
  cbor_encode_bstr_(&(item), sizeof(cbor_bstr16_t), (src), (len))
#define cbor_encode_bstr32(item, src, len)                                                         \
  cbor_encode_bstr_(&(item), sizeof(cbor_bstr32_t), (src), (len))

#define cbor_encode_array(item, len) cbor_encode_array_(&(item), sizeof(item), (len))
#define cbor_encode_array_tiny(item, len)                                                          \
  cbor_encode_array_(&(item), sizeof(cbor_array_tiny_t), (len))
#define cbor_encode_array8(item, len)  cbor_encode_array_(&(item), sizeof(cbor_array8_t), (len))
#define cbor_encode_array16(item, len) cbor_encode_array_(&(item), sizeof(cbor_array16_t), (len))
#define cbor_encode_array32(item, len) cbor_encode_array_(&(item), sizeof(cbor_array32_t), (len))

#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Implementations of Inline Functions ********************************************************

// TODO: move this function to GPI
static inline uint32_t hton(uint32_t x, uint_fast8_t size)
{
    switch (size)
    {
        case 1: break;
        case 2: asm("rev16 %0, %1" : "=r"(x) : "r"(x)); break;
        case 4: asm("rev   %0, %1" : "=r"(x) : "r"(x)); break;
        default: assert(0);
    }

    return x;
}

//**************************************************************************************************

static inline void *cbor_encode_marker_(void *dest, uint_fast8_t hdr)
{
    cbor_uint_tiny_t *x = (cbor_uint_tiny_t *) dest;
    x->hdr              = hdr;
    return ++x;
}

//**************************************************************************************************

static inline void *cbor_encode_uint_(void *dest, size_t size, uint_fast32_t value)
{
    //ASSERT_CT(IS_CONST_EXPRESSION(size));

    switch (size - 1)
    {
        case 0:
            assert(value < 24);
            ((cbor_uint_tiny_t *) dest)->hdr = value;
            break;

        case 1:
            ((cbor_uint8_t *) dest)->hdr = 24;
            ((cbor_uint8_t *) dest)->val = value;
            break;

        case 2:
            ((cbor_uint16_t *) dest)->hdr = 25;
            ((cbor_uint16_t *) dest)->val = hton(value, size - 1);
            break;

        case 4:
            ((cbor_uint32_t *) dest)->hdr = 26;
            ((cbor_uint32_t *) dest)->val = hton(value, size - 1);
            break;

        default: assert(0);
    }

    return dest + size;
}

#if 0
  #define cbor_encode_uint(field, value)                                                           \
    do {                                                                                           \
      typeof(field) *p = &(field);                                                                 \
      p->hdr           = 24 + MSB(sizeof(p->val));                                                 \
      p->val           = hton((value), sizeof(p->val));                                            \
    }                                                                                              \
    while (0)
		//(field).hdr = 24 + MSB(sizeof((field).val));
		//(field).val = hton((value), sizeof((field).val));
#endif

//**************************************************************************************************

static inline void *cbor_encode_uint_by_value_(void *dest, uint_fast32_t value)
{
    switch (value)
    {
        case 0 ... 23: return cbor_encode_uint_(dest, sizeof(cbor_uint_tiny_t), value);
        case 24 ... 0xff: return cbor_encode_uint_(dest, sizeof(cbor_uint8_t), value);
        case 0x100 ... 0xffff: return cbor_encode_uint_(dest, sizeof(cbor_uint16_t), value);
        default: return cbor_encode_uint_(dest, sizeof(cbor_uint32_t), value);
    }
}

//**************************************************************************************************

static inline void *cbor_encode_int_(void *dest, size_t size, int_fast32_t value)
{
    uint_fast8_t hdr = 0x00;

    if (value < 0)
    {
        hdr   = 0x20;
        value = ~value;
    }

    cbor_encode_uint_(dest, size, value);

    ((cbor_uint_tiny_t *) dest)->hdr |= hdr;

    return dest + size;
}

#if 0
  #define cbor_encode_int(field, value)                                                            \
    do {                                                                                           \
      typeof(field) *p = &(field);                                                                 \
      typeof(value)  x = (value);                                                                  \
      if (x < 0)                                                                                   \
      {                                                                                            \
        p->hdr = 0x20 + 24 + MSB(sizeof(p->val));                                                  \
        p->val = hton(-x, sizeof(p->val));                                                         \
      }                                                                                            \
      else cbor_encode_uint(*p, x);                                                                \
    }                                                                                              \
    while (0)
		//if (x < 0) {
		//	(field).hdr = 0x20 + 24 + MSB(sizeof((field).val));
		//	(field).val = hton(-x, sizeof((field).val));
		//} else cbor_encode_uint(field, x);
#endif

//**************************************************************************************************

static inline void *cbor_encode_bstr_(void *dest, size_t size, const void *src, size_t len)
{
    if (0 == len + 1)
    {
        cbor_bstr_tiny_t *x = dest;
        x->hdr              = 0x40 | 31;
        return &(x->data[0]);
    }

    //ASSERT_CT(IS_CONST_EXPRESSION(size));

    switch (size - 1)
    {
        case 0:
        {
            assert(len < 24);
            cbor_bstr_tiny_t *x = dest;
            x->hdr              = 0x40 | len;
            break;
        }

        case 1:
        {
            assert(len < 0x100);
            cbor_bstr8_t *x = dest;
            x->hdr          = 0x40 | 24;
            x->len          = len;
            break;
        }

        case 2:
        {
            assert(len < 0x10000);
            cbor_bstr16_t *x = dest;
            x->hdr           = 0x40 | 25;
            x->len           = hton(len, sizeof(x->len));
            break;
        }

        case 4:
        {
            assert(len < 0x100000000);
            cbor_bstr32_t *x = dest;
            x->hdr           = 0x40 | 26;
            x->len           = hton(len, sizeof(x->len));
            break;
        }

        default: assert(0);
    }

    uint8_t *data = (uint8_t *) dest + size;

    if (NULL != src) memcpy(data, src, len);
    else len = 0;

    return &data[len];
}

#if 0
static void* cbor_encode_bstr_auto(void *dest, const void *src, size_t len)
{
	assert(len < 0x100000000);

	size_t size;
	if (len < 24)			size = sizeof(cbor_bstr_tiny_t);
	else if (len < 0x100)	size = sizeof(cbor_bstr8_t);
	else if (len < 0x10000)	size = sizeof(cbor_bstr16_t);
	else					size = sizeof(cbor_bstr32_t);

	return cbor_encode_bstr_(dest, size, src, len);
}
#endif

//**************************************************************************************************

static inline void *cbor_encode_array_(void *dest, size_t size, size_t len)
{
    if (0 == len + 1)
    {
        cbor_array_tiny_t *x = dest;
        x->hdr               = 0x80 | 31;
        return &(x->data[0]);
    }

    //ASSERT_CT(IS_CONST_EXPRESSION(size));

    switch (size - 1)
    {
        case 0:
        {
            assert(len < 24);
            cbor_array_tiny_t *x = dest;
            x->hdr               = 0x80 | len;
            break;
        }

        case 1:
        {
            assert(len < 0x100);
            cbor_array8_t *x = dest;
            x->hdr           = 0x80 | 24;
            x->len           = len;
            break;
        }

        case 2:
        {
            assert(len < 0x10000);
            cbor_array16_t *x = dest;
            x->hdr            = 0x80 | 25;
            x->len            = hton(len, sizeof(x->len));
            break;
        }

        case 4:
        {
            assert(len < 0x100000000);
            cbor_array32_t *x = dest;
            x->hdr            = 0x80 | 26;
            x->len            = hton(len, sizeof(x->len));
            break;
        }

        default: assert(0);
    }

    return (uint8_t *) dest + size;
}

#if 0
static void* cbor_encode_array_auto(void *dest, const void *src, size_t len)
{
	assert(len < 0x100000000);

	size_t size;
	if (len < 24)			size = sizeof(cbor_array_tiny_t);
	else if (len < 0x100)	size = sizeof(cbor_array8_t);
	else if (len < 0x10000)	size = sizeof(cbor_array16_t);
	else					size = sizeof(cbor_array32_t);

	return cbor_encode_array_(dest, size, src, len);
}
#endif

//**************************************************************************************************
//**************************************************************************************************

#endif // __CBOR_H__
