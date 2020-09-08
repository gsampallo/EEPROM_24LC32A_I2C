/*
Created by: 	Guillermo sampallo
Last updated:	08/09/2020
gsampallo.com

Example of how to use library to read and write on 24LC32A via I2C.

Based on https://www.hobbytronics.co.uk/eeprom-page-write

*/
#include <EEPROM_24LC32A_I2C.h>

EEPROM_24LC32A_I2C eprom = EEPROM_24LC32A_I2C(0x50);
 
void setup() {
  Serial.begin(9600);

  eprom.begin();
  
  //Escribe los datos en la eeprom en la direccion 0
  char str_data[]={"Esto es un ejemplo gsampallo.com"};
  eprom.write(0,str_data);

  //Para leer los datos
  //El nro. 32 es la cantidad de digitos que tiene la cadena a leer.
  unsigned char temp[32];
  
  int address = 0; //comenzamos a leer desde la direccion 0
  eprom.read(address,temp,32);
  Serial.write(temp,32);
 
  Serial.println("");

}

void loop() {
  // put your main code here, to run repeatedly:

}