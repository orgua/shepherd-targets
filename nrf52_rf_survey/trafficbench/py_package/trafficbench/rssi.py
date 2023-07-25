import numpy as np

from .airtime import get_packet_airtime
from .airtime import get_ref_delay
from .constants import TICKS_PER_RSSI_SAMPLE
from .constants import TICKS_PER_US
from .logger import logger
from .unit_conversion import power_dBm_to_W
from .unit_conversion import power_W_to_dBm


def warn_rssi(r):  # TODO: hint interface
    rssi = r["rssi"]

    if rssi["num_samples"] == 0:
        logger.debug(
            "%3d @ %010x : no RSSI data available", r["node_id"], r["schedule_gts"]
        )
    else:
        if rssi["early_readout_detected"]:
            logger.warning(
                "%3d @ %010x : RSSI early readout detected",
                r["node_id"],
                r["schedule_gts"],
            )
        if rssi["late_readout_detected"]:
            logger.warning(
                "%3d @ %010x : RSSI late readout detected",
                r["node_id"],
                r["schedule_gts"],
            )
        if rssi["num_samples_missed"] > 0:
            logger.warning(
                "%3d @ %010x : RSSI %d sample(s) missed",
                r["node_id"],
                r["schedule_gts"],
                rssi["num_samples_missed"],
            )


