const int PHOTORESISTOR_PIN = A0;
const int GREEN_LED = 11;
const int YELLOW_LED = 12;
const int RED_LED = 13;  

int lowThreshold = 40;
int highThreshold = 70;

bool automaticMode = false;
String inputCommand = "";

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(PHOTORESISTOR_PIN);
  int lightPercent = map(sensorValue, 0, 1023, 0, 100);
  String environment = "N/A";
  String activeLED = "";

  //Automatic
  if (automaticMode) {
  if (lightPercent <= 40) {
    environment = "Cloudy";
    activateLED(GREEN_LED);
    activeLED = "Green";
  } 
  else if (lightPercent <= 70) {
    environment = "Clear";
    activateLED(YELLOW_LED);
    activeLED = "Yellow";
  } 
  else {
    environment = "Clear";
    activateLED(RED_LED);
    activeLED = "Red";
  }
} else {
  // manual mode using thresholds
  if (lightPercent <= lowThreshold) {
    activateLED(GREEN_LED);
    activeLED = "Green";
  } 
  else if (lightPercent <= highThreshold) {
    activateLED(YELLOW_LED);
    activeLED = "Yellow";
  } 
  else {
    activateLED(RED_LED);
    activeLED = "Red";
  }
}


  Serial.println("------------------------------------------");
  Serial.print("Light Intensity: ");
  Serial.print(lightPercent);
  Serial.println("%");
  Serial.print("Active LED: ");
  Serial.println(activeLED);
  

  if (automaticMode) {
    Serial.println("Current Mode: Automatic");
    Serial.print("Environment: ");
    Serial.println(environment);
  } else {
    Serial.println("Current Mode: Manual");
  }

  readSerialCommands();
  delay(1000);
}

void activateLED(int ledPin) {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(ledPin, HIGH);
}

void readSerialCommands() {
  String serial_input = Serial.readStringUntil('\n');
  serial_input.trim();
  if (serial_input.length() == 0) return;
  serial_input.toUpperCase();
  processCommand(serial_input); 
}

void processCommand(String cmd) {
  if (cmd == "MODE AUTO") {
    automaticMode = true;
    Serial.println("Switched to AUTOMATIC mode.");
    return;
  }

  if (cmd == "MODE MANUAL") {
    automaticMode = false;
    Serial.println("Switched to MANUAL mode.");
    return;
  }

  if (cmd.startsWith("SET LOW ")) {
    if (automaticMode) {
      Serial.println("Error: Wrong command");
      return;
    }
    int val = cmd.substring(8).toInt();
    if (val >= 0 && val <= 100 && val < highThreshold) {
      lowThreshold = val;
      Serial.print("Low threshold set to ");
      Serial.print(val);
      Serial.println("%");
    } else {
      Serial.println("Error: Wrong command");
    }
    return;
  }

  if (cmd.startsWith("SET HIGH ")) {
    if (automaticMode) {
      Serial.println("Error: Wrong command");
      return;
    }
    int val = cmd.substring(9).toInt();
    if (val >= 0 && val <= 100 && val > lowThreshold) {
      highThreshold = val;
      Serial.print("High threshold set to ");
      Serial.print(val);
      Serial.println("%");
    } else {
      Serial.println("Error: Wrong command");
    }
    return;
  }

  Serial.println("Error: Wrong command");
}
