#pragma once
#include "Sensor.h"
class SensorpHProbe :
	public Sensor
{
public:
	SensorpHProbe(void);
	~SensorpHProbe(void);
	int Init();
	int updateValue(double Temperature);
	double getpH();
	bool isCalibrating();
	int Calibrate();
private:
	double pH;
	bool Calibrating;
	double Temperature; //For compensation
};