def split_rssi(trx, rssi_heap):  # TODO: hint interface
    """
    split RSSI stream into noise and signal segments and estimate power values
    ATTENTION: current implementation assumes that there is a noise segment, followed by a signal
    segment, followed by another noise segment. This means that there is no special handling for
    overlayed packets with different lengths or time-shifts as well as transmissions with
    tx_carrier_period_1/2 > 0. The results will be wrong in such cases.
    TODO: detect mentioned situations and warn if function is used in such cases

    :param trx:
    :param rssi_heap:
    :return:
    """
    # guard times used to mask the rise and fall times of the RSSI measurements
    # The slew rate is limited by a low-pass filter in nRF52840's RSSI sampling block (single-pole
    # IIR filter with 15us settling time) [4413_417 v1.2 pp. 313 (6.20.8) and 359 (6.20.15.9)].
    # Additional uncertainties stem from undocumented delays in the radio events (EVENTS_ADDRESS,
    # EVENTS_END), see https://devzone.nordicsemi.com/f/nordic-q-a/83778/undocumented-tx---rx-radio-delay
    # for some details.
    # The following values have been selected based on manual evaluation of RSSI vs. bitstream plots.
    # ATTENTION: So far, the selected values have been checked only with BLE 1M mode.
    # They may need adaptations in case of other BLE modes.
    GUARD_TICKS_NOISE_TO_START = 20 * TICKS_PER_US
    GUARD_TICKS_START_TO_SIGNAL = (
        20 * TICKS_PER_US
    )  # skips potential overshoot (hard to say if present)
    GUARD_TICKS_SIGNAL_TO_END = 0 * TICKS_PER_US
    GUARD_TICKS_END_TO_NOISE = 35 * TICKS_PER_US

    results = {
        "rx_mean": np.nan,
        "rx_min": np.nan,
        "rx_max": np.nan,
        "noise_mean": np.nan,
        "rx_range": [(-1, 0)],
        "noise_range": [(-1, 0)],
    }

    rssi = trx["rssi"]

    if rssi["num_samples"] < 2:
        return results

    rssi_samples = rssi_heap.read(
        rssi["data_anchor"], rssi["data_anchor"] + rssi["num_samples"]
    )

    noise = np.array([], dtype=np.int8)
    signal = np.array([])
    noise_range = []
    signal_range = []

    if rssi["num_samples_missed"] > 0:
        logger.warning(
            "%3d @ %010x : unclear sample timing due to %d missed RSSI sample(s)",
            trx["node_id"],
            trx["schedule_gts"],
            rssi["num_samples_missed"],
        )

    elif trx["trx_status"]["header_detected"] and not trx["trx_status"]["timeout"]:
        packet_len = len(trx["packet_content_raw"]) // 2  # field is BASE16 encoded
        ts_end = trx["end_lts"]
        ts_ref = trx["packet_lts"]
        ts_start = ts_ref - get_ref_delay()
        ts_start2 = ts_end - get_packet_airtime(packet_len)
        ts_rssi_end = rssi["end_lts"]
        ts_rssi_start = ts_rssi_end - len(rssi_samples) * TICKS_PER_RSSI_SAMPLE

        # NOTE:
        # * ts_rssi_end = timestamp of last sample incl. RSSI sampling delay and PPI delay. The delays
        #   could be compensated by subtracting a small constant (which is far below TICKS_PER_RSSI_SAMPLE).
        # * ts_rssi_start is aligned with sample index -1 (-> half-open interval, end - start = num. samples).
        #   Hence, the timestamp of rssi_samples[0] is ts_rssi_start + TICKS_PER_RSSI_SAMPLE.
        # * ts_rssi_end - ts_rssi_start is a multiple of TICKS_PER_RSSI_SAMPLE,
        #   i.e. integer division by TICKS_PER_RSSI_SAMPLE is accurate.
        # * noise_range and signal_range timestamps represent sample timestamps. Hence, if a range
        #   starts at rssi_samples[i] then range.begin = ts_rssi_start + (i + 1) * TICKS_PER_RSSI_SAMPLE.
        #   If it starts at rssi_samples[-i] then range.begin = ts_rssi_end - (i - 1) * TICKS_PER_RSSI_SAMPLE.

        # check if oscillator drift and event timing uncertainty is "acceptable"
        # TODO: fine-tune the critical value (in case of problems)
        if abs(ts_start - ts_start2) >= 8:
            raise AssertionError()

        # ATTENTION: add lts to gts rate adaptation if necessary
        def lts_to_gts(value: float):
            return value - trx["schedule_lts"] + trx["schedule_gts"]

        n = (
            ts_start - GUARD_TICKS_NOISE_TO_START - ts_rssi_start
        ) // TICKS_PER_RSSI_SAMPLE
        if n > 0:
            noise = np.concatenate((noise, rssi_samples[:n]))
            noise_range.append((lts_to_gts(ts_rssi_start + TICKS_PER_RSSI_SAMPLE), n))
        else:
            logger.info(
                "%3d @ %010x : RSSI prologue interval (%f us) < guard time (%f us)",
                trx["node_id"],
                trx["schedule_gts"],
                (ts_start - ts_rssi_start) // TICKS_PER_US,
                GUARD_TICKS_NOISE_TO_START // TICKS_PER_US,
            )
            # NOTE: ts_start - ts_rssi_start can be negative due to (event) timing uncertainty.
            # Specifically, if a packet starts very short after receiver ramp-up, the combination of
            # long EVENTS_READY delay (starting RSSI sampling), short EVENTS_ADDRESS delay (-> ts_ref),
            # and high oscillator drift (causing get_ref_delay() > real ref_delay and in consequence
            # computed ts_start < real ts_start) can lead to ts_start < ts_rssi_start.

        n = (ts_rssi_end - (ts_end + GUARD_TICKS_END_TO_NOISE)) // TICKS_PER_RSSI_SAMPLE
        if n > 0:
            noise = np.concatenate((noise, rssi_samples[-n:]))
            noise_range.append(
                (lts_to_gts(ts_rssi_end - (n - 1) * TICKS_PER_RSSI_SAMPLE), n)
            )
        else:
            logger.info(
                "%3d @ %010x : RSSI epilogue interval (%f us) < guard time (%f us)",
                trx["node_id"],
                trx["schedule_gts"],
                (ts_rssi_end - ts_end) // TICKS_PER_US,
                GUARD_TICKS_END_TO_NOISE // TICKS_PER_US,
            )

        n0 = (
            max(0, ts_start + GUARD_TICKS_START_TO_SIGNAL - ts_rssi_start)
            // TICKS_PER_RSSI_SAMPLE
        )
        n1 = (
            max(0, ts_end - GUARD_TICKS_SIGNAL_TO_END - ts_rssi_start)
            // TICKS_PER_RSSI_SAMPLE
        )
        signal = rssi_samples[range(n0, n1)]
        signal_range.append(
            (lts_to_gts(ts_rssi_start + (n0 + 1) * TICKS_PER_RSSI_SAMPLE), len(signal))
        )

    # the following condition is true in case of a broken packet header (for instance)
    if not noise.size or not signal.size:
        min_ = rssi_samples.min()
        max_ = rssi_samples.max()
        hist = np.histogram(rssi_samples, 1 + max_ - min_, (min_, max_ + 1))
        (y, x) = hist
        if len(x) < 2:
            return results
        S = y.sum() * 0.95
        s = 0
        n = 0
        while s < S:
            s += y[n]
            n += 1
            s += y[-n]

    if True:  # TODO: use commandline switch
        # compute mean on linear scale, i.e. arithmetic mean
        def mean_(value_dBm):
            return power_W_to_dBm(power_dBm_to_W(value_dBm).mean())

        def mean_from_hist(value_dBm, y_):
            return power_W_to_dBm(np.dot(power_dBm_to_W(value_dBm), y_) / np.sum(y_))

    else:
        # compute mean on logarithmic scale, i.e. geometric mean
        def mean_(x):
            return x.mean()

        def mean_from_hist(x, y_):
            return np.dot(x, y_) / np.sum(y_)

    if noise.size:
        results["noise_mean"] = mean_(noise)
    else:
        logger.debug(
            "%3d @ %010x : unclear idle period, "
            "estimating noise power from histogram (using lower %d out of %d bins)",
            trx["node_id"],
            trx["schedule_gts"],
            n,
            len(x),
        )
        results["noise_mean"] = mean_from_hist(x[:n], y[:n])
        noise_range = [(-1, -n)]

    if signal.size:
        results["rx_mean"] = mean_(signal)
        results["rx_min"] = signal.min()
        results["rx_max"] = signal.max()
    else:
        logger.debug(
            "%3d @ %010x : unclear signal period, "
            "estimating signal power from histogram (using upper %d out of %d bins)",
            trx["node_id"],
            trx["schedule_gts"],
            n,
            len(x),
        )
        results["rx_mean"] = mean_from_hist(x[-n:], y[-n:])
        x = x[-n:]
        x = x[y[-n:] != 0]
        results["rx_min"] = x.min()
        results["rx_max"] = x.max()
        signal_range = [(-1, -n)]

    results["noise_range"] = noise_range
    results["rx_range"] = signal_range

    return results
