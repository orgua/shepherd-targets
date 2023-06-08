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
 *	@file					scheduler.c
 *
 *	@brief					communication scheduler (schedule instruction interpreter)
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
#define TRACE_INFO     GPI_TRACE_MSG_TYPE_INFO
#define TRACE_WARNING  GPI_TRACE_MSG_TYPE_WARNING
#define TRACE_ERROR    GPI_TRACE_MSG_TYPE_ERROR
#define TRACE_VERBOSE  (GPI_TRACE_MSG_TYPE_VERBOSE | 1)
#define TRACE_SCHEDULE (GPI_TRACE_MSG_TYPE_INFO | 2)

// select active message groups, i.e., the messages to be printed (others will be dropped)
#ifndef GPI_TRACE_BASE_SELECTION
  #define GPI_TRACE_BASE_SELECTION (GPI_TRACE_LOG_STANDARD | GPI_TRACE_LOG_PROGRAM_FLOW)
#endif
#ifndef GPI_TRACE_USER_SELECTION
  #define GPI_TRACE_USER_SELECTION GPI_TRACE_LOG_USER
#endif
GPI_TRACE_CONFIG(scheduler, GPI_TRACE_BASE_SELECTION | GPI_TRACE_USER_SELECTION |
                                    (TRACE_SCHEDULE & ~GPI_TRACE_MSG_TYPE_INFO));

//**************************************************************************************************
//**** Includes ************************************************************************************

#include "traffic_bench.h"

#include "gpi/clocks.h"
#include "gpi/interrupts.h"
#include "gpi/olf.h"
#include "gpi/platform.h"
#include "gpi/protothreads.h"
#include "gpi/tools.h"

#include <assert.h>
#include <inttypes.h>
//#include <stdlib.h>

//**************************************************************************************************
//***** Local Defines and Consts *******************************************************************

#if GPI_ARCH_IS_BOARD(FLOCKLAB_nRF5)
  #define LED_SYNC GPI_LED_3
#elif GPI_ARCH_IS_BOARD(nRF_PCA10056)
  #define LED_SYNC GPI_LED_1
#endif

#define SYNC_TIMEOUT GPI_TICK_S_TO_FAST(60)

//**************************************************************************************************

#ifdef NDEBUG
  #define RUNTIME_CHECKS 1
#else
  #define RUNTIME_CHECKS 0
#endif

#if RUNTIME_CHECKS
  #define ASSERT_ELSE(cond) if (!(cond))
#else
  #define ASSERT_ELSE(cond)                                                                        \
    if (1) assert(cond);                                                                           \
    else
#endif

//**************************************************************************************************
//***** Local Typedefs and Class Declarations ******************************************************

// current TRX group (runtime data)
typedef struct TRX_Group
{
    const Schedule_Entry *anchor;               // first instruction of group
    uint8_t               first_transmitter_id; // if first == last: single transmitter
    uint8_t               last_transmitter_id;
    uint8_t               checkpoint_offset; // common for all transmitters (else 0xff)
    uint32_t              max_air_time[3];   // [0] = cp1 + packet, [1] = cp1, [2] = cp2

    struct
    {
        int8_t  instruction_index; // index of assigned TRX instruction (-> anchor[...])
        uint8_t transmitter_index; // index inside Params_TRX::transmitter_ids

    } tx[256];

} TRX_Group;

//**************************************************************************************************
//***** Forward Declarations ***********************************************************************


//**************************************************************************************************
//***** Local (Static) Variables *******************************************************************

static uint8_t  num_hops_from_root;
static uint8_t  clock_master_id;
static uint32_t clock_master_received_at;

// current clock synchronization reference point (for global <-> local conversion)
static struct
{
    uint32_t global;
    uint32_t local;
    uint32_t mul_local_to_global;
    uint32_t mul_global_to_local;

} tick_ref;

// schedule execution state (virtual machine state)
static struct
{
    uint16_t pc;
    uint32_t pc_tick;
    uint32_t rng_state;

} program_state;

static enum {
    SYNC_NONE,
    SYNC_COMM,
    SYNC_FULL

} sync_state;

static const typeof(num_hops_from_root)    NUM_HOPS_INVALID = -1;
static const typeof(program_state.pc_tick) GTS_INVALID =
        UINT32_C(-1) + ASSERT_CT_EVAL(4 == sizeof(program_state.pc_tick));

// internal protothreads
static struct pt        pt_context_internal[1];
static struct pt *const pt_trx = &pt_context_internal[0];

//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Local Functions ****************************************************************************

// random number generator (XorShift)
static uint32_t         rand32()
{
    register uint32_t rand_state = program_state.rng_state;

    rand_state ^= rand_state << 2;
    rand_state ^= rand_state >> 15;
    rand_state ^= rand_state << 17;

    program_state.rng_state = rand_state;

    return rand_state;
}

//**************************************************************************************************
// clock sync. and conversion functions

static int tick_reference_update(uint32_t global, uint32_t local)
{
    GPI_TRACE_FUNCTION();

    uint64_t mul;

    // update only if some time went by (to avoid large accuracy issues)
    if (local - tick_ref.local < GPI_TICK_MS_TO_FAST(1000)) GPI_TRACE_RETURN(0);

    mul = ((uint64_t) (global - tick_ref.global) << 32) / (local - tick_ref.local);
    assert(mul >= 0x80000000u && mul <= 0x17FFFFFFFu);
    tick_ref.mul_local_to_global = mul;

    mul = ((uint64_t) (local - tick_ref.local) << 32) / (global - tick_ref.global);
    assert(mul >= 0x80000000u && mul <= 0x17FFFFFFFu);
    tick_ref.mul_global_to_local = mul;

    tick_ref.global              = global;
    tick_ref.local               = local;

    GPI_TRACE_MSG(
            TRACE_INFO,
            "tick reference update: global = 0x%08x, local = 0x%08x, g2l = %u:%08x, l2g = %u:%08x",
            tick_ref.global, tick_ref.local, (tick_ref.mul_global_to_local < 0x80000000) ? 1 : 0,
            tick_ref.mul_global_to_local, (tick_ref.mul_local_to_global < 0x80000000) ? 1 : 0,
            tick_ref.mul_local_to_global);

    GPI_TRACE_RETURN(1);
}

//**************************************************************************************************

static inline void tick_reference_init(uint32_t global, uint32_t local)
{
    tick_ref.global = global - GPI_TICK_MS_TO_FAST(1000);
    tick_ref.local  = local - GPI_TICK_MS_TO_FAST(1000);

    tick_reference_update(global, local);
}

//**************************************************************************************************

static inline uint32_t period_global_to_local(uint32_t delay)
{
    uint32_t mul    = tick_ref.mul_global_to_local;

    uint64_t tick64 = (gpi_mulu_32x32to64(delay, mul) + 0x80000000u);
    uint32_t tick   = tick64 >> 32;

    if (mul < 0x80000000u) tick += delay;

    return tick;
}

//**************************************************************************************************

static inline uint32_t period_local_to_global(uint32_t delay)
{
    uint32_t mul    = tick_ref.mul_local_to_global;

    uint64_t tick64 = (gpi_mulu_32x32to64(delay, mul) + 0x80000000u);
    uint32_t tick   = tick64 >> 32;

    if (mul < 0x80000000u) tick += delay;

    return tick;
}

