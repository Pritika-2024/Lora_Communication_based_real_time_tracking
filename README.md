# LoRa GPS Tracking System (STM32 + ESP32)

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

## Circuit Implementation and PCB Design
The transmitter circuit integrates STM32 with GPS (UART) and LoRa (SPI). A custom PCB was designed in KiCad for compact integration.

<p align="center">
  <img src="docs/Circuit_Implementation.jpeg" width="350">
</p>

---

## Components (BOM-Based)
- **STM32F103RBTx** (Main controller, LQFP-64)  
- **SX1278 LoRa Module (Ra-01)** (RF communication)  
- **NEO-6M GPS Module** (Location acquisition via UART)  
- **AP2112K-3.3 Voltage Regulator** (3.3V supply)  
- **Capacitors**  
  - 100nF (decoupling near ICs)  
  - 1µF (stability for regulator)  
  - 10µF (bulk filtering)  
- **Resistors (10kΩ)** (pull-up/pull-down for stable logic)  
- **Connectors**  
  - Battery input (2-pin header)  
  - Reset button header  
  - ST-Link programming header (SWD)  

---

## Power Supply Design (External Power)
The system is powered using an external battery connected via a **2-pin header (BatteryConnector1)**.

- The input voltage is regulated using **AP2112K-3.3**, a low-dropout regulator.
- **Input capacitor (1µF)** stabilizes the incoming supply.
- **Output capacitor (1µF)** ensures regulator stability.
- A **10µF bulk capacitor** handles transient load changes.
- Multiple **100nF capacitors** are placed close to STM32, LoRa, and GPS modules for noise suppression.

### Power Flow
Battery → Regulator (3.3V) →  
- STM32  
- LoRa Module  
- GPS Module  

This ensures all components operate at a stable **3.3V level**, which is critical for STM32 and SX1278.

---

## Schematic
<p align="center">
  <img src="docs/Schematic.png" width="500">
</p>

---

## PCB Design
<p align="center">
  <img src="docs/PCB_design.png" width="500">
</p>

---

## Prototype and Output
The hardware prototype validates real-time communication between transmitter and receiver.

<p align="center">
  <img src="docs/Prototype.jpeg" width="400">
</p>

<p align="center">
  <img src="docs/Output.jpeg" width="400">
</p>

---

## LoRa vs WiFi
| Feature | LoRa | WiFi |
|--------|------|------|
| Range | Long (km-level) | Short (meters) |
| Power Consumption | Low | High |
| Data Rate | Low | High |

LoRa is selected for its long-range and low-power characteristics, making it suitable for tracking applications.

---

## Basic Workflow
1. GPS provides latitude and longitude via UART  
2. STM32 processes and formats data  
3. LoRa transmits the data packet  
4. ESP32 receives and decodes the packet  
5. Output is displayed on serial monitor  

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
- LoRa → SPI  
- GPS → UART  

---

## Results
- Reliable long-range transmission of GPS data  
- Stable communication between STM32 and ESP32  
- Suitable for real-time tracking applications  

---

## Tools Used
- KiCad (PCB design)  
- Arduino IDE (firmware)  
- Embedded C (development)
