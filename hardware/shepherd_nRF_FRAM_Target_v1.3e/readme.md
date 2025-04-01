# nRF52 & MSP430 FRAM Target V1.3e

Documentation of v1.3 is still up-to-date. It can be found in `/hardware/shepherd_nRF_FRAM_Target_v1.3/readme.md`.

## Implemented Changes

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
- is there a paste-pad under the TS5A