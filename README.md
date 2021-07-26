# soc-peripherals-on-MGM210P032
## Hardware Used ##
1. BRD4001A Rev A01 SiLabs WSTK reffered as  Mainboard
2. BRD4308A Rev A01 (MGM210P032JIA) reffered as Radio Board
## Software Used ##
1. Gecko SDK v2.7.9 -> Bluetooth SDK v2.13.9.0
2. Simplicity Studio v4
3. GNU ARM GCC v7.2.1

## About the Project ##
The project provides an example for accessing peripherals on **SiLabs MGM210P032JIA** module along with BLE stack running. Radio Board BRD4308A has MGM210P032JIA module. The module is based on the EFR32MG21 SoC. 

## Important Files
Executable binaries are in `./GNU ARM v7.2.1 - Default`

The `./app.c` and `./app.h` contains event handler for BLE.

Files `./peripheral_utils.c` and `./peripheral_utils.h` contain functions that deal with peripherals on SoC.

## Gatt Profile ##
When Testing with mobile app, you will see following list of Custom Services and Characteristics. You might not see the names mentioned below but you will see the {UUID}. This can also be seen in Visual GATT Editor by opening `./soc-peripherals-on-MGM210P032.isc`

**Peripheral Test** {686d7b33-129f-4532-89c1-c502c6159bb3}
  - *LED0* {abe6b815-d38c-476e-ae7e-dd1d62e209de}
    * Type: USER
    * Size: 1 byte
  - *BUTTON1* {ebff5ca7-0398-422a-a0ea-63fefb0765ec}
    * Type: HEX
    * Size: 1 byte
  - *ADC DATA* {bb7b889f-587e-421f-a3b4-c3654998a742}
    * Type: USER
    * Size: 5 byte
  - *UART2 Data* {9b475432-881f-418a-98ca-003c65339261}
    * Type: HEX
    * Size: 80

## Peripherals Used ##
### GPIO ###
1. LED <br>
Mainboard has 2 on board LEDs out of which LED0 is used. This LED is connected to GPIO PB0. Therefore, GPIO PB0 is set as output. Characteristic LED0 is used which accepts following values<br>
<table style="width:20%">
  <tr>
    <th>Value</th>
    <th>Action</th>
  </tr>
  <tr>
    <td>0</td>
    <td>Turn OFF LED</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Turn ON LED</td>
  </tr> 
  <tr>
    <td>2</td>
    <td>Toggle LED</td>
  </tr>
</table>
2. BUTTON <br>
Mainboard has 2 on board push buttons out of which Button1 is used. This Button is connected to GPIO PB1. Therefore, GPIO PB1 is set as input. Characteristic BUTTON1 is used convey number of button presses. <br> 
Every button press generates a GPIO interrupt. The ISR keeps a counter for the number of times the button was pressed and generates a signal (SW interrupt to BLE stack). This signal raises an event in BLE stack. Using this event Client is notified of the counter value everytime button is pressed.

### IADC ###
ADC Configurations  | Value
---                 | ---
Mode                | Single input
Port and Pin        | PC02
Trigger Action      | Once
Over Sampling Ratio | 2x
`CLK_ADC_FREQ`      | 1,000,000 -> 1MHz
`CLK_SRC_ADC_FREQ`  | 1,000,000 -> 1MHz
* If Trigger Action was set to Continuous, then according to formula on pg14 of [AN1189: Incremental Analog to Digital Converter (IADC)](https://www.silabs.com/documents/public/application-notes/an1189-efr32-iadc.pdf), the converion time would be<br>
![Formula for Conversion Time](https://user-images.githubusercontent.com/31771892/123038444-0bf26e00-d40e-11eb-94ee-b6e9c73c6588.png)<br>
Conversion Time = 10/1,000,000<br>
This means Samples per seconds = 1,000,000/10 = 100,000 = 100ksps<br>
* Since, we are using Trigger Action as Once and we are invoking IADC every second using BLE stack soft timer, the effective Samples Per Second = 1 sps
* Enabling the notification will start the soft timer and also trigger IADC.
### UART ###
UART Configuration  | Value
---                 | ---
Tx Port and Pin     | PC00
Rx Port and Pin     | PC01
Baud Rate           | 115200
Flow Control        | No
Data Size           | 8 bit
Parity              | None
* The MGM210P has 3 USARTs, USART2 and been configured as asynchronous USART (i.e. UART). Since Rx can only take place in EM0 and EM1 the EM2 sleep must be blocked when MCU wants to receive the data.
* Enabling notification will allow MCU to receive the data.

## Sources and important links
1. EFR32xG21 Reference Manual                             - https://www.silabs.com/documents/public/reference-manuals/efr32xg21-rm.pdf
2. MGM210P Data Sheet                                     - https://www.silabs.com/documents/public/data-sheets/mgm210p-datasheet.pdf
3. BRD4308A User Guide                                    - https://www.silabs.com/documents/public/user-guides/ug388-brd4308a-user-guide.pdf
4. Peripheral Examples                                    - https://github.com/SiliconLabs/peripheral_examples/tree/master/series2
5. AN1189: Incremental Analog to Digital Converter (IADC) - https://www.silabs.com/documents/public/application-notes/an1189-efr32-iadc.pdf
6. AN0012: General Purpose Input Output                   - https://www.silabs.com/documents/public/application-notes/an0012-efm32-gpio.pdf
7. Bluetooth Software API Reference Manual                - https://www.silabs.com/documents/public/reference-manuals/bluetooth-api-reference.pdf