//**************************************************************************************************

static inline uint32_t tick_global_to_local(uint32_t global)
{
    return tick_ref.local + period_global_to_local(global - tick_ref.global);
}
/*
static uint32_t tick_global_to_local(uint32_t global)
{
	GPI_TRACE_FUNCTION();

	uint32_t delta = global - tick_ref.global;
	uint32_t mul = tick_ref.mul_global_to_local;

	uint64_t tick64 = (gpi_mulu_32x32to64(delta, mul) + 0x80000000u);
	uint32_t tick = tick64 >> 32;

	if (mul < 0x80000000u)
		tick += delta;

	tick += tick_ref.local;

	//// TODO: maybe move to tick_local_to_global(), whichever is used less often
	//delta = tick_local_to_global(tick) - global;
	//while ((int32_t)delta > 1)
	//{
	//	tick -= 1;
	//	delta = tick_local_to_global(tick) - global;
	//}
	//while ((int32_t)delta < -1)
	//{
	//	tick += 1;
	//	delta = tick_local_to_global(tick) - global;
	//}

	GPI_TRACE_RETURN(tick);
}
*/
//**************************************************************************************************

static uint32_t tick_local_to_global(uint32_t local)
{
    uint32_t tick = tick_ref.global + period_local_to_global(local - tick_ref.local);

    uint32_t delta;

    /*	uint32_t delta = local - tick_ref.local;
	uint32_t mul = tick_ref.mul_local_to_global;

	uint64_t tick64 = (gpi_mulu_32x32to64(delta, mul) + 0x80000000u);
	uint32_t tick = tick64 >> 32;

	if (mul < 0x80000000u)
		tick += delta;

	tick += tick_ref.global;
*/
    // TODO: maybe move to tick_global_to_local(), whichever is used less often
    delta = tick_global_to_local(tick) - local;
    while ((int32_t) delta > 1)
    {
        tick -= 1;
        delta = tick_global_to_local(tick) - local;
    }
    while ((int32_t) delta < -1)
    {
        tick += 1;
        delta = tick_global_to_local(tick) - local;
    }

    return tick;
}

//**************************************************************************************************

// convert time period (e.g. delay specification) from schedule format to fast clock rate
static inline uint32_t period_schedule_to_fast(uint32_t x)
{
    ASSERT_CT(!(GPI_FAST_CLOCK_RATE % 1000000));

    return x * (GPI_FAST_CLOCK_RATE / 1000000);
}

//**************************************************************************************************
//**************************************************************************************************

// get params pointer resulting from Schedule_Entry
// NOTE: using a function enables easy switching to PC-relative addressing (in case)
// returning void* enables assignment to specialized type without a cast
static inline const void *get_params_ptr(Schedule_Entry x)
//static inline const Instruction_Params* get_params_ptr(Schedule_Entry x)
{
    return (void *) ((uint8_t *) &schedule + x.params_ptr);
    //return (Instruction_Params*)((uint8_t*)&schedule + x.params_ptr);
}

//**************************************************************************************************

static inline uint_fast16_t get_checkpoint_marker_pos(const Radio_Packet *packet)
{
    int_fast16_t pos = schedule_options.TRX_checkpoint_marker_pos;

    if (pos < 0) pos += packet->raw_payload_length;

    return pos;
}

//**************************************************************************************************

static const Checkpoint_Data *get_checkpoint_ptr(const Radio_Packet *packet)
{
    uint_fast16_t pos;

    // cp marker pos
    pos = get_checkpoint_marker_pos(packet);
    if (pos >= packet->raw_payload_length) return NULL;

    // cp pos
    pos = packet->raw_payload[pos];
    if (pos + sizeof(Checkpoint_Data) > packet->raw_payload_length) return NULL;

    return (const Checkpoint_Data *) &(packet->raw_payload[pos]);
}

//**************************************************************************************************

// assemble packet content based on TRX specification
static void assemble_tx_packet(Radio_Packet *packet, const Params_TRX *params,
                               uint_fast8_t transmitter_index)
{
    GPI_TRACE_FUNCTION();

    const typeof(params->payload_descriptors[0]) *desc = 0;
    desc = (typeof(desc)) ((uint8_t *) params->payload_descriptors + params->num_transmitters);

    const uint8_t    DESC_HEADER_SIZE  = offsetof(typeof(*desc), fixed);
    //uint_fast16_t		desc_remaining = params->payload_descriptor_list_size;

    uint8_t         *payload           = &(packet->raw_payload[0]);
    const uint8_t   *payload_end       = &(packet->raw_payload[NUM_ELEMENTS(packet->raw_payload)]);
    uint_fast8_t     payload_remaining = payload_end - payload;

    const uint32_t   rng_state         = program_state.rng_state;
    const uint16_t   rng_offset        = transmitter_index * params->rng_offset;
    Checkpoint_Data *checkpoint        = NULL;

    {
        int_fast16_t i = (transmitter_index < params->num_transmitters)
                                 ? params->transmitter_ids[transmitter_index]
                                 : -1;

        GPI_TRACE_MSG(TRACE_VERBOSE, "assemble Tx packet for node %" PRIdFAST16, i);

        if (i < 0)
            GPI_TRACE_MSG(TRACE_ERROR, "invalid transmitter index: %" PRIuFAST8 " >= %" PRIu8,
                          transmitter_index, params->num_transmitters);
    }

    packet->is_tx_no_packet = 0;

    // process descriptor list
    while (1)
    //while (desc_remaining >= DESC_HEADER_SIZE)
    {
        ASSERT_ELSE(desc->size >= DESC_HEADER_SIZE /*&& desc->size <= desc_remaining*/)
        {
            GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: inconsistent size specs.",
                          program_state.pc, (uintptr_t) & (desc->size) - (uintptr_t) schedule);
            break;
        }

        switch (desc->type)
        {
            // end of list
            case TRX_DATA_END:
                goto break_loop;
                //break

            // transmit no packet, only carrier signal
            case TRX_DATA_NO_PACKET: packet->is_tx_no_packet = 1; break;

            // checkpoint
            case TRX_DATA_CHECKPOINT:
            {
                const uint_fast8_t n = sizeof(Checkpoint_Data);

                ASSERT_ELSE(n <= payload_remaining)
                {
                    GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: size exceeds payload length",
                                  program_state.pc,
                                  (uintptr_t) & (desc->size) - (uintptr_t) schedule);
                    goto break_loop;
                }

                checkpoint                     = (Checkpoint_Data *) payload;

                checkpoint->transmitter_id     = params->transmitter_ids[transmitter_index];
                checkpoint->transmitter_hop    = num_hops_from_root;
                checkpoint->schedule_pc        = program_state.pc;
                checkpoint->schedule_clock     = program_state.pc_tick;
                checkpoint->schedule_rng_state = rng_state;
                // ATTENTION: rng's state before it has been used for random payload parts

                payload += n;

                break;
            }

            // fixed data
            case TRX_DATA_FIXED:
            {
                uint_fast8_t n = desc->size - DESC_HEADER_SIZE;

                ASSERT_ELSE(n <= payload_remaining)
                {
                    GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: size exceeds payload length",
                                  program_state.pc,
                                  (uintptr_t) & (desc->size) - (uintptr_t) schedule);
                    goto break_loop;
                }

                memcpy(payload, desc->fixed.data, n);
                payload += n;

                break;
            }

            // random data
            case TRX_DATA_RANDOM:
            {
                uint32_t     r;
                uint_fast8_t n = desc->random.num_bytes;

                ASSERT_ELSE(n <= payload_remaining)
                {
                    GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: size exceeds payload length",
                                  program_state.pc,
                                  (uintptr_t) & (desc->random.num_bytes) - (uintptr_t) schedule);
                    goto break_loop;
                }

                for (uint_fast8_t m = 0; n > 0; n--)
                {
                    if (!m) r = rand32();
                    m          = (m - 1) % sizeof(r);

                    *payload++ = r + rng_offset; // TODO: find better usage of rng_offset
                    r >>= 8;
                }

                break;
            }

            // unknown / invalid descriptor type
            default:
                ASSERT_ELSE(0)
                {
                    GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: unknown payload type: %u",
                                  program_state.pc,
                                  (uintptr_t) & (desc->type) - (uintptr_t) schedule, desc->type);
                }
                goto break_loop;
                //break;
        }

        payload_remaining = payload_end - payload;

        //desc_remaining -= desc->size;
        desc              = (typeof(desc)) ((uint8_t *) desc + desc->size);
    }
