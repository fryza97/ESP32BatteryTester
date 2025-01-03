# ESP32 Battery Tester
ESP-IDF program for ESP32 development board that enables Wi-Fi controlled battery voltage measurements.

## Overview
![image](https://github.com/user-attachments/assets/d28f493a-77b4-4bbe-8813-5f5a2855e7b9)  
*Image 1: Block diagram*

The device creates a Wi-Fi access point named "ESP32 - batterytester". After connecting to this network, users can access a web interface to perform battery measurements using two different probes:

- **Red probe**: Connected via voltage divider for higher voltage measurements (with lower resolution in low range)
- **Green probe**: Direct ADC connection for lower voltage measurements (with higher resolution in low range)

The tester utilizes two channels of ADC1 (channels 4 and 5), enabling simultaneous measurement of two batteries.

## Web Interface
| ![image](https://github.com/user-attachments/assets/e3b8b3e2-7a1f-4eb7-91a2-9dae201d017c) | ![image](https://github.com/user-attachments/assets/8ed2df75-227b-43eb-815f-028f88e54324) |
|------------|------------|
| *Image 2: Website layout when probes are not connected* | *Image 3: Website layout showing measurements (CH1: 12V, CH2: 3.3V)* |



