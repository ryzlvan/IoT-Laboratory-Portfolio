# Laboratory Activity 1: Working with Digital Signals - Running Light Circuit

## 📖 Overview
This activity demonstrates how to control multiple digital outputs using arrays and loops. The project creates a sequential "running light" pattern where five LEDs turn on one by one, followed by a sequence where they turn off one by one.

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): The main microcontroller to execute the logic.
* **5x LEDs** (Any color): Visual indicators for the digital signals.
* **5x Resistors** (220Ω - 330Ω): Current limiting resistors to protect the LEDs.
* **Breadboard**: For prototyping the circuit without soldering.
* **Jumper Wires**: To connect the components to the Arduino pins.

## 🔌 Wiring Diagram
The LEDs are connected to digital pins 12 through 8.
Note: Connect the longer leg of the LED to the Pin, and the shorter leg to GND.

<img src="Breadboard Diagram.png" alt="Alt text for the image" width="1000" height="1000">

| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **LED 1** | Pin 12 | Anode (+) to Pin 12, Cathode (-)  |
| **LED 2** | Pin 11 | Anode (+) to Pin 11, Cathode (-)  |
| **LED 3** | Pin 10 | Anode (+) to Pin 10, Cathode (-) |
| **LED 4** | Pin 9 | Anode (+) to Pin 9, Cathode (-)  |
| **LED 5** | Pin 8 | Anode (+) to Pin 8, Cathode (-)  |
| **Ground and Resistor** | GND | **Note:** The resistor can be placed on either the Anode (+) or Cathode (-) side. Ensure the final leg connects to GND. |

## 💻 Code Explanation
The code uses an array to manage pin numbers efficiently, allowing the use of `for` loops rather than writing individual commands for every pin.
### 1. Global Variables
We define an array `ledPins[]` containing the digital pin numbers used.
```cpp
int ledPins[] = {12, 11, 10, 9, 8};
```

### 1. Setup
In setup(), a loop iterates through the ledPins array to configure each pin as an OUTPUT. This prepares the pins to drive the LEDs.
```cpp
void setup() {
  for (int i = 0; i < 5; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}
```
### 3. Main Loop
The loop() function consists of two sequential for loops:
- Turning ON: The first loop iterates through the array, setting each pin HIGH (ON) with a 1-second delay (1000 ms) between each activation.
- Turning OFF: The second loop iterates through the array again, setting each pin LOW (OFF) with a 1-second delay between each deactivation.
```cpp
void loop() {
  // Sequence ON
  for(int i = 0; i < 5; i++){
    digitalWrite(ledPins[i], HIGH);
    delay(1000);
  }

  // Sequence OFF
  for(int i = 0; i < 5; i++){
    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
}
```

