# Laboratory Activity 6: Bi-Directional Serial Communication

## 📖 Overview
This activity demonstrates a **closed-loop "Round Trip" system**. Unlike previous activities where communication was one-way (Arduino from Python [Laboratory 5] ), this system utilizes both directions simultaneously.

The logic follows this path:
1.  **Input:** User presses a button on the Arduino.
2.  **Request:** Arduino sends a request code ('R', 'G', or 'B') to the Python script.
3.  **Processing:** The Python script receives the code, logs the event, and determines the appropriate action.
4.  **Command:** Python sends a command back ('1', '2', or '3') to the Arduino.
5.  **Action:** Arduino receives the command and toggles the corresponding LED.

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): Acts as the I/O controller.
* **3x LEDs** (Red, Green, Blue): Output indicators.
* **3x Push Buttons**: Input triggers.
* **3x Resistors** (220Ω - 330Ω): Current limiting for LEDs.
* **Breadboard & Jumper Wires**: For connections.
* **Computer**: Runs the Python logic script.

## 🔌 Wiring Diagram
The pin assignments have changed from previous activities to accommodate both buttons and LEDs.

<img src="Breadboard Diagram.jpeg" alt="Alt text for the image" width="1000" height="1000">

| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Red LED** | Pin 7 | Anode (+) to Pin 7, Cathode (-) to GND via resistor. |
| **Green LED** | Pin 6 | Anode (+) to Pin 6, Cathode (-) to GND via resistor. |
| **Blue LED** | Pin 5 | Anode (+) to Pin 5, Cathode (-) to GND via resistor. |
| **Button 1** | Pin 12 | One leg to Pin 12, other leg to GND. |
| **Button 2** | Pin 11 | One leg to Pin 11, other leg to GND. |
| **Button 3** | Pin 10 | One leg to Pin 10, other leg to GND. |
| **GND** | GND | Common ground for all LEDs and Buttons. |

> **Wiring Note:** The buttons utilize the Arduino's internal Pull-Up resistors (`INPUT_PULLUP`). You do **not** need external resistors for the buttons. Simply connect the button between the Signal Pin and Ground.

## 💻 Code Explanation

### 1. Arduino Firmware
The Arduino code handles two parallel tasks inside the `loop()`:

**A. Inbound (Receiving from Python)**
It checks if data is available from the computer. If it receives '1', '2', or '3', it toggles the specific LED.
```cpp
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    char input = inputString[0]; // Get first char

    switch (input) {
      case '1': toggleRed(); break;
      case '2': toggleGreen(); break;
      case '3': toggleBlue(); break;
    }
  }
```
**B. Outbound (Sending to Python)**
It reads the buttons. To prevent sending thousands of messages while a button is held down, it uses State Change Detection. It only sends a signal when the button transitions from HIGH (Released) to LOW (Pressed).

```cpp
int currentBtn1 = digitalRead(BTN_1);

  // Check for "Falling Edge" (Press event)
  if (lastBtn1State == HIGH && currentBtn1 == LOW) {
    Serial.print("R\n"); // Signal Python that Red button was pressed
    delay(50);           // Debounce
  }
  lastBtn1State = currentBtn1; // Save state for next loop
```
### 2. Python Script
The Python script acts as an automated relay. It runs an infinite loop that constantly checks for incoming messages.

Logic Flow:
- **Read:** arduino.readline() waits for data.
- **Decide:** It checks if the data is 'R', 'G', or 'B'.
```python
while True:
    if arduino.in_waiting > 0:
        # Read from Arduino
        data = arduino.readline().decode('utf-8').strip()

        # Decision Logic
        if data == 'R':
            print("Received 'R' -> Sending '1'")
            send_command('1') # Command Arduino to toggle Red
        elif data == 'G':
            print("Received 'G' -> Sending '2'")
            send_command('2')
        elif data == 'B':
            print("Received 'B' -> Sending '3'")
            send_command('3')
```
- **Respond:** It immediately writes the corresponding toggle command ('1', '2', or '3') back to the Arduino.
```python
def send_command(command):
    """
    Sends a command to Arduino with the required newline character.
    """
    full_command = command + '\n'
    arduino.write(full_command.encode())
    arduino.flush()
```
