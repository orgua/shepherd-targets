"""
run this script after compilation (with segger studio), it will

- update the elf-file in this directory
- build hex-files with patched node-id

"""
import os
import shutil
from pathlib import Path
from shepherd_core import fw_tools

# CONFIG

node_count: int = 5
path_local = Path(__file__).parent
path_src = (
    path_local.parent
    / "trafficbench/target/nrf52840/project_ses/Output/Release/Exe/TrafficBench.elf"
)
path_elf = path_local / "build.elf"

# make local copy of elf-file

shutil.copy(path_src, path_elf)

# patch node id and prepare hex-file

for node in range(node_count):
    path_elf_node = path_local / f"build_{node}.elf"

    shutil.copy(path_elf, path_elf_node)
    fw_tools.modify_uid(path_elf_node, node)
    fw_tools.elf_to_hex(path_elf_node)
    os.remove(path_elf_node)
