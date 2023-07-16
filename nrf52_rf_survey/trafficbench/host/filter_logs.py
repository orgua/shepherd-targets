#!/usr/bin/env python3
"""
Extract special data records from log files

Author: Carsten Herrmann
"""
import argparse
import base64
import logging
import re
import sys
from io import BufferedReader
from io import BufferedWriter
from typing import BinaryIO
from typing import Dict
from typing import List
from typing import Optional
from typing import Union

from ._checksum import test_checksum

logger: logging.Logger = logging.getLogger("filter")
logger.setLevel(logging.INFO)
logger.addHandler(logging.NullHandler())

####################################################################################################


def test_and_warn(
    line_number: int,
    ctrl_chars: List[bytes],
    text: bytes,
    pos_start: int = 0,
    pos_end: Optional[int] = None,
    strict: bool = True,
) -> None:
    """
    test text and warn if it contains any special control characters (in case --strict is enabled)

    t = s[start:end]
    if (BEGIN_RECORD in t) or (BEGIN_CHUNK in t) or (END_CHUNK in t) or (END_RECORD in t):
        p = (t.find(x) for x in (BEGIN_RECORD, BEGIN_CHUNK, END_CHUNK, END_RECORD))
        p = min((len(t) if x < 0 else x for x in p))
        l = line_number - s.count(b'\n', start + p)
        c = 1 + start + p - max(0, s.rfind(b'\n', 0, start + p))
        warning(f'orphaned control characters in line {l} column {c}')
    """
    if not strict:
        return
    while True:
        section = text[pos_start:pos_end]

        if not any([ctrl_char in section for ctrl_char in ctrl_chars]):
            break

        pos_new = (section.find(char) for char in ctrl_chars)
        pos_new = min((len(section) if x < 0 else x for x in pos_new))
        pos_new += pos_start

        l = line_number - text.count(b"\n", pos_new)
        c = 1 + pos_new - max(0, text.rfind(b"\n", 0, pos_new))
        x = text[pos_new - (c - 1) : text.find(b"\n", pos_new + 1)]
        logger.warning(
            f"line {l} column {c}: orphaned control character {hex(text[pos_new])} in segment {x}"
        )

        pos_start = pos_new + 1


####################################################################################################


