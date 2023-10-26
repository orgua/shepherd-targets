"""
Extract special data records from log files

Author: Carsten Herrmann
"""
import base64
import re
import sys
from io import BufferedReader
from io import BufferedWriter
from pathlib import Path
from typing import Annotated
from typing import BinaryIO
from typing import Dict
from typing import List
from typing import Optional
from typing import Union

import typer

from .checksum import ByteOrder
from .checksum import test_checksum
from .cli_proto import app
from .cli_proto import exit_stack
from .filesystem import get_files
from .logger import logger


def test_and_warn(
    line_number: int,
    ctrl_chars: List[bytes],
    text: bytes,
    pos_start: int = 0,
    pos_end: Optional[int] = None,
    *,
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
        pos_new = min(len(section) if x < 0 else x for x in pos_new)
        pos_new += pos_start

        line = line_number - text.count(b"\n", pos_new)
        column = 1 + pos_new - max(0, text.rfind(b"\n", 0, pos_new))
        segment = text[pos_new - (column - 1) : text.find(b"\n", pos_new + 1)]
        logger.warning(
            "line %d column %d: orphaned control character %s in segment %s",
            line,
            column,
            hex(text[pos_new]),
            segment,
        )

        pos_start = pos_new + 1


filter_h = {
    # NOTE: used as long as typer can't read this from fn-docstring
    # https://github.com/tiangolo/typer/pull/436
    # TODO: maybe add typer.Option(help= ... )
    "inf": "Directory (for many .log), file-name or omit to read from stdin",
    "out": "resulting .b64-file, or omit to write to stdout",
    "buf": "disable output buffering (flush after every record)",
    "cch": "special markers, comma separated list of four 2-digit hex numbers representing "
    "BEGIN_RECORD, END_RECORD, BEGIN_CHUNK, END_CHUNK (in this order)",
    "mrz": "maximum allowed record size. "
    "avoids accumulation of arbitrarily large segments in case of missing END_RECORD markers",
    "sip": "check if all lines making a record stem from the same source, "
    "use if input contains intermixed data from different sources. "
    "PATTERN is a regular expression that extracts a line's source id",
    "rsp": "extract records of a specific type (multiple definitions allowed). "
    "ID is the identifier of the record type in the input stream. "
    "PREFIX will be prepended to each entry of this type in the output stream (use "
    " if PREFIX should be omitted).",
    "csu": "test & drop record if invalid",
    "csp": "position inside data. negative values specify position relative to the end",
    "cst": "type of checksum",
    "csb": "le = little-endian, be = big-endian",
    "str": "show warnings if control characters appear at unusual places during parsing. "
    "makes processing slower",
    "a2o": "OUTFILE is opened in append mode (keep existing content)",
}


@app.command("filter-log")
def filter_logfile(
    infile: Annotated[Optional[Path], typer.Argument(help=filter_h["inf"])] = None,
    outfile: Annotated[Optional[Path], typer.Argument(help=filter_h["out"])] = None,
    unbuffered: Annotated[bool, typer.Option(help=filter_h["buf"])] = False,
    control_chars: Annotated[
        Optional[List[str]], typer.Option(help=filter_h["cch"])
    ] = None,
    max_record_size: Annotated[
        int,
        typer.Option(help=filter_h["mrz"]),
    ] = 256
    * 1024,
    source_id_pattern: Annotated[
        Optional[str],
        typer.Option(help=filter_h["sip"]),
    ] = None,
    # record_spec: Annotated[Optional[Dict[str, str]], typer.Option(help="")] = None,
    # TODO: https://typer.tiangolo.com/tutorial/multiple-values/multiple-options/
    record_spec: Annotated[
        Optional[List[str]], typer.Option(help=filter_h["rsp"])
    ] = None,
    checksum: Annotated[bool, typer.Option(help=filter_h["csu"])] = True,
    checksum_min_len: Annotated[int, typer.Option(help="")] = 4,
    checksum_pos: Annotated[
        int,
        typer.Option(help=filter_h["csp"]),
    ] = -4,
    checksum_type: Annotated[str, typer.Option(help=filter_h["cst"])] = "fletcher32",
    checksum_byteorder: Annotated[
        ByteOrder, typer.Option(help=filter_h["csb"])
    ] = ByteOrder.big_endian,
    strict: Annotated[
        bool,
        typer.Option(help=filter_h["str"]),
    ] = True,
    append_data: Annotated[
        bool,
        typer.Option(help=filter_h["a2o"]),
    ] = False,
) -> None:
    """Extract special data records from log files (.log -> .b64)"""
    stack = exit_stack()

    if infile is None:
        files_in = [sys.stdin.buffer]
    elif isinstance(infile, Path) and infile.is_dir():
        files_in = get_files(infile, "", ".log")
    else:
        files_in = [infile]

    if outfile is None:
        outfile = sys.stdout.buffer
    elif outfile.exists() and append_data:
        outfile = open(outfile, "ab")
        stack.enter_context(outfile)
    else:
        outfile = open(outfile, "wb")
        stack.enter_context(outfile)
    if outfile.isatty():
        # automatically enable unbuffered mode if outfile is a TTY stream
        unbuffered = True

    if isinstance(control_chars, str):
        control_chars = control_chars.split(sep=",")
    if isinstance(control_chars, list):
        control_chars = [bytes.fromhex(char) for char in control_chars]

    if record_spec:
        record_spec = {_id.encode(): prefix.encode() for _id, prefix in record_spec}
    else:
        record_spec = {b"TRX": b""}

    if checksum:
        checksum_size: int = 4
        checksum_pos = [checksum_pos, checksum_pos + checksum_size]

        if checksum_pos[1] == 0:
            checksum_pos[1] = None
        if checksum_pos[0] < 0:
            checksum_min_len = -checksum_pos[0]
            if -checksum_pos[0] < checksum_size:
                logger.error(
                    "checksum-position is invalid with respect to checksum-size (%d vs. %d)",
                    checksum_pos[0],
                    checksum_size,
                )
        else:
            checksum_min_len = checksum_pos[1]

    if checksum_type != "fletcher32":
        raise RuntimeError("Only fletcher32 implemented ATM")

    for file_in in files_in:
        if isinstance(file_in, Path):
            logger.info("Filtering %s", file_in.name)
            file_rh = open(file_in, "rb")
        else:
            file_rh = file_in

        _filter_logfile(
            file_rh,
            outfile,
            unbuffered,
            control_chars,
            max_record_size,
            source_id_pattern,
            record_spec,
            checksum,
            checksum_min_len,
            checksum_pos,
            checksum_byteorder,
            strict,
        )


def _filter_logfile(
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
    checksum_byteorder: ByteOrder = ByteOrder.big_endian,
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
        # TODO: duplicate above
        record_spec = {b"TRX": b""}

    if checksum_pos is None:
        checksum_pos = [-4, None]

    # precompiled regular expressions
    re_record = re.compile(
        BEGIN_RECORD + rb"(\w+):([^" + BEGIN_RECORD + END_RECORD + rb"]*)" + END_RECORD
    )
    re_chunk = re.compile(
        BEGIN_CHUNK + rb"([^" + BEGIN_CHUNK + END_CHUNK + rb"]*)" + END_CHUNK
    )
    re_source_id = (
        re.compile(source_id_pattern.encode(), flags=re.MULTILINE)
        if source_id_pattern is not None
        else None
    )

    # process infile
    buffer = b""
    line_number = 1
    for line_raw in infile:  # TODO: put content in separate FN?
        # replace stand-alone \r by \n
        # NOTE: common text viewers / editors do the same,
        # so this step is important to be consistent with displayed line numbers
        line = line_raw.replace(b"\r\n", b"\n").replace(b"\r", b"\n")

        line_number += line.count(b"\n")

        # drop everything outside records
        # NOTE: this increases performance if infile contains a lot of other stuff
        if not (len(buffer) or BEGIN_RECORD in line):
            test_and_warn(line_number, control_chars, line, strict=strict)
            continue

        # append line to buffer
        buffer += line

        # collect text until buffer contains BEGIN_RECORD and END_RECORD markers (at least one of each)
        if END_RECORD not in line:
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
                line = line_number - buffer.count(b"\n")
                logger.warning(
                    "line %d: dropping record because size exceeds maximum (%d > %d)",
                    line,
                    len(buffer),
                    max_record_size,
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
                    line = line_number - buffer.count(b"\n", record_match.start(0))
                    logger.warning(
                        "line %d: dropping invalid record (%s)",
                        line,
                        ";".join(err.args),
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
                if END_RECORD not in buffer:
                    break
            else:
                # explicitly drop garbage to re-enable the fast dropping step in the outer loop (see above)
                test_and_warn(line_number, control_chars, buffer, strict=strict)
                buffer = b""
                break
