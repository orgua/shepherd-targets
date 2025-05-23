# nRF52 & MSP430 FRAM Target V1.1

- not yet manufactured / skipped
- changes to V1.0 are minimal, so the [documentation from there](https://github.com/nes-lab/shepherd-targets/tree/main/hardware/shepherd_nRF_FRAM_Target_v1.0) can be used

## Bugs, Changes, Improvements

### Changes & Improvements

see v1.0 document.

### Bugs

- rf-performance mediocre
- no compat to riotee-sdk
- skipped for v1.2

### Proposed Fixes & Improvements

- two bat-status pins from cape would be better
  - goal: offer hysteresis - working good for riotee so far
  - second goal: compatibility with riotee-SDK for targets
- shared gpio would benefit from external PU/PD-Resistors, so current mcu-code can be more independent
  - problem: msp430 is reacting with high currents for floating pins
  - current solution: activate internal PD-Res in msp430 - at least for our sleep- & FRAM-firmware
- add a system to identify pcb? OW-nodeid or i2c-rom?
- ditch PAN1780 module to allow an external antenna (rf-performance of pan-module is sub-par)

-> will be implemented in [v1.2](https://github.com/nes-lab/shepherd-targets/tree/main/hardware/shepherd_nRF_FRAM_Target_v1.2)
