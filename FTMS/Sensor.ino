#include "Sensor.h"

Sensor::Sensor(){
	name = "Unknown Sensor";
}
Sensor::Sensor(const char* _name, SensorType _type){
	name= _name;
	type=_type;
}
int Sensor::Init(){
	//nothing
	return 1;
}
const char* Sensor::getName(){
	return name;
}

