# Msp430 Testable

The firmware toggles all used GPIOs and depends on a receiver that verifies each pin. 3 LEDs >8 times (reacts to SHEPHERD_NODE_ID) for 100 ms and does the same for the 10 external GPIO (4 times).

## Functionality

- Startup-Routine 1:
  - toggles LEDs, Pins on the shepherd target-port (without UART-TX), I2C pins, Chip2chip (C2C) pins
  - blink / switch on each pin individually for 100 ms
- Startup-Routine 2: LEDs
  - switch each LED on for 100ms consecutive
  - (depending on node-id) >=8 repetitions
  - LED0:2 (Target v2.1)
