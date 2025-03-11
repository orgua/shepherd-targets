# PCBs and other hardware

This directory contains all files to manufacture hardware:

- schematic
- PCB-renderings (end of schematic pdfs)
- gerber for pcb manufacturing
- BOM to order parts
- pick and place and assembly drawings for PCB assembly

## nRF52 & MSP430 FRAM Target

- V1.0 was the initial target used by the testbed
- ~~V1.1 was designed, but is not yet manufactured~~
- ~~V1.2 was designed and tested - discarded because of manufacturing problems~~
- V1.3 is being deployed ATM
- V1.3e will accompany the base-version and will hopefully reduce failure-rate of msp430 

## Adapters

- debug-board for target v1.3 that can sit between cape and target and breaks out all GPIO to 0.1" header
- converter for cape v2.4 header to target v1.3 edge-connector
