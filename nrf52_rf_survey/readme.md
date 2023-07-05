# nRF using TrafficBench to survey the rf-conditions for the testbed

Trafficbench is configured to let each node send a packet. The other nodes listen automatically and try to capture the packet and also record the P_Rx. 

Current configuration 

- each node sends ~ 34 bytes via 1 MBit Bluetooth (~300 us) 
- the other nodes listen and capture for 5 ms (+ 500 us pre- & post-delay)
- sleep 1 s before next node begins
- repeat loop indefinitely

## Installation 

- adapt schedule with the [schedule-builder-script](/schedule_builder/build.py)
- compiling: follow the [readme](/trafficbench/README.md) of trafficbench 

## Usage

- patch SHEPHERD_NODE_ID in elf-file for each node
- run on testbed
- postprocessing, TODO
- NOTE: first loop-cycle should be discarded
 

## TODO:

- factor in TRX_PRE_DELAY and _POST_DELAY
- adapt uart-speed
- change GPI to use correct uart-pins
- look for other IO used by TB
- py: filter_log.py
- speed up loop
  - 1 ms tx-delay
  - 3 ms tx-timeout
  - 15 - 50 ms sleep


## Source

https://gitlab.com/nes-lab/trafficbench
