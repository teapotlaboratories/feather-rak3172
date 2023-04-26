# Measurement
Power consumption measured using [Nordic PPK2](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2). The following are the summary of the measurement:
- Sleep and all jumper disabled (JP1 - JP6): **10.44 uA**
- Sleep and UART-Bridge enabled ( JP3, JP5, and JP6 ): **23.76 uA**
- Sleep, UART-Bridge and Battery Sense enabled ( JP1, and JP3 - JP6 ): **25.41 uA** 
- Transmit at 14 dBm: **40.45 mA**
- Transmit at 20 dBm: **100.38 mA**

## Sleep and all jumper disabled
<p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/measurement/DisableAllJumper_Sleep.png" alt="disable_all_jumper_sleep"  width="90%" height="90%"/></p>

## Sleep, Enable UART Bridge
<p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/measurement/UARTBridge_Sleep.png" alt="uart_bridge_sleep"  width="90%" height="90%"/></p>

## Sleep, Enable UART Bridge and Battery Sense
<p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/measurement/UARTBridge_BatterySense_Sleep.png" alt="uart_bridge_battery_sense_sleep"  width="90%" height="90%"/></p>

## Transmit at 14 dBm
<p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/measurement/UARTBridge_BatterySense_Sleep_14dBm.png" alt="uart_bridge_battery_sense_sleep_14dbm"  width="90%" height="90%"/></p>

## Transmit at 20 dBm
<p align="center"><img src="https://github.com/teapotlaboratories/feather-rak3172/raw/main/docs/measurement/UARTBridge_BatterySense_Sleep_20dBm.png" alt="uart_bridge_battery_sense_sleep_20dbm"  width="90%" height="90%"/></p>
