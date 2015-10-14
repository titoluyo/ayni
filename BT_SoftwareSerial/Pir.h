#ifndef Pir_h
#define Pir_h


class Pir
{
  public:
    Pir(int pin);
    void setup();
    bool sense();

  private:
    unsigned long _previousMillis;
    int _pin;
    int _ledPin;
    int _val;
    bool _pirState;
};

#endif
