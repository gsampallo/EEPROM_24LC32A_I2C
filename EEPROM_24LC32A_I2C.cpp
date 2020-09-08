/*
Created by: 	Guillermo sampallo
Last updated:	08/09/2020
gsampallo.com

Use to save data to eeprom memory 24LC32A via I2C
Based on https://www.hobbytronics.co.uk/eeprom-page-write
*/

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM_24LC32A_I2C.h>

using namespace std;

EEPROM_24LC32A_I2C::EEPROM_24LC32A_I2C(int eeprom_addres) {
    eeprom = eeprom_addres;
}

void EEPROM_24LC32A_I2C::begin() {
    Wire.begin();
}

void EEPROM_24LC32A_I2C::read(unsigned int eeaddress, unsigned char* data, unsigned int num_chars) {
  unsigned char i=0;
  Wire.beginTransmission(eeprom);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(eeprom,num_chars);
 
  while(Wire.available()) data[i++] = Wire.read();

}

void EEPROM_24LC32A_I2C::write(unsigned int eeaddress, char* data) {
  // Uses Page Write for 24LC256
  // Allows for 64 byte page boundary
  // Splits string into max 16 byte writes
  unsigned char i=0, counter=0;
  unsigned int  address;
  unsigned int  page_space;
  unsigned int  page=0;
  unsigned int  num_writes;
  unsigned int  data_len=0;
  unsigned char first_write_size;
  unsigned char last_write_size;  
  unsigned char write_size;  
  
  // Calculate length of data
  do{ data_len++; } while(data[data_len]);   
   
  // Calculate space available in first page
  page_space = int(((eeaddress/64) + 1)*64)-eeaddress;

  // Calculate first write size
  if (page_space>16){
     first_write_size=page_space-((page_space/16)*16);
     if (first_write_size==0) first_write_size=16;
  }   
  else 
     first_write_size=page_space; 
    
  // calculate size of last write  
  if (data_len>first_write_size) 
     last_write_size = (data_len-first_write_size)%16;   
  
  // Calculate how many writes we need
  if (data_len>first_write_size)
     num_writes = ((data_len-first_write_size)/16)+2;
  else
     num_writes = 1;  
     
  i=0;   
  address=eeaddress;
  for(page=0;page<num_writes;page++) 
  {
     if(page==0) write_size=first_write_size;
     else if(page==(num_writes-1)) write_size=last_write_size;
     else write_size=16;
  
     Wire.beginTransmission(eeprom);
     Wire.write((int)((address) >> 8));   // MSB
     Wire.write((int)((address) & 0xFF)); // LSB
     counter=0;
     do{ 
        Wire.write((byte) data[i]);
        i++;
        counter++;
     } while((data[i]) && (counter<write_size));  
     Wire.endTransmission();
     address+=write_size;   // Increment address for next write
     
     delay(6);  // needs 5ms for page write
  }
}
 

