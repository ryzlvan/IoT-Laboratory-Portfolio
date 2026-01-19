# Laboratory Activity 7: Web Controlled IoT System with FastAPI

## 📖 Overview
This activity demonstrates how to implement an HTTP-based IoT System. By integrating FastAPI (a modern Python web framework) with Arduino serial communication, we create a web server that can control hardware components. The system allows users to toggle specific LEDs or control all of them simultaneously by sending HTTP requests to API endpoints (e.g., visiting a URL like /led/red). 

*> **Technical Note:** You must install the required Python libraries before running this script. Open your terminal and run:*
`pip install "fastapi[standard]" pyserial`

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): Acts as the serial-controlled actuator.
* **3x LEDs** (Red, Green, Blue): Visual indicators.
* **3x Push Buttons**: Input devices.
* **3x Resistors** (220Ω - 330Ω): Current limiting for LEDs.
* **Breadboard & Jumper Wires**: For circuit assembly.
* **Laptop/PC**: Running the Python FastAPI server.

## 🔌 Wiring Diagram
The circuit uses specific pins for LEDs and Buttons as defined in the laboratory instructions.

<img src="Breadboard Diagram.png" alt="Alt text for the image" width="1000" height="1000">

| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Red LED** | Pin 7 | Anode (+) to Pin 7, Cathode (-) to GND via resistor. |
| **Green LED** | Pin 6 | Anode (+) to Pin 6, Cathode (-) to GND via resistor. |
| **Blue LED** | Pin 5 | Anode (+) to Pin 5, Cathode (-) to GND via resistor. |
| **Button 1** | Pin 12 | Connect one leg to Pin 12, the other to GND. |
| **Button 2** | Pin 11 | Connect one leg to Pin 11, the other to GND. |
| **Button 3** | Pin 10 | Connect one leg to Pin 10, the other to GND. |
| **GND** | GND | Common ground for all components. |

The system is divided into two distinct parts: the **Microcontroller Firmware** (Arduino) and the **Web Server** (Python/FastAPI).

## 💻 Code Explanation

### 1. Arduino Firmware
The Arduino sketch listens for single-character commands via the Serial port to control the LEDs.
* **`initSystem()`**: Initializes Pins 7, 6, and 5 as Outputs (LEDs) and Pins 12, 11, 10 as Inputs (Buttons).
* **Command Logic**:
    * `'1'`: Toggles the **Red** LED.
    * `'2'`: Toggles the **Green** LED.
    * `'3'`: Toggles the **Blue** LED.
    * `'9'`: Turns **ALL** LEDs ON.
    * `'0'`: Turns **ALL** LEDs OFF.
```cpp
// Snippet from LabAct7.ino
switch (input) {
  case '1': toggleLED(PIN_RED); break;
  case '2': toggleLED(PIN_GREEN); break;
  case '3': toggleLED(PIN_BLUE); break;
  case '9': // All ON
    digitalWrite(PIN_RED, HIGH); digitalWrite(PIN_GREEN, HIGH); digitalWrite(PIN_BLUE, HIGH);
    break;
  case '0': // All OFF
    digitalWrite(PIN_RED, LOW); digitalWrite(PIN_GREEN, LOW); digitalWrite(PIN_BLUE, LOW);
    break;
}
```

### 2. Python FastAPI Server
The Python script creates an API server that translates HTTP requests into Serial commands.

**A. Setup**
- Uses pyserial to establish a connection with the Arduino (e.g., on COM7).
- Uses FastAPI to define URL routes.
```python
try:
        arduino = serial.Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=1)
        # Wait a moment for Arduino to reset after connection
        time.sleep(2) 
        print(f"Connected to Arduino on {SERIAL_PORT}")
    except serial.SerialException as e:
        print(f"Failed to connect to Arduino: {e}")
        print("Please check your port settings in the code.")
        sys.exit(1)
```

**B. API Endpoints:** The code implements the specific requirements for the activity:
- GET /led/on: Sends '9' to turn all LEDs on.
- GET /led/off: Sends '0' to turn all LEDs off.
- GET /led/{color}: This is a dynamic route. It reads the {color} parameter (e.g., "red"), converts it to lowercase, and sends the corresponding toggle command:
  -  "red" -> sends '1'
  -  "green" -> sends '2'
  -  "blue" -> sends '3'
  
```python
# Snippet from Python Script
@app.get("/led/{color}")
def control_led(color: str):
    color = color.lower() # Ensures case insensitivity
    if color == "red":
        arduino.write(b'1')
        return {"status": "Red LED toggled"}
    # ... logic continues for green ('2') and blue ('3')
```

## How to Run the Server:

**1. Install dependencies:** Open your terminal or command prompt and run the following command to install FastAPI (standard version) and the serial library:
```bash
pip install "fastapi[standard]" pyserial
```

**2. Connect Hardware:** Plug your Arduino into your computer. Check the Device Manager (Windows) or /dev/tty* (Mac/Linux) to identify your COM port (e.g., COM3, COM7).

**3. Configure Code:** Open the Python script and update the SERIAL_PORT variable to match your Arduino's port. Save the file as main.py.

**4. Start the Server:** In your terminal, navigate to the folder where you saved the file and run:
```bash
fastapi dev main.py
```

**5. Test the API:** Open your web browser and try the following URLs:
- http://127.0.0.1:8000/led/red (Toggles Red LED)
- http://127.0.0.1:8000/led/green (Toggles Green LED)
- http://127.0.0.1:8000/led/blue (Toggles Blue LED)
- http://127.0.0.1:8000/led/on (Turns All LEDs ON)
- http://127.0.0.1:8000/led/off (Turns All LEDs OFF)

**Test via Terminal:** If you prefer using command-line tools or python scripts, you can use these methods while the server is running:
- Using cURL:
```bash
curl -X POST http://127.0.0.1:8000/led/red
```
- Using cURL in Powershell: 
```bash
curl.exe -X POST http://127.0.0.1:8000/led/red
```
