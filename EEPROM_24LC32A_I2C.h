/*
Created by: 	Guillermo sampallo
Last updated:	08/09/2020
gsampallo.com

Use to save data to eeprom memory 24LC32A via I2C
Based on https://www.hobbytronics.co.uk/eeprom-page-write
*/

#define EEPROM_24LC32A_I2C_h

#include <Arduino.h>
#include <Wire.h>

using namespace std;

class EEPROM_24LC32A_I2C {
    
    public:
        EEPROM_24LC32A_I2C(int eeprom_addres);
        void begin();
        void write(unsigned int eeaddress, char* data);
        void read(unsigned int eeaddress, unsigned char* data, unsigned int num_chars);
    private:
        int eeprom = 0x50;
};