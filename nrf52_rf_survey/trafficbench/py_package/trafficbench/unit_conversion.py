from typing import Union

import numpy as np

from .constants import TICKS_PER_US


def power_dBm_to_W(power_dBm: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return np.power(10.0, power_dBm * 0.1)


def power_W_to_dBm(power_W: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    # this is safe for power < 0 (gets replaced by .nan)
    return 10.0 * np.log10(power_W)


def dB_to_factor(value_dB: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    pass  # TODO


def factor_to_dB(value_lin: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    pass


def gts_ticks_to_us(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return gts / TICKS_PER_US


def gts_us_to_ticks(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return np.int64(np.rint(gts * TICKS_PER_US))


def gts_ticks_to_s(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return gts_ticks_to_us(gts) / 1e6


def gts_s_to_ticks(gts: Union[float, np.ndarray]) -> Union[float, np.ndarray]:
    return gts_us_to_ticks(gts * 1e6)


# can be used to generate "unavailable" components (e.g. to enable "mixed" plots as in rx_viewer)
def const_nan(src: np.ndarray):
    return np.full(src.shape, np.nan, dtype=np.float16)
