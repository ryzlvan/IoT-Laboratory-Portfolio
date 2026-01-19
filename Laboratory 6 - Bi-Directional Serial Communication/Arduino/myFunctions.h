#ifndef myFunctions.h
#define myFunctions.h

// === Pin Assignments (Updated) ===
// LEDs moved to 7, 6, 5
#define RED_LED 7
#define GREEN_LED 6
#define BLUE_LED 5

// Buttons added to 12, 11, 10
// Note: Pin 10 was previously Blue LED, now it is Button 3
#define BTN_1 12
#define BTN_2 11
#define BTN_3 10

// === LED States ===
bool redState = false;
bool greenState = false;
bool blueState = false;

// === Button State Tracking (For Edge Detection) ===
// We need to track the previous state to detect a "press" event (High -> Low)
int lastBtn1State = HIGH;
int lastBtn2State = HIGH;
int lastBtn3State = HIGH;

// === Hardware Setup ===
void setupHardware() {
  // LED Outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Button Inputs with Internal Pull-up Resistors
  // (Input is HIGH when open, LOW when pressed)
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  // Initialize LEDs to OFF
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

// === Toggle Functions (Executed upon command from Python) ===
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

#endif