#include "Lab_Act7.h" // Import our custom header

void setup() {
  Serial.begin(9600);
  
  // This single line now handles all pin modes!
  initSystem(); 
}

void loop() {
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
        toggleLED(PIN_RED);
        break;
      case '2':
        toggleLED(PIN_GREEN);
        break;
      case '3':
        toggleLED(PIN_BLUE);
        break;
      case '9': // API "All On"
        digitalWrite(PIN_RED, HIGH);
        digitalWrite(PIN_GREEN, HIGH);
        digitalWrite(PIN_BLUE, HIGH);
        break;
      case '0': // API "All Off"
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_GREEN, LOW);
        digitalWrite(PIN_BLUE, LOW);
        break;
      default:
        Serial.println("Error: Please input valid numbers only.");
        break;
    }
  }
}}