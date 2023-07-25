"""
Analyze TRX records in PyTables HDF5 file (generated by trx_dump.py)
and add result data to the same file

Author: Carsten Herrmann
"""
import base64
import functools
import numbers
import warnings
from pathlib import Path
from typing import Annotated
from typing import List
from typing import Optional

import numpy as np
import tables as tbl
import typer

from .airtime import get_packet_airtime
from .airtime import get_ref_delay
from .cli_proto import app
from .constants import TICKS_PER_US
from .logger import logger
from .rssi import split_rssi
from .rssi import warn_rssi
from .table_records import MarkerRecord
from .table_records import RxInfoRecord
from .table_records import ScheduleRecord
from .table_records import SourceUncertainty
from .unit_conversion import power_dBm_to_W
from .unit_conversion import power_W_to_dBm

analyze_h = {
    # NOTE: used as long as typer can't read this from fn-docstring
    # https://github.com/tiangolo/typer/pull/436
    "ifn": ".h5-file generated by dump",
    "mrk": "mark all entries in TABLE that fulfill CONDITION."
    " The markers are stored in table /markers/NAME with title TITLE."
    " EXPRESSION defines an optional numerical expression over TABLE"
    " that gets evaluated and stored with each marker (in float64 format)."
    " EXPRESSION must be a valid PyTables expression or an empty string."
    " CONDITION must result in a valid PyTables where() clause."
    " # (sharp) characters inside CONDITION are replaced by EXPRESSION,"
    " which can be used to avoid repeating the expression term."
    " NODE_ID_FIELD specifies the field in TABLE that is used as node_id in the marker."
    " If NODE_ID_FIELD is left empty then the following field names will be tried"
    " (in this order): node_id, destination_node_id.",
}


