


  
# Teapot Feather RAK3172
 <p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/feather-rak3172/main/docs/images/assembled_front.jpg" alt="drawing"  width="80%" height="80%"/></p>
 
Teapot Feather RAK3172 breaks out [RAKwireless RAK3172](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Datasheet) to an Adafruit Feather-compatible format.

At the heart of the device is the RAK3172, a STM32WLE5CC based module with ARM Cortex M4 processor, 48 MHz and 3.3V logic. The chip has a 256K of flash and 64K of RAM. 
With low-power application in mind, the board is capable to be in sleep mode for as low as 12uA, it also has a built-in voltage divider to sense battery voltage and battery charger.

Teapot Feather RAK3172 is heavily inspired by [Penguino STM32WL LoRa-E5](https://github.com/azerimaker/Penguino-STM32WL-LoRa-E5) and [BastWAN-WLE](https://github.com/ElectronicCats/BastWAN-WLE) projects!

## Specification

- [RAK3172](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Overview/): An STM32WLE5CC module
- 3.3V only power/pin. 
- Up to 12uA Deep-Sleep
- Switchable TX Power. 14 dBm or 22 dBm on 915MHz frequency
- Supports LoRaWAN 1.0.3
- USB-C for **Arduino** and  **Mbed OS/STM32Cube** programming
- SMA antenna connector 
- JST-PH 2-Pin Battery Connector
- Built-in LiPo Charger ( 200mA Charge Rate )
- Voltage-Divider for Battery Monitoring ( default: **disabled** )
- LED Indicator on pin 8 ( default: **disabled** )
- Compatible with many Adafruit FeatherWings
- Max 1A power output

## Schematics
<p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/feather-rak3172/main/hardware/schematic.png" alt="schematic"/></p>

## Board
<p align="center">  <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/pcb_render.gif" alt="pcb_render"  width="80%" height="80%"/><br><b>PCB Render</b></p>

Built using KiCAD, the board is design to be as small as possible. The following design are based on the latest revision.
| Top Board | Bottom Board |
|--|--|
| <p align="center"> <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/assembled_front.jpg" alt="assembled_front"  width="90%" height="90%"/></p> | <p align="center"> <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/assembled_back.jpg" alt="assembled_back"  width="90%" height="90%"/></p> |
| <p align="center"> <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/pcb_front.png" alt="pcb_front"  width="100%" height="100%"/></p> | <p align="center"> <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/pcb_back.png" alt="pcb_bottom"  width="80%" height="80%"/></p> |

 <p align="center"> <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/hardware/pcb.png" alt="pcb"  width="80%" height="80%"/><br><b>PCB Top and Bottom Layout</b></p> 
  
### Case
<p align="center">  <img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/case_render.gif" alt="case_render"  width="80%" height="80%"/></p>

The case is design by [atmakers](https://www.thingiverse.com/atmakers/designs) with **Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0)** license.
The cases are 3D printable with any generic 3D printer with/without suppport (depends on the orientation). The STL files are available from authors download page  [here](https://www.thingiverse.com/thing:3212895) or from [this](https://github.com/teapotlaboratories/feather-rak3172/tree/main/hardware/case) repo.
 <p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/case_open.jpg" alt="drawing"  width="50%" height="50%"/><br><b>Case Open</b></p>
 
### Measurement
Power consumption measured using [Nordic PPK2](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2). The following are the summary of the measurement:
- Sleep and all jumper disabled (JP1 - JP6): **10.44 uA**
- Sleep and UART-Bridge enabled ( JP3, JP5, and JP6 ): **23.76 uA**
- Sleep, UART-Bridge and Battery Sense enabled ( JP1, and JP3 - JP6 ): **25.41 uA** 
- Transmit at 14 dBm: **40.45 mA**
- Transmit at 20 dBm: **100.38 mA**

More detailed measurement can be found [here](https://github.com/teapotlaboratories/feather-rak3172/tree/main/docs/measurement)

### Bill Of Materials
Most of the components are generic and can be bought from any electornics/semi-conductor distributor. RAK3172 is the only component available in [RAKwireless store](https://store.rakwireless.com/products/wisduo-lpwan-module-rak3172?variant=40014759493830). The bill of materials can be downloaded [here](https://github.com/teapotlaboratories/feather-rak3172/raw/main/hardware/bill_of_materials.csv)

> :warning: **Be sure to buy the RAK3172 variant without IPEX to use SMA connector** 

|Id|Designator|Quantity|Value|Footprint|
|:----|:----|:----|:----|:----|
|1|C11,C7,C4,C1|4|100n|0603_1608Metric|
|2|C6,C3|2|10u|0603_1608Metric|
|3|C9,C8,C10|3|10u|0805_2012Metric|
|4|D1|1|BLUE|0603_1608Metric|
|5|D2|1|ORANGE|0603_1608Metric|
|6|D3|1|B5819W|SOD-123|
|7|J3|1|U262-161N-4BVC11|USB_C_Receptacle_XKB_U262-16XN-4BVC11|
|8|J4|1|SMA-KE-P903|SMA-KE-P903|
|9|J6|1|S2B-PH-SM4-TB|JST_PH_S2B-PH-SM4-TB_1x02-1MP_P2.00mm_Horizontal|
|10|L1|1|0|0402_1005Metric|
|11|Q1|1|DMG3415UQ-7|SOT-23|
|12|R10|1|10M|0603_1608Metric|
|13|R2,R6,R1|3|1k|0603_1608Metric|
|14|R3,R5,R4|3|5.1k|0603_1608Metric|
|15|R7,R8|2|10k|0603_1608Metric|
|16|R9|1|4.7M|0603_1608Metric|
|17|SW1|1|B3U-1000P|SW_SPST_B3U-1000P|
|18|SW2|1|B3U-1000P|SW_SPST_B3U-1000P|
|19|U1|1|RAK3172|RAK3172|
|20|U2|1|CH340E|MSOP-10_3x3mm_P0.5mm|
|21|U3|1|MCP73831T-2ACI/OT|SOT-23-5|
|22|U4|1|XC6220B331MR-G|SOT-23-5|
|23|C5,C2|2|DNP|0402_1005Metric|
|24|J2|1|DNP|PinHeader_1x12_P2.54mm_Vertical|
|25|J1|1|DNP|PinHeader_1x16_P2.54mm_Vertical|


## Programming

By default, programming the device can be done over  the **USB-C**. Internally, the USB-C connects to the UART-Bridge that connects to the **UART2** port of the RAK3172. Out of the factory, the RAK3172 chip ships with an **AT firmware** that can be tested by sending AT command via the USB-C.

Using the USB-C, user can program the board using the **Arduino** or **MbedOS/STM32Cube** SDK.
The following are some very good tutorial to start developing with the device:
 - [Communicating with the AT firmware](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Quickstart/#rak3172-as-a-lora-lorawan-modem-via-at-command)
 - [Programming with Arduino](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Quickstart/#rak3172-as-a-stand-alone-device-using-rui3)
 - [Programming with STM32Cube](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Low-Level-Development/#rak3172-on-stm32cubeide-with-stm32wl-sdk-v1-0-0)
	 - RAKDAP1 is not needed. Before connecting to **STM32CubeProgrammer**, hold `BOOT` and press `RESET` on the board, to boot to UART bootloader of the RAK3172. After `RESET` button is pressed, `BOOT` button can be released, and the board should be able to connect to the **STM32CubeProgrammer**
 - [Programming with MbedOS](https://github.com/hallard/LoRa-E5-Tiny/blob/main/README.md#compile-and-flash-firmware)
	 - Programming the board can be done **without** using the ST-LINK, it should be simillar to [Programming with STM32Cube](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Low-Level-Development/#rak3172-on-stm32cubeide-with-stm32wl-sdk-v1-0-0) process.


## Example Project
Teapot Feather RAK3172 is a feather compatible board, and hence is compatible with the many available FeatherWing. The following are some example project that uses FeatherWings.

### Over-engineered Clock 
An over-engineered clock with main purpose to showcase FeatherWings compatibility.
FeatherWings and sensors used:  
- Ultimate GPS ( adafruit.com/product/3133 )  
- Tri-Color E-Ink ( adafruit.com/product/4814 )  
- Qwiic Shield ( sparkfun.com/products/16790 )  
- BME680 ( adafruit.com/product/3660 )  
- Modified E-Ink Case ( learn.adafruit.com/eink-featherwing-display-stand )

<p align="center">
<img align="center" width="38%" height="38%" src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/gps_clock_front.jpg">
<img align="center" width="34%" height="34%" src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/gps_clock_side.jpg">
<br><b>Front and Side View</b></p>

<p align="center">  
<img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/images/gps_clock_back.jpg" alt="pcb_render"  width="50%" height="50%"/>
<br><b>Back View</b>
</p>
 
## Reference
The project won't be possible without the amazing work from people across the globe. The following are the reference to those awesome projects:

 - [Adafruit Feather RP2040](https://github.com/adafruit/Adafruit-Feather-RP2040-PCB)
 - [Penguino STM32WL LoRa-E5](https://github.com/azerimaker/Penguino-STM32WL-LoRa-E5)
 - [BastWAN-WLE](https://github.com/ElectronicCats/BastWAN-WLE)

## License
The product is open-source! However, some part of library used under **src**, might have it's own license.
Please reach out or create a ticket to report any license violation.

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
