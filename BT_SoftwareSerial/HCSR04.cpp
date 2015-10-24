/*
Sensor HC-SR04
Sensor de distancia ultrasonico
TODO: Reemplazar por una libreria que no bloquee
Posible candidato: NewPing https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
*/

#include "Arduino.h"
#include "HCSR04.h"
#include <NewPing.h>

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Constructor
HCSR04::HCSR04(int pin, int pin2) : Sensor(pin, pin2) { // TRIGGER, ECHO
  _cantidadValores = CANTIDAD_VALORES;
  _title[0] = "D";
  _previousMillis = 0;
  _interval = 50;
  _sonar = new NewPing(pin, pin2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//  _functiontype = sense2;
}

// Seccion de setup
void HCSR04::setup() {
//	pinMode(_pin, OUTPUT);
//	pinMode(_pin2, INPUT);
//  pingTimer = millis();  
}


// Sensado
void HCSR04::sense() {

  _currentMillis = millis();
  if (_currentMillis - _previousMillis <= _interval) return; // {
  sense2();
  //_sonar->ping_timer(&func);
  _previousMillis = _currentMillis;
}

void HCSR04::sense2() {
  /*
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(_pin, LOW);
  _duration = pulseIn(_pin2, HIGH);

  _val[0] = _duration/58.2;
  */

    _valAux = _sonar->ping_cm();
    if (_valAux > 2.0) {
      _val[0] = _valAux;
      Serial.print("Distance:");
      Serial.println(_val[0]);
    }
}

// Obtener el valor actual del sensor
char* HCSR04::getValue(int index) 
{
  s = String(_val[index],2);
	return getValue2(_title[index]);
	/*
  s = "|" + _title[index] + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
	*/
}


