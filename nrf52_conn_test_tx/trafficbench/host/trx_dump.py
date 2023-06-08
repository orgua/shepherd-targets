#!/usr/bin/env python3
####################################################################################################
#
#   Copyright (c) 2021 - 2022, Networked Embedded Systems Lab, TU Dresden
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#       * Redistributions of source code must retain the above copyright
#         notice, this list of conditions and the following disclaimer.
#       * Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimer in the
#         documentation and/or other materials provided with the distribution.
#       * Neither the name of the NES Lab or TU Dresden nor the
#         names of its contributors may be used to endorse or promote products
#         derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
#   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
####################################################################################################
#
#   @file                   trx_dump.py
#
#   @brief                  read BASE64-encoded TRX records from input and (i) export them to a
#                           PyTables HDF5 file, (ii) print a human-readable packet dump, and/or
#                           (iii) send the packets to lognplot. All options (i) to (iii) can be
#                           enabled or disabled individually.
#
#   @version                $Id$
#   @date                   TODO
#
#   @author                 Carsten Herrmann
#
####################################################################################################

import argparse
import sys
import base64
import cbor2
import zlib
import itertools
import tables as tbl
import io

####################################################################################################
# PyTables format definitions

TRX_Operation = tbl.Enum({'RX' : 0, 'TX' : 1})

# PyTables TRX record specification used in outfile (HDF5)
class TRX_Record(tbl.IsDescription):
    
    ident                = tbl.StringCol(40)
    node_id              = tbl.UInt16Col(dflt=-1)
    schedule_gts         = tbl.UInt32Col()
    schedule_lts         = tbl.UInt32Col()
    operation            = tbl.EnumCol(TRX_Operation, 'RX', base='uint8')
    late_start_delay     = tbl.UInt16Col()
    tx_delay             = tbl.UInt32Col()
    packet_lts           = tbl.UInt32Col()
    packet_lts_deviation = tbl.Int16Col()
    end_lts              = tbl.UInt32Col()
    packet_content_raw   = tbl.StringCol(260 * 2)             # BASE16 encoded (= hex string)
#   packet_content_raw   = tbl.StringCol(260 * 4 // 3 + 5)    # BASE64 encoded
#   packet_content_raw   = tbl.StringCol(260)

    class trx_status(tbl.IsDescription):
        timeout          = tbl.BoolCol()
        header_detected  = tbl.BoolCol()
        crc_ok           = tbl.BoolCol()
        content_ok       = tbl.BoolCol()
    
    class rssi(tbl.IsDescription):
        end_lts                = tbl.UInt32Col()
        num_samples            = tbl.UInt32Col(dflt=0)
        data_anchor            = tbl.UInt64Col()
        early_readout_detected = tbl.BoolCol()
        late_readout_detected  = tbl.BoolCol()
        num_samples_missed     = tbl.UInt32Col()
    
    # NOTE:
    # * ident field's primary purpose is to support the human reader when looking for the source of the entry.
    #   The value is unique if the stored substring is long enough to include node_id and schedule_gts.
    # * schedule_gts can be used to find corresponding entries from different nodes.
    # * If datatype of schedule_gts needs to be extended, then use Int64.
    #   Do not use UInt64 because this is not supported in PyTable's in-kernel queries (PyTables 3.6.1).
    #   See <https://www.pytables.org/usersguide/condition_syntax.html#condition-syntax> for details.
    # * RSSI data is stored in the EArray /trx_data/rssi_data. rssi.data_anchor is a pointer into
    #   this array. We do not use a VLArray because the way data is stored in a VLArray does not compress
    #   the real data (only control data. For details, see 
    #   <https://www.pytables.org/usersguide/libref/homogenous_storage.html#the-vlarray-class>).
    
####################################################################################################

# CRC computation function
# polynomial: x^24 + x^10 + x^9 + x^6 + x^4 + x^3 + x + 1
# TODO: test which variant is faster (should be crcmod, at least with C extension)
try:

    # <https://pypi.org/project/crcmod>
    # <http://crcmod.sourceforge.net>
    import crcmod

    crc_core_function = crcmod.mkCrcFun(0b1000000000000011001011011, 0xaaaaaa, True, 0)

    bitswap = lambda x: (x * 0x0202020202 & 0x010884422010) % 1023

    bitswap_lut = bytes.maketrans(bytes(range(0, 256)), bytes(bitswap(x) for x in range(0, 256)))

    def crc(data):
        return crc_core_function(data).to_bytes(3, "big").translate(bitswap_lut)
    