break_loop:

    packet->raw_payload_length = payload - &(packet->raw_payload[0]);
    //memset(payload, 0, payload_remaining);

    // if no packet to transmit (only carrier signal)
    if (packet->is_tx_no_packet)
    {
        // check if feature is used right
        ASSERT_ELSE(0 == packet->raw_payload_length)
        {
            GPI_TRACE_MSG(TRACE_ERROR, "schedule at %04X:%04X: no_packet contains payload",
                          program_state.pc, (uintptr_t) desc - (uintptr_t) schedule);

            packet->raw_payload_length = 0;
        }
    }

    // else write checkpoint marker
    else
    {
        uint_fast16_t cpm_pos = get_checkpoint_marker_pos(packet);

        // if marker pos is out of range
        if (cpm_pos >= packet->raw_payload_length)
        {
            ASSERT_ELSE(0)
            {
                GPI_TRACE_MSG(TRACE_ERROR,
                              "schedule at %04X:%04X: checkpoint marker pos exceeds payload length "
                              "(%u >= %u)",
                              program_state.pc,
                              (uintptr_t) & (desc->random.num_bytes) - (uintptr_t) schedule,
                              cpm_pos, packet->raw_payload_length);
            }

            // nothing to do, will be detected on rx too
        }
        else
        {
            uint_fast8_t cp_pos = -1;

            if (NULL != checkpoint)
            {
                cp_pos = (uint8_t *) checkpoint - &(packet->raw_payload[0]);

                ASSERT_ELSE((cpm_pos < cp_pos) || (cpm_pos >= cp_pos + sizeof(*checkpoint)))
                {
                    GPI_TRACE_MSG(TRACE_ERROR,
                                  "schedule at %04X:%04X: checkpoint marker overwrites checkpoint "
                                  "(%u vs. %u + %u)",
                                  program_state.pc,
                                  (uintptr_t) & (desc->random.num_bytes) - (uintptr_t) schedule,
                                  cpm_pos, cp_pos, sizeof(*checkpoint));

                    // treat damaged checkpoint as no checkpoint
                    cp_pos = -1;
                }
            }

            packet->raw_payload[cpm_pos] = cp_pos;
        }
    }

    GPI_TRACE_RETURN();
}

//**************************************************************************************************

// transmit packet
static PT_THREAD(transmit(const Params_TRX *params, uint_fast8_t transmitter_index,
                          uint_fast8_t dry_run, uint32_t *execution_time))
{
    struct pt *const       pt = pt_trx;

    static Rx_Queue_Entry *q;
    static uint32_t        start_tick_local;
    static Radio_Packet   *p;
    uint32_t               tx_delay;
    uint32_t               tx_cp[2];
    uint32_t               timeout;

    PT_BEGIN(pt);

    timeout  = period_schedule_to_fast(params->timeout);
    tx_delay = period_schedule_to_fast(params->tx_delay);
    tx_cp[0] = period_schedule_to_fast(params->tx_carrier_period_1);
    tx_cp[1] = period_schedule_to_fast(params->tx_carrier_period_2);
    start_tick_local =
            tick_global_to_local(program_state.pc_tick + schedule_options.TRX_pre_delay + tx_delay);

    // virtual execution time of the TRX instruction
    *execution_time = schedule_options.TRX_pre_delay + timeout + schedule_options.TRX_post_delay;

    // rx_queue is also used for Tx packets (simplifies logging)
    q               = &rx_queue[rx_queue_num_written_radio % NUM_ELEMENTS(rx_queue)];
    p               = &(q->packet);

    rx_queue_num_writing = rx_queue_num_written_radio + 1;

    p->trx_status        = 0;
    p->is_tx             = 1;

    // ATTENTION: assemble_tx_packet() is necessary also at dry run
    // to update the RNG state (which is part of the program state)
    assemble_tx_packet(p, params, transmitter_index);

    // go out of sync if parent node (clock master) disappeared (i.e. has not been received for a long time)
    // NOTE: we test this here to catch this situation for sure,
    // even if a node enters an infinite Tx loop in the schedule
    if ((0 != num_hops_from_root) && (NUM_HOPS_INVALID != num_hops_from_root) &&
        (start_tick_local - clock_master_received_at > SYNC_TIMEOUT))
    {
        GPI_TRACE_MSG(TRACE_INFO, "clock master lost");
        num_hops_from_root = NUM_HOPS_INVALID;
    }

    // do not transmit anything if node is out of sync
    if (NUM_HOPS_INVALID == num_hops_from_root)
    {
        GPI_TRACE_MSG(TRACE_INFO, "out of sync -> Tx = dry run");
        dry_run = 1;
    }

    // skip transmission if timeout constraint would not be reached
    else
    {
        Gpi_Fast_Tick_Native air_time =
                (p->is_tx_no_packet)
                        ? 0
                        : radio_get_packet_airtime(gpi_radio_get_mode(), p->raw_payload_length);

        if ((tx_cp[0] + air_time + tx_cp[1]) >= (timeout - tx_delay))
        {
            GPI_TRACE_MSG(TRACE_ERROR,
                          "schedule at %04X:%04X: TRX timeout %u too short for tx_delay %u, "
                          "carrier periods %u + %u, and %u bytes payload -> dry run",
                          program_state.pc, (uintptr_t) params - (uintptr_t) schedule,
                          params->timeout, params->tx_delay, params->tx_carrier_period_1,
                          params->tx_carrier_period_2, p->raw_payload_length);

            dry_run = 1;
        }
    }

    // dry run means: do not perform the real operation (here: radio activities),
    // but do everything needed to update the program state
    if (dry_run) PT_EXIT(pt);

    GPI_TRACE_MSG(
            TRACE_INFO, "start Tx [%u] at %uus/0x%08x (global 0x%08x / %u + %u us), timeout %uus",
            rx_queue_num_written_radio, gpi_tick_fast_to_us(start_tick_local), start_tick_local,
            program_state.pc_tick + schedule_options.TRX_pre_delay + tx_delay,
            gpi_tick_fast_to_us(program_state.pc_tick + schedule_options.TRX_pre_delay),
            gpi_tick_fast_to_us(tx_delay), gpi_tick_fast_to_us(timeout));

    // start tx
    q->late_start_delay =
            radio_start_tx(start_tick_local, tx_cp[0], tx_cp[1], p) - start_tick_local;

    // prepare results in the meantime
    // NOTE: ref timestamp offset is used directly (without local to global conversion)
    // as we are the transmitter (i.e. the time reference during transmission)
    q->timestamp_schedule_global = program_state.pc_tick;
    q->timestamp_schedule_local  = tick_global_to_local(program_state.pc_tick);
    //q->rssi_space_num_written_begin = -1u;
    q->tx_delay                  = tx_delay;
    start_tick_local += tx_cp[0] + radio_get_ref_timestamp_offset(gpi_radio_get_mode());

    // wait until tx done
    PT_WAIT_UNTIL(pt, tx_ack.done);
    REORDER_BARRIER();

    q->timestamp_ref           = tx_ack.timestamp_ref;
    q->timestamp_end           = tx_ack.timestamp_end;
    q->timestamp_ref_deviation = (p->is_tx_no_packet) ? 0 : (q->timestamp_ref - start_tick_local);

    // release rx_queue entry
    uint32_t nw                = rx_queue_num_writing;
    rx_queue_num_written_radio = nw;
    rx_queue_num_written_trx   = nw;

    PT_END(pt);
}

