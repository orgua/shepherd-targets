# Msp430 Testable

The firmware toggles all 3 LEDs 16 times for 100 ms and does the same for the 10 external GPIO (4 times).

## Functionality

- LEDs
    - blink / switch all 3 in a row, 16x repetitions at startup
    - 100 ms on / 100 ms off
- GPIO
    - active: (GPIO 0 to 8)
    - switch on for 100 ms, all in a row, 4 repetitions after LEDs
