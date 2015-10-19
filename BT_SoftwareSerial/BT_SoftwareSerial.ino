#include <SoftwareSerial.h>
#include "Sensor.h"
#include "Pir.h"
#include <DHT.h>
#include "TempHum.h"
#include "HCSR04.h"
#include <MemoryFree.h>

SoftwareSerial mySerial(2, 3); // RX, TX
String command;

const int cantSensors = 3;  // Cantidad de sensores a usar (TODO: SE MANDARA DESDE EL RASPBERRY PI)
Sensor* sensor[cantSensors];  // Lista de sensores
int sensorsTypes[cantSensors];  // Lista de tipos de sensores (SE MANDARA DESDE EL RASPBERRY PI)
int sensorsParams[cantSensors][2]; // Lista de parametros de sensores (SE MANDARA DESDE EL RASPBERRY PI)

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando!");
	
	// TODO (Pendiente) : prueba de datos, estos se deben de mandar desde el Raspberry PI
  sensorsTypes[0] = 1;  // Pir
  sensorsTypes[1] = 2;  // TempHum
  sensorsTypes[2] = 3;  // Distancia

  sensorsParams[0][0] = 8;
  sensorsParams[1][0] = 5;
  sensorsParams[2][0] = 6;
  sensorsParams[2][1] = 7;

	// Creacion de los sensores
  for (int i = 0; i < cantSensors; i++) {
    switch (sensorsTypes[i]) {
      case 1:
        sensor[i] = new Pir(sensorsParams[i][0]);
        break;
      case 2:
        sensor[i] = new TempHum(sensorsParams[i][0]);
        break;
      case 3:
        sensor[i] = new HCSR04(sensorsParams[i][0], sensorsParams[i][1]);
        break;
    }
		Serial.print("Sensor:");
		Serial.print(i);
		Sensor.println(" creado");
  }

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  for(int i = 0; i < cantSensors; i++) {
    sensor[i]->setup();
  }

  mySerial.begin(9600);
  //mySerial.println("Inicio\r\n");
}


char cad;
void loop()
{

  // Sensar valores
  for(int i = 0; i < cantSensors; i++) {
    sensor[i]->sense();
  }

  // Responder a comandos enviados
  if (mySerial.available()){
    cad = mySerial.read();
    if (cad != 10 && cad != 13) {
        command += cad;
    }
    if (cad == 10) {
      executeCommand(command); // ejecuta el comando
      command = "";  // limpia el comando
    }
  }
  /*
  if (Serial.available()){
    mySerial.write(Serial.read());
  }
  */
}

void executeCommand(String command){
  //TODO: Hacer una lista de decisiones dependiendo del comando
  //Serial.print(command);
  if (true) { // reemplazar por un comando valido
    sendData();
  }
}

String p;
char pc[10];
void sendData(){

  mySerial.write("ID1"); // ID del nodo

  for(int i = 0; i < cantSensors; i++) {
    int cantVals = sensor[i]->getCantidadValores();
    for (int j = 0; j < cantVals; j++) {
      mySerial.write(sensor[i]->getValue(j));
    }
  }

  //Estado relay
  mySerial.write("|RA");
  mySerial.write("1");
  mySerial.write("\r\n");
  Serial.print("|");
  //Serial.print(th.getValue(0));
  Serial.print("freeMemory()=");
  Serial.print(freeMemory());
  Serial.println();
}

