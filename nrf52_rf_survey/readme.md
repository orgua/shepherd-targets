# nRF using TrafficBench to survey the rf-conditions for the testbed

Trafficbench is configured to let each node send a packet. The other nodes listen automatically and try to capture the packet and also record the P_Rx.

Current configuration

- each node sends ~ 34 bytes via 1 MBit Bluetooth (~300 us)
- the other nodes listen and capture for 5 ms (+ 500 us pre- & post-delay)
- sleep 1 s before next node begins
- repeat loop indefinitely

## Installation

- adapt schedule with the [schedule-builder-script](./schedule_builder/build.py)
- compiling: follow the [readme](./trafficbench/README.md) of trafficbench
  - newest studio version (tested with v7.30) is fine
  - extra package needed (and restart studio after install) - should be automatic: CMSIS 5 5 CMSIS-CORE Support Package

## Usage of ELF

- patch SHEPHERD_NODE_ID in elf-file for each node (see [example python script](./_build/update_and_patch.py))
- run on testbed
- postprocessing, TODO
- NOTE: first loop-cycle should be discarded

## Changes compared to vanilla trafficbench

- change testbed: flocklab -> shepherd
- correct spelling
- fix formatting
- fix for sensitivity to include-order: added #include "traffic_bench.h" in cbor.h
- removed node-id-magic in main.c (line 154:217)

## TODO:

- adapt uart-speed
- change GPI to use correct uart-pins
- look for other IO used by TB
  - gpi_button_read() in main.c
  - gpi_led_toggle() in main.c
  - gpi_led_on() & gpi_led_off() in scheduler.c
  - LED_SYNC, GPI_LED_2
  - GPI_BUTTON_SIG1, GPI_BUTTON_1
- py: filter_log.py
- speed up loop
  - 1 ms tx-delay
  - 3 ms tx-timeout
  - 15 - 50 ms sleep
  - factor in TRX_PRE_DELAY and _POST_DELAY
- packet-content: all random data might improve prx-consistency

## Source

https://gitlab.com/nes-lab/trafficbench
