# nRF52 & MSP430 FRAM Target V1.2

Shared pins between MCUs and Observer, **Cape V2.5 (not produced yet)**

| SHP-HDR  | Dir   | Riotee   | nRF52  | msp430  | Description                 |
|----------|-------|----------|--------|---------|-----------------------------|
| GPIO0    | <-A-> | GPIO.0   | P0.21  | P2.6    | UART Target-RX, msp.A1.CiPo |
| GPIO1    | <-B-> | GPIO.1   | P0.08  | P2.5    | UART Target-TX, msp.A1.CoPi |
| GPIO2    | <-C-> | GPIO.2   | P0.04  | P2.3    | msp.A1.PSel                 |
| GPIO3    | <-C-> | GPIO.3   | P0.05  | P2.4    | msp.A1.CLK                  |
| GPIO4    | <-C-> | GPIO.4   | P1.09  | P4.6    |                             |
| GPIO5    | <-C-> | GPIO.5   | P0.26  | P3.6    |                             |
| GPIO6    | <--   | GPIO.6   | P1.03  | PJ.6    |                             |
| GPIO7    | -->   | GPIO.7   | P0.11  | P5.3    | msp.B1.PSel                 |
| GPIO8    | <--   | GPIO.8   | P0.13  | P5.2    | msp.B1.CLK                  |
| GPIO9    | -->   | GPIO.9   | P0.16  | P5.1    | msp.B1.CiPo                 |
| PwrGoodL | -->   | PG_L     | P0.23  | P5.4    |                             |
| PwrGoodH | -->   | PG_H     | P0.07  | P5.5    |                             |
| prog11   | -->   | SWD.CLK  | swdclk | -       |                             |
| prog12   | <-A-> | SWD.IO   | swdio  | -       |                             |
| prog21   | -->   | SBW.CLK  | -      | sbwtck  |                             |
| prog22   | <-B-> | SBW.IO   | -      | sbwtdio |                             |
|          | -     | LED.0    | P0.12  | P5.0    | Riotee GPIO.10, msp.B1.CoPi |
|          | -     | LED.2P   | P0.03  | PJ.0    |                             |
|          | -     | I2C.SCL  | P1.08  | P6.5    |                             |
|          | -     | I2C.SDA  | P0.06  | P6.4    |                             |
|          | -     | RTC.INT  | P0.30  | P7.3    |                             |
|          | -     | C2C.CLK  | P0.18  | P1.5    | msp.A0.CLK                  |
|          | -     | C2C.CoPi | P0.17  | P2.0    | msp.A0.CoPi                 |
|          | -     | C2C.CiPo | P0.14  | P2.1    | msp.A0.CiPo                 |
|          | -     | C2C.PSel | P0.22  | P1.4    | msp.A0.PSel                 |
|          |       | C2C.GPIO | P0.15  | PJ.2    |                             |

**Note**:
- SHP-HDR Spec of Cape V2.5
- Testbed has still v2.4, 2024-08 - see table for target v1.0

## Verifying the PCBs

- first do a visual inspection (both sides)
  - backside should be complete
  - front side can have two caps DNP: big C14 @RTC & C9 in the middle (SW of MSP430)

### Assembly

- solder the 2x9-Pin-Header

### First Powerup

- 2 mA @ 3V on V_target without programming
- 0 mA @ 3V on 3V-Input

### Software-Prereqs

**NOTE**: all further tests are done on BBone

```Shell
cd ~
git clone https://github.com/nes-lab/shepherd-tools
cd shepherd-tools
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

NOTE: best done with interconnector that only routes: pwr1, serial, programming-pins, pwr2
Check UART output with logic analyzer or in shepherd recording.
Behavior is described [here](https://github.com/nes-lab/shepherd-targets/tree/main/firmware/nrf52_testable).

### Testing the Radio

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 /var/shepherd/content/fw/nes_lab/nrf52_rf_test/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 /var/shepherd/content/fw/nes_lab/msp430_deep_sleep/build.hex
sudo shepherd-sheep target-power -p A -v 3 --on
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test2.yaml
```

