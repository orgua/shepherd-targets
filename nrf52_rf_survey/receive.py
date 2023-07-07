import logging
import threading
from pathlib import Path
from time import sleep, time

import sys
import glob
from typing import List

import chromalog
import serial

# CONFIG

duration_s = 60
baud_rate = 230400
log_path = Path(__file__).parent / "traffic.log"


chromalog.basicConfig(format="%(message)s")
logger: logging.Logger = logging.getLogger("Receiver")
logger.setLevel(logging.INFO)
logger.addHandler(logging.NullHandler())


def serial_port_list() -> list:
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports_ = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports_ = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports_ = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port_ in ports_:
        try:
            s = serial.Serial(port_)
            s.close()
            result.append(port_)
        except (OSError, serial.SerialException):
            pass
    return result


def serial_receive(uart_port: str, file_path: Path, duration: int, baudrate: int) -> None:
    file_path = file_path.with_stem(file_path.stem + "_" + uart_port)
    try:
        with serial.Serial(uart_port, baudrate, timeout=0) as uart, open(file_path, "wb") as log:
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


if __name__ == '__main__':
    ports = serial_port_list()
    logger.info("Available Ports: %s (will all be logged)", ports)

    uart_threads: List[threading.Thread] = []
    for port in ports:
        uart_thread = threading.Thread(
                target=serial_receive,
                args=(port, log_path, duration_s, baud_rate,),
                daemon=True,
            )
        uart_thread.start()
        uart_threads.append(uart_thread)

    for uart_thread in uart_threads:
        uart_thread.join()

