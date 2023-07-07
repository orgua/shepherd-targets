import logging
import os
from pathlib import Path

import chromalog

from trafficbench.host.filter_logs import filter_logfile
import tables as tbl

# CONFIG
file_input_stem = "traffic_"
file_input_suffix = ".log"
file_log = "trx.log"
file_h5 = "trx.h5"

chromalog.basicConfig(format="%(message)s")
logger: logging.Logger = logging.getLogger("filter")
logger.setLevel(logging.INFO)
logger.addHandler(logging.NullHandler())


def get_files(start_path: Path, stem: str, suffix: str, recursion_depth: int = 0) -> list:
    if recursion_depth == 0:
        suffix = suffix.lower().split(".")[-1]
    dir_items = os.scandir(start_path)
    recursion_depth += 1
    files = []

    for item in dir_items:
        if item.is_dir():
            files += get_files(item.path, stem, suffix, recursion_depth)
            continue
        else:
            item_name = str(item.name).lower()
            item_ext = item_name.split(".")[-1]
            if item_ext == suffix and item_ext != item_name and stem in item_name:
                files.append(item.path)
            if suffix == "" and item_ext == item_name:
                files.append(item.path)
    if recursion_depth == 1 and len(files) > 0:
        logger.debug(" -> got %s files with the suffix '%s'", len(files), suffix)
    return files


files_in = get_files(Path(__file__).parent, stem=file_input_stem, suffix=file_input_suffix)
with open(file_log, "wb") as outfile:
    pass
for file in files_in:
    with open(file, "rb") as infile, open(file_log, "ab") as outfile:
        filter_logfile(infile, outfile)


# TODO: make these scripts more accessible if possible
# TODO: trx_dump.py does not work with windows!
os.system(f"python ./trafficbench/host/trx_dump.py -o {file_h5} -d dump.log {file_log}")
os.system(f"python ./trafficbench/host/trx_analyze.py {file_h5}")

h5file = tbl.open_file(file_h5, mode="r", title="TRX data")
link_matrix = h5file.root.catalogs.link_matrix_dBm
nodes = h5file.root.catalogs.nodes

print(nodes[:])
print(link_matrix[:])
