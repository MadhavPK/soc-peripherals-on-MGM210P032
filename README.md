# soc-peripherals-on-MGM210P032
## Hardware Used ##
1. SiLabs WSTK Mainboard BRD4001A Rev A01
2. Radio Board BRD4308A Rev A01 (MGM210P032JIA)
## Software Used ##
1. Gecko SDK v2.7.9 -> Bluetooth SDK v2.13.9.0
2. Simplicity Studio v4

## About the Project ##
The project provides an example for accessing peripherals on **SiLabs MGM210P032JIA** module along with BLE stack running. Radio Board BRD4308A has MGM210P032JIA module. The module is based on the EFR32MG21 SoC. 

## Important Files
Executable binaries are in `./GNU ARM v7.2.1 - Default`

The `./app.c` and `./app.h` contains event handler for BLE.

Files `./peripheral_utils.c` and `./peripheral_utils.h` contain functions that deal with peripherals on SoC.

## Peripherals Used ##
### GPIO ###
1. LED
2. Button
3. IADC

## Sources and important links
1. EFR32xG21 Reference Manual - https://www.silabs.com/documents/public/reference-manuals/efr32xg21-rm.pdf
2. MGM210P Data Sheet         - https://www.silabs.com/documents/public/data-sheets/mgm210p-datasheet.pdf
3. BRD4308A User Guide        - https://www.silabs.com/documents/public/user-guides/ug388-brd4308a-user-guide.pdf
4. Peripheral Examples        - https://github.com/SiliconLabs/peripheral_examples/tree/master/series2


