#pragma once
#include "Sensor.h"
#include "Definitions.h"
#include <DallasTemperature.h>
class SensorDS :
	public Sensor
{
public:
	//SensorDHT();
	SensorDS(const char* name, int _id, OneWire* _oneWire);
	~SensorDS(void);
	int Init();
	int updateValue();
	double getTemperature();
	void printAddress(DeviceAddress deviceAddress);
private:
	double Temperature;		
	double OffsetT; //For Temperature compensation	
	DeviceAddress address;
  DallasTemperature ds;
	int id;
	int pin;
};

