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
| ![image](https://github.com/user-attachments/assets/5066aab6-7afc-4cd8-b94d-e702210f31ee) | ![image](https://github.com/user-attachments/assets/4ae00c53-346c-42bd-a434-c38bef4a366a)|
|------------|------------|
| *Image 2: Website layout when probes are not connected* | *Image 3: Website layout showing measurements (CH1: 5V, CH2: 3.3V)* |



