#include "Arduino.h"
#include "Pir.h"

Pir::Pir(int pin) {
  _pin = pin;
  _ledPin = 13;  
}

void Pir::setup() {
  pinMode(_pin, INPUT);
  pinMode(_ledPin, OUTPUT);
  _pirState = LOW;
}

bool Pir::sense() {
  
  unsigned long currentMillis = millis();
  unsigned long diff = currentMillis - _previousMillis;  
  
  _val = digitalRead(_pin);  // read input value
  if (_val == HIGH) {            // check if the input is HIGH
    digitalWrite(_ledPin, HIGH);  // turn LED ON
    if (_pirState == LOW) {
      // we have just turned on
      //Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      _pirState = LOW;
    }
  } else {
    digitalWrite(_ledPin, LOW); // turn LED OFF
    if (_pirState == HIGH){
      // we have just turned off
      //Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      _pirState = LOW;
    }
  }

  return _val;
  
}





