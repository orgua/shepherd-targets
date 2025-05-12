# nRF52 & MSP430 FRAM Target V1.3e

Shared pins between MCUs and Observers with **Cape V2.5 (deployed in near future / mid 2025)**.

**The testbed still uses Cape v2.4 as of 2025-04. See 2nd table below for that mapping.**

**Note**:

- GPIO12 to GPIO15 are not recordable by the testbed with cape V2.5, as pins on the SBC are all used up
- The nRF has no outer reset line - so configuring one could keep the MCU in permanent reset. Code for the nRF52-DK may use P0.21 for reset - it is actively used for UART-Rx here. 
- A, B, C in DIR-Column refer to switch-groups. 1, 2 and/or 4 bits can be reversed to talk to the target.
- D, E are switch-groups needed for programming

| Tgt-Port | Dir   | Riotee     | nRF52  | msp430  | Description                 |
|----------|-------|------------|--------|---------|-----------------------------|
| GPIO0    | <-A-> | GPIO.0     | P0.21  | P2.6    | UART Target-RX, msp.A1.CiPo |
| GPIO1    | <--   | GPIO.1     | P0.08  | P2.5    | UART Target-TX, msp.A1.CoPi |
| GPIO2    | <-B-> | GPIO.2     | P0.04  | P2.3    | msp.A1.PSel                 |
| GPIO3    | <-B-> | GPIO.3     | P0.05  | P2.4    | msp.A1.CLK                  |
| GPIO4    | <-C-> | GPIO.4     | P1.09  | P4.6    |                             |
| GPIO5    | <-C-> | GPIO.5     | P0.26  | P3.6    |                             |
| GPIO6    | <-C-> | GPIO.6     | P1.03  | PJ.6    |                             |
| GPIO7    | <-C-> | GPIO.7     | P0.11  | P5.3    | msp.B1.PSel                 |
| GPIO8    | <--   | GPIO.8     | P0.13  | P5.2    | msp.B1.CLK                  |
| GPIO9    | <--   | GPIO.9     | P0.16  | P5.1    | msp.B1.CiPo                 |
| GPIO10   | <--   | -          | P0.12  | P5.0    | msp.B1.CoPi, SDA            |
| GPIO11   | <--   | -          | P0.10  | P6.0    | msp.A3.CoPi, TXD            |
| (GPIO12) | <--   | -          | P0.19  | P6.1    | msp.A3.CiPo, RXD            |
| (GPIO13) | <--   | -          | P0.20  | P6.3    | msp.A3.STE                  |
| (GPIO14) | <--   | -          | P0.24  | P6.6    | msp.A3.CLK                  |
| (GPIO15) | <--   | -          | P0.27  | P6.7    | msp.A3.STE                  |
| PwrGoodL | -->   | PG_L       | P0.23  | P5.4    |                             |
| PwrGoodH | -->   | PG_H       | P0.07  | P5.5    |                             |
| prog11   | -->   | SWD.CLK    | swdclk | -       |                             |
| prog12   | <-D-> | SWD.IO     | swdio  | -       |                             |
| prog21   | -->   | SBW.CLK    | -      | sbwtck  |                             |
| prog22   | <-E-> | SBW.IO     | -      | sbwtdio |                             |
|          | -     | LED.0      | P1.13  | P5.7    |                             |
|          | -     | LED.2P     | P0.03  | PJ.0    |                             |
|          | -     | I2C.SCL    | P1.08  | P6.5    |                             |
|          | -     | I2C.SDA    | P0.06  | P6.4    |                             |
|          | -     | RTC.INT    | P0.30  | P7.3    | shared, no fct for shp      |
|          | -     | MAX.INT    | P0.30  | PJ.1    | shared, no fct for shp      |
|          | -     | C2C.CLK    | P0.18  | P1.5    | msp.A0.CLK                  |
|          | -     | C2C.CoPi   | P0.17  | P2.0    | msp.A0.CoPi                 |
|          | -     | C2C.CiPo   | P0.14  | P2.1    | msp.A0.CiPo                 |
|          | -     | C2C.PSel   | P0.22  | P1.4    | msp.A0.PSel                 |
|          |       | C2C.GPIO   | P0.15  | PJ.2    |                             |
|          |       | THRCTRL.H0 | P0.09  | P1.3    | shared, no fct for shp      |
|          |       | THRCTRL.H1 | P1.02  | P3.3    | shared, no fct for shp      |
|          |       | THRCTRL.L0 | P1.07  | P6.2    | shared, no fct for shp      |
|          |       | THRCTRL.L1 | P1.04  | P7.0    | shared, no fct for shp      |
|          |       | VCAP.Sense | P0.29  | P7.5    | VTarget                     |

