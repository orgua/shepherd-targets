"""
script searches for .log-files in this folder and analyzes them
Log-Files contain the uart-output of the trafficbench-nodes
"""
from pathlib import Path

import tables as tbl
from trafficbench import analyze_trx
from trafficbench import dump_trx
from trafficbench import filter_logfile

# Config
files_input = Path(__file__).parent
file_b64 = Path("trx.b64")
file_h5 = Path("trx.h5")

# Process
filter_logfile(files_input, file_b64)
dump_trx(file_b64, file_h5)
analyze_trx(file_h5)

# Extract data
h5file = tbl.open_file(file_h5.as_posix(), mode="r", title="TRX data")

if False:
    nodes = h5file.root.catalogs.nodes
    print(nodes[:])

if True:
    link_matrix = h5file.root.catalogs.link_matrix_dBm
    print(link_matrix[:])
