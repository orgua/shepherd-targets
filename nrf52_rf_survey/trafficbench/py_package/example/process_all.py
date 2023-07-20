import os
from pathlib import Path

import tables as tbl
from trafficbench import filter_logfile, dump_trx, analyze_trx

# CONFIG
files_input = Path(__file__).parent
# file_input_suffix = ".log"
file_b64 = Path("trx.b64")
file_h5 = Path("trx.h5")


filter_logfile(files_input, file_b64)
dump_trx(file_b64, file_h5)
analyze_trx(file_h5)
# TODO: trx_dump.py does not work with windows!

h5file = tbl.open_file(file_h5, mode="r", title="TRX data")
link_matrix = h5file.root.catalogs.link_matrix_dBm
nodes = h5file.root.catalogs.nodes

print(nodes[:])
print(link_matrix[:])
