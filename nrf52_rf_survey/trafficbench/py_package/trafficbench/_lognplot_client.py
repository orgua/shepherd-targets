# see
# <https://github.com/windelbouwman/lognplot>
# <https://lognplot.readthedocs.io/en/latest/reference/misc.html>

TICKS_PER_BIT = 16
TICKS_PER_S = 16_000_000

# TODO: check if CRC bits have big-endian bitorder
header_bits = [0.5] * (
    8 + 32
)  # preamble + access address, value 0.5 = unknown (only timing)
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
pdu_bits = [0.0 if not x else 1.0 for x in itertools.chain.from_iterable(pdu_bits)]
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
if (
    (ts_header_begin >= ts_pdu_begin)
    or (ts_pdu_begin >= ts_pdu_end)
    or (ts_pdu_end >= 0x8000_0000)
):
    raise AssertionError()
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
        bin_list_out(x),
    )

# send RSSI data
if rssi_valid and (0 == rssi_num_samples_missed) and (0 == rssi_status_field):
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
    [(ts_sched, bin_out(operation)), (ts_end, bin_out(operation))],
)
lognclient.send_sample_batch(
    f"N{node_id} status",
    [(ts_sched, trx_status_field), (ts_end, trx_status_field)],
)
