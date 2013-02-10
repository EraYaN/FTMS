#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <Time.h>
/*Define shit here*/

enum EventType {
  Interval,
  Time,
  Random
}; 
struct Event{
	EventType type;
	unsigned long interval;
	unsigned int hour;
	unsigned int minute;
	unsigned long frequency;
	time_t lastExecution;
	char* name;
};
enum SensorType{
	Unknown,
	DHT11,
	DHT22,
	pHProbe,
	DS18B20,
	WaterLevel	
};
#endif
