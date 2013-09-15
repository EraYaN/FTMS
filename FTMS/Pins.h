#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
//Pin configurations
const int SDCARD_SLAVESELECT_PIN = 4;
const int SDCARD_SLAVESELECT_PIN_ORIG = SS; 
const int DHT11_PIN = 3;
const int ONEWIRE_PIN = 6; //DS18B20 etc. 4.7k resistor between +5V line and signal pin, for all one-wire devices. 2820B0AA0200001A
const int SCREEN_MOSI = 48;// Used for LCD R/W pin (SW SPI)
const int SCREEN_SCK = 47; // Used for LCD E pin (SW SPI)
const int SCREEN_SS = 49; //Used for LCD RS pin (SW SPI)
const int LED_WHITE_FRONT = 13; //LEDPWM1
const int LED_WHITE_REAR = 13; //LEDPWM2
const int LED_RED_FRONT = 11; //LEDPWM3
const int LED_RED_REAR = 9; //LEDPWM4
const int LED_BLUE_FRONT = 8; //LEDPWM5
const int LED_BLUE_REAR = 5; //LEDPWM6
const int FAN_SPEED = 7;
const int FAN_SPEED_INPUT1 = 46; //FAN_LEFT
const int FAN_SPEED_INPUT2= 45; //FAN_RIGHT
const int ETHERNET_INTERRUPT = 2;
//Module A
const int RELAY_TL1 = 23; // Day		(Amazon Day)		9000K,		All-day.
const int RELAY_TL2 = 25; // Day		(Sylvania Golux)	8500K,		All-day.
const int RELAY_TL3 = 27; // White	(Philips 840)		4000K,		Mid-day peak.
const int RELAY_TL4 = 29; // W-White (Philips 830)		3000K,		All-day.
const int RELAY_FLORAMATE = 31;
const int RELAY_CO2 = 33;
const int RELAY_PUMP_MAIN1 = 35;
const int RELAY_PUMP_MAIN2 = 37;
//Module B
const int RELAY_PUMP_CO2 = 22;
const int RELAY_AIRPUMP = 24;
const int RELAY_TERRA_LIGHT = 26;
const int RELAY_TERRA_HEAT = 28;
const int RELAY_RESERVE1 = 30;
const int RELAY_RESERVE2 = 32;
const int RELAY_RESERVE3 = 34;
const int RELAY_RESERVE4 = 36;

//pin, mode, default
const int pins[][3] = {
	{SDCARD_SLAVESELECT_PIN, OUTPUT, LOW},
	{SDCARD_SLAVESELECT_PIN_ORIG , OUTPUT, LOW},
	{DHT11_PIN, OUTPUT, LOW},
	{ONEWIRE_PIN , OUTPUT, LOW},
	{SCREEN_MOSI, OUTPUT, LOW},
	{SCREEN_SCK , OUTPUT, LOW},
	{SCREEN_SS , OUTPUT, LOW},
	{LED_WHITE_FRONT , OUTPUT, LOW},
	{LED_WHITE_REAR , OUTPUT, LOW},
	{LED_RED_FRONT , OUTPUT, LOW},
	{LED_RED_REAR , OUTPUT, LOW},
	{LED_BLUE_FRONT , OUTPUT, LOW},
	{LED_BLUE_REAR , OUTPUT, LOW},
	{FAN_SPEED, OUTPUT, LOW},
	{FAN_SPEED_INPUT1 , INPUT, LOW},
	{FAN_SPEED_INPUT2 , INPUT, LOW},
	{ETHERNET_INTERRUPT, INPUT, LOW},
	{RELAY_TL1 , OUTPUT, HIGH},
	{RELAY_TL2 , OUTPUT, HIGH},
	{RELAY_TL3 , OUTPUT, HIGH},
	{RELAY_TL4 , OUTPUT, HIGH},
	{RELAY_FLORAMATE, OUTPUT, HIGH},
	{RELAY_CO2, OUTPUT, HIGH},
	{RELAY_PUMP_MAIN1, OUTPUT, HIGH},
	{RELAY_PUMP_MAIN2, OUTPUT, HIGH},
	{RELAY_PUMP_CO2, OUTPUT, HIGH},
	{RELAY_AIRPUMP, OUTPUT, HIGH},
	{RELAY_TERRA_LIGHT, OUTPUT, HIGH},
	{RELAY_TERRA_HEAT, OUTPUT, HIGH},
	{RELAY_RESERVE1, OUTPUT, HIGH},
	{RELAY_RESERVE2, OUTPUT, HIGH},
	{RELAY_RESERVE3, OUTPUT, HIGH},
	{RELAY_RESERVE4, OUTPUT, HIGH}
};
const int pincount = 33;
#endif