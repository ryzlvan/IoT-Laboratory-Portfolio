#ifndef Lab_Act7.h
#define Lab_Act7.h

#include <Arduino.h> // Required to use Arduino commands like pinMode in a header

// --- PIN DEFINITIONS ---
const int PIN_RED   = 7;
const int PIN_GREEN = 6;
const int PIN_BLUE  = 5;

const int PIN_BTN1  = 12;
const int PIN_BTN2  = 11;
const int PIN_BTN3  = 10;

// --- INITIALIZATION FUNCTION ---
// Call this inside setup() to configure all pins at once
void initSystem() {
  // Set LED pins as OUTPUT
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  // Set Button pins as INPUT
  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
  pinMode(PIN_BTN3, INPUT);
}

// --- HELPER FUNCTIONS ---
// Keeps the main code clean by moving the toggle logic here
void toggleLED(int pin) {
  int state = digitalRead(pin);
  digitalWrite(pin, !state);
}

#endif