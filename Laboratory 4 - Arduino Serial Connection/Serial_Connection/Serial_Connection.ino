#define photoresistorPin A2
#define ledPin 12


const int brightThreshold = 220;

int readBright() {
  int Brightness = analogRead(photoresistorPin);
  float brightMap = map(Brightness, 0, 1023, 0, 255);
  return brightMap;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int currentBright = readBright();

  Serial.print(" Brightness: ");
  Serial.println(currentBright);
  delay(100);
  bool choice = false;
  if (currentBright >= brightThreshold) {
    choice = true;
  }
  while (choice == true) {
    String input = Serial.readStringUntil('\n');
    input.toLowerCase();
    if (input == "stop") {
      digitalWrite(ledPin, LOW);
      break;
    } else {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }
}
