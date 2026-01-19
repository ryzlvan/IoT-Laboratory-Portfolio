int ledPins[] = {12, 11, 10, 9, 8};

void setup() {
  int i=0;
  while(i<5){
    pinMode(ledPins[i], OUTPUT);
  	i++;
  }
}

void loop() {
  int i=0;
  while(i<5) {
    int power = 0;
    while(power<=255){
      analogWrite(ledPins[i], power);
      delay(1);
      power++;
    }
    delay(1000);
    i++;
  }
  int j=i-5;
  while(j<5){
    int power = 255;
    while(power>=0){
      analogWrite(ledPins[j], power);
      delay(1);
      power--;
    }
    delay(1000);
    j++;
  }
  
}