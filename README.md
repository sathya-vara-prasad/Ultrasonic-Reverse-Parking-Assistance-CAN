# Ultrasonic Reverse Parking Assistance System
### CAN Protocol | ARM7 LPC21xx | Embedded C

![Platform](https://img.shields.io/badge/Platform-LPC21xx%20ARM7-blue)
![Protocol](https://img.shields.io/badge/Protocol-CAN%202.0B-orange)
![Language](https://img.shields.io/badge/Language-Embedded%20C-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

---

##  Overview

The **Ultrasonic Reverse Parking Assistance System** is an embedded application
that uses two ARM7 LPC21xx microcontrollers communicating over the **CAN 2.0B**
protocol to provide real-time proximity alerts during vehicle reversing.

Node A (Master) initiates a CAN Remote Frame to request distance data.
Node B (Sensor Node) reads the ultrasonic sensor, encodes the proximity zone,
and responds with a CAN Data Frame. Node A then triggers the appropriate
buzzer/LED alert based on the received zone value.

---

## System Architecture
┌─────────────────────┐ CAN Bus ┌─────────────────────┐
│ NODE A │◄────────────────────────►│ NODE B │
│ (Master/Alert) │ │ (Sensor/Responder) │
│ │ 1. Sends Remote Frame │ │
│ - Buzzer │ ─────────────────────────►│ - HC-SR04 Sensor │
│ - LED Indicators │ │ - get_range() │
│ - UART Debug │ 2. Receives Data Frame │ - UART Debug │
│ │◄─────────────────────────-│ │
└─────────────────────┘ └─────────────────────┘
CAN ID: 0x123 CAN ID: 0x456

---

## Features

- CAN 2.0B protocol-based dual-node communication
- Interrupt-driven CAN frame reception (`flag_rx`)
- 5-level proximity zone detection
- Real-time ultrasonic distance measurement
- UART debug output at 9600 baud on both nodes
- 50 ms sensor polling rate for responsive detection
- Scalable architecture — easily extendable to multi-node CAN network

---

##  Proximity Zone Table

| `byteA` Value | Distance Range | Zone        | Action (Node A)         |
|:-------------:|:--------------:|:-----------:|:------------------------|
| `0x11`        | ≥ 150 cm       | Safe      | No alert                |
| `0x22`        | 100 – 149 cm   | Caution  | Slow blink / soft beep  |
| `0x33`        | 50 – 99 cm     | Warning  | Fast blink / beep       |
| `0x44`        | 10 – 49 cm     | Danger   | Rapid beep              |
| `0x55`        | ≤ 9 cm         | Critical | Continuous alarm — STOP |

---

## Repository Structure

Ultrasonic-Reverse-Parking-Assistance-CAN/
│
├── README.md
│
├── src/
│ ├── node_b_rx/
│ │ ├── main_rx.c # Node B — Sensor + CAN transmitter
│ │ └── header.h # Peripheral driver declarations
│ │
│ ├── node_a_tx/
│ │ ├── main_tx.c # Node A — CAN receiver + Alert logic
│ │ └── header.h
│ │
│ └── common/
│ ├── can2_driver.c # CAN2 init, TX, RX, interrupt
│ ├── uart0_driver.c # UART0 init and TX string
│ └── us_sensor.c # HC-SR04 get_range() implementation
│
├── docs/
│ ├── circuit_diagram.png # Hardware connection schematic
│ └── project_report.pdf # Detailed project documentation
│
└── hardware/
└── components_list.md # Bill of materials



---

## Hardware Requirements

| Component                  | Quantity | Notes                        |
|:---------------------------|:--------:|:-----------------------------|
| LPC21xx ARM7 Dev Board     | 2        | Nodes A and B                |
| HC-SR04 Ultrasonic Sensor  | 1        | Connected to Node B          |
| Buzzer (Active)            | 1        | Connected to Node A          |
| LED Indicators             | 3–5      | Alert levels on Node A       |
| DB-9 Connector / CAN cable | 1        | CAN H/L bus wiring           |
| UART-to-USB Module         | 2        | For debug monitoring         |
| Power Supply (5V/3.3V)     | 1        | For both nodes               |

---

## CAN Bus Pin Connections

| Signal  | LPC21xx Pin |
|:--------|:-----------:|
| CAN2 TX | P0.14       |
| CAN2 RX | P0.15       |
| GND     | Common GND  |

>  **Note:** Connect a **120Ω termination resistor** across CAN H and CAN L
> at both ends of the bus for signal integrity.

---

## Software Setup

### Prerequisites
- Keil µVision 4/5 IDE
- LPC21xx CMSIS / startup files
- Flash Magic (for programming via UART ISP)

### Build & Flash
1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/Ultrasonic-Reverse-Parking-Assistance-CAN.git
   ```
2. Open `node_a_tx/` and `node_b_rx/` projects separately in Keil µVision
3. Build each project (`F7`)
4. Flash `.hex` files to respective boards using **Flash Magic**
5. Open a serial terminal (e.g., Tera Term) at **9600 baud** to view debug output

---

## CAN Frame Details

**Remote Frame (Node A → Node B)**
ID : 0x123
RTR : 1 (Remote Frame)
DLC : 1

**Data Frame (Node B → Node A)**
ID : 0x456
RTR : 0 (Data Frame)
DLC : 1
Data : byteA (0x11 / 0x22 / 0x33 / 0x44 / 0x55)

---

## UART Debug Output

**Node B Console:**
NODE B
RMOTE FRAME iS RECIVED
data frame is recived

**Node A Console:**
NODE A
REMOTE FRAME SENT
DATA RECEIVED: 0x33 → WARNING ZONE


---

## Applications

- Automotive reverse parking assistance (ADAS prototype)
- Industrial obstacle detection over CAN network
- Multi-node sensor fusion systems in vehicles
- Embedded systems academic/training projects

---

## Author

**Your Name**
Embedded Systems Engineer
sathyaprasadkotapati@gmail.com
🔗 [LinkedIn](https://linkedin.com/in/yourprofile) | [GitHub](https://github.com/yourusername)

---

## License

This project is licensed under the **MIT License** — see the
[LICENSE](LICENSE) file for details.

---

> *"Bringing CAN protocol intelligence to real-world parking safety — one frame at a time."*
