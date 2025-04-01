# Msp430 Testable

This is the companion-firmware for `/nrf_testable` to verify the hardware.
The firmware toggles all used & shared GPIOs and depends on a receiver / supervisor that verifies each pin.

Sequence:

- LEDs go first
- all pins of GPIO-Header
- shared I2C-Pins
- shared C2C-Pins (SPI)
- blink LEDs >8 times (reacts to SHEPHERD_NODE_ID) for 100 ms

## Functionality

- Startup-Routine 1:
  - toggles LEDs, Pins on the shepherd target-port (without UART-TX), I2C pins, Chip2chip (C2C) pins
  - blink / switch on each pin individually for 100 ms
- Startup-Routine 2: LEDs
  - switch each LED on for 100ms consecutive
  - (depending on node-id) >=8 repetitions
  - LED0:2 (Target v2.1)
