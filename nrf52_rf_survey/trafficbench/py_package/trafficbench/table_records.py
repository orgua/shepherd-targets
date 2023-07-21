import numpy as np
import tables as tbl

# PyTables format definitions
TRxOperation = tbl.Enum({"RX": 0, "TX": 1})


class TRXStatus(tbl.IsDescription):
    timeout = tbl.BoolCol()
    header_detected = tbl.BoolCol()
    crc_ok = tbl.BoolCol()
    content_ok = tbl.BoolCol()


class Rssi(tbl.IsDescription):
    end_lts = tbl.UInt32Col()
    num_samples = tbl.UInt32Col(dflt=0)
    data_anchor = tbl.UInt64Col()
    early_readout_detected = tbl.BoolCol()
    late_readout_detected = tbl.BoolCol()
    num_samples_missed = tbl.UInt32Col()


class TRXRecord(tbl.IsDescription):
    """PyTables TRX record specification used in outfile (HDF5)

    NOTE:
    * ident field's primary purpose is to support the human reader when looking for the source of the entry.
      The value is unique if the stored substring is long enough to include node_id and schedule_gts.
    * schedule_gts can be used to find corresponding entries from different nodes.
    * If datatype of schedule_gts needs to be extended, then use Int64.
      Do not use UInt64 because this is not supported in PyTable's in-kernel queries (PyTables 3.6.1).
      See <https://www.pytables.org/usersguide/condition_syntax.html#condition-syntax> for details.
    * RSSI data is stored in the EArray /trx_data/rssi_data. rssi.data_anchor is a pointer into
      this array. We do not use a VLArray because the way data is stored in a VLArray does not compress
      the real data (only control data. For details, see
      <https://www.pytables.org/usersguide/libref/homogenous_storage.html#the-vlarray-class>).
    """

    ident = tbl.StringCol(40)
    node_id = tbl.UInt16Col(dflt=-1)
    schedule_gts = tbl.UInt32Col()
    schedule_lts = tbl.UInt32Col()
    operation = tbl.EnumCol(TRxOperation, "RX", base="uint8")
    late_start_delay = tbl.UInt16Col()
    tx_delay = tbl.UInt32Col()
    packet_lts = tbl.UInt32Col()
    packet_lts_deviation = tbl.Int16Col()
    end_lts = tbl.UInt32Col()
    packet_content_raw = tbl.StringCol(260 * 2)  # BASE16 encoded (= hex string)
    #   packet_content_raw   = tbl.StringCol(260 * 4 // 3 + 5)    # BASE64 encoded
    #   packet_content_raw   = tbl.StringCol(260)

    trx_status = TRXStatus()
    rssi = Rssi()


SourceUncertainty = tbl.Enum({"EXTERNAL": 0, "WEAK": 1, "STRONG": 2})


class RxInfoRecord(tbl.IsDescription):
    """
    NOTE:
    * The combination of schedule_gts and (source_/destination_)node_id
      is a unique identifier for corresponding TRX entries.
    * We do not use subclasses (e.g. for markers) because members of
      subclasses cannot be directly evaluated in where() clauses.
    * Power values are stored in dBm, which is typically preferred
      (when formulating queries or manually inspecting results).
      In addition, some values are also stored with linear scaling (in mW)
      to avoid unnecessary conversion steps and accompanying accuracy losses.
    """

    schedule_gts = tbl.UInt32Col(dflt=-1, pos=0)
    source_node_id = tbl.Int16Col(dflt=-1, pos=1)
    destination_node_id = tbl.Int16Col(dflt=-1, pos=2)

    rssi_sum = tbl.Float32Col(dflt=np.nan)  # in dBm
    rssi_sum_min = tbl.Float32Col(dflt=np.nan)  # in dBm
    rssi_sum_max = tbl.Float32Col(dflt=np.nan)  # in dBm
    rssi_noise = tbl.Float32Col(dflt=np.nan)  # in dBm

    P_sigint = tbl.Float32Col(dflt=np.nan)
    P_sigint_dBm = tbl.Float32Col(dflt=np.nan)
    P_sigint_link_dBm = tbl.Float32Col(dflt=np.nan)
    SNR_dB = tbl.Float32Col(dflt=np.nan)
    SNR_min_dB = tbl.Float32Col(dflt=np.nan)
    SNR_max_dB = tbl.Float32Col(dflt=np.nan)
    SINR_link_dB = tbl.Float32Col(dflt=np.nan)

    # markers
    is_link_measurement = tbl.BoolCol(dflt=False)
    num_transmitters = tbl.Int16Col(dflt=-1)
    # ⤷ alternative: enum NONE / SINGLE / MULTIPLE
    ambiguous_source = tbl.StringCol(2)
    source_uncertainty = tbl.EnumCol(SourceUncertainty, "EXTERNAL", base="uint8")

    # ranges determined by split_rssi()
    rssi_range_noise1_begin = tbl.UInt32Col(dflt=-1)
    rssi_range_noise1_len = tbl.Int32Col(dflt=0)
    rssi_range_noise2_begin = tbl.UInt32Col(dflt=-1)
    rssi_range_noise2_len = tbl.Int32Col(dflt=0)
    rssi_range_sum_begin = tbl.UInt32Col(dflt=-1)
    rssi_range_sum_len = tbl.Int32Col(dflt=0)

    # oscillator frequency drift between transmitter and receiver
    osc_drift_ppm_min = tbl.Float32Col(dflt=np.nan)
    osc_drift_ppm_max = tbl.Float32Col(dflt=np.nan)
    osc_drift_num_periods_min = tbl.Float32Col(dflt=np.nan)
    osc_drift_num_periods_max = tbl.Float32Col(dflt=np.nan)


class ScheduleRecord(tbl.IsDescription):
    schedule_gts = tbl.UInt32Col(pos=0)
    num_nodes = tbl.UInt16Col(pos=1)
    num_transmitters = tbl.UInt16Col(pos=2)


class MarkerRecord(tbl.IsDescription):
    schedule_gts = tbl.UInt32Col(dflt=-1, pos=0)
    node_id = tbl.Int16Col(dflt=-1, pos=1)
    expression_value = tbl.Float64Col(dflt=np.nan)
