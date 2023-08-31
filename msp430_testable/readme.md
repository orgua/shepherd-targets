# Msp430 Testable

The firmware toggles all 3 LEDs >8 times (reacts to SHEPHERD_NODE_ID) for 100 ms and does the same for the 10 external GPIO (4 times).

## Functionality

- Startup-Routine 1: LEDs
  - blink / switch each LED consecutive
  - 100 ms on each
  - (depending on node-id) >=8 repetitions
  - LED0:2 (Target v2.1)
- Startup-Routine 2: Header GPIO
  - switch each on for 100ms consecutive
  - 4 repetitions
  - GPIO0:9 (Target v2.1)
