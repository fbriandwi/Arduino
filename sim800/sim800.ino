#include "gprs.h"
#include <SoftwareSerial.h>

GPRS gprs(9600);//BaudRate Gsm

void setup(){
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Test Serial debug ...");
  gprs.preInit();//Power on Gsm 
  while(0 != gprs.sendATTest())
  {
      Serial.println("Sim800L init error!");
  }
  Serial.println("Sim800L init O.K!");
}

void loop(){
  gprs.serialDebug();
}
