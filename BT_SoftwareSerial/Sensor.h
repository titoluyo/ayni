#ifndef Sensor_h
#define Sensor_h

//Clase generalizada
class Sensor
{
  public:
	  //Constructrs
    Sensor(int pin);
    Sensor(int pin, int pin2);
		//setup
    inline virtual void setup();
    inline virtual void sense();
    inline virtual void sense2();
    inline virtual char* getValue(int index);
    inline virtual int getCantidadValores();

  protected:
    unsigned long _previousMillis;
    unsigned long _currentMillis;

		// Internal variables
    int _pin;  // Pin1 for sensor
    int _pin2; // Pin2 for sensor
    int _ledPin;
    int _interval; // Cada cuanto tiempo se va a sensar
    String s;
    char c[10];
    
    int _cantidadValores;
};

#endif