Behavior is described [here](https://github.com/nes-lab/shepherd-targets/tree/main/firmware/nrf52_rf_test).

### Testing Power-consumption during sleep

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 /var/shepherd/content/fw/nes_lab/nrf52_deep_sleep/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 /var/shepherd/content/fw/nes_lab/msp430_deep_sleep/build.hex
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test3.yaml
```

## Assembled Units

- visual inspection -> reflow fails:
  - A: crystal on ABx & MSP, one R240 on back
  - B: crystal on MSP,
  - C: crystal on ABx & nRF
- PowerUp
  - C: 3-4 mA on VTarget, instead of 2 mA
- Programming -> A, B fully responding
- Testable-FW
  - many shorts or permanent-high GPIO
- RF-Test - 1 m away in Doughnut-Pattern & 1 m above
  - A: -56 dBm in, -49 dBm above (SMA-Port loosely attached)
  - B: -56 dBm in, -48 dBm above
  - C: -50 dBm in, -52 dBm above
  - C: -47 dBm above (soldered SMA)
  - Target 7 with Stub-Antenna: -64 dBm in, -62 dBm above
  - Target 18 with Chip-Antenna: -67 to -72 dBm in, -69 to -72 dBm above
  - Various far points in flat show: 80-100 with chip antenna, 85-90 with stub, 65-83 with dedicated Antenna


```A
GPIO WATCHER
Missing: 2 12         -> GPIO3, LED2
Always:  5 8 10 [14]  -> GPIO6, GPIO9, PH
              1
          1   1
        1 1   1
     1  1 1   1
     1  1 11  1
1    1  1 1   1
 1   1  1 1   1
   1 1  1 1   1
    11  1 1   1
     11 1 1   1
     1 11 1   1
     1  1 1   1
     1  111   1
     1  1 1   1
     1  1 1
     1  1 1  1
     1  1 1   1
     1  1 1     1
     1  1 1      1
     1  1 1       1
     1  1 1        1
     1  1 1         1
     1  1 11
     1  1 1
```

```B
GPIO WATCHER
Missing: 2 12 15
Always:  5 8 9 13 [14]
     1       11
     1  1    11
     1  1 1  11
     1  1    11
     1  11   11
     1  11 1 11
1    1  11   11
 1   1  11   11
   1 1  11   11
    11  11   11
     1  11   11
     11 11   11
     1 111   11
     1  11   11
     1  111  11
     1  11   11
     1  11   1
     1  11   11
     1  11   1
     1  11   1  1
     1  11   1   1
     1  11   1    1
     1  11   1     1
     1  11   1      1
     1  11 1 1
     1  11   11
     1  11 1 11
```

```C
GPIO WATCHER
Missing: none
Always:  [3] 5 9 [13]
   1
   1     1
   1 1   1
   1 1   1 1
   1 1   1
   1 1   1  1
   1 1   1  11
   1 1   1   1
   1 1   1  11
   1 1   1   1
   1 1   1  11
   1 1   1   1
     1   1   1
1    1   1   1
     1   1   1
     1   1  11
     1   1   1
 1   1   1   1
     1   1   1
     1   1  11
     1   1   1
  1  1   1   1
     1   1   1
     1   1  11
     1   1   1
   1 1   1   1
     1   1   1
     1   1  11
     1   1   1
    11   1   1
     1   1   1
     1   1  11
     1   1   1
     1   1  11
     1   1   1
     11  1   1
     1   1   1
     1   1  11
     1   1   1
     1 1 1   1
     1   1   1
     1   1  11
     1   1   1
     1  11   1
     1   1   1
     1   1  11
     1   1   1
     1   1  11
     1   1   1
     1   11  1
     1   1   1
     1   1  11
     1   1   1
     1   1
     1   1   1
     1   1
     1   1  1
     1   1
     1   1    1
     1   1
     1   1  1
     1   1
     1   1     1
     1   1
     1   1  1
     1   1
     1   1      1
   1 1   1      1
   1 1   1
   1 1   1  1
   1 1   1
   1 1   1       1
   1 1   1
   1 1   1  1
   1 1   1
   1 1   1        1
   1 1   1
   1 1   1  1
   1 1   1
   1 1   1         1
   1 1   1
   1 1   1  1
   1 1   1
   1 1   1          1
Received all 21 shared pins!!
```

## Bugs, Changes, Improvements

### Changes from prev Version

- two bat-status pins from cape would be better
    - goal: offer hysteresis - working good for riotee so far
    - second goal: compatibility with riotee-SDK for targets
- shared gpio would benefit from external PU/PD-Resistors, so current mcu-code can be more independent
    - problem: msp430 is reacting with high currents for floating pins
    - current solution: activate internal PD-Res in msp430 - at least for our sleep- & FRAM-firmware
- add a system to identify pcb? OW-nodeid or i2c-rom?
- ditch PAN1780 module to allow an external antenna (rf-performance of pan-module is sub-par)

#### Details

- additional parts to order
  - rpi pico - https://www.mouser.de/ProductDetail/Raspberry-Pi/SC0915?qs=T%252BzbugeAwjgnLi4azxXVFA%3D%3D
  - rpi pico H https://www.mouser.de/ProductDetail/Raspberry-Pi/SC0917?qs=T%252BzbugeAwjjvYEYcRJk%252Bxw%3D%3D
  - rpi pico W https://www.mouser.de/ProductDetail/Raspberry-Pi/SC0918?qs=T%252BzbugeAwjj9dgdBLZSmdg%3D%3D
  - rpi 5 https://www.mouser.de/ProductDetail/Raspberry-Pi/SC1112?qs=HoCaDK9Nz5c86n0i5EQ%2FPA%3D%3D
  - Antenna https://www.mouser.de/c/passive-components/antennas/?q=antenna%20sma&minimum%20frequency=2.4%20GHz%7C~2.41%20GHz~~2.45%20GHz&instock=y&NewSearch=1&rp=passive-components%2Fantennas%7C~Minimum%20Frequency&sort=pricing
  - Antenna refinement https://www.mouser.de/c/passive-components/antennas/?q=antenna%20sma&antenna%20connector%20type=SMA%20Connector%7C~SMA%20Male~~SMA%20Plug&maximum%20frequency=2.48%20GHz~~2.5%20GHz&minimum%20frequency=2.4%20GHz%7C~2.41%20GHz~~2.45%20GHz&instock=y&sort=pricing&NewSearch=1&rp=passive-components%2Fantennas%7C~Minimum%20Frequency%7C~Maximum%20Frequency%7C~Antenna%20Connector%20Type
  - HDR2x10 RM2 737-2PH2-20-UA
  - rare cape-parts
- gpio.9 is now dedicated gpio and not bat_OK anymore (free from LED.0)
- gpio.10 was LED.1, is now LED.0
- `VCAP_SENSE` was floating, now V_Target
  - https://github.com/NessieCircuits/Riotee_MSP430Fram/blob/main/src/main.c
  - https://github.com/NessieCircuits/Riotee_SDK/blob/main/core/include/riotee.h
  - `PIN_VCAP_SENSE`, `AIN_VCAP_SENSE` are configured, but unused by riotee (FRAM-FW & SDK)
- `PIN_MAX_INT` is left floating (unchanged) as it is configured, but unused by SDK & not avail on target
- discrete nRF52 IC,
  - Riotee: NRF52833-CJAA (+direction finding)
  - Targetv11: 52840 (+matter) -> Choose this one
  - CJAA => WLCS 3.2x3.2 mm
  - QIAA => aQFN73 7x7mm -> Choose this one
  - QDAA => QFN40
  - CFAA => WLCSP-44
- switch ClockCrystal from 20 ppm to 5 ppm
- LED.1 is unused -> removed
- 2x10 HDR -> RM2.0mm
- re-aligned gpios between observer & target
- nRF - 2 crystals
- also share threshold-control + max-int between MCUs (with 470R)
- SMA or uFL? -> SMA
- adapt capacities for crystals
- nRF - Antenna path - 630 um on L1/L4 are 50 Ohms,
  - both ant-traces are < 5 mm and therefore well below 10% of 2.4 GHz wavelength
- add antenna to schematic
- replace msp430 128kb (-FR5962) with riotees 256kb (-FR5994),

Skipped:
- PD-Res for internal Pins - 10 M?

### Riotee-SDK-patching

- target uses nRF52840 instead of Riotees -833
- main makefile specifies `NRF_DEV_NUM`
- Size of FRAM auto-adjust? -> main makefile `RIOTEE_RAM_RETAINED_SIZE`, `RIOTEE_STACK_SIZE`
- type of nRF relevant? -> main Makefile `NRF_DEV_NUM`