@app.command("analyze")
def analyze_trx(
    file_name: Annotated[Path, typer.Argument(help=analyze_h["ifn"])],
    # markers: Annotated[Optional[dict], typer.Option(help=analyze_h["mrk"])] = None,
    # TODO: https://typer.tiangolo.com/tutorial/multiple-values/multiple-options/
    markers: Annotated[Optional[List[str]], typer.Option(help=analyze_h["mrk"])] = None,
) -> None:
    """analyze PyTables HDF5 file generated by trafficbench (.h5 -> .h5 enriched)"""

    # open PyTables file, TODO: move into file_database, separate functionality
    h5file = tbl.open_file(file_name.as_posix(), mode="a")
    trx_table = h5file.root.trx_data.trx
    rssi_heap = h5file.root.trx_data.rssi_data
    TRX_Operation = trx_table.get_enum("operation")

    if markers:
        mark_elem = [
            "name",
            "table",
            "expression",
            "condition",
            "title",
            "node_id_field",
        ]
        markers = [dict(zip(mark_elem, x)) for x in markers]
    else:
        markers = []

    if "/markers" in h5file:
        logger.info("removing existing markers")
        h5file.root.markers._f_remove(recursive=True, force=True)

    h5file.create_group(
        "/",
        "markers",
        title="interesting RX entries (markers)",
        filters=h5file.root.trx_data._v_filters,
    )

    if "/catalogs" in h5file:
        logger.info("removing existing catalogs")
        h5file.root.catalogs._f_remove(recursive=True, force=True)

    h5file.create_group(
        "/",
        "catalogs",
        title="information extracted from trx_data",
        filters=h5file.root.trx_data._v_filters,
    )

    for idx in trx_table.indexedcolpathnames:
        logger.info("removing index of %s.%s", trx_table._v_pathname, idx)
        trx_table.cols._f_col(idx).remove_index()

    logger.info("creating RX info catalog")
    rx_info_table = h5file.create_table(
        "/catalogs", "rx_info", RxInfoRecord, title="RX actions"
    )

    logger.info("creating transactions catalog")
    trans_table = h5file.create_table(
        "/catalogs",
        "transactions",
        ScheduleRecord,
        title="transfers grouped to transactions",
    )

    h5file.flush()

    # create some indexes to accelerate queries
    logger.info("creating TRX data indexes")
    trx_table.cols.schedule_gts.create_csindex()
    trx_table.cols.node_id.create_csindex()
    trx_table.flush()

    ####################################################################################################

    # scan and group TRX records
    logger.info("scanning and grouping TRX records (%d entries)", trx_table.nrows)
    nodes = set()
    gts_last = -1
    n_tx = n_rx = n_skip = 0
    for row in trx_table.itersorted("schedule_gts", checkCSI=True):
        # In older versions we used the root node (= node 0) as reference (as it is always in sync),
        # like this: for row in trx_table.where("node_id == 0"): ...
        # However, doing so skips all transactions without the root node.

        # concurrent transfers are identified by schedule_gts
        schedule_gts = row["schedule_gts"]

        # skip records where node was out of sync
        if -1 == np.int32(schedule_gts):
            logger.debug(
                "skipping TRX record %d because schedule_gts = -1 (out of sync)",
                row.nrow,
            )
            n_skip += 1
            continue

        # we process concurrent transfers at once, so each schedule_gts is handled only once
        # (note: iteration is sorted)
        if schedule_gts == gts_last:
            continue
        gts_last = schedule_gts

        indexes = trx_table.get_where_list(f"schedule_gts == {schedule_gts}")
        trx = trx_table[indexes]

        indexes_tx = np.flatnonzero(trx["operation"] == TRX_Operation.TX)
        indexes_rx = np.flatnonzero(trx["operation"] == TRX_Operation.RX)

        # TODO: print helpful error message, skip transaction and continue
        if (len(set(trx["node_id"])) != len(trx)) or (
            len(indexes_tx) + len(indexes_rx) != len(trx)
        ):
            raise AssertionError()

        n_tx += len(indexes_tx)
        n_rx += np.count_nonzero(trx["trx_status"]["crc_ok"][indexes_rx])

        # add unknown nodes
        nodes.update(trx["node_id"])

        # create rx_info entries
        if len(indexes_rx) > 0:
            x = rx_info_table.row
            x["schedule_gts"] = schedule_gts
            x["num_transmitters"] = len(indexes_tx)
            x.append()
            rx_info_table.flush()
            rx_info_table.append(np.repeat(x.fetch_all_fields(), len(indexes_rx) - 1))
            rx_info_table.modify_column(
                start=len(rx_info_table) - len(indexes_rx),
                colname="destination_node_id",
                column=trx[indexes_rx]["node_id"],
            )

        # create transaction
        x = trans_table.row
        x["schedule_gts"] = schedule_gts
        x["num_nodes"] = len(trx)
        x["num_transmitters"] = len(indexes_tx)
        x.append()

    nodes = tuple(nodes)

    h5file.create_array("/catalogs", "nodes", nodes)
    h5file.flush()
    if n_skip > 0:
        logger.info(
            "skipped %d TRX record(s) because schedule_gts = -1 (out of sync)", n_skip
        )
    logger.info(
        "found %d nodes, %d transactions, %d transmissions, %d receptions (CRC ok)",
        len(nodes),
        trans_table.nrows,
        n_tx,
        n_rx,
    )
    logger.info("creating RX info index and transactions index")
    rx_info_table.cols.schedule_gts.create_csindex()
    rx_info_table.cols.destination_node_id.create_csindex()
    rx_info_table.flush()
    trans_table.cols.schedule_gts.create_csindex()
    trans_table.flush()

    ####################################################################################################

    # accomplish link measurements
    logger.info("accomplishing link measurements")
    n = 0
    for trans in trans_table.where("num_transmitters == 1"):
        schedule_gts = trans["schedule_gts"]

        indexes = trx_table.get_where_list(f"schedule_gts == {schedule_gts}")
        trx = trx_table[indexes]

        indexes_tx = np.flatnonzero(trx["operation"] == TRX_Operation.TX)
        indexes_rx = np.flatnonzero(trx["operation"] == TRX_Operation.RX)

        # the following is ensured / has already been checked during grouping step or where-clause:
        # assert(len(set(trx["node_id"])) == len(trx))
        # assert(len(I_tx) + len(I_rx) == len(trx))
        # assert(len(I_tx) == 1)

        t = trx[indexes_tx]

        for idx in indexes_rx:
            r = trx[idx]

            warn_rssi(r)

            if (
                r["trx_status"]["crc_ok"]
                and r["packet_content_raw"] == t["packet_content_raw"]
            ):
                rssi = split_rssi(r, rssi_heap)

                for x in rx_info_table.where(
                    f'(schedule_gts == {schedule_gts}) & (destination_node_id == {r["node_id"]})'
                ):
                    # K = rx_info_table.get_where_list(f'(schedule_gts == {schedule_gts}) & (destination_node_id == {r["node_id"]})')
                    # assert(len(K) == 1)
                    # k = K[0]
                    # x = rx_info_table[k]

                    x["source_node_id"] = t["node_id"]

                    x["rssi_sum"] = rssi["rx_mean"]
                    x["rssi_sum_min"] = rssi["rx_min"]
                    x["rssi_sum_max"] = rssi["rx_max"]
                    x["rssi_noise"] = rssi["noise_mean"]

                    range_ = rssi["noise_range"]
                    (x["rssi_range_noise1_begin"], x["rssi_range_noise1_len"]) = range_[
                        0
                    ]
                    if len(range_) > 1:
                        (
                            x["rssi_range_noise2_begin"],
                            x["rssi_range_noise2_len"],
                        ) = range_[1]
                        if len(range_) > 2:
                            raise AssertionError()

                    range_ = rssi["rx_range"]
                    (x["rssi_range_sum_begin"], x["rssi_range_sum_len"]) = range_[0]
                    if len(range_) > 1:
                        raise AssertionError()

                    sum_dBm = rssi["rx_mean"]
                    noise_dBm = rssi["noise_mean"]

                    if not np.isnan(sum_dBm) and not np.isnan(noise_dBm):
                        if sum_dBm < noise_dBm:
                            logger.warning(
                                "%3d @ %010x : implausible RSSI split, skipping measurement (sum = %f dBm, noise = %f dBm)",
                                r["node_id"],
                                schedule_gts,
                                sum_dBm,
                                noise_dBm,
                            )
                        else:
                            noise_W = power_dBm_to_W(noise_dBm)
                            sigint = power_dBm_to_W(sum_dBm) - noise_W
                            sigint_dBm = power_W_to_dBm(sigint)

                            # NOTE: at this place it is enough to init P_sigint (-> link measurement),
                            # the remaining fields are filled later on
                            x["P_sigint"] = sigint
                            x["P_sigint_dBm"] = sigint_dBm

                            x["is_link_measurement"] = True

                            n += 1

                    x.update()
                # rx_info_table[k] = [x]

    rx_info_table.flush()
    logger.info("found %d receptions that can be exploited for link estimation", n)

    # estimate link matrix
    logger.info("creating link matrix")

    id_map = np.full((max(nodes) + 1,), -1, dtype=np.int32)
    for n in enumerate(nodes):
        id_map[n[1]] = n[0]

    n = len(nodes)
    link_matrix = np.zeros((n, n))
    n = np.zeros((n, n), dtype=trx_table.description.schedule_gts.dtype)

    for x in rx_info_table.where("is_link_measurement"):
        if np.isnan(x["P_sigint"]):
            raise AssertionError()
        # if np.isnan(x['P_sigint']):
        #     continue

        s = id_map[x["source_node_id"]]
        d = id_map[x["destination_node_id"]]

        link_matrix[s, d] += x["P_sigint"]
        n[s, d] += 1

    with np.errstate(invalid="ignore"):
        link_matrix /= n

    h5file.create_carray("/catalogs", "link_matrix", obj=link_matrix)
    h5file.flush()
    h5file.create_carray("/catalogs", "link_matrix_dBm", obj=10 * np.log10(link_matrix))
    h5file.flush()

    logger.info("link matrix:")
    logger.info("       %s", "  ".join([f"{x:4d}" for x in nodes]))
    logger.info("     +-%s", "--" * (len(nodes) - 1) + "----" * len(nodes))
    for x in enumerate(power_W_to_dBm(link_matrix)):
        logger.info(
            "%4d | %s",
            nodes[x[0]],
            "  ".join(["    " if np.isnan(val) else f"{val:4.0f}" for val in x[1]]),
        )

    ####################################################################################################

    # evaluate transactions and compute SINRs
    logger.info("evaluating transactions, computing SNRs and SINRs")

    # disable auto-indexing while updating (allows for faster updates)
    # NOTE: we do not change content of indexed columns
    rx_info_table.autoindex = False
    for trans in trans_table:
        schedule_gts = trans["schedule_gts"]

        indexes = trx_table.get_where_list(f"schedule_gts == {schedule_gts}")
        trx = trx_table[indexes]

        indexes_tx = np.flatnonzero(trx["operation"] == TRX_Operation.TX)
        indexes_rx = np.flatnonzero(trx["operation"] == TRX_Operation.RX)

        # the following is ensured / has already been checked during grouping step or where-clause:
        # assert(len(set(trx["node_id"])) == len(trx))
        # assert(len(I_tx) + len(I_rx) == len(trx))

        for idx in indexes_rx:
            r = trx[idx]

            k = rx_info_table.get_where_list(
                f'(schedule_gts == {schedule_gts}) & (destination_node_id == {r["node_id"]})'
            )
            if len(k) != 1:
                raise AssertionError()
            k = k[0]

            rxi = rx_info_table[k]

            # print('\rprocessing {:3d} @ {:#010x}, {} transmitters'.format(r['node_id'], schedule_gts, len(I_tx)), end='')

            # TODO: select method via command line param
            rx_power = np.zeros(len(indexes_tx))
            if True:
                rx_power = link_matrix[
                    id_map[trx["node_id"][indexes_tx]], id_map[r["node_id"]]
                ]
            else:
                if r["schedule_gts"].dtype != np.uint32:
                    raise AssertionError()

                def fmap(x):
                    return (
                        abs(np.int32(x["schedule_gts"] - np.uint32(schedule_gts))),
                        x["P_sigint"],
                    )

                def fmin(a, b):
                    return a if a[0] <= b[0] else b

                for l, k in enumerate(indexes_tx):
                    x = functools.reduce(
                        fmin,
                        map(
                            fmap,
                            rx_info_table.where(
                                "is_link_measurement"
                                f' & (destination_node_id == {r["node_id"]})'
                                f' & (source_node_id == {trx[k]["node_id"]})'
                            ),
                        ),
                        (0x7FFFFFFF, np.nan),
                    )
                    rx_power[l] = x[1]

            rx_power_isnan = np.isnan(rx_power)

            S = []
            s = None

            if r["trx_status"]["crc_ok"]:
                S = np.flatnonzero(
                    trx[indexes_tx]["packet_content_raw"] == r["packet_content_raw"]
                )

            # same packet from multiple transmitters
            if len(S) > 1:
                rxi["ambiguous_source"] = b"*"

            # unsuccessful reception / no transmitters / packet from external interferer
            elif len(S) == 0:
                S = np.arange(len(indexes_tx))

                if r["trx_status"]["crc_ok"]:
                    rxi["ambiguous_source"] = b"!!"
                elif len(indexes_tx) > 0:
                    rxi["ambiguous_source"] = b"?"
                elif r["trx_status"]["header_detected"]:
                    rxi["ambiguous_source"] = b"!"

                # find transmitter(s) with smallest Hamming distance
                if len(indexes_tx) > 1:
                    with warnings.catch_warnings():
                        warnings.filterwarnings(
                            "ignore", "overflow encountered in uint_scalars"
                        )

                        dst_bits = np.unpackbits(
                            np.frombuffer(
                                base64.b16decode(r["packet_content_raw"]),
                                dtype=np.uint8,
                            ),
                            bitorder="little",
                        )
                        dist = np.empty(len(indexes_tx), dtype=np.uint32)
                        for itx in range(len(indexes_tx)):
                            t = trx[indexes_tx[itx]]

                            src_bits = np.unpackbits(
                                np.frombuffer(
                                    base64.b16decode(t["packet_content_raw"]),
                                    dtype=np.uint8,
                                ),
                                bitorder="little",
                            )
                            ts_shift = np.int32(
                                r["packet_lts"] - r["schedule_lts"]
                            ) - np.int32(t["packet_lts"] - t["schedule_lts"])
                            bitshift = np.int32(np.rint(ts_shift / TICKS_PER_US))
                            if bitshift < 0:
                                src_bits = np.concatenate(
                                    (
                                        np.full(
                                            min(-bitshift, len(dst_bits)), 2, np.uint8
                                        ),
                                        src_bits,
                                    )
                                )
                            else:
                                src_bits = src_bits[bitshift:]

                            lmin = min(len(src_bits), len(dst_bits))
                            dist[itx] = np.count_nonzero(
                                src_bits[:lmin] != dst_bits[:lmin]
                            )

                            # if lengths do not match: count extra bits only if length field has been received correctly.
                            # otherwise we would penalize bit errors in length field more severely than other bit errors
                            if lmin >= 16 and np.all(src_bits[8:16] == dst_bits[8:16]):
                                dist[itx] += max(len(src_bits), len(dst_bits)) - lmin

                    S = np.flatnonzero(dist == dist.min())

            # exclude all transmitters that started transmission after reception has begun
            # use margin since synchronization has limited precision
            if len(S) > 1:
                with warnings.catch_warnings():
                    warnings.filterwarnings(
                        "ignore", "overflow encountered in uint_scalars"
                    )
                    S1 = S
                    for itx in S1:
                        t = trx[indexes_tx[itx]]
                        ts_shift = np.int32(
                            r["packet_lts"] - r["schedule_lts"]
                        ) - np.int32(t["packet_lts"] - t["schedule_lts"])
                        if (
                            ts_shift < -10 * TICKS_PER_US
                        ):  # TODO: make this a commandline arg
                            S = np.setdiff1d(S, itx)
                        if len(S) < 2:
                            break

            if len(S) > 0:
                S1 = S
                if len(S) == 1:
                    if rx_power_isnan[S[0]]:
                        rxi["source_uncertainty"] = SourceUncertainty.WEAK
                else:
                    if rx_power_isnan[S].all():
                        rxi["source_uncertainty"] = SourceUncertainty.STRONG
                        S1 = S[0:1]
                    elif rx_power_isnan[S].any():
                        rxi["source_uncertainty"] = SourceUncertainty.WEAK
                        S1 = S[rx_power_isnan[S] == False]

                s = S1[rx_power[S1].argmax()] if len(S1) > 0 else None
                if s is not None:
                    rxi["source_node_id"] = trx[indexes_tx[s]]["node_id"]

                if (SourceUncertainty.STRONG == rxi["source_uncertainty"]) and (
                    rxi["ambiguous_source"] in b"*!!"
                ):
                    n = trx["node_id"][indexes_tx[S[rx_power_isnan[S]]]]
                    logger.debug(
                        "%3d @ %010x : strong link power uncertainty due to missing link measurement(s) for transmitting node(s) %s",
                        r["node_id"],
                        schedule_gts,
                        ",".join(map(str, n)),
                    )

            # split RSSI only if not already done during link measurement processing (above)
            if rxi["source_node_id"] >= 0:
                rssi = {
                    "rx_mean": rxi["rssi_sum"],
                    "rx_min": rxi["rssi_sum_min"],
                    "rx_max": rxi["rssi_sum_max"],
                    "noise_mean": rxi["rssi_noise"],
                    # 'rx_range'      : [(rxi['rssi_range_sum_begin'], rxi['rssi_range_sum_len'])],
                    # 'noise_range'   : [(rxi['rssi_range_noise1_begin'], rxi['rssi_range_noise1_len']), (rxi['rssi_range_noise2_begin'], rxi['rssi_range_noise2_len'])]
                }
            else:
                warn_rssi(r)
                rssi = split_rssi(r, rssi_heap)

                rxi["rssi_sum"] = rssi["rx_mean"]
                rxi["rssi_sum_min"] = rssi["rx_min"]
                rxi["rssi_sum_max"] = rssi["rx_max"]
                rxi["rssi_noise"] = rssi["noise_mean"]

                range_ = rssi["noise_range"]
                (rxi["rssi_range_noise1_begin"], rxi["rssi_range_noise1_len"]) = range_[
                    0
                ]
                if len(range_) > 1:
                    (
                        rxi["rssi_range_noise2_begin"],
                        rxi["rssi_range_noise2_len"],
                    ) = range_[1]
                    if len(range_) > 2:
                        raise AssertionError()

                range_ = rssi["rx_range"]
                (rxi["rssi_range_sum_begin"], rxi["rssi_range_sum_len"]) = range_[0]
                if len(range_) > 1:
                    raise AssertionError()

            sum_dBm = rssi["rx_mean"]
            noise_dBm = rssi["noise_mean"]

            if not np.isnan(sum_dBm) and not np.isnan(noise_dBm):
                if sum_dBm < noise_dBm:
                    logger.warning(
                        "%3d @ %010x : implausible RSSI split, skipping measurement (sum = %f dBm, noise = %f dBm)",
                        r["node_id"],
                        schedule_gts,
                        sum_dBm,
                        noise_dBm,
                    )
                else:
                    noise_W = power_dBm_to_W(noise_dBm)

                    # signal + interference
                    sigint_now = power_dBm_to_W(sum_dBm) - noise_W
                    sigint_now_min = power_dBm_to_W(rssi["rx_min"]) - noise_W
                    sigint_now_max = power_dBm_to_W(rssi["rx_max"]) - noise_W
                    sigint_link = rx_power.sum() if len(rx_power) else np.nan

                    # signal
                    # sig_now       = sigint_now if len(I_tx) == 1 else np.nan
                    sig_link = rx_power[s] if s is not None else np.nan

                    # interference
                    # int_now       = sigint_now - sig_now
                    int_link = sigint_link - sig_link

                    rxi["P_sigint"] = sigint_now
                    rxi["P_sigint_dBm"] = power_W_to_dBm(sigint_now)
                    rxi["P_sigint_link_dBm"] = power_W_to_dBm(sigint_link)
                    # rxi['P_sigint_diff_dB']  = abs(rxi['P_sigint_dBm'] - rxi['P_sigint_link_dBm'])

                    rxi["SNR_dB"] = power_W_to_dBm(sigint_now) - noise_dBm
                    rxi["SNR_min_dB"] = power_W_to_dBm(sigint_now_min) - noise_dBm
                    rxi["SNR_max_dB"] = power_W_to_dBm(sigint_now_max) - noise_dBm

                    rxi["SINR_link_dB"] = power_W_to_dBm(
                        sig_link / (int_link + noise_W)
                    )

            # theoretically, fastest way to update should be modify_columns(), as this
            # only updates columns that are really touched, which avoids unnecessary
            # reindexing operations. However, the implementation of modify_columns()
            # (in PyTables 3.6.x) contains two issues that make it slower than needed:
            # 1) It is based on numpy.rec.fromarrays(), which requires that the input
            #    has a list-of-arrays format. This means that we cannot use an efficient
            #    view on rxi like this (where names could be built outside the for loop):
            #       names = list(rxi.dtype.names)
            #       names.remove('schedule_gts')
            #       names.remove('destination_node_id')
            #       rx_info_table.modify_columns(start=k, columns=rxi[names], names=names)
            #    Instead, we have to rearrange the input like this:
            #       x = [(rxi[n],) for n in names]
            #       rx_info_table.modify_columns(start=k, columns=x, names=names)
            # 2) Every call tests all touched columns for the need of reindexing (of course,
            #    this is necessary).
            # So overall, it appears more efficient to just update the full row with
            # autoindexing disabled.
            rx_info_table[k] = [rxi]

    rx_info_table.flush()
    rx_info_table.autoindex = True
    rx_info_table.reindex_dirty()

    ####################################################################################################

    # estimate oscillator drifts
    # ATTENTION: this is a very imprecise method provided only as a coarse hint that comes at no extra costs
    logger.info("estimating oscillator drifts")
    for trx in trx_table.where(
        f"(schedule_gts != 0xffffffff) & (operation == {TRX_Operation.RX})"
    ):
        # TODO: flatten trx_status and integrate this into where() clause
        x = trx.fetch_all_fields()
        if not x["trx_status"]["header_detected"] or x["trx_status"]["timeout"]:
            continue

        for rxi in rx_info_table.where(
            f'(schedule_gts == {trx["schedule_gts"]}) & (destination_node_id == {trx["node_id"]})'
        ):
            packet_len = len(trx["packet_content_raw"]) // 2  # field is BASE16 encoded
            ts_end = trx["end_lts"]
            ts_ref = trx["packet_lts"]

            t_nom = get_packet_airtime(packet_len) - get_ref_delay()
            t_meas = ts_end - ts_ref

            # Let fT and fR the transmitter's and receiver's oscillator frequency, respectively.
            # With L the (fixed) number of periods that follows from the number of bits, we have
            # t_meas = L / fT and t_nom = L / fR. Hence,
            #   f_ratio := fT / fR = (L / t_meas) / (L / t_nom) = t_nom / t_meas
            # +/- 1 accounts for the potential inaccuracy that follows from the timestamp resolution.
            f_ratio_min = t_nom / (t_meas + 1)
            f_ratio_max = t_nom / (t_meas - 1)

            # df := fT - fR = fT / fR * fR - fR = f_ratio * fR - fR = (f_ratio - 1) * fR
            # fR is unknown but in the ISM band, i.e. 2400MHz < fR < 2484MHz.
            df_min = (f_ratio_min - 1) * (2484e6 if f_ratio_min < 1 else 2400e6)
            df_max = (f_ratio_max - 1) * (2400e6 if f_ratio_max < 1 else 2484e6)

            # ticks -> seconds
            t_meas /= 1e6 * TICKS_PER_US

            # num. periods = t_mead * df
            if df_max < 0:  # df_min <= df_max < 0
                periods_min = -df_max * t_meas
                periods_max = -df_min * t_meas
            elif df_min < 0:  # df_min < 0 <= df_max
                periods_min = 0
                periods_max = max(-df_min, df_max) * t_meas
            else:  # 0 <= df_min <= df_max
                periods_min = df_min * t_meas
                periods_max = df_max * t_meas

            rxi["osc_drift_ppm_min"] = (f_ratio_min - 1) * 1e6
            rxi["osc_drift_ppm_max"] = (f_ratio_max - 1) * 1e6
            rxi["osc_drift_num_periods_min"] = periods_min
            rxi["osc_drift_num_periods_max"] = periods_max
            rxi.update()

    rx_info_table.flush()

    ####################################################################################################

    # create markers
    for desc in markers:
        where_clause = desc["condition"].replace("#", "(" + desc["expression"] + ")")

        logger.info("creating markers: %s (where %s)", desc["name"], where_clause)

        source_table = h5file.get_node("/", desc["table"])

        node_id_field = desc["node_id_field"]
        if not node_id_field:
            for n in ["node_id", "destination_node_id"]:
                if n in source_table.colnames:
                    node_id_field = n
                    break
        if node_id_field is None:
            raise AssertionError()

        marker_table = h5file.create_table(
            "/markers", desc["name"], MarkerRecord, title=desc["title"]
        )
        marker_table._f_setattr("TABLE", source_table._v_pathname)
        marker_table._f_setattr("NODE_ID_FIELD", node_id_field)
        marker_table._f_setattr("CONDITION", where_clause)
        marker_table._f_setattr("EXPRESSION", desc["expression"])
        marker_table.flush()

        # generate markers
        m = marker_table.row
        for x in source_table.where(where_clause):
            m["schedule_gts"] = x["schedule_gts"]
            m["node_id"] = x[node_id_field]
            m.append()
        marker_table.flush()

        # compute expression for marked records
        x = source_table.read_where(where_clause)
        x = {n: x[n] for n in x.dtype.names}
        expr = tbl.Expr(desc["expression"], uservars=x)
        expr.set_output(marker_table.cols.expression_value)
        expr.eval()
        del x, expr
        marker_table.flush()

    ####################################################################################################

    # print transactions
    # TODO: only if requested (command-line) or in another script
    UNCERT = {
        SourceUncertainty.EXTERNAL: "",
        SourceUncertainty.WEAK: "(?)",
        SourceUncertainty.STRONG: "?",
    }
    for trans in trans_table:
        schedule_gts = trans["schedule_gts"]

        indexes = trx_table.get_where_list(f"schedule_gts == {schedule_gts}")
        trx = trx_table[indexes]

        indexes_tx = np.flatnonzero(trx["operation"] == TRX_Operation.TX)
        indexes_rx = np.flatnonzero(trx["operation"] == TRX_Operation.RX)

        # the following is ensured / has already been checked during grouping step or where-clause:
        # assert(len(set(trx["node_id"])) == len(trx))
        # assert(len(I_tx) + len(I_rx) == len(trx))

        logger.info("\ntransaction at %010x:", schedule_gts)

        actions = [("-", "")] * len(trx)
        SNRs = [(None, None)] * len(trx)
        SINRs = [("", "")] * len(trx)

        for idx in indexes_tx:
            actions[idx] = ("Tx", "")

        for idx in indexes_rx:
            r = trx[idx]

            rxi = rx_info_table.read_where(
                f'(schedule_gts == {schedule_gts}) & (destination_node_id == {r["node_id"]})'
            )
            if len(rxi) != 1:
                raise AssertionError()
            rxi = rxi[0]

            m = rxi["ambiguous_source"].decode()
            if m not in "?!!":
                m += UNCERT[rxi["source_uncertainty"]]

            if not r["trx_status"]["header_detected"]:
                actions[idx] = ("", "")
            else:
                s = rxi["source_node_id"]
                actions[idx] = (s if s >= 0 else "", m)

                if not r["trx_status"]["crc_ok"]:
                    actions[idx] = ("(",) + actions[idx] + (")",)

            if not np.isnan(rxi["SNR_dB"]):
                SNRs[idx] = (rxi["SNR_min_dB"], rxi["SNR_dB"], rxi["SNR_max_dB"])

            x = rxi["SINR_link_dB"]
            if not np.isnan(x):
                SINRs[idx] = (x, m)

        def fmt(c):
            return " | ".join([f"{x:^6}" for x in c])

        def fmtx(c):
            return " | ".join(f"{''.join(map(str, x)):^6}" for x in c)

        logger.info("\tnode:          %s", fmt(trx["node_id"]))
        logger.info("\treceive from:  %s", fmtx(actions))
        logger.info(
            "\tSINR (link):   %s",
            fmtx(
                [
                    (f"{x[0]:5.1f}", x[1]) if isinstance(x[0], numbers.Number) else x
                    for x in SINRs
                ]
            ),
        )
        logger.info(
            "\tSNR (mean):    %s",
            fmt([f"{x[1]:5.1f}" if x[0] is not None else "" for x in SNRs]),
        )
        logger.info(
            "\tSNR (min:max): %s",
            fmt([f"{x[0]:1.0f}:{x[2]:1.0f}" if x[0] is not None else "" for x in SNRs]),
        )

    # done
    h5file.close()
