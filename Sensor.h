#ifndef SENSOR_H
#define SENSOR_H
#include "Definitions.h"

/// <summary>
///	Class that will serve as a basis for all other sensorclasses.
/// </summary>
class Sensor{
	//Class discription
public:
	Sensor(char* _name, SensorType _type);   
	Sensor();
	int Init();
	char* getName();
protected:
	char* name;
	SensorType type;
};
#endif