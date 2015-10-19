/*
Sensor HC-SR04
Sensor de distancia ultrasonico
TODO: Reemplazar por una libreria que no bloquee
Posible candidato: NewPing https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
*/

#include "Arduino.h"
#include "HCSR04.h"

// Constructor
HCSR04::HCSR04(int pin, int pin2) : Sensor(pin, pin2) { // TRIGGER, ECHO
  _cantidadValores = CANTIDAD_VALORES;
  _title[0] = "D";
  _previousMillis = 0;
  _interval = 50;
}

// Seccion de setup
void HCSR04::setup() {
	pinMode(_pin, OUTPUT);
	pinMode(_pin2, INPUT);
}

// Sensado
void HCSR04::sense() {
  _currentMillis = millis();
  if (_currentMillis - _previousMillis <= _interval) return; // {
	sense2();
  _previousMillis = _currentMillis;
}

void HCSR04::sense2() {
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(_pin, LOW);
  _duration = pulseIn(_pin2, HIGH);

  _val[0] = _duration/58.2;
  
}

// Obtener el valor actual del sensor
char* HCSR04::getValue(int index) 
{
  s = String(_val[index],2);
  s = "|" + _title[index] + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
}


