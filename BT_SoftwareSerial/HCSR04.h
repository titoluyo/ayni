#ifndef HCSR04_h
#define HCSR04_h

#include "Sensor.h"

#define CANTIDAD_VALORES 1

class HCSR04 : public Sensor
{
  public:
    HCSR04(int pin);
    HCSR04(int pin, int pin2);
    virtual void setup();
    virtual void sense();
    virtual void sense2();
    virtual char* getValue(int index);

  private:
    long _duration;
    float _val[CANTIDAD_VALORES];
    String _title[CANTIDAD_VALORES];
};

#endif
