#include <SoftwareSerial.h>
#include "Pir.h"

SoftwareSerial mySerial(2, 3); // RX, TX
String command;
Pir pir1(8);
int pir1Val = LOW;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Iniciando comunicaciones!");

  pir1.setup();

  mySerial.begin(9600);
  mySerial.println("Inicio\r\n");
}


char cad;
void loop()
{

  // Sensar valores
  pir1Val = pir1.sense();

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
  Serial.println(command);
  if (true) { // reemplazar por un comando valido
    sendData();
  }
}

String p;
char pc[5];
void sendData(){

  mySerial.write("ID1"); // ID del nodo
  mySerial.write("|T12.9|H87");
  mySerial.write("|P");
  p = String(pir1Val);
  p.toCharArray(pc,5);
  mySerial.write(pc);
  mySerial.write("|RA");
  mySerial.write("1");
  mySerial.write("\r\n");

}