def filter_logfile(
    infile: Union[BufferedReader, BinaryIO],
    outfile: Union[BufferedWriter, BinaryIO],
    unbuffered: bool = False,
    control_chars: Optional[List[bytes]] = None,
    max_record_size: int = 256 * 1024,
    source_id_pattern: Optional[str] = None,
    record_spec: Optional[Dict[bytes, bytes]] = None,
    checksum: bool = True,
    checksum_min_len: int = 4,
    checksum_pos: Optional[List[int]] = None,
    checksum_byteorder: str = "be",
    strict: bool = True,
) -> None:
    # special control characters
    if control_chars is None:  # TODO: move higher up - data-model?
        # start of record = SOH (ASCII "Start of Header")
        BEGIN_RECORD = b"\x01"
        # end of record = ETB, was EOT (ASCII "End of Transmission")
        END_RECORD = b"\x17"
        # start of chunk = STX (ASCII "Start of Text")
        BEGIN_CHUNK = b"\x02"
        # end of chunk = ETX (ASCII "End of Text")
        END_CHUNK = b"\x03"
        control_chars = [BEGIN_RECORD, END_RECORD, BEGIN_CHUNK, END_CHUNK]
    else:
        BEGIN_RECORD = control_chars[0]
        END_RECORD = control_chars[1]
        BEGIN_CHUNK = control_chars[2]
        END_CHUNK = control_chars[3]

    if record_spec is None:
        record_spec = {b"TRX": b""}

    if checksum_pos is None:
        checksum_pos = [-4, None]

    # precompiled regular expressions
    re_record = re.compile(
        BEGIN_RECORD + b"(\w+):([^" + BEGIN_RECORD + END_RECORD + b"]*)" + END_RECORD
    )
    re_chunk = re.compile(
        BEGIN_CHUNK + b"([^" + BEGIN_CHUNK + END_CHUNK + b"]*)" + END_CHUNK
    )
    re_source_id = (
        re.compile(source_id_pattern.encode(), flags=re.MULTILINE)
        if not source_id_pattern is None
        else None
    )

    # process infile
    buffer = b""
    line_number = 1
    for line in infile:  # TODO: put content in separate FN?
        # replace stand-alone \r by \n
        # NOTE: common text viewers / editors do the same,
        # so this step is important to be consistent with displayed line numbers
        line = line.replace(b"\r\n", b"\n").replace(b"\r", b"\n")

        line_number += line.count(b"\n")

        # drop everything outside records
        # NOTE: this increases performance if infile contains a lot of other stuff
        if not (len(buffer) or BEGIN_RECORD in line):
            test_and_warn(line_number, control_chars, line, strict=strict)
            continue

        # append line to buffer
        buffer += line

        # collect text until buffer contains BEGIN_RECORD and END_RECORD markers (at least one of each)
        if not END_RECORD in line:
            # drop data in front of BEGIN_RECORD
            # ATTENTION: this is important for the record size check below to work right
            p = buffer.find(BEGIN_RECORD)
            if p > 0:
                test_and_warn(line_number, control_chars, buffer, 0, p, strict=strict)
                buffer = buffer[p:]

            # if there are multiple BEGIN_RECORD markers (without END_RECORD): keep only the last one
            p = buffer.rfind(BEGIN_RECORD, p + 1)
            if p >= 0:
                test_and_warn(line_number, control_chars, buffer, 0, p, strict=strict)
                buffer = buffer[p:]

            # limit maximum record size
            if len(buffer) > max_record_size:
                l = line_number - buffer.count(b"\n")
                logger.warning(
                    f"line {l}: dropping record because size exceeds maximum ({len(buffer)} > {max_record_size})"
                )
                buffer = b""

            # ATTENTION: The steps above avoid accumulation of malformed records in buffer, which is
            # important to prohibit arbitrarily large buffer size due to missing END_RECORD markers.

            continue

        # parse buffered text
        while True:
            # extract first record
            # NOTE: buffer may contain more than one record
            record_match = re_record.search(buffer)
            if (
                not record_match
            ):  # i.e. all END_RECORD come before all BEGIN_RECORD (there is at least one of each)
                p = buffer.rfind(BEGIN_RECORD)
                if re_source_id:
                    p = buffer.rfind(b"\n", 0, p) + 1
                test_and_warn(line_number, control_chars, buffer, 0, p, strict=strict)
                buffer = buffer[p:]
                break

            # check text before record
            test_and_warn(
                line_number,
                control_chars,
                buffer,
                0,
                record_match.start(0),
                strict=strict,
            )

            # if current record type has to be processed
            if record_match.group(1) in record_spec:
                try:
                    # test if all input lines stem from the same source
                    if re_source_id:
                        start = buffer.rfind(b"\n", 0, record_match.start(0)) + 1
                        end = buffer.find(b"\n", record_match.end(0)) + 1
                        x = re_source_id.findall(buffer, start, end)
                        if 1 != len(set(x)):
                            raise ValueError(
                                f'inconsistent source id(s) {",".join(map(bytes.decode, x))}'
                            )

                    # extract data chunks
                    chunk_data = []
                    pos = record_match.start(2)
                    for chunk_match in re_chunk.finditer(record_match.group(2)):
                        chunk_data.append(chunk_match.group(1))
                        # check text between last and current chunk
                        test_and_warn(
                            line_number,
                            control_chars,
                            buffer,
                            pos,
                            chunk_match.start(1),
                            strict=strict,
                        )
                        pos = record_match.start(2) + chunk_match.end(1) + 1
                    chunk_data = b"".join(chunk_data)

                    # check text between last chunk and end of record
                    test_and_warn(
                        line_number,
                        control_chars,
                        buffer,
                        pos,
                        record_match.end(2),
                        strict=strict,
                    )

                    # test encoding
                    try:
                        x = base64.b64decode(chunk_data, validate=strict)
                    except BaseException as err:
                        raise ValueError("BASE64 decode: " + ";".join(err.args))

                    # test checksum
                    if checksum:
                        test_checksum(
                            x, checksum_pos, checksum_byteorder, checksum_min_len
                        )

                except ValueError as err:
                    l = line_number - buffer.count(b"\n", record_match.start(0))
                    logger.warning(
                        f"line {l}: dropping invalid record ("
                        + ";".join(err.args)
                        + ")"
                    )

                # if ok: write output text
                else:
                    outfile.write(
                        record_spec[record_match.group(1)] + chunk_data + b"\n"
                    )
                    if unbuffered:
                        outfile.flush()

            # remove current record from buffer
            if re_source_id:
                # there can be multiple records per line, so keep everything outside the record
                buffer = buffer[: record_match.start(0)] + buffer[record_match.end(0) :]
            else:
                buffer = buffer[record_match.end(0) :]

            # continue with next record
            if BEGIN_RECORD in buffer:
                if not END_RECORD in buffer:
                    break
            else:
                # explicitly drop garbage to re-enable the fast dropping step in the outer loop (see above)
                test_and_warn(line_number, control_chars, buffer, strict=strict)
                buffer = b""
                break


####################################################################################################


