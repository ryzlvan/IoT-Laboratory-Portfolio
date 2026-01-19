# 📡 COSC 111: Internet of Things (IoT) Laboratory Portfolio

Welcome to the complete compilation of laboratory activities and examinations for the subject **COSC 111 (Internet of Things)**. This repository documents my journey in embedded systems, starting from basic digital signals to building full-stack web-controlled IoT solutions.

## 📂 Repository Structure & Activity Summaries

Below is a summary of every project included in this repository. Each folder contains the specific source code (Arduino sketches, Python scripts) and documentation for that activity.

### 🟢 Basics of Embedded Systems

**1. [Laboratory 1: Working with Digital Signals](./Laboratory%201%20-%20Working%20with%20Digital%20Signals%20-%20Running%20Light%20Circuit)**
* **Focus:** Digital Output & Arrays.
* **Description:** An introduction to Arduino General-Purpose Input/Output (GPIO control). This project implements a "Running Light" circuit using 5 LEDs, demonstrating the use of arrays and `for` loops to sequence digital signals.

**2. [Laboratory 2: Working with Analog Signals](./Laboratory%202%20-%20Working%20with%20Analog%20Signal)**
* **Focus:** PWM (Pulse Width Modulation) & Fading.
* **Description:** Moves beyond simple On/Off logic. It utilizes PWM capable pins to simulate analog output, creating a smooth "breathing" or fading effect on a series of LEDs using nested loops.
---
### 🟡 Sensors and Serial Communication

**3. [Laboratory 3: Fire Sensor Simulation](./Laboratory%203%20-%20Fire%20Sensor%20Simulation)**
* **Focus:** Analog Input & Sensor Logic.
* **Description:** A safety system simulation that reads data from a **Thermistor** (Temperature) and a **Photoresistor** (Light). It triggers an audible and visual alarm only when specific thresholds for both heat and light are met simultaneously.

**4. [Laboratory 4: Arduino Serial Connection](./Laboratory%204%20-%20Arduino%20Serial%20Connection)**
* **Focus:** Serial Input Parsing.
* **Description:** Demonstrates how to control the Arduino using text commands via the Serial Monitor. The system acts as a "latched" alarm that stays active until the user types a specific password ("stop") to reset it.
---
### 🟠 Advanced Serial & Python Integration

**5. [Laboratory 5: Receiving Serial Connection (Python to Arduino)](./Laboratory%205%20-%20Receiving%20Serial%20Connection%20using%20Arduino%20from%20Python)**
* **Focus:** Cross-Platform Control (PC to MCU).
* **Focus:** Cross-Platform Control (PC to MCU).
* **Description:** Establishes a one-way communication link where a **Python script** running on a laptop sends commands to the Arduino to control specific LEDs. This introduces the concept of using a high-level language to control hardware.

**6. [Laboratory 6: Bi-Directional Serial Communication](./Laboratory%206%20-%20Bi-Directional%20Serial%20Communication)**
* **Focus:** Round Trip Communication
* **Description:** Implements a feedback loop. When a physical button is pressed on the Arduino, it notifies Python. Python processes the request and sends a command back to the Arduino to toggle an LED.
  
---
### 🔴 IoT Web Architecture (Midterm and Final Projects)

**7. [Laboratory 7: Web Controlled IoT System with FastAPI](./Laboratory%207%20-%20Web%20Controlled%20IoT%20System%20with%20FastAPI)**
* **Focus:** Web APIs & HTTP.
* **Description:** A modern IoT implementation using **FastAPI**. It turns the computer into a local web server, allowing users to control Arduino hardware by visiting web URLs (e.g., `/led/red`).

**8. [Midterm Laboratory Exam: Smart Light Monitoring System](./%20Midterm%20Laboratory%20Exam%20-%20Smart%20Light%20Monitoring%20System)**
* **Focus:** Logic Modes & Dynamic Configuration.
* **Description:** An intelligent environment monitor with two operating modes: **Automatic** (classifies weather based on fixed values) and **Manual** (allows the user to update sensor thresholds dynamically via Serial commands).

**9. [Final Laboratory Exam: Remote API Trigger Client](./Final%20Laboratory%20Exam%20-%20Remote%20Button%20API%20Trigger)**
* **Focus:** Client-Side HTTP Requests.
* **Description:** A system where the Arduino acts as a physical trigger client. Pressing a button sends a signal to a Python script, which then makes an HTTP GET request to a remote API server to perform an action. This demonstrates how offline hardware can interact with the internet via a gateway.

---

## 🎓 Acknowledgment

As this semester concludes, I would like to express my gratitude for the knowledge gained in **COSC 111 - Internet of Things**.

This journey has taken me from understanding simple `HIGH/LOW` voltages to constructing complex, bi-directional communication systems between microcontrollers and web servers. The transition from hardware wiring to Python scripting and API development has been challenging but incredibly rewarding.

A special thank you to our instructor, **Mr. Johnroe Paulo Cañamaque**, for the guidance, patience, and for pushing us to understand not just the *how*, but the *why* behind Internet of Things architecture.

**"Hardware is the body, Software is the soul, and Connectivity is the heart of IoT."**

***
*Repository maintained for academic purposes.*
