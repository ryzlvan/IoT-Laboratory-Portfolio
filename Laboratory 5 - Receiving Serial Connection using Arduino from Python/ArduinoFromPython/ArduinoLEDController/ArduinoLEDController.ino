#include "LED_Controller.h"

void setup() {
  Serial.begin(9600);
  setupLEDs();
  Serial.println("Arduino LED Serial Controller Ready...");
}

void loop() {
  if (Serial.available() > 0) {
    
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();

    if (inputString.length() != 1) {
      Serial.println("Error: Input must be a single character");
      return;
    }
    char input = toupper(inputString.charAt(0));
    checkInput(input);
  }
}