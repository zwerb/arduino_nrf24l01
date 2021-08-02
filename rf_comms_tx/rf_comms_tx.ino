/*
* RF Comms Transmitter (TX) Code
*     With additonal features added by: Nerdami
*     -collecting data from DHT11
*                
* With Radio code adapted from: www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 4

// TEMP SENSOR
DHT dht(DHTPIN, DHTTYPE);

// RANDINT GENERATOR
int iterator;

// RF24 MODULE
RF24 radio(10,9); // CE, CSN
const byte address[6] = "00001";

void setup() {

Serial.begin(115200);
Serial.println("init");

iterator=1;

randomSeed(analogRead(0));

dht.begin();
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  float hum = dht.readHumidity();
  float tmp = dht.readTemperature(true);

  char outputbuffer[32];
  strcpy(outputbuffer, "{\"h\":");

  char valbuffer[8];
  dtostrf(hum,6,2,valbuffer);

  strcat(outputbuffer, valbuffer);
  strcat(outputbuffer, ","); 
  strcat(outputbuffer, "\"t\":"); 

  dtostrf(tmp,6,2,valbuffer);
  strcat(outputbuffer, valbuffer);
  strcat(outputbuffer, ","); 

 
  strcat(outputbuffer, "\"i\":"); 

  itoa(iterator,valbuffer,16);
  strcat(outputbuffer, valbuffer);
  strcat(outputbuffer, "}"); 
  
  
  Serial.println(outputbuffer);
  
  if (isnan(hum) || isnan(tmp)) {
    hum = -1.01;
    tmp = -1.01;
  }

  char text[32];
  strcpy(text, outputbuffer);
  radio.write(&text, sizeof(text));
  Serial.println("tx: "+String(text));
  delay(2500);
  
  if(iterator>14){
    iterator=0;
  }else{
    iterator=iterator+1;
  }
}
