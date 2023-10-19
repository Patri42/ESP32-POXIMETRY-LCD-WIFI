# ESP32 with LCD and PPG to Measure BPM and Oximetry Level

This project is designed to measure BPM and oximetry levels using ESP32 integrated with an LCD and a PPG (max30102). The measured data is then sent to ThingSpeak for observation and data storage.

## Table of Contents

- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Unit Tests](#unit-tests)
- [Contributions](#contributions)

## Project Structure

The project consists of several files structured as follows:

- `CMakeLists.txt` - Main CMake configuration file.
- `connect_wifi.c` & `connect_wifi.h` - Manages the WiFi connection functionalities.
- `i2c-driver.c` & `i2c-driver.h` - Driver for the I2C interface.
- `lcd-manager.c` & `lcd-manager.h` - Manager to control and interface with the LCD.
- `lcd.c` & `lcd.h` - Basic driver for the LCD.
- `main.c` - Entry point of the program.
- `max30102.c` & `max30102.h` & `max30102-data.h` - Files related to the MAX30102 PPG sensor.
- `thingspeak-manager.c` & `thingspeak-manager.h` - Manages the connection and data transfer to ThingSpeak cloud.

## Unit Tests

Unit tests for this project are currently under development.

## Demonstration Video

https://github.com/Patri42/ESP32-POXIMETRY-LCD-WIFI/assets/123195888/facbbd3f-6b16-4892-b47d-675998182d70

## Documentation with Diagrams/Images

## Source Code Management on GitHub

## Development Process Documentation on GitHub
