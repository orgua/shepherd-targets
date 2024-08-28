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

NOTE: best done with interconnector that only routes: pwr1, serial, programming-pins, pwr2
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

### Bugs & Proposed Fixes / Improvements

- nRF - remove resist of alignment crosses
- less paste on thermal pad of nRF? Thermal paste is OK
  - solder on thermal is 9 * 1.1² = 8.6 mm² (round) -> 38 %
  - info: nRF-IC thermal pad ~4.75², 22.6 m² (IC and footprint match)
- make ABx Thermal pad bigger
  - info: ABx-IC thermal pad is ~ (1.8 mm)²
  - datasheet says D2xE2 is 1.65 - 1.75 - 1.85 -> area: 2.6 - 3.1 - 3.4 mm²
  - footprint was (1.13mm)² with 50% paste reduction (1.27 / 0.65 mm²)
  - now it is 1.5² with 65% reduction (2.25 / 0.79 mm²)
- stencil holes of nRF a bit bigger - pad 0.26mm round = 53.1e-3 mm², now with .28mm stencil (.213 distance, 61.6e-3 mm²)
  - ref design: pads .275mm with 19% expansion (.012mm) -> measured .299 (area .0594, .0647, .0702 for .275, .287, .299)
- stencil holes of MSP a bit bigger - pad 0.25mm round = 49.1e-3 mm², now with .28mm stencil (.213 distance)
- 1uF has two versions in BOM -> 10V version stays
- make more clear what is DNP -> Variants "Only Populate" changes Value, Mnf PN, Price to DNP
- Riotee has an MSP430FR5962 (like target v1.0) and not the current 5994?!? (256 vs 128 kByte)
  - linker and makefile needed a small adaption (include proper device-file)
  - Riotees FRAM-firmware is adapting automatically to FRAM-Size
  - datasheets memory map (section 9.15) shows identical maps with just double the FRAM-Space (end at x43FFF instead of x23FFF)
- why did the crystals footprint change (larger) but not the part? tombstone rate ~ 50%
  - correct crystal for that larger footprint: 520-ECX-.327CDX-1293, 5ppm, 3.2x1.5mm -> all correct & available
  - OLD: CM8V-T1A-32.768kHz-9pF-20PPM-TA-QC, 20ppm, 2.0x1.2mm
- add C on ABx-Crystal? YES - datasheet is misleading by not showing any
- board dimensions:
  - capes 54.8 / 2 = 27.4 mm max width -> 27
  - edge-connector, slit-bit is 6 x 17.4 mm -> side cutout is 6 x 4.8
  - target with hdr is 38.2 mm, so limiting the whole length now to 37
  - old-area was 25 x 24 = 600 mm², new usable area is 27 x 31 = 837
- nRF has high current draw between 500...1650 mV -> VSrc with diode+cap is problematic
  - voltage sweep is plotted in [this graphic](emu_ramp.plot_0s000_to_20s000.png)
  - add comparator to delay power of nRF
  - fix targets: comparator + pwr-switch -> on when above 1.65 .. 1.70 V
    - off again when going below 1.4 V
  - https://github.com/geissdoerfer/find/blob/master/hardware/schematic.pdf
  - 2x 6.5 MOhm Divider to
  - ~~TS5A23166DCUR~~ -> needs comparator
  - ~~in our stock: NLAS4684, FSA2258~~
  - 595-TS5A3167DCKR, ROn .9 Ohm, SC70-5, 50nA supply, SPST -> V_analog_max = VCC, V_EN_max = VIn_max = 6.5V
    - COM connected to NC (normally closed) when logic is LOW, so input is nEN!
  - 579-MCP6546RT-I/OT, comparator, VIN+ gets Ref ResistorNW, When VIN- is below VIN+ the output is high (WANTED)
    - open drain output, so PU to 3V3 - switch has <20nA leakage, so ~100k should be fine
- extend to 16 GPIO
  - order adapter to old shepherd 2x9
  - order pinheader and sockets for the new port
  - which pins to add?
  - 2x10 Angled Socket: SQT-110-01-F-D-RA -> new 2x13: SQT-113-01-F-D-RA -> without Angle: SQT-113-01-F-D
  - 2x10 PinHeader: 2PH2-20-UA -> new 2x13 only available from samtec, but they fit next to each other -> 2PH2-16-UA + 2PH2-10-UA
  - width: 20.35/10*13=26.5mm or better 20.35/11*14=25.9mm, MAX of Cape is 54.7/2=27.35mm
  - PCB-Edge-Connectors: https://www.mouser.de/c/connectors/card-edge-connectors/?number%20of%20positions=26%20Position%7C~30%20Position&instock=y&active=y&sort=pricing
    - PCIe 1x is cheap, has 1 mm distance and comes as TH & SMD, but it is designed for thick PCBs
    - HSEC8-120-01-S-DV-A-GR-K: 40Con, Guide Rails 7x20.6mm 11.75mm high
    - HSEC8-120-01-S-DV-A-K: without guide rails only 7.8mm high
    - **HSEC8-120-01-L-DV-A-K-TR**: same, but cheaper
  - ~~FFC/FPC-Con~~: https://www.mouser.de/c/connectors/ffc-fpc/ffc-fpc-connectors/?number%20of%20positions=26%20Position%7C~28%20Position%7C~30%20Position%7C~32%20Position&instock=y&active=y
  - ~~FFC/FPC-Cable~~: https://www.mouser.de/c/connectors/ffc-fpc/ffc-fpc-jumper-cables/?number%20of%20conductors=26%20Conductor%7C~28%20Conductor%7C~30%20Conductor%7C~32%20Conductor&instock=y&active=y
- current-limit LED0 (MSP430 is lower prio, so it gets 470R)
- NEW GPIO
  - GP10 P0.12  P5.0 (UCB1SIMO/SDA)
  - GP11 P0.10  P6.0 (UCA3SIMO/TXD)
  - GP12 P0.19  P6.1 (UCA3SOMI/RXD)
  - GP13 P0.20  P6.3 (UCA3STE)
  - GP14 P0.24  P6.6 (UCA3CLK)
  - GP15 P0.27  P6.7 (UCA3STE)
  - LED0 P1.13  P5.7
- verify RF-Path
  - PS_v1.8 ref circuit 7 shows improved 4 component filter: 1pF, 4.7nH, 1.2pF, 2.2nH (NP0 5%, hf ind. 5%)
  - keepout under antenna-path for
  - fanout shorter and thinner, C1 directly on RFOUT and GND

- review problematic pins


### to order

- new C27 1pF: 100x 81-GJM1555C1H1R0JB1D
- new C28 1.2pF: 100x 81-GJM1555C1H1R2JB1D
- new L2 2.2nH: 100x 81-LQG15HZ2N2C02D
- ~~SMA-Con?~~
- new HSEC8-120-01-L-DV-A-K-TR: 20x 200-HSEC812001LDVAKT
  - new headers for old cape?
- more 1uF - 4x30 - 200x 81-GCM155C71A105KE8D
- more 12pF -8x30 - 250x 77-VJ0402A120JXQPBC
- 12x 240R per unit (more IO)
- switch + comparator (MCP6546, TS5A3167)
  - 3x 100k, 1x 10k, 1x 1M,
  - 2x 100nF
- 1x 470R

## Extra remark

- DNP: C9, C14, ~~C29~~
- SMA-Con
- ~~HDR~~
