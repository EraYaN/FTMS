#ifndef SENSOR_H
#define SENSOR_H
#include "Definitions.h"

/// <summary>
///	Class that will serve as a basis for all other sensorclasses.
/// </summary>
class Sensor{
	//Class discription
public:
	Sensor(const char* _name, SensorType _type);   
	Sensor();
	int Init();
	const char* getName();
protected:
	const char* name;
	SensorType type;
};
#endif