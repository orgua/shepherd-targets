"""
Log-Files contain the uart-output of the trafficbench-nodes
"""
from pathlib import Path

from trafficbench import receive_serial

# CONFIG
duration_s = 60
baud_rate = 230400
files_log = Path(__file__).parent


receive_serial(files_log, None, duration_s, baud_rate)
