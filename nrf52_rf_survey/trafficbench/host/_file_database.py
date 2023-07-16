from pathlib import Path
from typing import Optional

import tables as tbl

# PyTables format definitions
TrxOperation = tbl.Enum({"RX": 0, "TX": 1})


# PyTables TRX record specification used in outfile (HDF5)
class TrxRecord(tbl.IsDescription):
    ident = tbl.StringCol(40)
    node_id = tbl.UInt16Col(dflt=-1)
    schedule_gts = tbl.UInt32Col()
    schedule_lts = tbl.UInt32Col()
    operation = tbl.EnumCol(TrxOperation, "RX", base="uint8")
    late_start_delay = tbl.UInt16Col()
    tx_delay = tbl.UInt32Col()
    packet_lts = tbl.UInt32Col()
    packet_lts_deviation = tbl.Int16Col()
    end_lts = tbl.UInt32Col()
    packet_content_raw = tbl.StringCol(260 * 2)  # BASE16 encoded (= hex string)
    #   packet_content_raw   = tbl.StringCol(260 * 4 // 3 + 5)    # BASE64 encoded
    #   packet_content_raw   = tbl.StringCol(260)

    class TrxStatus(tbl.IsDescription):
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

    # NOTE:
    # * ident field's primary purpose is to support the human reader when looking for the source of the entry.
    #   The value is unique if the stored substring is long enough to include node_id and schedule_gts.
    # * schedule_gts can be used to find corresponding entries from different nodes.
    # * If datatype of schedule_gts needs to be extended, then use Int64.
    #   Do not use UInt64 because this is not supported in PyTable's in-kernel queries (PyTables 3.6.1).
    #   See <https://www.pytables.org/usersguide/condition_syntax.html#condition-syntax> for details.
    # * RSSI data is stored in the EArray /trx_data/rssi_data. rssi.data_anchor is a pointer into
    #   this array. We do not use a VLArray because the way data is stored in a VLArray does not compress
    #   the real data (only control data. For details, see
    #   <https://www.pytables.org/usersguide/libref/homogenous_storage.html#the-vlarray-class>).


class FileWriter:
    def __init__(self, file_name: Path, num_lines: Optional[int]) -> None:
        """
        see <https://www.pytables.org/usersguide/libref/helper_classes.html#the-filters-class>
        for details regarding compression
        use zlib if you want to use external tools like HDFView
        and blosc if you want it to be fast
          comp_def = tbl.Filters(complevel=0)
          comp_def = tbl.Filters(complevel=1, complib='zlib')

        exemplary compression ratios (achieved in a test example):
            601016 trx_data_uncompressed.h5
            160372 trx_data_zlib1.h5
            134569 trx_data_zlib9.h5
            124825 trx_data_bzip1.h5
            188213 trx_data_blosclz4hc1.h5
            152200 trx_data_blosclz4hc9.h5
            156885 trx_data_blosczlib1.h5
            129184 trx_data_blosczlib9.h5
            144550 trx_data_blosczstd1.h5
            120223 trx_data_blosczstd9.h5

        """

        comp_def = tbl.Filters(complevel=1, complib="blosc:zstd")

        self.h5file = tbl.open_file(file_name.as_posix(), mode="w", title="TRX data")

        group = self.h5file.create_group("/", "trx_data", filters=comp_def)

        self.trx_table = self.h5file.create_table(
            group, "trx", TrxRecord, title="TRX log records", expectedrows=num_lines
        )

        self.rssi_heap = self.h5file.create_earray(
            group,
            "rssi_data",
            atom=tbl.Int8Atom(),
            shape=(0,),
            expectedrows=10000000,
            title="RSSI data heap",
        )
        self.trx_record = self.trx_table.row

    def __del__(self):
        self.h5file.close()