## Connections to Cape V2.4 via Adapter

The 40-pin Edge-Connector of Target V1.3 has an adapter to interface the 2x9 Header of Cape V2.4.
This keeps connections compatible to Target V1.0.

**Note**:
- A, B, C, D in DIR-Column refer to switch-groups
- Shepherds GPIO8 (target-rx) will be re-assigned to PwrGoodL (BATOK is PwrGoodH)

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

## Features

- similarity to Riotee
- MCU 1 - nRF52840
- MCU 2 - msp430FR5994
- low power RTC & Watchdog
- one led to burn energy fast
- SMA port to connect external antenna
  - balun is optimized for higher transmit power (>= 5 dBm, ref circuit 7 in PS v1.8)
- MCUs share SPI-Connection + some additional pins
- edge-connector routes out
  - programming pins (SWD & SBW)
  - power-good signals
  - 16x shared GPIO
- all shared GPIO is current limited to prevent damages to the hardware
  - limit to 8-10 mA @ 4V with 470 R or (2x) 220 R on each IC entry
- IO-Pins not interfering with RF (nRF PS v1.6 page 578)
- clock-crystals have high precision, 5 ppm, with matched impedance
- protection for over- & under-voltage, see sub-sections below

### Over-Voltage-Protection

The target voltage coming from the shepherd-cape can reach up to 5 V.
The MCUs on the target board can't handle that voltage, so the ICs have to be protected.

Abs Max Ratings:

- 3.9 V nRF52
- 3.8 V RTC AB1805
- 4.1 V MSP430

A fitting shottky diode is used to burn energy above 3.7V.

One PMEG10010ELR Diode is between V_target and 3V3:
+ 0.0 V -> 6 pA (noise)
+ 0.1 V -> 47 nA
+ 0.2 V -> 2.3 uA
+ 0.3 V -> 120 uA
+ 0.4 V -> 4.83 mA

### Under-Voltage-Protection

- the nRF consumes ~.5mA below 1.7V, even in deep-sleep
- consumption drops when going above 1.69 V
- consumption rises when going below 1.58 V
- tested 13 nodes range from
  - ON = 1.63 to 1.69 V
  - OFF = 1.58 to 1.60 V

Solution

- analog switch controlled by comparator with small hysteresis
- VON = 1.729 V, VOFF = 1.652 V according to formular in datasheet (values are wrong?)
- VON = 1.797 V, VOFF = 1.642 V when solving the network with traditional methods
- VON = 1.802 V, VOFF = 1.641 V from actual measurements

Possible Caveats

- hysteresis is currently only 150 mV and unstable behavior must be avoided
- charging the decoupling caps (2.6 uF) of the MCUs leads to voltage drop
  - 10 uF storage, 2.6 uF decoupling -> 230 mV drop (trouble)
  - 47 uF storage, 2.6 uF decoupling -> 48 mV drop
  - 100 uF storage, 2.6 uF decoupling -> 22 mV drop
- turning on the switch shows current spike of ~ 4 mA for < 50 us for target v1.0 with 1.6 uF decoupling
  - 10 uF storage, 5 mA draw -> 200 us for 100 mV drop
  - 10 uF storage, 1 mA draw -> 1000 us for 100 mV drop
  - 47 uF storage, 5 mA draw -> 940 us for 100 mV drop
  - 100 uF storage, 5 mA draw -> 2000 us for 100 mV drop

Calculating the charging drop for the decoupling caps with `maxima`:

```maxima
C_store: 10e-6;
C_out: 2.6e-6;
V_set: 1.7;
dVc: V_set * (sqrt(1 - C_out / C_store) - 1);
```

Calculating the allowed time for high current during switching on:

```maxima
V_set: 1.7;
C_store: 10e-6;
I_out: 5e-3;
dV: 100e-3;
t: dV * C_store / I_out;
```

See `.wxmx`-maxima-file for more details.

## Difference to Riotee

- nRF52840 instead of Riotees -833
  - main makefile specifies `NRF_DEV_NUM`
- msp430FR5994 has more storage (256 KB)
  - Size of FRAM auto-adjust? -> main makefile `RIOTEE_RAM_RETAINED_SIZE`, `RIOTEE_STACK_SIZE`
- extra LED.0
- 16x GPIO instead of 10x
- no power-converters, but over-voltage-protection and under-volt-switch for nRF

## Cost of Production

