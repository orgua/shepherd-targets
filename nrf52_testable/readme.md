# nRF52 Testable

The app monitors up to eight GPIO pins for rising edges and upon detection prints the index of the pin where the edge was detected over UART. Simultaneously, it waits for incoming messages on the UART. When receiving an ASCII encoded number between 0 and the number of configured pins, the app sets the corresponding pin high for ~100us.

Edit the `pins` array and the UART pin definitions at the top of `src/main.c` to reflect your hardware.

# Functionality

- LEDs
    - blink / switch 10x at startup
    - 50 ms on / 150 ms off
    - P0_13, _14 (Target v2.1)
- UART
    - P0_06 TX, _08 RX (Target v2.1, SDK)
    - listens and answers
    - should report when GPIOs are triggered
- GPIO
    - active: P0_20 - P0_25 (GPIO 0 to 5)
    - switch on for 100 us after receiving on UART ("(%u)\r\n")

## Source

https://github.com/geissdoerfer/shepherd-nrf52-demo
