import glob
import sys
from pathlib import Path
from time import sleep
from time import time

import serial

from ._logger import logger


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
        raise EnvironmentError("Unsupported platform")

    result = []
    for port_ in ports_:
        try:
            s = serial.Serial(port_)
            s.close()
            result.append(port_)
        except (OSError, serial.SerialException):
            pass
    return result


def serial_receive(
    uart_port: str, file_path: Path, duration: int, baudrate: int
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
