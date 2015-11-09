#include "Arduino.h"
#include "Regla.h"

Regla::Regla()
{
}

void Regla::AddSensor(byte sensor, byte index)
{
  _sensor[_currentSensor] = sensor;
  _index[_currentSensor] = index;
  _currentSensor++;
}

void Regla::Validar()
{
  
}

void Regla::Actuar()
{
  
}

