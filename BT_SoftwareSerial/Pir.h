#ifndef Pir_h
#define Pir_h

#include "Sensor.h"

#define CANTIDAD_VALORES 1

class Pir : public Sensor
{
  public:
    Pir(int pin);
    Pir(int pin, int pin2);
    virtual void setup();
    virtual void sense();
    virtual void sense2();
    virtual char* getValue(int index);

  protected:
    bool _val[CANTIDAD_VALORES];
    String _title[CANTIDAD_VALORES];
    int _valor;
    bool _pirState;
};

#endif
