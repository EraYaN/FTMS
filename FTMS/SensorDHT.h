#pragma once
#include "Sensor.h"
#include "Definitions.h"
#include <DHT.h>

class SensorDHT :
	public Sensor
{
public:
	//SensorDHT();
	SensorDHT(const char* name, SensorType type, int _pin);
	~SensorDHT(void);
	int Init();
	int updateValue();
	double getTemperature();
	double getHumidity();
private:
	double Temperature;	
	double Humidity;
	double OffsetT; //For Temperature compensation
	double OffsetH; //For Humidiy compensation
	int pin;
  DHT dht;
};

