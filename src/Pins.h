#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
//Pin configurations
const int SDCARD_SLAVESELECT_PIN = 4;
const int SDCARD_SLAVESELECT_PIN_ORIG = SS; 
const int DHT11_PIN = 3;
const int DHT22_PIN = 6; //unused
const int ONEWIRE_PIN = 7; //DS18B20 etc. 4.7k resistor between +5V line and signal pin, for all one-wire devices. http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
const int SCREEN_MOSI = 47;// Used for LCD R/W pin (SW SPI)
const int SCREEN_SCK = 48; // Used for LCD E pin (SW SPI)
const int SCREEN_SS = 49; //Used for LCD RS pin (SW SPI)
#endif