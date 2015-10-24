#include <SoftwareSerial.h>
#include "Sensor.h"
#include "Pir.h"
#include <DHT.h>
#include "TempHum.h"
#include <NewPing.h>
#include "HCSR04.h"
#include <MemoryFree.h>

SoftwareSerial mySerial(2, 3); // RX, TX
uint8_t mode = 0; // 0: Setup; 1: Send data
uint8_t currentSensor = 0;
char cad;

//#define CANT_TIPOS_SENSORES 4
#define MAX_SENSORES 10
uint8_t cantSensors = 3;  // Cantidad de sensores a usar (TODO: SE MANDARA DESDE EL RASPBERRY PI)
Sensor* sensor[MAX_SENSORES];  // Lista de sensores

uint8_t numParametrosSensor[] = {
  0, // No definido
  1, // Pir
  1, // TempHum
  2  // HCSR04
};

uint8_t fase = 0;
/*1
 0 libre / inicio
 1 inicio / comando
   (setup)
 2 / tipo de sensor
 3 / parametro
 */
uint8_t tipoSensor = 0;
int parametro[10];
int actualParametro = 0;

/*
 Tipos de sensores:
 0: No definido
 1: Pir
 2: TempHum
 3: HCSR04
 */

/* "Cabecera"
@ Inicio Comunicaciones
$ Comando SETUP
3 cantidad de sensores
1 Tipo de sensor (deduce la cantidad de parametros?)
8 Parametro
2 Tipo de sensor
5 Parametro
3 Tipo de sensor
6 Parametro1
7 Parametro2
10 Fin Setup
*/

void sendData() {

  mySerial.write("ID1"); // ID del nodo

  for (int i = 0; i < cantSensors; i++) {
    int cantVals = sensor[i]->getCantidadValores();
    for (int j = 0; j < cantVals; j++) {
      mySerial.write(sensor[i]->getValue(j));
    }
  }

  //Estado relay
  mySerial.write("|RA1");
  mySerial.write("\r\n");

  //  Serial.print("|");
  //  Serial.print("freeMemory()=");
  //  Serial.print(freeMemory());
  //  Serial.println();
}


void executeCommand(String command) {
  //TODO: Hacer una lista de decisiones dependiendo del comando
  //Serial.print(command);
  if (true) { // reemplazar por un comando valido
    sendData();
  }
}

void instanciarSensores()
{
    switch (tipoSensor)
    {
    case 1: // Pir
      sensor[currentSensor] = new Pir(parametro[0]);
      Serial.print("Pir creado :");
      Serial.println(parametro[0]);
      break;
    case 2: // TempHum
      sensor[currentSensor] = new TempHum(parametro[0]);
      Serial.print("TempHum creado :");
      Serial.println(parametro[0]);
      break;
    case 3: // '3' : HCSR04
      sensor[currentSensor] = new HCSR04(parametro[0], parametro[1]);
      Serial.print("HCSR04 creado :");
      Serial.print(parametro[0]);
      Serial.print(",");
      Serial.println(parametro[1]);
      break;
    }
    Serial.print("Sensor:");
    Serial.print(currentSensor);
    Serial.println(" creado");
/*
    // Ejecucion del setup de los sensores
    for (int i = 0; i < cantSensors; i++) {
      sensor[i]->setup();
    }
    */
}


void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando!");

  mySerial.begin(9600);
}



void processInput(int n) {
/*
  Serial.println();
  Serial.println();
  Serial.println((int)c);
  Serial.println();
*/
  Serial.print("fase:");
  Serial.print(fase);
  Serial.print("-");
  switch (fase) {
    case 0: // Inicio
      if(n != 64){
        Serial.print("Error inicio debe ser @(64)");
        Serial.print(n);
      }
      Serial.print("Debug:Inicio");
      fase = 1;
      break;
    case 1: // Comando
      switch (n) {
        case 36: // '$' Setup
          mode = 0;
          fase = 2;
          Serial.print("Modo setup");
          break;
        case 62: // '>' Send
          mode = 1;
          Serial.print("Modo send");
          sendData();
          //fase = 1; //??
          break;
        default:
          Serial.print("Error:dato incorrecto");
          Serial.print(n);
      }
      break;
    case 2: // Tipo de sensor
      tipoSensor = n;
      Serial.print("Tipo sensor:");
      Serial.print(tipoSensor);
      if (numParametrosSensor[tipoSensor] > 0) {
        fase = 3;
      }
      break;
    case 3: // Parametro
      Serial.print("actualParametro:");
      Serial.print(actualParametro);
      parametro[actualParametro] = n;
      Serial.print(",Parametro:");
      Serial.print(parametro[actualParametro]);
      Serial.print(",tipoSensor:");
      Serial.print(tipoSensor);
      Serial.print(",numParametrosSensor[tipoSensor]:");
      Serial.print(numParametrosSensor[tipoSensor]);
      actualParametro++;
      if (actualParametro >= numParametrosSensor[tipoSensor]) {
        Serial.print(" act>num ");
        instanciarSensores();
        fase = 2;
        actualParametro = 0;
        currentSensor++;
        Serial.print("    fase=2,actualParametro=0 ");
      }
      //TODO: terminar, falta determinar cuando termina y luego instanciar el sensor
      break;
    default:
      Serial.print("Default:");
      Serial.print("modo:");
      Serial.print(mode);
      Serial.print(",fase:");
      Serial.print(fase);
      Serial.print(",n:");
      Serial.print(n);
  }
}
//@$1825367
int n;
void loop()
{
  // Sensar valores
  
  if (mode != 0) {
    for (int i = 0; i < cantSensors; i++) {
      sensor[i]->sense();
    }
  }
  

  //receiveData();
  if (mySerial.available()) {
    cad = mySerial.read();
    n = (int)cad;
    Serial.print(n);
    Serial.print(":");
    if (cad == 10) {
      Serial.println("Terminando");
      fase = 0;
      if (mode == 0) {
        // Ejecucion del setup de los sensores
        for (int i = 0; i < currentSensor; i++) {
          sensor[i]->setup();
          Serial.print("Setup:");
          Serial.println(i);
        }          
        mode = 1;
        mySerial.write("ok\r\n");
      }
    } else {
      processInput(n);
    }
    Serial.println();
  }
}






