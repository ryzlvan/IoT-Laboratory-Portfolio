// ====== CONFIG ======
const int buttonPin = 4; 
const int groupNumber = 3;     
const unsigned long debounceDelay = 50;

// ====== VARIABLES ======
int lastButtonState = HIGH;
int buttonState;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {  
        // Button pressed
        Serial.println(groupNumber);  // Send group number to Python
      }
    }
  }

  lastButtonState = reading;
}
