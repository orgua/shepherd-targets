#!/usr/bin/env python3
"""
Read BASE64-encoded TRX records from input and

(i) export them to a PyTables HDF5 file,
(ii) print a human-readable packet dump, and/or
(iii) send the packets to lognplot.

All options (i) to (iii) can be enabled or disabled individually.

Author: Carsten Herrmann
"""
import argparse
import base64
import io
import itertools
import sys
import zlib
from pathlib import Path
from typing import Optional

import cbor2

from ._checksum import fletcher32
from ._crc import calc_crc
from ._file_database import FileWriter
from ._table_records import TRxOperation


def dump_trx(
    infile: io.TextIOWrapper,
    outfile: Optional[Path],
    logfile: io.TextIOWrapper,
    num_lines: Optional[int],
    rssi_dump_max: int,
    rssi_test_samples: bool,
    lognclient,  # TODO
) -> None:
    # create outfile
    if outfile:
        file_db = FileWriter(outfile, num_lines)
    else:
        file_db = None

    # process infile
    record_counters = {}
    gts_high = {}
    for b64 in infile:
        # load chunk list (outer CBOR format)
        x = base64.standard_b64decode(b64)
        #   if (not len(x)):
        #       continue
        try:
            #       chunks = cbor2.loads(x)
            decoder = cbor2.decoder.CBORDecoder(io.BytesIO(x))
            chunks = decoder.decode()
            checksum = decoder.decode()
            assert checksum == fletcher32(x[:-4])
        except:
            # TODO: print detailed error message and continue
            print("CBOR error")
            continue

        # encapsulate data (inner CBOR format) in an extra array to parse everything at once
        data = [b"\x9f"]

        # extract inner CBOR data
        for x in zip(chunks[0::2], chunks[1::2]):
            if 0 == x[0]:
                data.append(x[1])
            elif 1 == x[0]:
                data.append(zlib.decompress(x[1], wbits=-15))
            else:
                raise ValueError()

        # close encapsulating array
        data.append(b"\xff")

        # parse data (inner CBOR format)
        data = b"".join(data)
        data = cbor2.loads(data)

        # extract fields

        ident = b64.rstrip()
        if len(ident) > 40:
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
            tx_delay,
        ) = data[0:11]

        operation = not not (trx_status_field & 0x80)

        trx_status = {
            "timeout": (trx_status_field & 0x88 == 0x08),
            "header_detected": (trx_status_field & 0x90 == 0x10),
            "crc_ok": (trx_status_field & 0xA0 == 0x20),
            "content_ok": (trx_status_field & 0xC0 == 0x40),
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
        if "TX" == TRxOperation(operation):
            packet = packet[0:-3] + calc_crc(packet[0:-3])

        # NOTE: data[-1] of RSSI data = is_valid flag
        rssi_valid = len(data) > 11 and data[-1]

        if rssi_valid:
            (
                rssi_status_field,
                rssi_end_lts,
                rssi_num_samples_missed,
                rssi_samples,
            ) = data[11:-1]
            # convert RSSI samples from differential format
            x = memoryview(rssi_samples).cast("b").tolist()
            rssi_samples = [-x for x in itertools.accumulate(x)]
            if rssi_test_samples:
                i = [i for i in range(2, len(x)) if x[i] != 1]
                if i:
                    i = ", ".join(
                        map(str, i[:3] + ["..."] + i[-3:] if len(i) > 10 else i)
                    )
                    print(
                        f"warning: {node_id} @ {schedule_gts:#010x} : RSSI sample test failed at position(s) {i}"
                    )

        # check and update record_counter
        if node_id in record_counters:
            rc1 = record_counters[node_id] + 1
            if record_counter != rc1:
                print(
                    "warning: {} record(s) lost at node {} before gts {:#010x} (record_counter = {}, expected {})".format(
                        (record_counter - rc1) % 65_536,
                        node_id,
                        schedule_gts,
                        record_counter,
                        rc1,
                    ),
                    file=sys.stderr,
                )
        record_counters[node_id] = record_counter

        # append record to outfile
        if file_db:
            # check for duplicate entries
            # NOTE: unfortunately cannot check schedule_gts inside where() call
            # because UInt64Col evaluation is not implemented so far (PyTables 3.6.1)
            x = [
                x.nrow
                for x in file_db.trx_table.where(f"node_id == {node_id}")
                if x["schedule_gts"] == schedule_gts
            ]
            if x:
                assert False  # TODO: raise exception

            file_db.trx_record["ident"] = ident
            file_db.trx_record["node_id"] = node_id
            file_db.trx_record["schedule_gts"] = schedule_gts
            file_db.trx_record["schedule_lts"] = schedule_lts
            file_db.trx_record["operation"] = operation
            file_db.trx_record["packet_lts"] = ref_lts
            file_db.trx_record["end_lts"] = end_lts
            file_db.trx_record["packet_lts_deviation"] = ref_lts_dev
            file_db.trx_record["late_start_delay"] = late_start_delay
            file_db.trx_record["tx_delay"] = tx_delay

            # ATTENTION: Due to an issue in PyTables we cannot store binary strings directly
            # because trailing null bytes would be stripped off (for details, see
            # <https://github.com/PyTables/PyTables/issues/264>).
            # It seems that it would be enough to append a dummy non-null character,
            # but it is unclear if we can safely rely on that (may change in future version?).
            # Hence, we use a safe string encoding and hope that the waste in space gets
            # somewhat compensated by the compression algorithm.
            # We use BASE16 (i.e. hex strings) because this is easy to decode
            # for a human reader when manually inspecting the data.
            file_db.trx_record["packet_content_raw"] = base64.b16encode(packet)
            # file_db.trx_record["packet_content_raw"] = packet + b'#'

            file_db.trx_record["trx_status/timeout"] = trx_status["timeout"]
            file_db.trx_record["trx_status/header_detected"] = trx_status[
                "header_detected"
            ]
            file_db.trx_record["trx_status/crc_ok"] = trx_status["crc_ok"]
            file_db.trx_record["trx_status/content_ok"] = trx_status["content_ok"]

            if rssi_valid:
                file_db.trx_record["rssi/end_lts"] = rssi_end_lts
                file_db.trx_record["rssi/num_samples"] = len(rssi_samples)
                file_db.trx_record["rssi/early_readout_detected"] = (
                    rssi_status_field & 0x01
                )
                file_db.trx_record["rssi/late_readout_detected"] = (
                    rssi_status_field & 0x02
                )
                file_db.trx_record["rssi/num_samples_missed"] = rssi_num_samples_missed

                if len(rssi_samples):
                    file_db.trx_record["rssi/data_anchor"] = file_db.rssi_heap.nrows
                    file_db.rssi_heap.append(rssi_samples)

            file_db.trx_record.append()

        #       rssi_data.flush()
        #       trx_table.flush()

        # print human-readable packet dump
        if logfile:
            print(f"\n{ident}", file=logfile)

            print(
                f"transmission scheduled at {schedule_gts:#010x} (record {record_counter}):"
                f"\n\tnode             : {node_id}"
                f"\n\toperation        : {TRxOperation(operation)}"
                f"\n\tschedule ts.     : {schedule_lts:#010x}"
                f"\n\tlate start delay : {late_start_delay}"
                f"\n\ttransmit delay   : {tx_delay}"
                f"\n\tpacket ref. ts.  : {ref_lts:#010x} (nominal {ref_lts_dev:+})"
                f"\n\tpacket end ts.   : {end_lts:#010x}"
                f"\n\tstatus           : {', '.join([x[0] for x in trx_status.items() if x[1]])}"
                f"\n\tpacket (PDU\u2016CRC) : {packet[0:1].hex()} | {packet[1:2].hex()} | "
                f"{packet[2:-3].hex(' ')} \u2016 {packet[-3:].hex(' ')}",
                file=logfile,
            )

            if rssi_valid:
                rssi_status = (
                    "\r".join(
                        (
                            "early readout detected"
                            if (rssi_status_field & 0x01)
                            else "",
                            "late readout detected"
                            if (rssi_status_field & 0x02)
                            else "",
                            f"{rssi_num_samples_missed} samples missed"
                            if rssi_num_samples_missed
                            else "",
                        )
                    )
                    .strip()
                    .replace("\r", ", "),
                )

                print(
                    f"\tRSSI end ts.     : {rssi_end_lts:#010x}"
                    f"\n\tRSSI status      : {rssi_status}"
                    f"\n\tRSSI samples     : ",
                    end="",
                    file=logfile,
                )
                if len(rssi_samples) <= rssi_dump_max:
                    print("{}".format(rssi_samples)[1:-1], file=logfile)
                else:
                    print(
                        "{} ... {} ... {} ({} samples)".format(
                            ", ".join(map(str, rssi_samples[:5])),
                            ", ".join(
                                map(
                                    str,
                                    rssi_samples[
                                        len(rssi_samples) // 2
                                        - 2 : len(rssi_samples) // 2
                                        + 3
                                    ],
                                )
                            ),
                            ", ".join(map(str, rssi_samples[-5:])),
                            len(rssi_samples),
                        ),
                        file=logfile,
                    )

            if logfile.isatty() or logfile is sys.stdout:
                logfile.flush()

        # send packet to lognplot
        if lognclient:
            # see
            # <https://github.com/windelbouwman/lognplot>
            # <https://lognplot.readthedocs.io/en/latest/reference/misc.html>

            TICKS_PER_BIT = 16
            TICKS_PER_S = 16_000_000

            # TODO: check if CRC bits have big-endian bitorder
            header_bits = [0.5] * (8 + 32)
            # preamble + access address, value 0.5 = unknown (only timing)
            pdu_bits = [
                (
                    x & 0x01,
                    x & 0x02,
                    x & 0x04,
                    x & 0x08,
                    x & 0x10,
                    x & 0x20,
                    x & 0x40,
                    x & 0x80,
                )
                for x in packet
            ]
            pdu_bits = [
                0.0 if not x else 1.0 for x in itertools.chain.from_iterable(pdu_bits)
            ]
            # pdu_bits = np.unpackbits(np.frombuffer(packet, dtype=np.uint8), bitorder='little')

            # choose dummy timestamps in case no packet has been detected
            if not trx_status["header_detected"]:
                ref_lts = schedule_lts + len(header_bits) * TICKS_PER_BIT
            if trx_status["timeout"]:
                end_lts = rssi_end_lts if rssi_valid else ref_lts + 24 * TICKS_PER_BIT

            # compute timestamps
            # ATTENTION: subtracting schedule_lts early ensures correct datatype and wrap-around handling
            # (adding a standard Python integer can silently extend the bit width)
            ts_pdu_begin = np.uint32(ref_lts - schedule_lts)
            ts_pdu_end = np.uint32(end_lts - schedule_lts)
            if not trx_status["crc_ok"]:
                ts_header_begin = ts_pdu_begin - (len(header_bits) * TICKS_PER_BIT)
                dt = TICKS_PER_BIT / TICKS_PER_S
            else:
                ts_header_begin = ts_pdu_begin - (
                    len(header_bits) * (ts_pdu_end - ts_pdu_begin)
                ) / len(pdu_bits)
                dt = ((ts_pdu_end - ts_pdu_begin) / len(pdu_bits)) / TICKS_PER_S
            ts_header_begin = np.uint32(ts_header_begin)
            assert ts_header_begin < ts_pdu_begin
            assert ts_pdu_begin < ts_pdu_end
            assert ts_pdu_end < 0x8000_0000
            ts_header_begin = int(ts_header_begin) + schedule_gts
            ts_end = int(ts_pdu_end) + schedule_gts

            # send bitstream
            # ATTENTION: ts_header_begin marks the beginning of the first bit,
            # so we shift the timestamps to the middle of each bit (using simplified triangular bit shapes in the plot)
            if trx_status["header_detected"]:
                x = header_bits + pdu_bits
                lognclient.send_samples(
                    f"N{node_id} bitstream",
                    (ts_header_begin / TICKS_PER_S) + (dt / 2),
                    dt,
                    bin_list_out(x, node_id),
                )

            # send RSSI data
            if (
                rssi_valid
                and (0 == rssi_num_samples_missed)
                and (0 == rssi_status_field)
            ):
                ts_rssi_last = np.uint32(rssi_end_lts - schedule_lts)
                ts_rssi_last = int(ts_rssi_last) + schedule_gts
                ts_rssi_first = ts_rssi_last - (len(rssi_samples) - 1) * TICKS_PER_BIT
                ts_end = max(ts_end, ts_rssi_last)

                lognclient.send_samples(
                    f"N{node_id} RSSI",
                    ts_rssi_first / TICKS_PER_S,
                    TICKS_PER_BIT / TICKS_PER_S,
                    rssi_samples,
                )

            # send status data (mark at schedule_gts and end of frame)
            ts_sched = schedule_gts / TICKS_PER_S
            ts_end /= TICKS_PER_S
            lognclient.send_sample_batch(
                f"N{node_id} operation",
                [
                    (ts_sched, bin_out(operation, node_id)),
                    (ts_end, bin_out(operation, node_id)),
                ],
            )
            lognclient.send_sample_batch(
                f"N{node_id} status",
                [(ts_sched, trx_status_field), (ts_end, trx_status_field)],
            )


####################################################################################################


if __name__ == "__main__":
    # define command line arguments
    # (see <https://docs.python.org/3.8/howto/argparse.html> for details)

    a_prs = argparse.ArgumentParser(
        description="decode TRX messages and import them into PyTables HDF5 file"
    )
    a_prs.add_argument(
        "infile",
        type=argparse.FileType("r"),
        nargs="?",
        default=sys.stdin,
        help="use - to read from stdin",
    )
    a_prs.add_argument(
        "-d", "--logfile", type=argparse.FileType("w"), help="use - to write to stdout"
    )
    a_prs.add_argument(
        "-o",
        "--outfile",
        type=Path,
    )
    a_prs.add_argument(
        "-l",
        "--num-lines",
        type=int,
        default=None,
        help="number of lines (= number of records) in INFILE. can improve performance if provided",
    )
    a_prs.add_argument(
        "--rssi-dump-max",
        type=int,
        default=20,
        metavar="LEN",
        help="max. #samples dumped in LOGFILE",
    )
    a_prs.add_argument(
        "--rssi-test-samples",
        action="store_true",
        help="test if RSSI samples result in a sawtooth signal (useful for debugging)",
    )
    a_grp = a_prs.add_argument_group(
        "lognplot options", "can be used to enable realtime data plotting with lognplot"
    )
    a_grp.add_argument(
        "--lognplot-host",
        type=str,
        metavar="HOST",
        default=None,
        help='hostname of lognplot server, e.g. "localhost" or "127.0.0.1". default = disabled',
    )
    a_grp.add_argument(
        "--lognplot-port",
        type=int,
        metavar="PORT",
        default=12345,
        help="TCP port of lognplot server. default = 12345",
    )
    a_grp.add_argument(
        "--lognplot-bin-gain",
        type=float,
        metavar="MUL",
        default=1,
        help="gain of binary data output. output value = MUL * input + OFS * node_id",
    )
    a_grp.add_argument(
        "--lognplot-bin-offset",
        type=float,
        metavar="OFS",
        default=0,
        help="offset of binary data output. output value = MUL * input + OFS * node_id",
    )

    # parse command line
    args = a_prs.parse_args()
    if args.rssi_dump_max < 20:
        a_prs.error("argument --rssi-dump-max: invalid value (must be >= 20)")

    # determine expected number of rows
    if args.num_lines is None and args.infile.seekable():
        args.num_lines = sum(1 for _ in args.infile)  # TODO: WHAT? inefficient
        args.infile.seek(0)
    else:
        args.num_lines = 10_000

    # init lognplot client
    if args.lognplot_host is None:
        lognclient = None
    else:
        # import modules only if needed (may be not installed)
        import numpy as np
        from lognplot.client import LognplotTcpClient

        lognclient = LognplotTcpClient(
            hostname=args.lognplot_host, port=args.lognplot_port
        )
        lognclient.connect()

        bin_out = (
            lambda x, node_id: x * args.lognplot_bin_gain
            + node_id * args.lognplot_bin_offset
        )
        bin_list_out = lambda x, node_id: [bin_out(xx, node_id) for xx in x]
        # TODO: cleanup

    dump_trx(
        args.infile,
        args.outfile,
        args.logfile,
        args.num_lines,
        args.rssi_dump_max,
        args.rssi_test_samples,
        lognclient,
    )
