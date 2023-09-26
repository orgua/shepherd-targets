# nRF52 & MSP430 FRAM Target V1.1

- not yet manufactured
- changes to V1.0 are minimal, so the [documentation from there](https://github.com/orgua/shepherd-targets/tree/main/hardware/shepherd_nRF_FRAM_Target_v1.0) can be used

## Bugs, Changes, Improvements

### v1.1

- two bat-status pins from cape would be better
  - goal: offer hysteresis - working good for riotee so far
  - second goal: compatibility with riotee-SDK for targets
- shared gpio would benefit from external PU/PD-Resistors, so current mcu-code can be more independent
  - problem: msp430 is reacting with high currents for floating pins
  - current solution: activate internal PD-Res in msp430 - at least for our sleep- & FRAM-firmware
- add a system to identify pcb? OW-nodeid or i2c-rom?
