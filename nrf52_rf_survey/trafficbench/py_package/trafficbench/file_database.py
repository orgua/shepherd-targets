from pathlib import Path
from typing import Optional

import tables as tbl

from .table_records import TRXRecord


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
            group, "trx", TRXRecord, title="TRX log records", expectedrows=num_lines
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
