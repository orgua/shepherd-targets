# nRF using TrafficBench to survey the rf-conditions for the testbed

Trafficbench is configured to let each node send a packet. The other nodes listen automatically and try to capture the packet and also record the P_Rx.

Current configuration

- loop - one node after the other talks - the others listen
- each node sends ~ 34 bytes via 1 MBit Bluetooth (~300 us airtime), PTx = 0 dBm
- the other nodes listen and capture for 5 ms (+ 500 us pre- & post-delay)
- sleep 1 s before next node begins

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
- transformed py-scripts to be more accessible

specially for shepherd

- reduced uart-speed to 115_200 for now (in config.h)
- disable flow control (readme warns about it) to just stream uart (`mode=0` in config.h)
- disable button press to start (section removed in main.c)
- deactivate DEBUG_GPIO in `radio.c`
- current GPI modifications
  - reformatted with projects clang-format
  - use `GPI_ARCH_BOARD_TUDNES_SHEPHERD_NRF52840FRAM_V13` as `GPI_ARCH_PLATFORM` in `trafficbench/config.h`
  - added `#include "gpi/arm/nordic/nrf528xx/platform_internal.h"` in `trafficbench/target/nrf52840/radio_queues_custom.h` to add back macros for trafficbench
  - added `#define LED_SYNC GPI_LED_0` for our target `#elif GPI_ARCH_IS_BOARD(TUDNES_SHEPHERD_NRF52840FRAM_V13)` in `trafficbench/scheduler.c`

## Usage on the testbed

on server - prereq:

```shell
cd ~
git clone https://github.com/nes-lab/shepherd-tools
cd shepherd-tools/extr

python3 gen_energy_envs.py
python3 gen_firmwares.py
python3 gen_rf_survey.py
# current firmware is now in /var/shepherd/content/fw/, accessible by all observers
# task is also accessible for all observers, but in our case we send it out via herd-tool
```

for the actual run:
```Shell
shepherd-herd -v run -a /var/shepherd/content/task/nes_lab/tasks_rf_survey.yaml
# this takes ~ 8min and will exit after. Then we collect the data
scp
```

scp /var/shepherd/recordings/

## TODO:

- vary send-power (?)
- look for other IO used by TB
  - gpi_button_read() in main.c
  - gpi_led_toggle() in main.c
  - gpi_led_on() & gpi_led_off() in scheduler.c
  - LED_SYNC, GPI_LED_2
  - GPI_BUTTON_SIG1, GPI_BUTTON_1
- py:
  - filter_log.py and more
  - make code usable by other py-code
  - modularize + make testable
- speed up loop
  - 1 ms tx-delay
  - 3 ms tx-timeout
  - 15 - 50 ms sleep
  - factor in TRX_PRE_DELAY and _POST_DELAY
- packet-content: all random data might improve prx-consistency

## Source

https://gitlab.com/nes-lab/trafficbench