except:
    
    # <https://pypi.org/project/crc>
    import crc

    crc_calculator = crc.CrcCalculator(
        crc.Configuration(width=24, polynomial=0b11001011011, init_value=0x555555, reverse_input=True),
        table_based=True)
    
    def crc(data):
        return crc_calculator.calculate_checksum(data).to_bytes(3, 'little')

####################################################################################################
# handle command line
# (see <https://docs.python.org/3.8/howto/argparse.html> for details)

# define command line arguments
ap = argparse.ArgumentParser(description="decode TRX messages and import them into PyTables HDF5 file")
ap.add_argument("infile", type=argparse.FileType("r"), nargs="?", default=sys.stdin, help="use - to read from stdin")
ap.add_argument("-d", "--logfile", type=argparse.FileType("w"), help="use - to write to stdout")
ap.add_argument("-o", "--outfile")
ap.add_argument("-l", "--num-lines", type=int, default=None, help="number of lines (= number of records) in INFILE. can improve performance if provided")
ap.add_argument("--rssi-dump-max", type=int, default=20, metavar="LEN", help="max. #samples dumped in LOGFILE")
ap.add_argument("--rssi-test-samples", action="store_true", help= "test if RSSI samples result in a sawtooth signal (useful for debugging)")
x = ap.add_argument_group('lognplot options', 'can be used to enable realtime data plotting with lognplot')
x.add_argument("--lognplot-host", type=str, metavar="HOST", default=None, help='hostname of lognplot server, e.g. "localhost" or "127.0.0.1". default = disabled')
x.add_argument("--lognplot-port", type=int, metavar="PORT", default=12345, help="TCP port of lognplot server. default = 12345")
x.add_argument("--lognplot-bin-gain", type=float, metavar="MUL", default=1, help="gain of binary data output. output value = MUL * input + OFS * node_id")
x.add_argument("--lognplot-bin-offset", type=float, metavar="OFS", default=0, help="offset of binary data output. output value = MUL * input + OFS * node_id")

# parse command line
args = ap.parse_args()
if (args.rssi_dump_max < 20):
    ap.error("argument --rssi-dump-max: invalid value (must be >= 20)")

# determine expected number of rows
if args.num_lines is None:
    if args.infile.seekable():
        args.num_lines = sum(1 for _ in args.infile)
        args.infile.seek(0)
    else:
        args.num_lines = 10000

####################################################################################################

