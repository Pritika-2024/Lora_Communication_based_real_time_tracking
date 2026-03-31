# LoRa GPS Tracking System

## Introduction
This project implements a long-range wireless tracking system using LoRa communication. An STM32-based transmitter acquires real-time GPS coordinates and transmits them over LoRa, while an ESP32-based receiver processes and displays the received data. The system is optimized for low-power, long-distance IoT tracking.

---

## Project Overview
The system consists of two nodes:
- **Transmitter (STM32 + GPS + LoRa)**  
- **Receiver (ESP32 + LoRa)**  

<p align="center">
  <img src="docs/Block%20Diagram.jpeg" width="500">
</p>

---

## Technical Details

### Baud Rate
- GPS: 9600 bps  
- Serial: 115200 bps  

### Frequency of Operation
- LoRa: **433 MHz**

### STM32 Programming and Debugging
- Programming via **ST-Link (SWD interface)**  
- Pins: SWCLK, SWDIO, GND, VCC  
- Supports debugging (breakpoints, step execution)

### Communication Interfaces
- LoRa → Uses SPI communication with STM32  
- GPS → Uses UART communication with STM32  

### Hardware Connections

**LoRa (SX1278 → STM32)**
- NSS (CS) → SPI Chip Select  
- SCK → SPI Clock  
- MOSI → SPI MOSI  
- MISO → SPI MISO  
- DIO0 → External interrupt pin  

**GPS (NEO-6M → STM32)**
- TX → STM32 RX  
- RX → STM32 TX  
- VCC → 3.3V  
- GND → GND  

**ST-Link (Programming)**
- SWDIO → STM32 SWDIO  
- SWCLK → STM32 SWCLK  
- GND → GND  
- 3.3V → VCC  

---

## PCB Design
The transmitter circuit integrates STM32 with GPS (UART) and LoRa (SPI). A custom PCB was designed in KiCad for compact integration.

## Schematic
<p align="center">
  <img src="docs/Schematic.png" width="500">
</p>

---

## Components (BOM-Based)
- **STM32F103RBTx** (Main controller, LQFP-64)  
- **SX1278 LoRa Module (Ra-01)** (RF communication)  
- **NEO-6M GPS Module** (Location acquisition via UART)  
- **AP2112K-3.3 Voltage Regulator** (3.3V supply)  
- **Capacitors**  
  - 100nF (decoupling near ICs)  
  - 1µF (regulator stability)  
  - 10µF (bulk filtering)  
- **Resistors (10kΩ)** (pull-up/pull-down)  
- **Connectors**  
  - Battery input (2-pin)  
  - Reset header  
  - ST-Link header  

---

## Power Supply Design (External Power)
The system is powered using an external battery connected via a **2-pin header (BatteryConnector1)**.

- Regulated using **AP2112K-3.3 (LDO)**  
- 1µF capacitors at input/output for stability  
- 10µF bulk capacitor for transient response  
- 100nF capacitors for local decoupling  

### Power Flow
Battery → Regulator (3.3V) →  
STM32, LoRa, GPS  

Ensures stable 3.3V operation for all modules.

---

## PCB Layout
<p align="center">
  <img src="docs/PCB_design.png" width="500">
</p>

---

## Prototype
The hardware prototype validates real-time communication between transmitter and receiver.

<p align="center">
  <img src="docs/Prototype.jpeg" width="400">
</p>

---

## Basic Workflow
1. GPS provides latitude and longitude via UART  
2. STM32 processes and formats data  
3. LoRa transmits the data packet  
4. ESP32 receives and decodes the packet  
5. Output is displayed on serial monitor  

---

## Results
<p align="center">
  <img src="docs/Output.jpeg" width="400">
</p>

---

## Source Code

| File | Description |
|------|------------|
| [`src/transmitter.cpp`](./src/transmitter.cpp) | STM32 code for GPS data acquisition and LoRa transmission |
| [`src/receiver.cpp`](./src/receiver.cpp) | ESP32 code for LoRa reception and data decoding |

---

## Libraries Used

- **LoRa.h**  
  Used for interfacing with SX1278 module using SPI and handling packet transmission/reception.

- **TinyGPS++**  
  Parses raw NMEA data from GPS module into usable latitude and longitude values.

- **SPI.h**  
  Enables SPI communication between STM32/ESP32 and LoRa module.

- **SoftwareSerial (if used)**  
  Provides UART interface when hardware UART is limited (mainly for GPS).

---

## Tools Used
- KiCad (PCB design)  
- Arduino IDE (firmware development)  
- Embedded C (programming)
