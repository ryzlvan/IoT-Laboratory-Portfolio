# Laboratory Activity 3: Fire Sensor Simulation

## 📖 Overview
This activity simulates a **Fire Alarm System** using environmental sensors. It monitors both temperature and light levels to detect potential fire conditions.

The system uses a **Thermistor** to measure heat and a **Photoresistor (LDR)** to measure light intensity. The alarm logic requires *both* conditions to be met simultaneously (High Temperature AND Bright Light) to trigger the visual (LED) and audio (Buzzer) alarm. This dual-sensor approach helps reduce false alarms caused by sunlight or ambient heat alone.

## 🛠 Components Used
* **Arduino Board** (Uno, Nano, or similar): The central controller.
* **1x Thermistor (NTC 10k)**: Analog sensor for measuring temperature.
* **1x Photoresistor (LDR)**: Analog sensor for measuring light brightness.
* **1x LED (Red)**: Visual alarm indicator.
* **1x Piezo Buzzer**: Audio alarm indicator.
* **2x 10kΩ Resistors**: For the voltage divider circuits (required for the sensors).
* **1x 220Ω Resistor**: Current limiting resistor for the LED.
* **Jumper Wires & Breadboard**: For circuit connections.

## 🔌 Wiring Diagram
This circuit requires constructing two "voltage dividers" for the analog sensors.

<img src="Breadboard Diagram.png" alt="Alt text for the image" width="1000" height="1000">

| Component | Arduino Pin | Connection Details |
| :--- | :--- | :--- |
| **Thermistor** | Pin A0 | Connect one leg to 5V. Connect the other leg to **A0** AND to GND via a **10kΩ resistor**. |
| **Photoresistor** | Pin A2 | Connect one leg to 5V. Connect the other leg to **A2** AND to GND via a **10kΩ resistor**. |
| **LED (+)** | Pin 12 | Anode (+) to Pin 12 (shared with buzzer). |
| **Buzzer (+)** | Pin 12 | Positive leg to Pin 12 (shared with LED). |
| **GND** | GND | Common ground for Resistors, LED, and Buzzer. |

> **Wiring Note:** In this simulation, both the LED and Buzzer share **Pin 12**. In a real-world scenario, you might separate them, but this code drives both simultaneously to create a synchronized beep and flash.

## 💻 Code Explanation

### 1. Configuration & Helper Functions
We define the pins and set thresholds. The system triggers if the temperature exceeds **50°C** and brightness exceeds **220** (out of 255).

Two helper functions convert raw analog data into usable units:
* `readBright()`: Maps the LDR reading (0-1023) to a byte range (0-255).
* `readTempC()`: Uses the Beta parameter equation to convert the Thermistor resistance into degrees Celsius.

```cpp
// Function to read brightness
int readBright() {
  int analogLight = analogRead(photoresistorPin); 
  int brightlight = map(analogLight,0,1023,0,255);
  return brightlight;
}

// Function to read temperature in Celsius
float readTempC() {  
  int analogValue = analogRead(thermistorPin);  
  float tempC = beta / (log((1025.0 * resistance / analogValue - resistance) / resistance ) + beta / 298.0) - 273.0;
  return tempC;
}
```
### 2. Setup
We configure the alarm pin and initialize serial communication to monitor the sensor values on the PC.
```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
```
### 3. Main Loop: Monitoring & Alarm
The loop constantly reads the sensors and prints the values to the Serial Monitor.

It then checks the Fire Condition:
IF Temperature > 50°C AND Brightness > 220:
The system activates a rapid alarm (blinking LED and 4kHz tone).

ELSE:
The alarm remains off.
```cpp
void loop() {
  float currentTemp = readTempC();
  int currentBright = readBright();

  // Serial Monitor Output
  Serial.print("Temperature: ");
  Serial.print(currentTemp);
  Serial.print(" | Brightness: ");
  Serial.println(currentBright);
  delay(1000);
  
  // Logic: Both Heat AND Light must be high to trigger alarm
  if(currentTemp >= tempThreshold && currentBright >= brightThreshold) {
    digitalWrite(ledPin, HIGH);
    tone(ledPin, 4000); // Play 4kHz sound
    delay(100);
    digitalWrite(ledPin, LOW);
    noTone(ledPin);     // Stop sound
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);  
    noTone(ledPin);
  }
}
```
