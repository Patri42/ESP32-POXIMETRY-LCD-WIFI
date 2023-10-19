# ESP32 with LCD and PPG to Measure BPM and Oximetry Level

This project is designed to measure BPM and oximetry levels using ESP32 integrated with an LCD and a PPG (max30102). The measured data is then sent to ThingSpeak for observation and data storage.

## Table of Contents

- [Inspiration](#inspiration)
- [Project Structure](#project-structure)
- [Unit Tests](#unit-tests)
- [Demonstration Video](#demonstration-video)
- [Diagrams](#diagrams)
- [Source Code Management on GitHub](#source-code-management-on-gitHub)
- [Development Process](#development-process)

## Inspiration

This project draws inspiration from two of my previous projects:
- **ESP32-MAX30102**: An initial exploration into interfacing the ESP32 with the MAX30102 sensor.
- **ESP32-WIFI-Thingspeak**: An endeavor where I worked on connecting the ESP32 to WiFi and sending data to ThingSpeak.

Building upon the knowledge and experience gained from these projects, this current project aims to seamlessly integrate the capabilities of both into a comprehensive solution.

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

### Development Environment
The code for this project was written using [Visual Studio Code](https://code.visualstudio.com/) as the preferred IDE. The project utilizes the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) framework and is coded in the C programming language.

## Unit Tests

Unit tests for this project are currently under development.

## Demonstration Video

https://github.com/Patri42/ESP32-POXIMETRY-LCD-WIFI/assets/123195888/facbbd3f-6b16-4892-b47d-675998182d70

## Diagrams

## Source Code Management on GitHub
All source code for this project is managed and versioned on GitHub. Regular updates, commits, and modifications can be tracked in the repository's commit history.

## Development Process

