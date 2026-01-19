#ifndef LED_Controller_H
#define LED_Controller_H

#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10

// === LED States ===
bool redState = false;
bool greenState = false;
bool blueState = false;

// === All OFF ===
void allOff() {
  redState = greenState = blueState = false;
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

// === Setup Function for LEDs ===
void setupLEDs() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  allOff();  
}

// === Toggle Functions ===
void toggleRed() {
  redState = !redState;
  digitalWrite(RED_LED, redState);
}

void toggleGreen() {
  greenState = !greenState;
  digitalWrite(GREEN_LED, greenState);
}

void toggleBlue() {
  blueState = !blueState;
  digitalWrite(BLUE_LED, blueState);
}

void allOn() {
  redState = greenState = blueState = true;
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void checkInput(char input){
  switch(input) {
      case 'R':
        toggleRed();
        Serial.println("Red LED toggled.");
        break;

      case 'G':
        toggleGreen();
        Serial.println("Green LED toggled.");
        break;

      case 'B':
        toggleBlue();
        Serial.println("Blue LED toggled.");
        break;

      case 'A':
        allOn();
        Serial.println("All LEDs ON.");
        break;

      case 'O':
        allOff();
        Serial.println("All LEDs OFF.");
        break;

      default:
        Serial.print("Error: Invalid input '");
        Serial.print(input);
        Serial.println("'");
        break;
    }
}

#endif