# compute Fletcher-32 checksum
def fletcher32(data):

    assert(isinstance(data, bytes))
    assert(not (len(data) & 1))
    
    len_ = len(data)
    i = 0
    c0 = c1 = 0
    
    while i < len_:
        
        l = min(len_ - i, 360)
        
        for k in range(l // 2):
            c0 += (data[i] << 8) | data[i+1]
            c1 += c0
            i += 2

        c0 %= 0xffff
        c1 %= 0xffff

    return (c1 << 16) | c0

####################################################################################################

# create outfile
if (args.outfile):

    # see <https://www.pytables.org/usersguide/libref/helper_classes.html#the-filters-class>
    # for details regarding compression
    # use zlib if you want to use external tools like HDFView
    # and blosc if you want it to be fast
#   comp_def = tbl.Filters(complevel=0)
#   comp_def = tbl.Filters(complevel=1, complib='zlib')
    comp_def = tbl.Filters(complevel=1, complib='blosc:zstd')
    
    h5file = tbl.open_file(args.outfile, mode="w", title="TRX data")
    
    group = h5file.create_group("/", "trx_data", filters=comp_def)
    
    trx_table = h5file.create_table(group, "trx", TRX_Record, title="TRX log records", expectedrows=args.num_lines)
    
    rssi_heap = h5file.create_earray(group, "rssi_data", atom=tbl.Int8Atom(), shape=(0,),
                                     expectedrows=10000000, title="RSSI data heap")
    trx_record = trx_table.row

    # examplary compression ratios (achieved in a test example):
    # 601016 trx_data_uncompressed.h5
    # 160372 trx_data_zlib1.h5
    # 134569 trx_data_zlib9.h5
    # 124825 trx_data_bzip1.h5
    # 188213 trx_data_blosclz4hc1.h5
    # 152200 trx_data_blosclz4hc9.h5
    # 156885 trx_data_blosczlib1.h5
    # 129184 trx_data_blosczlib9.h5
    # 144550 trx_data_blosczstd1.h5
    # 120223 trx_data_blosczstd9.h5

# init lognplot client
if args.lognplot_host is None:
    lognclient = None
else:

    # import modules only if needed (may be not installed)
    from lognplot.client import LognplotTcpClient
    import numpy as np

    lognclient = LognplotTcpClient(hostname=args.lognplot_host, port=args.lognplot_port)
    lognclient.connect()

    bin_out = lambda x: x * args.lognplot_bin_gain + node_id * args.lognplot_bin_offset
    bin_list_out = lambda x: [bin_out(xx) for xx in x]

####################################################################################################

# process infile
record_counters = dict()
gts_high = dict()
for b64 in args.infile:

    # load chunk list (outer CBOR format)
    x = base64.standard_b64decode(b64)
#   if (not len(x)):
#       continue
    try:
#       chunks = cbor2.loads(x)
        decoder = cbor2.decoder.CBORDecoder(io.BytesIO(x))
        chunks = decoder.decode()
        checksum = decoder.decode()
        assert(checksum == fletcher32(x[:-4]))
    except:
        # TODO: print detailed error message and continue
        print("CBOR error")
        continue
        
    # encapsulate data (inner CBOR format) in an extra array to parse everything at once
    data = [b'\x9f']

    # extract inner CBOR data
    for x in zip(chunks[0::2], chunks[1::2]):
        if (0 == x[0]):
            data.append(x[1])
        elif (1 == x[0]):
            data.append(zlib.decompress(x[1], wbits=-15))
        else: raise ValueError()

    # close encapsulating array
    data.append(b'\xff')

    # parse data (inner CBOR format)
    data = b''.join(data)
    data = cbor2.loads(data)

    # extract fields

    ident = b64.rstrip()
    if (len(ident) > 40):
        ident = ident[0:37] + "..."
    
    (
        record_counter,
        node_id,
        schedule_gts,
        schedule_lts,
        ref_lts,
        end_lts,
        ref_lts_dev,
        late_start_delay,
        trx_status_field,
        packet,
        tx_delay
        
    ) = data[0:11]

    operation = not not (trx_status_field & 0x80)
    
    trx_status = {
        "timeout"         : (trx_status_field & 0x88 == 0x08),
        "header_detected" : (trx_status_field & 0x90 == 0x10),
        "crc_ok"          : (trx_status_field & 0xa0 == 0x20),
        "content_ok"      : (trx_status_field & 0xc0 == 0x40)
        }

    # extend schedule_gts
    # ATTENTION: this simple approach assumes that the first record from each node has high part 0
    if not node_id in gts_high:
        gts_high[node_id] = (schedule_gts, 0)
    x = gts_high[node_id]
    h = x[1] + (schedule_gts < x[0])
    gts_high[node_id] = (schedule_gts, h)
    schedule_gts += h << 32

    # if transmitter: compute CRC
    if ('TX' == TRX_Operation(operation)):
        packet = packet[0:-3] + crc(packet[0:-3])

    # NOTE: data[-1] of RSSI data = is_valid flag
    rssi_valid = len(data) > 11 and data[-1]
    
    if (rssi_valid):
        (rssi_status_field, rssi_end_lts, rssi_num_samples_missed, rssi_samples) = data[11:-1]
        # convert RSSI samples from differential format
        x = memoryview(rssi_samples).cast('b').tolist()
        rssi_samples = [-x for x in itertools.accumulate(x)]
        if args.rssi_test_samples:
            i = [i for i in range(2, len(x)) if x[i] != 1]
            if i:
                i = ', '.join(map(str, i[:3] + ['...'] + i[-3:] if len(i) > 10 else i))
                print(f"warning: {node_id} @ {schedule_gts:#010x} : RSSI sample test failed at position(s) {i}")

    # check and update record_counter
    if node_id in record_counters:
        rc1 = record_counters[node_id] + 1
        if (record_counter != rc1):
            print("warning: {} record(s) lost at node {} before gts {:#010x} (record_counter = {}, expected {})" \
                .format((record_counter - rc1) % 65536, node_id, schedule_gts, record_counter, rc1),
                file=sys.stderr)
    record_counters[node_id] = record_counter


    # append record to outfile
    if (args.outfile):
        
        # check for duplicate entries
        # NOTE: unfortunately cannot check schedule_gts inside where() call
        # because UInt64Col evaluation is not implemented so far (PyTables 3.6.1) 
        x = [ x.nrow for x in trx_table.where(f"node_id == {node_id}") if x["schedule_gts"] == schedule_gts ]
        if x:
            assert False    # TODO: raise exception
        
        trx_record["ident"]                      = ident
        trx_record["node_id"]                    = node_id
        trx_record["schedule_gts"]               = schedule_gts
        trx_record["schedule_lts"]               = schedule_lts
        trx_record["operation"]                  = operation
        trx_record["packet_lts"]                 = ref_lts
        trx_record["end_lts"]                    = end_lts
        trx_record["packet_lts_deviation"]       = ref_lts_dev
        trx_record["late_start_delay"]           = late_start_delay
        trx_record["tx_delay"]                   = tx_delay
        
        # ATTENTION: Due to an issue in PyTables we cannot store binary strings directly
        # because trailing null bytes would be stripped off (for details, see
        # <https://github.com/PyTables/PyTables/issues/264>).
        # It seems that it would be enough to append a dummy non-null character,
        # but it is unclear if we can safely rely on that (may change in future version?).
        # Hence, we use a safe string encoding and hope that the waste in space gets
        # somewhat compensated by the compression algorithm.
        # We use BASE16 (i.e. hex strings) because this is easy to decode
        # for a human reader when manually inspecting the data.
        trx_record["packet_content_raw"]         = base64.b16encode(packet)
#       trx_record["packet_content_raw"]         = packet + b'#'

        trx_record["trx_status/timeout"]         = trx_status["timeout"]
        trx_record["trx_status/header_detected"] = trx_status["header_detected"]
        trx_record["trx_status/crc_ok"]          = trx_status["crc_ok"]
        trx_record["trx_status/content_ok"]      = trx_status["content_ok"]
        
        if (rssi_valid):
            trx_record["rssi/end_lts"]                = rssi_end_lts
            trx_record["rssi/num_samples"]            = len(rssi_samples)
            trx_record["rssi/early_readout_detected"] = (rssi_status_field & 0x01)
            trx_record["rssi/late_readout_detected"]  = (rssi_status_field & 0x02)
            trx_record["rssi/num_samples_missed"]     = rssi_num_samples_missed
            
            if (len(rssi_samples)):
                trx_record["rssi/data_anchor"]        = rssi_heap.nrows
                rssi_heap.append(rssi_samples)
            
        trx_record.append()
        
#       rssi_data.flush()
#       trx_table.flush()
        

    # print human-readable packet dump
    if (args.logfile):
    
        print(f'\n{ident}', file=args.logfile)
    
        print('transmission scheduled at {:#010x} (record {}):' \
            '\n\tnode             : {}' \
            '\n\toperation        : {}' \
            '\n\tschedule ts.     : {:#010x}' \
            '\n\tlate start delay : {}' \
            '\n\ttransmit delay   : {}' \
            '\n\tpacket ref. ts.  : {:#010x} (nominal {:+})' \
            '\n\tpacket end ts.   : {:#010x}' \
            '\n\tstatus           : {}' \
            '\n\tpacket (PDU\u2016CRC) : {} | {} | {} \u2016 {}' \
            ''.format(
                schedule_gts,
                record_counter,
                node_id,
                TRX_Operation(operation),
                schedule_lts,
                late_start_delay,
                tx_delay,
                ref_lts, ref_lts_dev,
                end_lts,
                ', '.join([x[0] for x in trx_status.items() if x[1]]),
                packet[0:1].hex(), packet[1:2].hex(), packet[2:-3].hex(' '), packet[-3:].hex(' ')),
            file=args.logfile)

        if (rssi_valid):
            print(
                '\tRSSI end ts.     : {:#010x}' \
                '\n\tRSSI status      : {}' \
                '\n\tRSSI samples     : ' \
                ''.format(rssi_end_lts,
                    '\r'.join((
                        'early readout detected' if (rssi_status_field & 0x01) else '',
                        'late readout detected' if (rssi_status_field & 0x02) else '',
                        f'{rssi_num_samples_missed} samples missed' if (rssi_num_samples_missed) else ''
                    )).strip().replace('\r', ', '),
                    ),
                end='', file=args.logfile)
            if (len(rssi_samples) <= args.rssi_dump_max):
                print('{}'.format(rssi_samples)[1:-1], file=args.logfile)
            else:
                print('{} ... {} ... {} ({} samples)'.format(
                        ', '.join(map(str, rssi_samples[:5])),
                        ', '.join(map(str, rssi_samples[len(rssi_samples) // 2 - 2: len(rssi_samples) // 2 + 3])),
                        ', '.join(map(str, rssi_samples[-5:])),
                        len(rssi_samples)
                    ), file=args.logfile)

        if (args.logfile.isatty() or args.logfile is sys.stdout):
            args.logfile.flush()


    # send packet to lognplot
    if not lognclient is None:

        # see
        # <https://github.com/windelbouwman/lognplot>
        # <https://lognplot.readthedocs.io/en/latest/reference/misc.html>

        TICKS_PER_BIT   = 16
        TICKS_PER_S     = 16000000

        # TODO: check if CRC bits have big-endian bitorder
        header_bits = [0.5] * (8 + 32)   # preamble + access address, value 0.5 = unknown (only timing)
        pdu_bits = [(x & 0x01, x & 0x02, x & 0x04, x & 0x08, x & 0x10, x & 0x20, x & 0x40, x & 0x80) for x in packet]
        pdu_bits = [0.0 if not x else 1.0 for x in itertools.chain.from_iterable(pdu_bits)]
        #pdu_bits = np.unpackbits(np.frombuffer(packet, dtype=np.uint8), bitorder='little')

        # choose dummy timestamps in case no packet has been detected
        if not trx_status["header_detected"]:
            ref_lts = schedule_lts + len(header_bits) * TICKS_PER_BIT
        if trx_status["timeout"]:
            end_lts = rssi_end_lts if rssi_valid else ref_lts + 24 * TICKS_PER_BIT

        # compute timestamps
        # ATTENTION: subtracting schedule_lts early ensures correct datatype and wrap-around handling
        # (adding a standard Python integer can silently extend the bit width)
        ts_pdu_begin    = np.uint32(ref_lts - schedule_lts)
        ts_pdu_end      = np.uint32(end_lts - schedule_lts)
        if not trx_status["crc_ok"]:
            ts_header_begin = ts_pdu_begin - (len(header_bits) * TICKS_PER_BIT)
            dt = TICKS_PER_BIT / TICKS_PER_S
        else:
            ts_header_begin = ts_pdu_begin - (len(header_bits) * (ts_pdu_end - ts_pdu_begin)) / len(pdu_bits)
            dt = ((ts_pdu_end - ts_pdu_begin) / len(pdu_bits)) / TICKS_PER_S
        ts_header_begin = np.uint32(ts_header_begin)
        assert(ts_header_begin < ts_pdu_begin)
        assert(ts_pdu_begin < ts_pdu_end)
        assert(ts_pdu_end < 0x80000000)
        ts_header_begin = int(ts_header_begin) + schedule_gts
        ts_end = int(ts_pdu_end) + schedule_gts

        # send bitstream
        # ATTENTION: ts_header_begin marks the beginning of the first bit,
        # so we shift the timestamps to the middle of each bit (using simplified triangular bit shapes in the plot)
        if trx_status["header_detected"]:
            x = header_bits + pdu_bits
            lognclient.send_samples(f"N{node_id} bitstream", (ts_header_begin / TICKS_PER_S) + (dt / 2), dt, bin_list_out(x))

        # send RSSI data
        if rssi_valid and (0 == rssi_num_samples_missed) and (0 == rssi_status_field):

            ts_rssi_last  = np.uint32(rssi_end_lts - schedule_lts)
            ts_rssi_last  = int(ts_rssi_last) + schedule_gts
            ts_rssi_first = ts_rssi_last - (len(rssi_samples) - 1) * TICKS_PER_BIT
            ts_end = max(ts_end, ts_rssi_last)

            lognclient.send_samples(f"N{node_id} RSSI", ts_rssi_first / TICKS_PER_S, TICKS_PER_BIT / TICKS_PER_S, rssi_samples)

        # send status data (mark at schedule_gts and end of frame)
        ts_sched = schedule_gts / TICKS_PER_S
        ts_end /= TICKS_PER_S
        lognclient.send_sample_batch(f"N{node_id} operation", [(ts_sched, bin_out(operation)), (ts_end, bin_out(operation))])
        lognclient.send_sample_batch(f"N{node_id} status", [(ts_sched, trx_status_field), (ts_end, trx_status_field)])

####################################################################################################

# close outfile
if (args.outfile):
    h5file.close()

####################################################################################################