if __name__ == "__main__":
    # define command line arguments
    # (see <https://docs.python.org/3.8/howto/argparse.html> for details)

    ap = argparse.ArgumentParser(
        description="extract special data records from log files"
    )

    ap.add_argument(
        "infile",
        type=argparse.FileType("rb"),
        nargs="?",
        default=sys.stdin.buffer,
        help="default = stdin (or use - to read from stdin)",
    )
    group = ap.add_mutually_exclusive_group()
    group.add_argument(
        "-o",
        "--outfile",
        type=argparse.FileType("wb"),
        default=None,
        help="default = stdout (or use - to write to stdout)",
    )
    group.add_argument(
        "-a",
        "--append-to",
        metavar="OUTFILE",
        type=argparse.FileType("ab"),
        default=sys.stdout.buffer,
        help="same as -o, but OUTFILE is opened in append mode (keep existing content)",
    )

    ap.add_argument(
        "-r",
        "--record-spec",
        nargs=2,
        metavar=("ID", "PREFIX"),
        default=[],
        action="append",
        help="extract records of a specific type (multiple definitions allowed). "
        "ID is the identifier of the record type in the input stream. "
        "PREFIX will be prepended to each entry of this type in the output stream "
        '(use "" if PREFIX should be omitted).',
    )

    group = ap.add_mutually_exclusive_group()
    group.add_argument(
        "--strict",
        action="store_true",
        default=True,
        help="parse input more strictly, show warnings if control characters appear at unusual places. "
        "makes processing slower. default = on",
    )
    group.add_argument("--no-strict", dest="strict", action="store_false")

    ap.add_argument(
        "-c",
        "--checksum",
        action="store_true",
        help="test checksum, drop record if invalid",
    )
    ap.add_argument(
        "--checksum-type",
        choices=("fletcher32",),
        default="fletcher32",
        help="type of checksum, default = fletcher32",
    )
    ap.add_argument(
        "--checksum-position",
        metavar="POS",
        dest="checksum_pos",
        type=int,
        default=-4,
        help="position of checksum inside data. negative values specify position relative to the end. default = -4",
    )
    ap.add_argument(
        "--checksum-byteorder",
        choices=("le", "be"),
        default="be",
        help="le = little-endian, be = big-endian (default)",
    )

    ap.add_argument(
        "--check-source-id",
        metavar="PATTERN",
        dest="source_id_pattern",
        help="check if all lines making a record stem from the same source. "
        "PATTERN is a regular expression that extracts a line's source id. "
        "use this option if input contains intermixed data from different sources.",
    )

    ap.add_argument(
        "--control-chars",
        help="control characters used as the special markers. "
        "CONTROL_CHARS is a comma separated list of four 2-digit hex numbers representing "
        "BEGIN_RECORD, END_RECORD, BEGIN_CHUNK, END_CHUNK  (in this order). default=01,04,02,03 (i.e. SOH, EOT, STX, ETX)",
    )

    ap.add_argument(
        "--max-record-size",
        type=int,
        default=256 * 1024,
        help="maximum allowed record size. default = 256KB. "
        "prohibits accumulation of arbitrarily large segments in case of missing END_RECORD markers.",
    )

    ap.add_argument(
        "-u",
        "--unbuffered",
        action="store_true",
        help="disable output buffering (flush after every record)",
    )

    # parse command line
    args = ap.parse_args()

    if args.outfile is None:
        args.outfile = args.append_to

    if not len(args.record_spec):
        ap.error("no record type defined (would generate empty output)")

    args.record_spec = dict([(x[0].encode(), x[1].encode()) for x in args.record_spec])

    # automatically enable unbuffered mode if outfile is a TTY stream
    if args.outfile.isatty():
        args.unbuffered = True

    if args.checksum:
        checksum_size: int = 4

        args.checksum_pos = [args.checksum_pos, args.checksum_pos + checksum_size]
        if args.checksum_pos[1] == 0:
            args.checksum_pos[1] = None

        if args.checksum_pos[0] < 0:
            args.checksum_min_len = -args.checksum_pos[0]
            if -args.checksum_pos[0] < checksum_size:
                ap.error(
                    f"checksum-position is invalid with respect to checksum-size ({args.checksum_pos[0]} vs. {checksum_size})"
                )
        else:
            args.checksum_min_len = args.checksum_pos[1]

    if isinstance(args.control_chars, (str, bytes)):
        # string to list of strings
        hex_chars = args.control_chars.split(sep=",")
        args.control_chars = [bytes.fromhex(char) for char in hex_chars]

    arg_dict = args.__dict__
    arg_dict.pop("append_to")
    arg_dict.pop("checksum_type")  # TODO: not handled
    filter_logfile(**arg_dict)

####################################################################################################
