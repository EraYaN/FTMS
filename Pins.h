#ifndef PINS_H
#define PINS_H

//Pin configurations
#define SDCARD_SLAVESELECT_PIN = 4;
#define SDCARD_SLAVESELECT_PIN_ORIG = SS;
#define DHT11_PIN = 6;
#define DHT22_PIN = 5;
#define ONEWIRE_PIN = 7; //DS18B20 etc. 4.7k resistor between +5V line and signal pin, for all one-wire devices. http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
#define SPI_MISO = MISO;
#define SPI_MOSI = MOSI;
#define SPI_SCK = SCK;
#endif