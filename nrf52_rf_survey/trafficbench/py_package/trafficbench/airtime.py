from typing import Union

import numpy as np

from .constants import TICKS_PER_US


def get_packet_airtime(pdu_crc_length: Union[int, float, np.nditer]) -> Union[int, float, np.nditer]:
    """
    compute nominal packet airtime
    TODO: make it dependent from radio mode

    field lengths:	PREAMBLE	ADDRESS		CI		TERM1		PDU			CRC		TERM2
    always [bit]:				 32							(2...258)*8		24
    1M:				 8, 8us		 32us		0		0						 24us	0
    2M:				16, 8us		 16us		0		0						 12us	0
    125k:			80,80us		256us		2,16us	3,24us					192us	3,24us
    500k:			80,80us		256us		2,16us	3,24us					 48us	3, 6us

    PDU:			S0			LENGTH		S1		PAYLOAD
    always [bit]:	8			8			0		(0...255)*8

    switch (gpi_radio_get_mode())
      case BLE_1M: airtime = GPI_TICK_US_TO_FAST( 8 +  32 +  0 +  0 +  16 +  24 +  0) +
                            (GPI_TICK_US_TO_FAST(8) * payload_length)
      case BLE_2M: airtime = GPI_TICK_US_TO_FAST( 8 +  16 +  0 +  0 +   8 +  12 +  0) +
                            GPI_TICK_US_TO_FAST(4) * payload_length)
      case BLE_125k: airtime = GPI_TICK_US_TO_FAST(80 + 256 + 16 + 24 + 128 + 192 + 24) +
                            (GPI_TICK_US_TO_FAST(64) * payload_length)
      case BLE_500k: airtime = GPI_TICK_US_TO_FAST(80 + 256 + 16 + 24 +  32 +  48 +  6) +
                            (GPI_TICK_US_TO_FAST(16) * payload_length)

    :param pdu_crc_length:
    :return:
    """
    us = 8 + 32 + 0 + 0 + 0 + (8 * pdu_crc_length)
    return us * TICKS_PER_US


def get_ref_delay() -> float:
    """
    # TODO: make it dependent from radio mode
    :return:
    """
    us = 8 + 32
    return us * TICKS_PER_US
