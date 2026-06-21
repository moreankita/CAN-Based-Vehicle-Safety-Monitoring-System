# CAN-Based Vehicle Safety and Monitoring System

## Project Overview

This project is a CAN-Based Vehicle Safety and Monitoring System developed using LPC2129 microcontrollers. The system demonstrates how multiple embedded nodes can communicate using the Controller Area Network (CAN) protocol for automotive safety applications.

The project consists of three independent nodes:

1. Main Node
2. Indicator Node
3. Reverse Alert Node

All nodes communicate through CAN protocol to provide real-time monitoring and safety features.

---

## Objective

To design and develop an automotive safety and monitoring system using CAN communication, where:

- Engine temperature is continuously monitored.
- Vehicle indicators are controlled through interrupts.
- Reverse obstacle detection is performed using an ultrasonic sensor.
- Safety alerts are communicated between nodes through CAN.

---

## System Architecture

### Main Node

Functions:
- Reads engine temperature using DS18B20 sensor.
- Displays information on LCD.
- Handles left and right indicator interrupts.
- Sends indicator commands through CAN.
- Receives reverse alert messages from Reverse Alert Node.
- Provides warning indication during reverse mode.

### Indicator Node

Functions:
- Receives CAN messages from Main Node.
- Controls left and right vehicle indicators.
- Displays indicator status using LEDs and custom LCD symbols.

### Reverse Alert Node

Functions:
- Measures obstacle distance using HC-SR05 ultrasonic sensor.
- Compares measured distance with predefined threshold.
- Sends obstacle alert information to Main Node through CAN.

---

## Hardware Requirements

- LPC2129 Microcontroller
- MCP2551 CAN Transceiver
- DS18B20 Temperature Sensor
- HC-SR05 Ultrasonic Sensor
- 16x2 LCD
- LEDs
- Push Buttons / Switches
- USB to UART Converter
- Power Supply

---

## Software Requirements

- Embedded C
- Keil uVision
- Flash Magic

---

## Communication Protocol

### CAN Protocol

The nodes communicate using Controller Area Network (CAN) protocol.

Advantages:
- Multi-node communication
- High reliability
- Error detection capability
- Reduced wiring complexity
- Suitable for automotive applications

---

## Project Flow

### Main Node Flow

1. Initialize peripherals.
2. Read temperature from DS18B20.
3. Display temperature on LCD.
4. Detect indicator switch interrupts.
5. Send indicator status through CAN.
6. Monitor reverse mode.
7. Receive obstacle alerts from Reverse Alert Node.
8. Generate warning indication if obstacle is detected.

### Indicator Node Flow

1. Initialize CAN.
2. Wait for CAN message.
3. Receive indicator command.
4. Activate corresponding indicator LEDs.
5. Display indicator direction.

### Reverse Alert Node Flow

1. Initialize ultrasonic sensor.
2. Measure obstacle distance.
3. Compare distance with threshold.
4. Send alert through CAN if obstacle detected.
5. Continue monitoring.

---

## Features

- CAN-based communication
- Engine temperature monitoring
- Reverse obstacle detection
- Interrupt-based indicator control
- Custom LCD indicator symbols
- Real-time monitoring
- Modular node architecture

---

## Folder Structure

```text
CAN-Based-Vehicle-Safety-Monitoring-System
│
├── main_node
│
├── indicator_node
│
├── reverse_node
│
├── Images
│
└── README.md
```

---

## Learning Outcomes

Through this project, the following concepts were implemented and understood:

- Embedded C Programming
- LPC2129 Microcontroller
- CAN Communication Protocol
- Interrupt Handling
- LCD Interfacing
- DS18B20 Sensor Interfacing
- Ultrasonic Sensor Interfacing
- Real-Time Embedded Systems

---

## Applications

- Automotive Safety Systems
- Vehicle Monitoring Systems
- Industrial Monitoring Systems
- Distributed Embedded Systems
- Smart Transportation Solutions

---

## Author

Ankita More

Embedded Systems Project
