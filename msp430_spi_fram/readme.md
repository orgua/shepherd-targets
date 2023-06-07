# MSP430 as SPI-FRAM (non-volatile memory)

The code in this repository turns an MSP430FR5962 microcontrollers into a general purpose non-volatile memory controlled via SPI.

The MSP430FR59XX series of microcontrollers come with on-board ferroelectric RAM (FRAM). In contrast to SRAM, this memory is non-volatile, i.e. it keeps its state without requiring periodic refreshs and without requiring a power supply. In contrast to flash memory, which must be erased before being written, FRAM can be treated just like SRAM and writing consumes very little energy.

## Building

To build the code, you'll need the gcc toolchain for the MSP430 microcontroller series. Refer to [the GitHub workflow](../.github/workflows/build_msp.yml) for how to install the toolchain and build the project.

## Interface

The firmware in this repository exposes a 4-wire SPI interface that allows reading and writing data to the on-board FRAM.
The SPI interface uses mode 0 (Clock low when inactive, data sampled on leading edge) and supports a frequency of 8MHz.

After the SPI controller pulls the CS line low, the peripheral (this firmware) sets up an initial transfer of 3 control bytes.
These three control bytes contain the 20-bit target address of the memory access and the type of operation (R/W).
The address is transferred lowest byte first.
If the highest bit of the third address byte is set, the operation is a write operation, otherwise it is a read operation.
After receiving the three command bytes, the peripheral will setup the corresponding DMA transfer and wait in a low power mode until the CS line goes high.
The controller shall keep the CS line low until the transfer has finished.
Upon this rising edge, the peripheral stops the transfer and transitions to low power mode again.

Transfers can have a maximum size of 65535 bytes.

## Timing requirements

The time from the falling edge of the CS line until the transmission of the first command byte must be at least 15us.
The time from the transmission of the last command byte to the transmission of the first data byte must be at least 25us.
The time from the rising edge of the CS line until the next falling edge of the CS line must be at least 10us.

## Memory map

The MSP430FR5962 has a total of 128kB FRAM.
Unfortunately, the interrupt vector table lives in the middle of this memory so the 128kB cannot be used contiguosly. Instead they are separated into two regions.
The lower region starts at 0x4000 and ends at 0xFF80 where the IVT lives.
The upper region starts at 0xFFFF and ends at 0x24000.
The code/data for this firmware also has to be placed within this area.
The linker script in this repository defines a dedicated section for the code and data of the firmware ranging from 0x4000 to 0x6000.

The remaining memory area from 0x6000 to 0x24000, excluding the IVT (0xFF80-0xFFFF) is available as data storage.
For an external application talking to the device over SPI, this memory gets mapped to 0x0000 to 0x1E000.
The firmware will protect the IVT from access.
Any operation extending over the IVT region or the end of the memory will get truncated without the controller noticing.

**The code on the SPI controller talking to this firmware must avoid reading/writing to the IVT region, which lies between 0x9F80 and 0x9FFF from its view.**

## Source

https://github.com/NessieCircuits/Riotee_MSP430Fram
