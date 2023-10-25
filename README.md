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

### Component Optimization

For this project, the selected components - ESP32, LCD, and the MAX30102 sensor - have been carefully chosen and optimized with respect to business-critical parameters:

- **Price**: Each component was selected based on its cost-effectiveness, ensuring the project remains budget-friendly.
  
- **Power Consumption**: Power efficiency was a primary concern. The ESP32, LCD, and MAX30102 have been configured to operate with minimal energy wastage.
  
- **Performance**: While maintaining affordability and energy efficiency, the performance of the components was not compromised. The combination ensures accurate and efficient measurement and display of BPM and oximetry levels.
  
In practical terms, this project does not utilize any development board as such, but focuses solely on the microcontroller and the essential components, offering a streamlined and purpose-specific design.

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

### ThingSpeak Data Send Test for ESP32

#### Overview
This repository contains a test setup for the ESP32's functionality to send data to ThingSpeak. We've mocked the HTTP client calls to verify the behavior without actually sending data over the network. This approach ensures that our core logic functions correctly without relying on external factors like network connectivity or ThingSpeak's server status.

#### Key Components:

- **Mocked HTTP Client:** Instead of making actual network calls, the mock functions simulate the behavior of the `esp_http_client`. They provide controlled responses to the main code, ensuring we can consistently reproduce various scenarios for testing.

- **Test Logic:** The test function, `test_successful_data_send`, checks whether our code correctly initializes the mock HTTP client, sets the expected header, and constructs the correct URL to send data.

#### Testing Instructions:

1. Ensure you've installed the required dependencies, especially the [PlatformIO](https://platformio.org/) CLI.
2. Navigate to the project's root directory.
3. Run the test with the following command:

```bash
pio test -vvv
```
This command will execute the tests with very verbose output (-vvv), giving you detailed information on each step of the test.

Once the tests are complete, you should see a summary indicating whether the tests passed or failed.

## Demonstration Video

https://github.com/Patri42/ESP32-POXIMETRY-LCD-WIFI/assets/123195888/facbbd3f-6b16-4892-b47d-675998182d70

## Diagrams
![setup1](https://github.com/Patri42/ESP32-POXIMETRY-LCD-WIFI/assets/123195888/ea925538-89c2-4900-920a-d2055831acc6)

### Hardware Connections

#### LED to ESP32 Connections:

| **LED Pin** | **ESP32 Pin**  |
|-------------|----------------|
| K           | GND            |
| A           | 5V             |
| D7          | RX2            |
| D6          | TX2            |
| D5          | D18            |
| D4          | D19            |
| E/R         | D22            |
| RW          | GND            |
| V0          | Potentiometer  |
| VSS         | GND Pot        |
| VDD         | 5V Pot         |

#### MAX30102 to ESP32 Connections:

| **MAX30102 Pin** | **ESP32 Pin** |
|------------------|---------------|
| VIN              | 3V3           |
| SDA              | D21           |
| SCL              | D5            |
| GND              | GND           |

## Source Code Management on GitHub
All source code for this project is managed and versioned on GitHub. Regular updates, commits, and modifications can be tracked in the repository's commit history.

## Development Process

### Ideation and Initial Planning:

#### Core Idea and Inspiration:

The spark behind this project stemmed from my background in physiotherapy. As someone deeply immersed in healthcare, I've always been curious about the workings of various medical devices. One such device, the pulse oximeter, caught my attention. My inquisitiveness led me to wonder about the mechanism behind its operation and its potential in cloud data transfer. This thought was the cornerstone of my project. The overarching goal was clear: Develop a method to transmit data directly from a sensor to cloud storage.

#### Component Selection Reasons:

My choices for the core components - ESP32, LCD, and MAX30102 - were driven by a mix of cost-effectiveness and energy efficiency. Moreover, I intended to make the most out of the C programming language. Through rigorous research and trial, I found that these components offered the best balance in terms of cost, power consumption, and functionality.

### Hardware Integration:

#### Prototyping Challenges:

The initial stages of prototyping weren't smooth . I initially began with Arduino Uno and tried using AVR-C. However, the limitations soon became evident, prompting a switch to ESP32. This transition was fueled by ESP32's robust capabilities and the ease of coding it offered, especially with the ESP-IDF framework.

#### Validation Findings:

From a hardware integration standpoint, this project wasn't particularly challenging in terms of setup. The connections were straightforward, with minimal complications.

### Software Development:

#### Environment Challenges:

Diving into the ESP-IDF and Platform IO was like stepping into a whole new world for me. Sure, I knew a bit about some of the parts, but putting together the WiFi, LED display, and the sensor? That was something I hadn't tackled before. It was tough, but with a bit of grit, I got the hang of it. 

#### Individual Module Challenges:

The project necessitated extensive code modification. Drawing from various sources on GitHub, I had to reshape the code to fit the project's unique requirements. One particular challenge was managing queuetasks, which took considerable effort to streamline.

#### Integration Challenges:

After wrestling with the queuetasks and streamlining their operation, the integration of different modules became a smoother process.

### Testing:

#### Unit Testing:

Choosing the appropriate unit testing method posed its own set of challenges. While there were multiple options like unity and googletest, I eventually settled on unity because of its prevalent use in ESP-IDF projects.

#### Integration Testing:

Hardware-based tests proved to be a stumbling block. Encountering issues with the ESP32's reset button, I pivoted to mock testing, relying on mock functions and variables for validation.

#### Performance Testing:

Performance testing didn't yield any standout benchmarks or challenges.

### Iteration and Feedback:

#### Initial Testing Feedback:

The first round of testing with the ThingSpeak Data Send Test yielded successful results. However, challenges arose when attempting to use googletest with a Makefile, primarily due to compatibility issues with ESP-IDF libraries.

#### Significant Iterations:

Based on feedback and test results, no major iterations or overhauls were needed for the project.

### Documentation and Deployment:

#### Documentation Challenges:

I adopted a proactive approach to documentation by maintaining records throughout the development process. This strategy proved invaluable, especially in keeping track of progress and revisiting earlier stages of the project.

### Miscellaneous:

#### Major Challenges:

Throughout the project's lifecycle, I faced and overcame numerous unforeseen challenges.

#### Collaborations:

My programming teacher and fellow classmates played a pivotal role in guiding me through the intricacies of the development process. Their invaluable input and expertise significantly influenced the project's direction and success.

