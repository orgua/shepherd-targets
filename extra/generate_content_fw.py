"""
script will:
- generate embedded firmware-models
- it assumes sub-dirs in the same dir with ./build.elf in it
- works together with .github/workflows/release_files.yml
"""
from pathlib import Path
from typing import Dict

from shepherd_core.data_models.content.firmware import Firmware
from shepherd_core.logger import logger

if __name__ == "__main__":

    firmwares: Dict[str, str] = {
        "msp430_deep_sleep": "practically turned off MCU with the lowest possible consumption",
        "msp430_spi_fram": "riotee implementation to use MSP as a flash storage",
        "msp430_testable": "blinks LEDs on boot and listens/answers to UART (verification after assembly)",
        "nrf52_demo_rf": "A simple demo that sends BLE packets when energy budget allows it",
        "nrf52_testable": "blinks LEDs on boot and listens/answers to UART (verification after assembly)",
        "nrf52_deep_sleep": "practically turned off MCU with the lowest possible consumption",
        "nrf52_rf_survey": "Link Matrix Generator - TX-Unit - sends packet with every possible P_TX, loops until stopped",
    }
    path_here = Path(__file__).parent.absolute()

    for _fw, _descr in firmwares.items():

        path_fw = path_here/_fw/"build.elf"
        if path_fw.exists():
            Firmware.from_firmware(
                file=path_fw,
                name=_fw,
                description=_descr,
                owner="Ingmar",
                group="NES Lab",
                visible2group=True,
                visible2all=True,
            ).to_file(path_here/_fw)
        else:
            logger.error("FW not found, will skip: %s", path_fw.name)
