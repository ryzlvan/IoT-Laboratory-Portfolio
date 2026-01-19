#include "myFunctions.h"

void setup() {
  Serial.begin(9600);
  setupHardware(); // Initialize Pins
  // Note: We avoid printing a startup message to keep the serial buffer clean for the Python parser
}

void loop() {
  // ==========================================
  // PART 1: INBOUND - Read from Python
  // Logic: Python sends '1', '2', '3' -> Toggle LEDs
  // ==========================================
    if (Serial.available() > 0) {
    
    String inputString = Serial.readStringUntil('\n');

    inputString.trim();

    if (inputString.length() == 0) {
      return;
    }

    if (inputString.length() > 1) {
      Serial.println("Error: Please input only one character.");
      return; 
    }

    char input = inputString[0];

    // Ignore newline characters or carriage returns
    if (input != '\n' && input != '\r') {
      switch (input) {
        case '1': 
          toggleRed();
          break;
        case '2':
          toggleGreen();
          break;
        case '3':
          toggleBlue();
          break;
        default:
        Serial.print("Error: Invalid input '");
        Serial.print(input);
        Serial.println("'");
          break;
        // No default case needed; ignore invalid data
      }
    }
  }

  // ==========================================
  // PART 2: OUTBOUND - Read Buttons & Send to Python
  // Logic: Button Press -> Send 'R', 'G', 'B'
  // Uses State Change Detection (Falling Edge)
  // ==========================================
  
  // Read current states
  int currentBtn1 = digitalRead(BTN_1);
  int currentBtn2 = digitalRead(BTN_2);
  int currentBtn3 = digitalRead(BTN_3);

  // --- Button 1 Logic (Red Request) ---
  if (lastBtn1State == HIGH && currentBtn1 == LOW) {
    Serial.print("R\n"); // Send single char
    delay(50);         // Simple Debounce
  }
  lastBtn1State = currentBtn1;

  // --- Button 2 Logic (Green Request) ---
  if (lastBtn2State == HIGH && currentBtn2 == LOW) {
    Serial.print("G\n");
    delay(50);
  }
  lastBtn2State = currentBtn2;

  // --- Button 3 Logic (Blue Request) ---
  if (lastBtn3State == HIGH && currentBtn3 == LOW) {
    Serial.print("B\n");
    delay(50);
  }
  lastBtn3State = currentBtn3;
}