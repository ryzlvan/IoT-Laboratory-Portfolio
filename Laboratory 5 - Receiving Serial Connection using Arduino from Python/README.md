# Laboratory Activity 5: Receiving Serial Connection using Arduino from Python

## 📖 Overview
This activity demonstrates **Receiving Serial Connection using Arduino from Python**. Instead of using the Arduino IDE's Serial Monitor, we create using **Python** Terminal to control hardware connected to the Arduino.

The project consists of two parts:
1.  **Arduino Code:** Listens for incoming character commands over the USB cable to toggle LEDs.
2.  **Python Script:** Runs on the computer, displaying a menu to the user and sending commands to the Arduino via the Serial Port.

This architecture is the foundation for IoT devices and computer-controlled automation.

*> **Technical Note:** This activity requires Python installed on your computer. You must also install the serial library by running `pip install pyserial` in your terminal/command prompt.*

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): Receives commands and controls LEDs.
* **1x Red LED**: Connected to Pin 8.
* **1x Green LED**: Connected to Pin 9.
* **1x Blue LED**: Connected to Pin 10.
* **3x Resistors** (220Ω - 330Ω): Current limiting resistors for the LEDs.
* **Computer**: Running the Python script.
* **USB Cable**: For power and data transmission.

## 🔌 Wiring Diagram
The LEDs are connected to digital pins 8, 9, and 10.

<img src="Breadboard Diagram.png" alt="Alt text for the image" width="1000" height="1000">

| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Red LED** | Pin 8 | Anode (+) to Pin 8, Cathode (-) to GND via resistor. |
| **Green LED** | Pin 9 | Anode (+) to Pin 9, Cathode (-) to GND via resistor. |
| **Blue LED** | Pin 10 | Anode (+) to Pin 10, Cathode (-) to GND via resistor. |
| **GND** | GND | Common ground for all LEDs. |

## 💻 Code Explanation
The logic is split between the **Arduino (Receiver)** and **Python (Sender)**.

### 1. Arduino Firmware (Receiver)
The Arduino code is split into two files for better organization:
* **Core Functions** (`LED_Controller.h`): This header file manages the hardware state. It contains the `checkInput(char)` function, which uses a `switch` statement to route commands (e.g., `'R'` calls `toggleRed()`).

```cpp
// --- LED_Controller.h (Core Helper Functions) ---
#ifndef LED_Controller_H
#define LED_Controller_H

#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10

void toggleRed() {
  redState = !redState;
  digitalWrite(RED_LED, redState);
}
// ... (other state variables)

void checkInput(char input){
  switch(input) {
      case 'R': toggleRed(); break;
      case 'G': toggleGreen(); break;
      case 'B': toggleBlue(); break;
      case 'A': allOn(); break;
      case 'O': allOff(); break;
      default: Serial.println("Error: Invalid input"); break;
  }
}
#endif
```

* **Main Loop** (`ArduinoLEDController.ino`): This listens to the serial port. When data arrives, it reads the string, cleans it, and passes the character to the controller logic.
```cpp
// --- ArduinoLEDController.ino ---
#include "LED_Controller.h"

void setup() {
  Serial.begin(9600);
  setupLEDs();
  Serial.println("Arduino LED Serial Controller Ready...");
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); // Clean whitespace

    if (inputString.length() != 1) return; // Validation
    
    char input = toupper(inputString.charAt(0));
    checkInput(input); // Execute command
  }
}
```
### 2. Python Script (Sender)
The Python script acts as the User Interface.
Library: Uses pyserial to communicate with the specific COM port (e.g., COM5).

**A. Setup & Connection Handshake of Port**
We import the `serial` library to talk to the USB port.
* **`try...except`:** We wrap the connection in a try block. If the Arduino is not plugged in or the wrong port is used, the script catches the error and prints a friendly message instead of crashing.
* **`time.sleep(2)`:** **Crucial Step.** When a serial connection opens, most Arduinos auto-reset. We pause for 2 seconds to allow the Arduino to reboot and be ready to receive data.

```python
# --- ArduinoLEDController.py ---
import serial
import time
import sys

arduino_port = "COM5" # <--- CHECK YOUR DEVICE MANAGER FOR THE CORRECT PORT

try:
    arduino = serial.Serial(arduino_port, 9600)
    time.sleep(2) # Wait for Arduino to reset/stabilize
except serial.SerialException:
    print(f"Error: Could not connect to {arduino_port}.")
    sys.exit()
```
B. **User Interface & Input Sanitization:** Inside the while True loop, we display the menu.

- **`input().strip().upper()`:** This cleans the user's input. If the user accidentally types "r " (with a space) or "r" (lowercase), this converts it to a clean "R", matching the cases expected by the Arduino.

C. **Data Transmission:** Serial ports transmit raw bytes, not text strings.

- **`command.encode('utf-8')`:** We must convert the Python string (e.g., "R\n") into bytes before sending.
- **`arduino.write(...)`:** Pushes the data down the USB cable.

```python
# Inside the main loop...
    choice = input("Enter selection: ").strip().upper()

    if choice in ['R', 'G', 'B', 'A', 'O']:
        command = choice + '\n'
        arduino.write(command.encode('utf-8')) # Convert String to Bytes
    elif choice == 'X':
        print("Closing connection...")
        arduino.close()
        sys.exit()
```
