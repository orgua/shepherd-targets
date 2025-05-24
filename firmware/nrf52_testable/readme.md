# nRF52 Testable

The app monitors shared GPIO pins and reports via uart upon detection.
This needs a second MCU that toggles these gpio (companion-firmware `/msp430_testable`).
Alternatively this FW can change the mode to toggling-behavior.

Other modes:

Print the index of the pin where the edge was detected over UART.
Simultaneously, it waits for incoming messages on the UART.
When receiving an ASCII encoded number between 0 and the number of configured pins,
the app sets the corresponding pin high for ~100us.

Edit the `pins` array and the UART pin definitions at the top of `src/main.c` to reflect your hardware.

## Functionality

### Mode 0 - Supervisor (default)

- monitor all shared GPIO and report activity via uart
- msp-testable-firmware is actor (gpio toggle, here mode 1)
- NOTE: requires special Header-Inter-connector that only routes pwr, uart tx, programming (pin 1, 2, 10, 13 - 18)
- NOTE 3: 115200 baud datarate

### Mode 1 - Actor

- Startup-Routine 1:
  - toggles LEDs, Pins on the shepherd target-port (without UART-TX), I2C pins, chip-to-chip (C2C) pins
  - blink / switch on each pin individually for 100 ms
- Startup-Routine 2: LEDs
  - switch each LED on for 100ms consecutive
  - (depending on node-id) >=8 repetitions
  - LED0:2 (Target v2.1)

### Mode >=2

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
GPIO WATCHER (31 pins)
               56
0              56
               56
 1             56
               56
  2            56
               56
   3           56
               56
    4          56
               56
     5         56
               56
      6        56
               56
       7       56
               56
        8      56
               56
         9     56
               56
          0    56
               56
           1   56
               56
            2  56
               56
             3 56
               56
              456
               56
               567
               56
               56 8
               56
               56  9
               56
               56   0
               56
               56    1
               56
               56     2
               56
               56      3
               56
               56       4
               56
               56        5
               56
               56         6
               56
               56          7
               56
               56           8
               56
               56            9
               56
               56             0
Received all 31 shared pins!!
```

## Source

https://github.com/geissdoerfer/shepherd-nrf52-demo
