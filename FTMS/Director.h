#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "SensorDHT.h"
#include "SensorDS.h"
#include "SensorpHProbe.h"
#include "Pins.h"

/// <summary>
///	Class that will direct all actions of the arduino and store its status.
/// </summary>
class Director{
	//Class discription
public:	
    Director();
	void Init();
	void Tick();
	int SpecialRoutine();
	void StartProgram();
	SensorpHProbe s_pHProbe;
	SensorDHT s_DHT11;
	SensorDS s_DS18B20;	
};
#endif
