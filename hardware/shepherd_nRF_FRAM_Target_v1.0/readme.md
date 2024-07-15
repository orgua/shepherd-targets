# nRF52 & MSP430 FRAM Target V1.0

Shared pins between MCUs

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

**Note**: Pins P[3:12] on Target-Header of V1.0 are GPIO[0:8] & BATOK

## Verifying the PCBs

- first do a visual inspection (both sides)
  - backside should be complete
  - front side can have two caps DNP (C14 & C9 in the middle)

### Assembly

- solder the 2x9-Pin-Header

### First Powerup

- 2 mA @ 3V without programming on V_target
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
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 extra/content/nrf52_testable/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 extra/content/msp430_testable/build.hex
sudo shepherd-sheep target-power -p A -v 3 --on
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test1.yaml
```

NOTE: best done with interconnector that only routes: pwr1, serial, programming-pins, pwr2
Check UART output with logic analyzer or in shepherd recording.
Behavior is described [here](https://github.com/orgua/shepherd-targets/tree/main/nrf52_testable).

### Testing the Radio

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 extra/content/nrf52_rf_test/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 extra/content/msp430_deep_sleep/build.hex
sudo shepherd-sheep target-power -p A -v 3 --on
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test2.yaml
```

Behavior is described [here](https://github.com/orgua/shepherd-targets/tree/main/nrf52_rf_test).

### Testing Power-consumption during sleep

```Shell
sudo shepherd-sheep program -p A -m 1 -v 3 -t nrf52 extra/content/nrf52_deep_sleep/build.hex
sudo shepherd-sheep program -p A -m 2 -v 3 -t msp430 extra/content/msp430_deep_sleep/build.hex
# new
sudo shepherd-sheep run /etc/shepherd/target_device_test3.yaml
```

-> Overview / Results for manufactured PCBs moved to [doc_testbed](https://github.com/orgua/shepherd_v2_planning/tree/main/doc_testbed)

## Bugs, Changes, Improvements

### Changes after v1.0

- nrf module - trace cross / lines should be realigned
  - silk is more correct
  - fix on short side larger (~.5mm in)
  - result: set .4 mm in, crosses are 1.3 mm (X&Y) away from edge-pads
- 240R all same orientation? -> easier placing
- there are two different 1uF -> >4V, <<25 V, 0402 is wanted
- name LEDs

-> implemented in v1.1

### v1.1

[here](https://github.com/orgua/shepherd-targets/tree/main/hardware/shepherd_nRF_FRAM_Target_v1.1) - skipped

### v1.2

[here](https://github.com/orgua/shepherd-targets/tree/main/hardware/shepherd_nRF_FRAM_Target_v1.2)
