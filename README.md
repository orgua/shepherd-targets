# shepherd-targets

A collection of target-hardware and mcu-firmwares used by the shepherd-testbed.

## nRF52 with msp430 as FRAM

Hardware

- nRF52840 (Panasonic PAN1780)
- MSP430FR5962 (TI)


### nRF52-Firmwares

- [nrf52_demo_rf](/nrf52_demo_rf): demo implementation for a simple node that sends BLE packets when energy budget allows it
- nrf52_spi_radio: default implementation to use nRF as a radio frontend
- [nrf52_testable](/nrf52_testable): blinks LEDs on boot and listens/answers to UART (verification after assembly)
- [nrf52_rf_survey](/nrf52_rf_survey): Link Matrix Generator - TX-Unit - sends packet with every possible P_TX, loops until stopped
- [nrf52_deep_sleep](/nrf52_deep_sleep): practically turned off MCU with the lowest possible consumption

### MSP430FR-Firmwares

- [msp430_deep_sleep](/msp430_deep_sleep): practically turned off MCU with the lowest possible consumption
- [msp430_spi_fram](/msp430_spi_fram): [riotee](https://github.com/NessieCircuits/Riotee_MSP430Fram) implementation to use MSP as a flash storage
- [msp430_testable](/msp430_testable): blinks LEDs on boot and listens/answers to UART (verification after assembly)

- TODO: cleanup-fw - FRAM & program-storage should be wiped between runs

## Getting started

### nRF52

- Make sure you have the [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) installed
- If `arm-none-eabi-gcc` is not in your path, set the environment variable `GNU_INSTALL_ROOT` accordingly, e.g.: `export GNU_INSTALL_ROOT=/opt/toolchain/` (note the trailing foreslash)
- Download the nRF5 SDK from [here.](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download "here.") (You don't need a SoftDevice) and extract it
- Set the environment variables `SDK_ROOT` to the corresponding absolute path, e.g.: `export SDK_ROOT=/home/user/nRF5_SDK_17.0.2_d674dde/`
- run `make`

Refer to [the GitHub workflow](../.github/workflows/build_nrf.yml) for how to install the toolchain and build the project.

### MSP430

To build the code, you'll need the gcc toolchain for the MSP430 microcontroller series. Refer to [the GitHub workflow](../.github/workflows/build_msp.yml) for how to install the toolchain and build the project.

### Controlling the Node-ID

When an elf-firmware contains a ``SHEPHERD_NODE_ID`` the variable will patched with the actual target-ID before running the experiment. See the proposed [c-file](/nrf52_demo_rf/src/shepherd_node_id.c) for more information.
