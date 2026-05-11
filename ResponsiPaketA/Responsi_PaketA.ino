#include <Arduino.h>

const int ledMerah = 12;
const int ledHijau = 13;
const int buttonPin = 2;

const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

byte digitPattern[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

volatile bool buttonPressed = false;
bool lampHijau = true;   

void buttonISR() {
  buttonPressed = true;
}

void displayDigit(int num) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], digitPattern[num][i]);
  }
}

void clearDisplay() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
}

void setup() {
  // LED
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  // Button
  pinMode(buttonPin, INPUT_PULLUP);

  // Seven segment
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  clearDisplay();

  digitalWrite(ledHijau, HIGH);
  digitalWrite(ledMerah, LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;

    delay(50);

    countdown();

    delay(2000);

    if (lampHijau) {
  
      digitalWrite(ledHijau, LOW);
      digitalWrite(ledMerah, HIGH);
      lampHijau = false;
    } else {
  
      digitalWrite(ledMerah, LOW);
      digitalWrite(ledHijau, HIGH);
      lampHijau = true;
    }
  }
}