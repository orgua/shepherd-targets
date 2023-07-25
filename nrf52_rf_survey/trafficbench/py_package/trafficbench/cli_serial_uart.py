import glob
import sys
import threading
from pathlib import Path
from time import sleep
from time import time
from typing import Annotated
from typing import List
from typing import Optional

import serial
import typer

from .cli_proto import app
from .logger import logger


def serial_port_list() -> list:
    """Lists serial port names

    :raises EnvironmentError:
        On unsupported or unknown platforms
    :returns:
        A list of the serial ports available on the system
    """
    if sys.platform.startswith("win"):
        ports_ = ["COM%s" % (i + 1) for i in range(256)]
    elif sys.platform.startswith("linux") or sys.platform.startswith("cygwin"):
        # this excludes your current terminal "/dev/tty"
        ports_ = glob.glob("/dev/tty[A-Za-z]*")
    elif sys.platform.startswith("darwin"):
        ports_ = glob.glob("/dev/tty.*")
    else:
        raise OSError("Unsupported platform")

    result = []
    for port_ in ports_:
        try:
            s = serial.Serial(port_)
            s.close()
            result.append(port_)
        except (OSError, serial.SerialException):
            pass
    return result


def receive_serial_thread(
    file_path: Path,
    uart_port: str,
    duration: int,
    baudrate: int,
) -> None:
    file_path = file_path.with_stem(file_path.stem + "_" + uart_port)
    try:
        with serial.Serial(uart_port, baudrate, timeout=0) as uart, open(
            file_path, "wb"
        ) as log:
            time_end = time() + duration
            logger.info("started logging for %s", uart_port)
            while time() < time_end:
                output = uart.read(uart.in_waiting)
                log.write(output)
                sleep(0.1)

    except ValueError as e:
        logger.error(  # noqa: G200
            "[UartMonitor] PySerial ValueError '%s' - "
            "couldn't configure serial-port '%s' "
            "with baudrate=%d -> will not be logged",
            e,
            uart_port,
            baudrate,
        )

    except serial.SerialException as e:
        logger.error(  # noqa: G200
            "[UartMonitor] pySerial SerialException '%s - "
            "Couldn't open Serial-Port '%s' to target -> will not be logged",
            e,
            uart_port,
        )
    logger.debug("[UartMonitor] ended itself")


receive_h = {
    # NOTE: used as long as typer can't read this from fn-docstring
    # https://github.com/tiangolo/typer/pull/436
    "fp": "Directory or file-name (will add port to stem)",
    "sp": "will capture every port when omitted",
    "du": "how long to capture",
    "br": "of serial port",
}


@app.command("receive")
def receive_serial(
    file_path: Annotated[Path, typer.Argument(help=receive_h["fp"])],
    serial_ports: Annotated[
        Optional[List[str]], typer.Option(help=receive_h["sp"])
    ] = None,
    duration_s: Annotated[int, typer.Option(help=receive_h["du"])] = 600,
    baud_rate: Annotated[int, typer.Option(help=receive_h["br"], min=9_600)] = 230_400,
) -> None:
    """collect logs from trafficbench-nodes (uart -> .log)"""
    if isinstance(file_path, Path) and file_path.is_dir():
        file_path = file_path / "trafficbench.log"

    if serial_ports is None:
        serial_ports = serial_port_list()
    if isinstance(serial_ports, str):
        serial_ports = [serial_ports]

    logger.info("Receiving Ports: %s", serial_ports)

    uart_threads: List[threading.Thread] = []
    for port in serial_ports:
        uart_thread = threading.Thread(
            target=receive_serial_thread,
            args=(
                file_path,
                port,
                duration_s,
                baud_rate,
            ),
            daemon=True,
        )
        uart_thread.start()
        uart_threads.append(uart_thread)

    for uart_thread in uart_threads:
        uart_thread.join()