//**************************************************************************************************

// receive packet
static PT_THREAD(receive(TRX_Group *trx_group, uint_fast8_t dry_run, uint32_t *execution_time))
{
    struct pt *const         pt = pt_trx;

    static const Params_TRX *params;
    static Radio_Packet      tx_packet;
    static Rx_Queue_Entry   *q;
    static uint32_t          num_read;
    static uint32_t          start_tick_local;
    static uint32_t          ref_tick_global;
    static int_fast16_t      pre_trigger_pos;
    uint32_t                 timeout;
    uint32_t                 rssi_buf_size;
    uint32_t                 rssi_pretrigger_time, rssi_posttrigger_time;

    PT_BEGIN(pt);

    // trx_group == NULL means receive whatever arrives, without timeout.
    // this is used during synchronization
    if (NULL == trx_group)
    {
        params                = NULL;

        start_tick_local      = gpi_tick_fast_native() + schedule_options.TRX_pre_delay;
        timeout               = 0; // = inactive (no timeout)
        rssi_pretrigger_time  = 0;
        rssi_posttrigger_time = 0;
        rssi_buf_size         = 0; // not important (as small as possible)
    }
    else
    {
        params = get_params_ptr(trx_group->anchor[0]);

        start_tick_local =
                tick_global_to_local(program_state.pc_tick + schedule_options.TRX_pre_delay);
        timeout               = period_schedule_to_fast(params->timeout);
        rssi_pretrigger_time  = period_schedule_to_fast(params->rssi_pretrigger_time);
        rssi_posttrigger_time = period_schedule_to_fast(params->rssi_posttrigger_time);

        // rssi_buf_size = 0 means automatic
        if (0 == params->rssi_buffer_size_msb)
        {
            // Keep in mind that
            // (a) argmax(cp1 + packet + cp2) can be different from argmax(cp1) and argmax(cp2)
            // (b) it is unknown which packet gets received beforehand
            // (c) in general, transmitter is also unknown after reception (e.g. due to
            //     unsuccessful reception, or because packet does not contain a checkpoint)
            // So: Ideally rssi_buf_size = max(cp1 + packet + cp2). However, due to (b)
            // rssi_posttrigger_time must include max(cp2) (to capture enough samples for sure),
            // and consequently rssi_buf_size >= max(cp1 + packet) + max(cp2).
            // On the other hand, because of (c) there is no chance to adapt rssi_pretrigger_time
            // after reception, so we need rssi_pretrigger_time >= max(cp1).

            rssi_buf_size =
                    gpi_tick_fast_to_us(rssi_pretrigger_time + trx_group->max_air_time[0] +
                                        trx_group->max_air_time[2] + rssi_posttrigger_time) +
                    400; // additional 400 accounts for delayed sampling stop due to ISR runtime

            rssi_pretrigger_time += trx_group->max_air_time[1];
            rssi_posttrigger_time += trx_group->max_air_time[2];
        }
        else rssi_buf_size = 1 << params->rssi_buffer_size_msb;
    }

    // virtual execution time of the TRX instruction
    *execution_time = schedule_options.TRX_pre_delay + timeout + schedule_options.TRX_post_delay;

    // dry run means: do not perform the real operation (here: radio activities),
    // but do everything needed to update the program state
    if (dry_run)
    {
        GPI_TRACE_MSG(TRACE_INFO, "Rx dry run at %uus/0x%08x (global 0x%08x/%uus), timeout %uus",
                      gpi_tick_fast_to_us(start_tick_local), start_tick_local,
                      program_state.pc_tick + schedule_options.TRX_pre_delay,
                      gpi_tick_fast_to_us(program_state.pc_tick + schedule_options.TRX_pre_delay),
                      gpi_tick_fast_to_us(timeout));

        assert(NULL != params);

        // ATTENTION: assemble_tx_packet() is necessary to update the RNG state
        // (which is part of the program state)
        // NOTE: the new state is independent of the transmitter index (which is an important
        // property to keep different transmitters and receivers in sync). Hence, we can use
        // any index here (as we do not evaluate the resulting packet).
        if (NULL != params) assemble_tx_packet(&tx_packet, params, 0);

        PT_EXIT(pt);
    }

    // get rx_queue entry pointer
    num_read = rx_queue_num_written_radio;
    q        = &rx_queue[num_read % NUM_ELEMENTS(rx_queue)];

    GPI_TRACE_MSG(TRACE_INFO, "start Rx [%u] at %uus/0x%08x (global 0x%08x/%uus), timeout %uus",
                  num_read, gpi_tick_fast_to_us(start_tick_local), start_tick_local,
                  program_state.pc_tick + schedule_options.TRX_pre_delay,
                  gpi_tick_fast_to_us(program_state.pc_tick + schedule_options.TRX_pre_delay),
                  gpi_tick_fast_to_us(timeout));

    timeout         = period_global_to_local(timeout);

    // if the TRX instruction belongs to a group with multiple transmitters:
    // activate intermediate trigger event after transmitter_id has been received, enabling us
    // to assemble the expected packet content *before* the full packet has been received
    pre_trigger_pos = -1;
    if (NULL != trx_group)
    {
        if ((trx_group->first_transmitter_id != trx_group->last_transmitter_id) &&
            (0xff != trx_group->checkpoint_offset))
        {
            pre_trigger_pos =
                    trx_group->checkpoint_offset + offsetof(Checkpoint_Data, transmitter_id);
        }
    }

    // start rx
    q->late_start_delay =
            radio_start_rx(start_tick_local, timeout, pre_trigger_pos, my_node_id, rssi_buf_size,
                           rssi_pretrigger_time, rssi_posttrigger_time) -
            start_tick_local;

    // prepare results in the meantime
    if (NULL == trx_group)
    {
        q->timestamp_schedule_global = -1u;
        q->timestamp_schedule_local  = start_tick_local - schedule_options.TRX_pre_delay;
    }
    else
    {
        q->timestamp_schedule_global = program_state.pc_tick;
        q->timestamp_schedule_local  = tick_global_to_local(program_state.pc_tick);
    }

    // drop parent (clock master) if it disappeared (i.e. has not been received for a long time)
    // NOTE: we test this here because maybe we can immediately adopt a new one (below)
    if ((0 != num_hops_from_root) && (NUM_HOPS_INVALID != num_hops_from_root) &&
        (start_tick_local - clock_master_received_at > SYNC_TIMEOUT))
    {
        GPI_TRACE_MSG(TRACE_INFO, "clock master lost");
        num_hops_from_root = NUM_HOPS_INVALID;
    }

    if (NULL != trx_group)
    {
        // ATTENTION: values will not survive PT_WAIT_UNTIL()
        uint_fast8_t i = 0;
        int_fast8_t  k = 0;

        // detect transmitter id
        // (wait until it has been received or select it statically)

        // NOTE: from above we have params = get_params_ptr(trx_group->anchor[0]);

        // if only one transmitter: use it (-> first entry)
        if (trx_group->first_transmitter_id == trx_group->last_transmitter_id)
        {
            assert(0 == trx_group->tx[trx_group->first_transmitter_id].instruction_index);
            assert(0 == trx_group->tx[trx_group->first_transmitter_id].transmitter_index);

            // i = k = 0;
        }

        // if unable to identify transmitter: use first one
        else if (pre_trigger_pos < 0)
            ; // i = k = 0;

        else
        {
            // wait for intermediate trigger or rx done
            // ATTENTION: do not rely on intermediate trigger alone because it may not be reached
            // in case of shorter or broken packets
            PT_WAIT_UNTIL(pt, rx_intermediate_trigger_event ||
                                      (rx_queue_num_written_radio != num_read));
            REORDER_BARRIER();

            // NOTE: At radio_start_rx(), we set intermediate_trigger_preset_content = my_node_id.
            // We know for sure that this is an invalid value (without scanning trx_group)
            // because we are in receive mode. The following lines implicitly catch the case
            // that the received field has not been written to memory by radio's EasyDMA so far
            // (which should not happen and be fixed with adjusted timing in case).
            // Note that the invalid value can be received due to transmission errors,
            // so it would be incorrect to assume that it can never appear.
            i = q->packet.raw_payload[pre_trigger_pos];
            k = trx_group->tx[i].instruction_index;
            if (-1 == k)
            {
                i = 0;
                k = 0;
            }
            else
            {
                params = get_params_ptr(trx_group->anchor[k]);
                i      = trx_group->tx[i].transmitter_index;
            }
        }

        GPI_TRACE_MSG(TRACE_VERBOSE, "expecting transmitter %u.%u (node %u)", k, i,
                      params->transmitter_ids[i]);

        // assemble tx packet to keep RNG state consistent with transmitter
        // and to prepare data for comparisons (used below)
        // ATTENTION: temporarily advance PC to generate consistent checkpoint data
        program_state.pc += k;
        assemble_tx_packet(&tx_packet, params, i);
        program_state.pc -= k;

        // compute timing values
        // NOTE: Nodes do not adjust their hardware clocks. Since the effective ref timestamp offset
        // depends on the transmitter's hardware clock, it is a matter of taste if its nominal value
        // should be interpreted as local or global (eventually, both can be equally inaccurate).
        // Since the offset is relatively small, it is unlikely that the interpretation even makes a
        // difference (e.g. if offset < 400us and clock rate = 16MHz (i.e. offset < 6400 ticks),
        // one tick difference corresponds to a clock deviation of > 150ppm). Consequently,
        // we neglect this issue.
        // NOTE: ref_tick_global will be wrong if NULL == trx_group.
        // This is ok, as in this case ref_tick_global is invalid anyway.
        uint32_t tx_delay = period_schedule_to_fast(params->tx_delay + params->tx_carrier_period_1);
        uint32_t ref_offset = radio_get_ref_timestamp_offset(gpi_radio_get_mode());
        start_tick_local += period_global_to_local(tx_delay) + ref_offset;
        ref_tick_global =
                program_state.pc_tick + schedule_options.TRX_pre_delay + tx_delay + ref_offset;
    }

    // wait until rx done (packet received or timeout reached)
    PT_WAIT_UNTIL(pt, rx_queue_num_written_radio != num_read);
    REORDER_BARRIER();

    // NOTE: will be wrong if NULL == trx_group
    q->timestamp_ref_deviation = q->timestamp_ref - start_tick_local;

    // process rx data
    do {
        Radio_Packet    *p = &(q->packet);
        uint_fast16_t    cpm_pos, cp_pos;
        Checkpoint_Data *cp = NULL;

        GPI_TRACE_MSG(TRACE_VERBOSE,
                      "Rx done [%u], header detected: %u, CRC ok: %u, timeout reached: %u, RSSI "
                      "space hot/radio: %08x/%08x",
                      num_read, p->header_detected, p->crc_ok, p->timeout_triggered,
                      rssi_space_num_writing, rssi_space_num_written_radio);

        if (!(p->crc_ok)) break;

        cpm_pos = get_checkpoint_marker_pos(p);
        if (cpm_pos >= p->raw_payload_length) break;

        cp_pos = p->raw_payload[cpm_pos];
        if (cp_pos + sizeof(Checkpoint_Data) < p->raw_payload_length)
            cp = (Checkpoint_Data *) &(p->raw_payload[cp_pos]);

        // check content
        if (NULL != trx_group)
        {
            if (tx_packet.is_tx_no_packet) break;

            if (p->raw_payload_length != tx_packet.raw_payload_length) break;

            if (cp_pos != params->checkpoint_offset) break;

            if ((0xff != cp_pos) && (NULL == cp)) break;

            // patch transmitter_hop before memcmp()
            if (NULL != cp)
                ((Checkpoint_Data *) &tx_packet.raw_payload[cp_pos])->transmitter_hop =
                        cp->transmitter_hop;

            if (memcmp(p->raw_payload, tx_packet.raw_payload, tx_packet.raw_payload_length))
            {
                // If there are differences, it could be worth to rate the situation:
                // Based on the differences, what is more likely to be the error source,
                // transmission errors or lost schedule synchronization? Unfortunately,
                // it is difficult to formulate a general rule for this because it is
                // very dependent on the packet contents defined by the schedule.
                // If different packets typically have different payloads, then what could
                // be evaluated here? However, if a part of the payload is equal in different
                // (timely nearby) packets, and memcmp() reveals no errors in this part, then
                // lost schedule synchronization seems more likely than transmission errors.
                // We do not implement anything in this direction so far, but leave the comment
                // for future enhancements. Anyway, we suggest to consider lost schedule sync.
                // only if (cp->transmitter_hop < num_hops_from_root) to establish a clear hierarchy.

                //int n = tx_packet.raw_payload_length - (tx_packet.payload - tx_packet.raw_payload);
                //if ((cp->transmitter_hop < num_hops_from_root) && !memcmp(p->payload, tx_packet.payload, n))
                //	sync_state = SYNC_COMM;
                //else break;

                break;
            }

            p->content_ok = 1;
            GPI_TRACE_MSG(TRACE_VERBOSE, "content ok");
        }

        // if root node: done
        if (0 == num_hops_from_root) break;

        if (NULL == cp) break;

        GPI_TRACE_MSG(TRACE_VERBOSE, "checkpoint available");

        // if transmitter is closer to the root node than current parent (clock master): adopt it
        if (cp->transmitter_hop < num_hops_from_root - 1)
        {
            GPI_TRACE_MSG(TRACE_INFO, "selecting new clock master: node %u (%u hops from root)",
                          cp->transmitter_id, cp->transmitter_hop);

            clock_master_id = cp->transmitter_id;

            // reinit tick_ref because otherwise tick_reference_update() would intermix values from old clock master
            tick_reference_init(ref_tick_global, q->timestamp_ref);
        }

        // if packet comes from parent (clock master): update time sync
        if (cp->transmitter_id == clock_master_id)
        {
            GPI_TRACE_MSG(TRACE_VERBOSE,
                          "clock master received (node %u, %u hops from root), updating reference",
                          clock_master_id, cp->transmitter_hop);

            clock_master_received_at = q->timestamp_ref;
            num_hops_from_root = (NUM_HOPS_INVALID != cp->transmitter_hop) ? cp->transmitter_hop + 1
                                                                           : NUM_HOPS_INVALID;

            tick_reference_update(ref_tick_global, q->timestamp_ref);
        }
    }
    while (0);

// ATTENTION: q->timestamp_schedule and tick reference are invalid (most likely wrong)
// if SYNC_FULL != sync_state (nonsync. schedule (pc and pc_tick) -> invalid tx_delay
// -> invalid ref_tick_global)

// DEBUG: test RSSI samples
// at this moment there is no concurrent writer (Rx is inactive and postproc is interrupted),
// so except for the special case that postproc damaged the buffer in between we are save
#if 0
	{
		Rssi_Buffer	*rssi = (Rssi_Buffer*)&rssi_space[q->rssi_space_num_written_begin % NUM_ELEMENTS(rssi_space)];
		uint32_t	buf_size = 1 << rssi->size_msb;
		uint32_t	n = MIN(rssi->num_written, buf_size);
		uint32_t	i = (rssi->num_written - n) & (buf_size - 1);

		GPI_TRACE_MSG(TRACE_VERBOSE, "checking RSSI samples");
		while (n-- > 0)
		{
			if (rssi->samples[i] & 0x80)
			{
				GPI_TRACE_MSG(TRACE_ERROR, "invalid RSSI sample at 0x%05x!", i);
				//trace_dump("samples:", &(rssi->samples[i & ~15]), 16);
			}

			i = ++i & (buf_size - 1);
		}
	}
#endif

    // release rx_queue slot
    rx_queue_num_written_trx = rx_queue_num_written_radio;

    PT_END(pt);
}

