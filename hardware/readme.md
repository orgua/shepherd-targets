# Target PCBs

## nRF52 & MSP430 Target

Shared pins between MCU

-> Pins P3:12 on Target-Header of V1.0 are GPIO0:8 & BATOK


| SHP-HDR | Riotee   | nRF52 | msp430 | Description                         |
|---------|----------|-------|--------|-------------------------------------|
| GPIO0   | GPIO.7   | P0.11 | P5.3   |                                     |
| GPIO1   | GPIO.8   | P0.13 | P5.2   |                                     |
| GPIO2   | GPIO.2   | P0.04 | P2.3   |                                     |
| GPIO3   | GPIO.3   | P0.05 | P2.4   |                                     |
| GPIO4   | GPIO.4   | P1.09 | P4.6   |                                     |
| GPIO5   | GPIO.5   | P0.26 | P3.6   |                                     |
| GPIO6   | GPIO.6   | P1.03 | PJ.6   |                                     |
| GPIO7   | GPIO.1   | P0.08 | P2.5   | UART TX (this MCU as Point of view) |
| GPIO8   | GPIO.0   | P0.21 | P2.6   | UART RX (this MCU as Point of view) |
| BATOK   | GPIO.9   | P0.07 | P5.5   |                                     |
|         | LED.0    | P0.16 | P5.1   |                                     |
|         | LED.1    | P0.12 | P5.0   |                                     |
|         | LED.2P   | P0.03 | PJ.0   |                                     |
|         | I2C.SCL  | P1.08 | P6.5   |                                     |
|         | I2C.SDA  | P0.06 | P6.4   |                                     |
|         | RTC.INT  | P0.30 | P7.3   |                                     |
|         | C2C.CLK  | P0.18 | P1.5   |                                     |
|         | C2C.CoPi | P0.17 | P2.0   |                                     |
|         | C2C.CiPo | P0.14 | P2.1   |                                     |
|         | C2C.PSel | P0.22 | P1.4   |                                     |
|         | C2C.GPIO | P0.15 | PJ.2   |                                     |
