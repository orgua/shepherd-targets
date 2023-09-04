# nRF52 Testable

The app monitors shared GPIO pins and reports via uart upon detection.
This needs a second MCU that toggles these gpio.
Alternatively this FW can change the mode to toggling-behavior.

Other modes:

Print the index of the pin where the edge was detected over UART.
Simultaneously, it waits for incoming messages on the UART.
When receiving an ASCII encoded number between 0 and the number of configured pins,
the app sets the corresponding pin high for ~100us.

Edit the `pins` array and the UART pin definitions at the top of `src/main.c` to reflect your hardware.

## Functionality

Mode 0 (default)

- monitor all shared GPIO and report activity via uart
- NOTE 1: msp-testable is actor (gpio toggle, here mode 1)
- NOTE 2: requires special Header-Inter-connector that only routes pwr, uart tx, programming (pin 1, 2, 10, 13 - 18)
- NOTE 3: 115200 baud datarate

Mode 1

- Startup-Routine 1:
  - toggles LEDs, Pins on the shepherd target-port (without UART-TX), I2C pins, chip-to-chip (C2C) pins
  - blink / switch on each pin individually for 100 ms
- Startup-Routine 2: LEDs
  - switch each LED on for 100ms consecutive
  - (depending on node-id) >=8 repetitions
  - LED0:2 (Target v2.1)

Mode >=2

- UART
    - P0_06 TX, _08 RX (Target v2.1, SDK)
    - listens and answers
    - should report when GPIOs are triggered
- GPIO
    - active: GPIO of shepherd target header (GPIO 0 to 6, 8, BATOK -> map to 0:8)
    - switch on for 100 us after receiving on UART ("(%u)\r\n")
- NOTE: 115200 baud datarate

## Example Output Mode 0

```uart
GPIO WATCHER
9 triggered
10 triggered
11 triggered
0 triggered
1 triggered
2 triggered
3 triggered
4 triggered
5 triggered
6 triggered
7 triggered
8 triggered
12 triggered
13 triggered
14 triggered
15 triggered
16 triggered
17 triggered
18 triggered
19 triggered
Received all 20 shared pins!!
9 triggered
Received all 20 shared pins!!
10 triggered
Received all 20 shared pins!!
11 triggered
Received all 20 shared pins!!
[repeated last 6 lines]
```

## Source

https://github.com/geissdoerfer/shepherd-nrf52-demo
