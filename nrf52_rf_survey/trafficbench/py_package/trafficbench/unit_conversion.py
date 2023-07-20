from typing import Union

import numpy as np


def dB_to_linear(value_dB: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return np.power(
        10.0, value_dB / 10
    )  # TODO: the first two are redundant to the others


def linear_to_dB(value_linear: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    # TODO: this is not working on array
    return np.nan if value_linear < 0 else 10 * np.log10(value_linear)


def power_dBm_to_W(power_dB: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return 10.0 ** (power_dB * 0.1)


def power_W_to_dBm(power_W: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return 10.0 * np.log10(power_W)  # TODO: is it safe for val<0


def dB_to_factor(value_dB: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    pass  # TODO


def factor_to_dB(value_lin: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    pass


def gts_ticks_to_us(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    TICKS_PER_US = 16
    return gts / TICKS_PER_US


def gts_us_to_ticks(gts: Union[float, np.ndarray]):
    TICKS_PER_US = 16
    return np.int64(np.rint(gts * TICKS_PER_US))


def gts_ticks_to_s(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return gts_ticks_to_us(gts) / 1e6


def gts_s_to_ticks(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return gts_us_to_ticks(gts * 1e6)


# can be used to generate "unavailable" components (e.g. to enable "mixed" plots as in rx_viewer)
def const_nan(src: np.ndarray):
    return np.full(src.shape, np.nan, dtype=np.float16)
