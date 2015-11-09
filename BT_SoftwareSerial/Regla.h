#ifndef Regla_h
#define Regla_h

class Regla 
{
  public:
    Regla();
    void AddSensor(byte sensor, byte index);
    void Validar();
    void Actuar();
  protected:
    byte _sensor[10];
    byte _index[10];
    byte _currentSensor = 0;
};


#endif

