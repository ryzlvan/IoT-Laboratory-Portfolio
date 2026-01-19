# Midterm Laboratory Activity: Smart Light Monitoring System

## 📖 Overview
This activity implements an **Light Sensing System** capable of operating in two distinct modes: **Automatic** and **Manual**.

The system reads ambient light levels using a photoresistor (LDR) and converts the analog signal into a percentage (0-100%). Based on the light intensity, it activates a specific LED (Green, Yellow, or Red) to indicate the environment status. Uniquely, this system allows the user to dynamically configure threshold values and switch operating modes via **Serial Commands** without re-uploading the code.

* **Automatic Mode:** Uses fixed, pre-programmed thresholds to classify the environment (Cloudy/Clear).
* **Manual Mode:** Allows the user to customize the sensitivity thresholds via the Serial Monitor.

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): Central processing unit.
* **1x Photoresistor (LDR)**: Analog sensor to measure light intensity.
* **1x Red LED**: High intensity indicator.
* **1x Yellow LED**: Medium intensity indicator.
* **1x Green LED**: Low intensity indicator.
* **3x Resistors (220Ω - 330Ω)**: Current limiting for LEDs.
* **1x Resistor (10kΩ)**: For the LDR voltage divider circuit.
* **Breadboard & Jumper Wires**: For connections.

## 🔌 Wiring Diagram
The system uses analog input A0 for sensing and digital PWM pins for the LEDs.



| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Photoresistor** | Pin A0 | 5V → LDR leg 1. **Pin A0** AND **10kΩ Resistor** → LDR leg 2. Resistor other leg → GND. |
| **Green LED** | Pin 11 | Anode (+) to Pin 11, Cathode (-) to GND via resistor. |
| **Yellow LED** | Pin 12 | Anode (+) to Pin 12, Cathode (-) to GND via resistor. |
| **Red LED** | Pin 13 | Anode (+) to Pin 13, Cathode (-) to GND via resistor. |
| **GND** | GND | Common ground. |

## 💻 Code Explanation

### 1. Variables & Setup
We define the pins and default thresholds (Low: 40%, High: 70%). A boolean flag `automaticMode` tracks which state the system is in.

```cpp
const int PHOTORESISTOR_PIN = A0;
// LED Pins: 11 (Green), 12 (Yellow), 13 (Red)
int lowThreshold = 40;
int highThreshold = 70;
bool automaticMode = false;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  // ... (Other LEDs)
  Serial.begin(9600);
}
```

### 2. Main Loop: Sensing & Logic
The loop continuously monitors the light level and determines which LED to light up based on the selected mode.

1.  **Sensing:** It reads the analog value from the Photoresistor (0-1023) and maps it to a percentage (0-100%).
```cpp
  int sensorValue = analogRead(PHOTORESISTOR_PIN);
  int lightPercent = map(sensorValue, 0, 1023, 0, 100);
```
2.  **Automatic Mode:**
    * Uses **Fixed Thresholds** (40% and 70%).
    * Classifies the environment as "Cloudy" or "Clear".
    * Logic: Green (≤40%), Yellow (41-70%), Red (>70%).
```cpp
  if (automaticMode) {
    // Fixed Logic with Environment Classification
    if (lightPercent <= 40) { 
      environment = "Cloudy"; 
      activateLED(GREEN_LED); 
    } 
    // ... handles Yellow (<=70) and Red (>70)
  } else {
```

3.  **Manual Mode:**
    * Uses **Variable Thresholds** (`lowThreshold` and `highThreshold`).
    * Does *not* classify the environment text; it simply indicates intensity.
    * These thresholds can be changed dynamically by the user via Serial.

  ```cpp
  } else {
    // Manual Logic using adjustable variables
    if (lightPercent <= lowThreshold) {
      activateLED(GREEN_LED);
    } 
    // ... handles Yellow (<=highThreshold) and Red
  }
  ```

4. **Reporting:** Prints the current light percentage, the active LED color, and the current mode to the Serial Monitor every second.

```cpp
  // Serial Reporting...
  readSerialCommands(); // Check for "MODE" or "SET" commands
  delay(1000);
}
```

### 3. Command Processing
The system listens for text commands to change settings.

- **MODE AUTO / MODE MANUAL:** Switches the automaticMode flag.
- **SET LOW <value>:** Updates the low threshold (Manual Mode only).
- **SET HIGH <value>:** Updates the high threshold (Manual Mode only).
```cpp
void processCommand(String cmd) {
  if (cmd == "MODE AUTO") {
    automaticMode = true;
  }
  else if (cmd.startsWith("SET LOW ")) {
    // Parses the number after "SET LOW "
    int val = cmd.substring(8).toInt();
    // Validates that Low is less than High before saving
    if (val < highThreshold) lowThreshold = val;
  }
  // ... (Similar logic for SET HIGH)
}
```

## 🎮 How to Use (Serial Commands)
Open the Serial Monitor (set to **9600 Baud**) and type the following commands into the input field:

| Command | Description | Example |
| :--- | :--- | :--- |
| `MODE AUTO` | Switches system to Automatic logic (uses fixed thresholds). | `MODE AUTO` |
| `MODE MANUAL` | Switches system to Manual logic (enables custom thresholds). | `MODE MANUAL` |
| `SET LOW <num>` | Sets the boundary for Green/Yellow (0-100). **Only works in Manual Mode.** | `SET LOW 30` |
| `SET HIGH <num>` | Sets the boundary for Yellow/Red (0-100). **Only works in Manual Mode.** | `SET HIGH 85` |

**Note:** The code includes validation to prevent errors. You cannot set a `LOW` threshold that is higher than the `HIGH` threshold, and `SET` commands are ignored if the system is currently in `MODE AUTO`.


