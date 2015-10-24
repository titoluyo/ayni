/*
Sensor HC-SR501
Sensor de presencia (PIR)
*/
#include "Arduino.h"
#include "Pir.h"

Pir::Pir(int pin) : Sensor(pin) {
  _cantidadValores = CANTIDAD_VALORES;
  _title[0] = "P";
  _ledPin = 13;  
}

void Pir::setup() {
  pinMode(_pin, INPUT);
  pinMode(_ledPin, OUTPUT);
  _pirState = LOW;
}

void Pir::sense() {
  _currentMillis = millis();
  sense2();
}

void Pir::sense2() {
  
  _valor = digitalRead(_pin);  // read input value
  _val[0] = _valor;
  if (_valor == HIGH) {            // check if the input is HIGH
    digitalWrite(_ledPin, HIGH);  // turn LED ON
    if (_pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      _pirState = HIGH;
    }
  } else {
    digitalWrite(_ledPin, LOW); // turn LED OFF
    if (_pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      _pirState = LOW;
    }
  }
}

// Obtener el valor actual del sensor
char* Pir::getValue(int index) 
{
  s = String(_val[index],2);
	return getValue2(_title[index]);
	/*
  s = "|" + _title[index] + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
	*/
}




