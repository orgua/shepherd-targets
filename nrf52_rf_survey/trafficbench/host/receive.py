import threading
from pathlib import Path
from typing import List

from ._logger import logger
from ._serial import serial_port_list
from ._serial import serial_receive

# CONFIG, TODO: CLI

duration_s = 60
baud_rate = 230400
log_path = Path(__file__).parent / "traffic.log"


if __name__ == "__main__":
    ports = serial_port_list()
    logger.info("Available Ports: %s (will all be logged)", ports)

    uart_threads: List[threading.Thread] = []
    for port in ports:
        uart_thread = threading.Thread(
            target=serial_receive,
            args=(
                port,
                log_path,
                duration_s,
                baud_rate,
            ),
            daemon=True,
        )
        uart_thread.start()
        uart_threads.append(uart_thread)

    for uart_thread in uart_threads:
        uart_thread.join()