- PCB-Fabrication
  - 190 € / 30 n with shipping
  - 1.6mm thick, 4 layer, .3mm vias - filled and capped, .1 mm traces and distance
  - electro-polished stencil
- BOM cost
  - parts for 1 n when ordering 10 n = 20.60 €
  - parts for n=10 are 182 € (18.20 €/n)
  - parts for n=20 are 360 € (18 €/n)
- Pick & place
  - 29 different parts, 120 in total
  - 0.5 mm pitch

### Extra remark

- DNP: C20, SMA-Con, Antenna

## Verifying the PCBs

- first do a visual inspection
- front side has one cap DNP: C20, lower left corner, near edge-connector

### Assembly

- solder the SMA-Connector, add Antenna

### First Powerup

- 2 mA @ 3V on V_target without programming
- 0 mA @ 3V on 3V-Input

### Software-Prereqs

**NOTE**: all further tests are done on BBone

```Shell
cd ~
git clone https://github.com/orgua/shepherd-datalib
cd shepherd-datalib
git checkout dev
git pull

python3 ./extra/gen_firmwares.py
sudo python3 ./extra/gen_experiments.py
```

Put Target on BBone with Target on Port 1!

### Test all GPIO & LEDs

First test all used gpio with this fw-combo (msp toggles, nrf watches and reports via uart):

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 /var/shepherd/content/fw/nes_lab/nrf52_testable/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 /var/shepherd/content/fw/nes_lab/msp430_testable/build.hex
sudo shepherd-sheep target-power -p A -v 3 --on
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test1.yaml
```

NOTE: best done with inter-connector that only routes: pwr1, serial, programming-pins, pwr2
Check UART output with logic analyzer or in shepherd recording.
Behavior is described [here](https://github.com/orgua/shepherd-targets/tree/main/nrf52_testable).

### Testing the Radio

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 /var/shepherd/content/fw/nes_lab/nrf52_rf_test/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 /var/shepherd/content/fw/nes_lab/msp430_deep_sleep/build.hex
sudo shepherd-sheep target-power -p A -v 3 --on
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test2.yaml
```

Behavior is described [here](https://github.com/orgua/shepherd-targets/tree/main/nrf52_rf_test).

### Testing Power-consumption during sleep

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 /var/shepherd/content/fw/nes_lab/nrf52_deep_sleep/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 /var/shepherd/content/fw/nes_lab/msp430_deep_sleep/build.hex
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test3.yaml
```

## Testing

- programming via debug-adapter fails for nRF (OK for MSP), even at 200kbit or 100kbit instead of 500k
  - reason: unsoldered press-fit to shepherd cape
- 6 of 24 targets had trouble programming the MSP
  - removing two ICs showed no flaws
  - as visual inspection is OK the next suspects are: pcb or chip-failure
- report is in [planning-repo](https://github.com/orgua/shepherd_v2_planning/tree/main/doc_testbed)

## Implemented Changes / Bugs of prior Version

- Edge-Connector is 17.40 mm wide, PCB-Edge has 17.20 mm, exactly to spec
  - resist bridge between pads is 0.3 mm, so this is fine, but pcb can be moved
  - -> still widen edge on both sides .05 mm to 17.30 mm (measures as 17.25 mm on final PCB)
  - connector wiggles and prongs are almost on outer edge of pad
- edge-connector is still a bit loose,
  - PCB has only 1.48 mm thickness without copper, resist, silk, but outer rail of connector is 1.75 mm (spec)
  - 1.64 to 1.70 mm on Cu, silk, resist -> measures as 1.64
  - railing edge now has resist and silk screen
- as 6 of 24 MSP430s were failing to be programmed - programming pins were checked & redone
  - R61 is 47k, but measures 4.0k? on failing boards R<3.9k, on good ones larger, more like 4.1
  - optimize via-placement with regard to distance from pad
- update parts from Libs
- panel - move holes of bridges a bit further out
- finished as v1.3e

**Production of v1.3e**

- BOM for 30n with spare, 650 € @ Mouser
- Panels for 30n, 214 € @ JLCPCB

## Errata & future Improvements

- BGA without paste? MSP-failure-rate stays ~ 20 %
  - low temp paste is harder to control - does not wet as good and needs manual fixes (almost on every PCB)
- bridge to panel should be moved away from BGA
- holes on panel can be 3.2 mm for stencil printer
- QR Code can now be directly created in Altium
- perforated breaking lines on panels (extension of milled line)
- bridge to panel can be thinner
- move LED a bit away from SMA
- pin 1 marking bigger on ICs
- is there a paste-pad under the TS5A?
- allow using internal switching regulator from nRF to lower power-consumption
