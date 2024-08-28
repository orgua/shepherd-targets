# nRF52 & MSP430 FRAM Target V1.3

Shared pins between MCUs and Observer, **hypothetical Cape V2.6 (not produced yet)**.
The testbed still used Cape v2.4 as of 2024-08.

| SHP-V26  | Dir   | Riotee   | nRF52  | msp430  | Description                 |
|----------|-------|----------|--------|---------|-----------------------------|
| GPIO0    | TBD   | GPIO.0   | P0.21  | P2.6    | UART Target-RX, msp.A1.CiPo |
| GPIO1    | TBD   | GPIO.1   | P0.08  | P2.5    | UART Target-TX, msp.A1.CoPi |
| GPIO2    | TBD   | GPIO.2   | P0.04  | P2.3    | msp.A1.PSel                 |
| GPIO3    | TBD   | GPIO.3   | P0.05  | P2.4    | msp.A1.CLK                  |
| GPIO4    | TBD   | GPIO.4   | P1.09  | P4.6    |                             |
| GPIO5    | TBD   | GPIO.5   | P0.26  | P3.6    |                             |
| GPIO6    | TBD   | GPIO.6   | P1.03  | PJ.6    |                             |
| GPIO7    | TBD   | GPIO.7   | P0.11  | P5.3    | msp.B1.PSel                 |
| GPIO8    | TBD   | GPIO.8   | P0.13  | P5.2    | msp.B1.CLK                  |
| GPIO9    | TBD   | GPIO.9   | P0.16  | P5.1    | msp.B1.CiPo                 |
| GPIO10   | TBD   | -        | P0.12  | P5.0    | msp.B1.CoPi, SDA            |
| GPIO11   | TBD   | -        | P0.10  | P6.0    | msp.A3.CoPi, TXD            |
| GPIO12   | TBD   | -        | P0.19  | P6.1    | msp.A3.CiPo, RXD            |
| GPIO13   | TBD   | -        | P0.20  | P6.3    | msp.A3.STE                  |
| GPIO14   | TBD   | -        | P0.24  | P6.6    | msp.A3.CLK                  |
| GPIO15   | TBD   | -        | P0.27  | P6.7    | msp.A3.STE                  |
| PwrGoodL | -->   | PG_L     | P0.23  | P5.4    |                             |
| PwrGoodH | -->   | PG_H     | P0.07  | P5.5    |                             |
| prog11   | -->   | SWD.CLK  | swdclk | -       |                             |
| prog12   | <-A-> | SWD.IO   | swdio  | -       |                             |
| prog21   | -->   | SBW.CLK  | -      | sbwtck  |                             |
| prog22   | <-B-> | SBW.IO   | -      | sbwtdio |                             |
|          | -     | LED.0    | P0.13  | P5.7    |                             |
|          | -     | LED.2P   | P0.03  | PJ.0    |                             |
|          | -     | I2C.SCL  | P1.08  | P6.5    |                             |
|          | -     | I2C.SDA  | P0.06  | P6.4    |                             |
|          | -     | RTC.INT  | P0.30  | P7.3    |                             |
|          | -     | C2C.CLK  | P0.18  | P1.5    | msp.A0.CLK                  |
|          | -     | C2C.CoPi | P0.17  | P2.0    | msp.A0.CoPi                 |
|          | -     | C2C.CiPo | P0.14  | P2.1    | msp.A0.CiPo                 |
|          | -     | C2C.PSel | P0.22  | P1.4    | msp.A0.PSel                 |
|          |       | C2C.GPIO | P0.15  | PJ.2    |                             |

Note: A, B, C in DIR-Column refer to switch-groups

## Connections to Cape V2.4 via Adapter

The 40-pin Edge-Connector of Target V1.3 has an adapter to interface the 2x9 Header of Cape V2.4. This keeps connections compatible to Target V1.0.

| SHP-V24 | Dir   | Riotee   | nRF52  | msp430  | Description                 |
|---------|-------|----------|--------|---------|-----------------------------|
| GPIO0   | <-A-> | GPIO.7   | P0.11  | P5.3    | msp.B1.PSel                 |
| GPIO1   | <-A-> | GPIO.8   | P0.13  | P5.2    | msp.B1.CLK                  |
| GPIO2   | <-A-> | GPIO.2   | P0.04  | P2.3    | msp.A1.PSel                 |
| GPIO3   | <-A-> | GPIO.3   | P0.05  | P2.4    | msp.A1.CLK                  |
| GPIO4   | <--   | GPIO.4   | P1.09  | P4.6    |                             |
| GPIO5   | <--   | GPIO.5   | P0.26  | P3.6    |                             |
| GPIO6   | <--   | GPIO.6   | P1.03  | PJ.6    |                             |
| GPIO7   | <--   | GPIO.1   | P0.08  | P2.5    | UART Target-TX, msp.A1.CoPi |
| GPIO8   | <-B-> | GPIO.0   | P0.21  | P2.6    | UART Target-RX, msp.A1.CiPo |
| BATOK   | -->   | PG_H     | P0.07  | P5.5    |                             |
| prog11  | -->   | SWD.CLK  | swdclk | -       |                             |
| prog12  | <-C-> | SWD.IO   | swdio  | -       |                             |
| prog21  | -->   | SBW.CLK  | -      | sbwtck  |                             |
| prog22  | <-D-> | SBW.IO   | -      | sbwtdio |                             |

Note: A, B, C, D in DIR-Column refer to switch-groups

## Difference to Riotee

- extra LED.0
- larger msp430FR5994
- 16x GPIO instead of 10x
- no power-converters, but over-voltage-protection and under-volt-switch for nRF
