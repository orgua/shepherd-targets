# Msp430 Testable

The firmware toggles all 3 LEDs 16 times for 100 ms and does the same for the 10 external GPIO (4 times).

# Functionality

- LEDs
    - blink / switch on 16x at startup
    - 100 ms on / 100 ms off
- GPIO
    - active: P0_20 - P0_25 (GPIO 0 to 5)
    - switch on for 100 us after receiving on UART ("(%u)\r\n")