//**************************************************************************************************
//***** Global Functions ***************************************************************************

// communication scheduler (virtual machine instruction interpreter)
PT_THREAD(execution_thread())
{
    struct pt *const                 pt = pt_scheduler;

    static const Schedule_Entry     *x;
    static Opcode                    op;
    static const Instruction_Params *params;
    static uint32_t                  execution_time;
    static TRX_Group                 trx_group;

    PT_BEGIN(pt);

    memset(&program_state, 0, sizeof(program_state));
    program_state.rng_state = 1;

    // assign root node (global clock master, always in sync)
    if (ROOT_NODE_ID == my_node_id)
    {
        num_hops_from_root = 0;         // this node is the root
        sync_state         = SYNC_FULL; // root node is in sync (always)
        gpi_led_on(LED_SYNC);
    }
    else
    {
        num_hops_from_root = NUM_HOPS_INVALID;
        sync_state         = SYNC_NONE; // other nodes must synchronize first
        gpi_led_off(LED_SYNC);
    }

    // first call = init
    GPI_TRACE_MSG(TRACE_INFO, "execution thread started");
    PT_YIELD(pt);

    // right before start: add a delay to bring the scheduler "in front of" the first instruction
    tick_reference_init(0, gpi_tick_fast_native() + GPI_TICK_MS_TO_FAST(1));

    // forever
    while (1)
    {
        // use two separate loops for sync'd and non-sync'd handling
        // to keep the sync'd loop lightweight and performant

        // non-sync'd loop
        while (SYNC_FULL != sync_state)
        {
            // if out of sync: enter receive mode (without timeout)
            while (SYNC_NONE == sync_state)
            {
                GPI_TRACE_MSG(TRACE_INFO, "out of sync, entering continuous Rx mode");
                PT_SPAWN(pt, pt_trx, receive(NULL, 0, &execution_time));

                // trigger postprocessing (after we are done here)
                trigger_postprocessing();

                // if packet received: try to resync
                if (NUM_HOPS_INVALID != num_hops_from_root) sync_state = SYNC_COMM;
            }

            // if packet received but schedule not in sync (seemingly)
            // NOTE: assume that SYNC_COMM could be set also by receive()
            if (SYNC_COMM == sync_state)
            {
                Rx_Queue_Entry *q =
                        &rx_queue[(rx_queue_num_written_radio - 1) % NUM_ELEMENTS(rx_queue)];
                const Radio_Packet    *p  = &(q->packet);
                const Checkpoint_Data *cp = get_checkpoint_ptr(p);

                // test validity of received packet

                if (NULL == cp)
                {
                    GPI_TRACE_MSG(TRACE_VERBOSE, "Rx packet contains no checkpoint data");
                    num_hops_from_root = NUM_HOPS_INVALID;
                    sync_state         = SYNC_NONE;
                    continue;
                }

                // this condition is a matter of taste.
                // we assume that all nodes synchronize in a reasonable time after network startup,
                // so huge differences indicate problems
                if (gpi_tick_compare_fast_native(cp->schedule_clock, program_state.pc_tick) < 0)
                {
                    GPI_TRACE_MSG(TRACE_INFO,
                                  "ignoring Rx packet for sync because clock tick appears "
                                  "questionable (received: 0x%08x, local: 0x%08x)",
                                  cp->schedule_clock, program_state.pc_tick);

                    num_hops_from_root = NUM_HOPS_INVALID;
                    sync_state         = SYNC_NONE;
                    continue;
                }

                GPI_TRACE_MSG(TRACE_INFO, "resynchronize schedule: PC = %u, tick = 0x%08x (%uus)",
                              cp->schedule_pc, cp->schedule_clock,
                              gpi_tick_fast_to_us(cp->schedule_clock));

                // TODO: would be good to perform fast forward instead of directly copying the value
                // (goal: do what is possible to not _directly_ rely on anything received)

                program_state.pc             = cp->schedule_pc;
                program_state.pc_tick        = cp->schedule_clock;
                program_state.rng_state      = cp->schedule_rng_state;

                x                            = &schedule[program_state.pc];
                params                       = get_params_ptr(*x);

                // reinit tick reference
                // ATTENTION: This is important because the update in receive() leads to invalid
                // results while SYNC_FULL != sync_state. Besides that, it is a good idea to
                // reinit because we go back in time (schedule tick < rx timestamp).
                // NOTE: In case of a TRX group, the received PC points to the individual group
                // member (i.e. to the right tx_delay).
                q->timestamp_schedule_global = program_state.pc_tick;
                q->timestamp_schedule_local =
                        q->timestamp_ref -
                        (schedule_options.TRX_pre_delay +
                         period_schedule_to_fast(params->TRX.tx_delay +
                                                 params->TRX.tx_carrier_period_1) +
                         radio_get_ref_timestamp_offset(gpi_radio_get_mode()));
                tick_reference_init(program_state.pc_tick, q->timestamp_schedule_local);

                // At this point the PC points to an instruction in the past (-> we received the
                // corresponding packet). From the fact that we received the corresponding packet
                // we know that it is a TRX instruction. We do not know our role in this instruction
                // (could be receiver, but also transmitter (we could have been in receive mode
                // only because we are out of sync)). However, as the program state of each node
                // advances independent of its role (which is an important property to keep all
                // nodes in sync), we need not distinguish them here and simply act as a receiver
                // would have done, i.e. we execute receive() in a dry run fast-forward manner
                // to advance the program state to the next "real" instruction.
                // ATTENTION: In case of a TRX group, the received PC points to the individual group
                // member. We have to skip back to the group anchor (first instruction) in this case.
                if (x->TRX.group_offset < 0)
                {
                    program_state.pc += x->TRX.group_offset;
                    x += x->TRX.group_offset;
                }
                trx_group.anchor = x;
                PT_SPAWN(pt, pt_trx, receive(&trx_group, 1, &execution_time));
                program_state.pc += 1 + x->TRX.group_offset;
                program_state.pc_tick += execution_time;
                program_state.pc_tick += (GTS_INVALID == program_state.pc_tick) ? 1 : 0;

                // NOTE: Another way of performing fast forward is to execute every TRX with
                // dry_run = (gpi_tick_compare_fast_native(tick_global_to_local(program_state.pc_tick), now) < 0);
                // or dry_run = (program_state.pc_tick < tick_local_to_global(now));
                // It could be implemented in conjuction with some flag or similar that clearly marks
                // if a TRX operation has been skipped. This could be advantageous when analyzing
                // the log output (to distinguish if a packet has not been received due to
                // transmission errors or due to sync / timing problems).
                // For the moment we leave this out to save the extra check on every TRX operation.

                sync_state = SYNC_FULL;
                gpi_led_on(LED_SYNC);
                // execution continues in SYNC_FULL loop
            }
        }

        // sync'd loop (instruction interpreter)
        while (SYNC_FULL == sync_state)
        {
            x              = &schedule[program_state.pc];
            op             = (x >= &schedule_end) ? opTERMINATE : x->opcode;
            params         = get_params_ptr(*x);
            execution_time = GPI_TICK_US_TO_FAST(10);

            GPI_TRACE_MSG(TRACE_SCHEDULE, "schedule at %04x, tick 0x%08x (%uus), RNG 0x%08x",
                          program_state.pc, program_state.pc_tick,
                          gpi_tick_fast_to_us(program_state.pc_tick), program_state.rng_state);

            // switch (opcode) ...
            // ATTENTION: cannot use switch statement in a protothread

            if (opTERMINATE == op)
            {
                GPI_TRACE_MSG(TRACE_INFO, "schedule at %04X: program terminated", program_state.pc);

                while (1) PT_YIELD(pt);
            }

            else if (opSLEEP == op)
            {
                // sleep at least minimum execution time
                execution_time = MAX(execution_time, period_schedule_to_fast(params->SLEEP.delay));
            }

            else if (opTRX == op)
            {
                const Params_TRX    *pTRX;
                Gpi_Fast_Tick_Native air_time_base, air_time_byte;
                int_fast16_t         i;

                // NOTE:
                // In first instruction group_offset marks number of following entries (>= 0).
                // In other instructions group_offset marks offset to first instruction (< 0).

                ASSERT_ELSE(x->TRX.group_offset >= 0)
                {
                    // one reason for this error could be a branch with an invalid destination address
                    // (jumping in the middle of a group)

                    GPI_TRACE_MSG(TRACE_ERROR,
                                  "schedule at %04X:%04X: TRX group broken -> terminate program",
                                  program_state.pc, (uintptr_t) params - (uintptr_t) schedule);

                    while (1) PT_YIELD(pt);
                }

                // get air time values used for faster computation
                // (without calling radio_get_packet_airtime() for each group member)
                {
                    Gpi_Radio_Mode mode = gpi_radio_get_mode();
                    air_time_base       = radio_get_packet_airtime(mode, 0);

                    // cannot use switch-case inside protothread, use LUT instead
                    // (adapt mapping if necessary)

                    ASSERT_CT(BLE_1M == 2);
                    ASSERT_CT(BLE_2M == 3);
                    ASSERT_CT(BLE_125k == 4);
                    ASSERT_CT(BLE_500k == 5);

                    static const uint16_t AIR_TIME_LUT[] = {
                            GPI_TICK_US_TO_FAST(8),  // BLE_1M
                            GPI_TICK_US_TO_FAST(4),  // BLE_2M
                            GPI_TICK_US_TO_FAST(64), // BLE_125
                            GPI_TICK_US_TO_FAST(16)  // BLE_500k
                    };

                    mode -= 2;
                    if (mode >= 4)
                    {
                        GPI_TRACE_MSG(TRACE_ERROR,
                                      "schedule at %04X:%04X: invalid radio mode (%d) -> terminate "
                                      "program",
                                      program_state.pc, (uintptr_t) params - (uintptr_t) schedule,
                                      mode);

                        while (1) PT_YIELD(pt);
                    }

                    air_time_byte = AIR_TIME_LUT[mode];
                }

                trx_group.anchor               = x;
                trx_group.max_air_time[0]      = 0;
                trx_group.max_air_time[1]      = 0;
                trx_group.max_air_time[2]      = 0;
                trx_group.first_transmitter_id = 0xff;
                trx_group.last_transmitter_id  = 0;
                trx_group.checkpoint_offset    = 0xfe; // marker for "not set"
                memset(&trx_group.tx, 0xff, sizeof(trx_group.tx));

                // ATTENTION: The loops must run backwards to be consistent in cases where a node
                // is selected as transmitter multiple times. (This should be avoided. However,
                // since it is not catched at compile time, we must provide a defined behavior.)
                // Background: By the use of trx_group.tx[id], each transmitting node is assigned
                // to one instruction and transmitter index. Running backwards ensures that the
                // first match is selected. The advantage of this behavior is as follows. If there
                // is only a single transmitter (i.e. first_transmitter_id = last_transmitter_id),
                // then we know that instruction_index = transmitter_index = 0 in advance, i.e.
                // there is no need to look into trx_group.tx[id] in this case. This fact is
                // exploited in receive().
                for (i = x->TRX.group_offset; i >= 0; i--)
                {
                    ASSERT_ELSE((opTRX == x[i].opcode) &&
                                ((0 == i) || (i == -x[i].TRX.group_offset)))
                    {
                        GPI_TRACE_MSG(TRACE_ERROR,
                                      "schedule at %04X:%04X: illegal instruction: 0x%08X -> "
                                      "terminate program",
                                      program_state.pc, (uintptr_t) params - (uintptr_t) schedule,
                                      *(uint32_t *) x);

                        while (1) PT_YIELD(pt);
                    }

                    pTRX = get_params_ptr(x[i]);

                    {
                        Gpi_Fast_Tick_Native at0, at1, at2;

                        at0 = air_time_base + (air_time_byte * pTRX->payload_length);
                        at1 = period_schedule_to_fast(pTRX->tx_carrier_period_1);
                        at2 = period_schedule_to_fast(pTRX->tx_carrier_period_2);

                        at0 += at1;

                        if (trx_group.max_air_time[0] < at0) trx_group.max_air_time[0] = at0;

                        if (trx_group.max_air_time[1] < at1) trx_group.max_air_time[1] = at1;

                        if (trx_group.max_air_time[2] < at2) trx_group.max_air_time[2] = at2;

                        //air_time =
                        //	air_time_base + (air_time_byte * pTRX->payload_length)
                        //	+ period_schedule_to_fast(pTRX->tx_carrier_period_1 + pTRX->tx_carrier_period_2);
                        //if (trx_group.max_air_time < air_time)
                        //	trx_group.max_air_time = air_time;
                    }

                    // if group members have different checkpoint offsets: do not use them
                    // (too much effort)
                    if (trx_group.checkpoint_offset != pTRX->checkpoint_offset)
                    {
                        if (0xfe == trx_group.checkpoint_offset)
                            trx_group.checkpoint_offset = pTRX->checkpoint_offset;
                        else trx_group.checkpoint_offset = 0xff;
                    }

                    for (uint_fast8_t k = pTRX->num_transmitters; k-- > 0;)
                    {
                        uint_fast8_t id                    = pTRX->transmitter_ids[k];

                        trx_group.tx[id].instruction_index = i;
                        trx_group.tx[id].transmitter_index = k;

                        if (trx_group.first_transmitter_id > id)
                            trx_group.first_transmitter_id = id;

                        if (trx_group.last_transmitter_id < id) trx_group.last_transmitter_id = id;
                    }
                }

                // instruction_index >= 0 marks transmitter, -1 marks receiver

                i = trx_group.tx[my_node_id].instruction_index;
                if (i >= 0)
                {
                    pTRX           = get_params_ptr(x[i]);
                    uint_fast8_t k = trx_group.tx[my_node_id].transmitter_index;

                    // ATTENTION: i does not survive PT_SPAWN()
                    program_state.pc += i;
                    PT_SPAWN(pt, pt_trx, transmit(pTRX, k, 0, &execution_time));
                    program_state.pc -= trx_group.tx[my_node_id].instruction_index;
                }
                else { PT_SPAWN(pt, pt_trx, receive(&trx_group, 0, &execution_time)); }

                // if parent (clock master) disappeared: go out of sync
                // NOTE: this can also be detected in transmit(), so check this always
                if (NUM_HOPS_INVALID == num_hops_from_root)
                {
                    sync_state = SYNC_NONE;
                    gpi_led_off(LED_SYNC);
                    break; // execution continues in !SYNC_FULL loop
                }

                program_state.pc += x[0].TRX.group_offset;

                Rx_Queue_Entry *q =
                        &rx_queue[(rx_queue_num_written_radio - 1) % NUM_ELEMENTS(rx_queue)];
                int32_t dev = q->timestamp_ref_deviation;

                GPI_TRACE_MSG(TRACE_INFO, "clock deviation: %+d (%dus)", dev,
                              (dev < 0) ? -gpi_tick_fast_to_us(-dev) : gpi_tick_fast_to_us(dev));

                // trigger postprocessing
                trigger_postprocessing();
            }

            else if (opBRANCH == op)
            {
                uint16_t dest = program_state.pc + x->BRANCH.offset;

                if (&schedule[dest] >= &schedule_end)
                {
                    GPI_TRACE_MSG(TRACE_ERROR,
                                  "schedule at %04X:%04X: branch target 0x%04X is out of range -> "
                                  "terminate program",
                                  program_state.pc, (uintptr_t) params - (uintptr_t) schedule,
                                  dest);

                    while (1) PT_YIELD(pt);
                }

                // offset - 1 because pc += 1 below
                program_state.pc = dest - 1;
            }

            else // invalid instruction
            {
                GPI_TRACE_MSG(TRACE_ERROR,
                              "schedule at %04X:%04X: illegal opcode: 0x%02X -> terminate program",
                              program_state.pc, (uintptr_t) params - (uintptr_t) schedule, op);

                while (1) PT_YIELD(pt);
            }

            // go to next instruction
            program_state.pc += 1;
            program_state.pc_tick += execution_time;

            // skip reserved timestamp values
            // NOTE: This introduces a tiny uncertainty to the execution time (once in a while, if at all).
            // Besides that, it does not cause any issues as long as all nodes perform this step.
            if (GTS_INVALID == program_state.pc_tick) program_state.pc_tick += 1;

            // pause if pc_tick is "far" in the future (and we are fully synchronized)
            // NOTE: Running not too much ahead facilitates sleeping at the right points.
            // For example, with the instruction sequence SLEEP(long time), TRX we prefer
            // to sleep between SLEEP and TRX, not with TRX's start timer armed and waiting
            // for a long time. The reason is that some activities are not possible while TRX
            // is active, e.g. radio_update_rssi_num_written() has no effect during this time.
            {
                Gpi_Fast_Tick_Native now, wake_at;

                wake_at = tick_global_to_local(program_state.pc_tick) - GPI_TICK_MS_TO_FAST(2);
                now     = gpi_tick_fast_native();

                if (gpi_tick_compare_fast_native(wake_at, now) > 0)
                {
                    // NOTE: Here, we could test if clock master disappeared and go out of sync in case,
                    // as we do in TRX (before transmit and receive). So far we save the effort, since
                    // (a) the TRX tests ensure sync state in case of communication
                    //     (i.e. as soon as we interact with other nodes)
                    // (b) for full safety without communication, we would have to do the test after
                    //     all instructions, not only if there is time to sleep a bit
                    // Option (b) would increase the execution time of all instructions, so we avoid
                    // this right now and consider option (a) as enough. Adding an extra test right
                    // here would be a compromise, which is an option in case it seems beneficial
                    // (e.g. if the schedule contains long sleep phases).

                    GPI_TRACE_MSG(TRACE_VERBOSE, "pause execution (sleep)...");

                    scheduler_wake_at(wake_at);
                    PT_YIELD(pt);

                    GPI_TRACE_MSG(TRACE_VERBOSE, "continue execution");
                }
            }
        }
    }

    //while (1)
    //{
    //	GPI_TRACE_MSG(TRACE_ERROR, "catch -> should not be reached!!!");
    //	PT_YIELD(pt);
    //}

    PT_END(pt);
}

//**************************************************************************************************
//**************************************************************************************************
