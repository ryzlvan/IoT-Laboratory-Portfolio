# Final Laboratory Exam: Remote Button API Trigger

## 📖 Overview
This activity demonstrates how to create a **Physical IoT Client** that triggers remote web actions. The system is designed to solve a specific problem: enabling an offline microcontroller to interact with a web server by using a computer as a gateway.

The system consists of two distinct parts:
1.  **Arduino (The Trigger):** A physical button acts as the input. The code implements **Software Debouncing** to ensure one press equals exactly one signal, filtering out electrical noise. When pressed, it sends a "Group Number" via USB Serial.
2.  **Python (The Bridge):** A script running on a laptop listens to the Serial port. When it receives the signal, it constructs an HTTP URL and sends a request to a remote FastAPI server to toggle an LED system.

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): Acts as the input controller.
* **1x Push Button**: The physical trigger.
* **Jumper Wires**: For connections.
* **USB Cable**: Connects Arduino to the computer for power and data.
* **Computer**: Runs the Python script to bridge Serial data to the Internet.
* **Software Libraries**: Python `pyserial` (for USB comms) and `requests` (for HTTP calls).

## 🔌 Wiring Diagram
The button is configured using the Arduino's internal **Input Pull-up** resistor. This simplifies wiring as no external resistor is required.



| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Button Leg A** | Pin 4 | Connect directly to **Pin 4**. |
| **Button Leg B** | GND | Connect directly to **GND**. |

> **Wiring Note:** Since `INPUT_PULLUP` is used, the logic is inverted. The pin reads `HIGH` when the button is open (unpressed) and `LOW` when the button is pressed (closed).

## 💻 Code Explanation

### 1. Arduino Firmware (The Trigger)
The Arduino code is responsible for detecting the physical press and ensuring only one clear signal is sent.

* **Debouncing Logic:** Mechanical buttons often "bounce," creating multiple electrical spikes in milliseconds. The code uses `millis()` to wait for a `debounceDelay` (50ms) to ensure the signal is stable before registering a press.
* **State Detection:** It compares `reading != lastButtonState` to detect changes and `reading != buttonState` to confirm a valid press.
* **Serial Output:** When a confirmed press (LOW state) occurs, it prints the `groupNumber` (e.g., "3") to the Serial connection.

```cpp
// Snippet: Debounce Logic
if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != buttonState) {
    buttonState = reading;
    if (buttonState == LOW) {  
       // Valid Press Detected
       Serial.println(groupNumber);  
    }
  }
}
```

### 2. Python Client (The Bridge)
The Python script is a "non-terminating" application that constantly monitors the USB port.

- Configuration: You must set SERIAL_PORT (e.g., COM7) and the BASE_URL of the instructor's server.
- Serial Listening: ser.in_waiting checks if data has arrived. ser.readline() captures the group number sent by the Arduino.
- HTTP Request: The script constructs a dynamic URL (/led/group/3/toggle) and uses requests.get() to trigger the API.
- Feedback: It prints the server's response code (200 OK or Error) to the terminal for debugging

```python
# Snippet: Main Logic Loop
if ser.in_waiting > 0:
    # 1. Read from Arduino
    group_number = ser.readline().decode('utf-8').strip()

    # 2. Construct URL
    endpoint = f"/led/group/{group_number}/toggle"
    full_url = BASE_URL + endpoint

    # 3. Call API
    response = requests.get(full_url)
```

## ▶️ How to Run
Network Setup (Crucial): Ensure your laptop is connected to the same WiFi network or Hotspot as the Instructor's Server.

- **Upload Firmware:** Connect the Arduino to your PC and upload the provided sketch via Arduino IDE.
- **Install Libraries:** Open your terminal and run: pip install pyserial requests
- **Configure Script:** Open the Python script and check two variables:
- **SERIAL_PORT:** Set this to your Arduino's port (e.g., COM3 or COM7).
- **BASE_URL:** Ensure this matches the IP address provided by the instructor (e.g., http://172.20.10.3:8000).
- **Run Client:** Execute the script: python your_script_name.py
- **Test:** Press the physical button. You should see "SUCCESS" in your terminal.

⚠️ Note: Critical Network Requirement
This system will ONLY work if your computer and the Instructor's API Server are on the same local network.
Since the Python script attempts to connect to a private IP address (e.g., 172.20.10.x or 192.168.1.x), your request will fail with a Connection Error or Timeout if you are using a different WiFi network or mobile data. 
You must connect to the specific classroom WiFi or Hotspot provided by the instructor.

> For uploading purposes only ....
