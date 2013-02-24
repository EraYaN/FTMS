#include "SensorDHT.h"


SensorDHT::SensorDHT(char* name, SensorType type, int _pin)
	: Sensor(name,type)
{
	pin = _pin;
	Humidity = -1;
	Temperature = -1;
}
/*SensorDHT::SensorDHT()
	: Sensor("DHT",DHT11)
{
	pin = 0;
	Humidity = 0;
	Temperature = 0;
}*/
int SensorDHT::Init(){
	//nothing
	OffsetH = 0;
	OffsetT = 0;
}
int SensorDHT::updateValue(){
	int chk = 1;
	if(type==DHT11){
		chk = DHT.read11(pin);
	} else if (type==DHT22){
		chk = DHT.read22(pin);
	} else {
		return -4;
	}
	switch (chk)
	{
		case DHTLIB_OK:  
			 //everything is fine
			break;
		case DHTLIB_ERROR_CHECKSUM: 
			return -1; 
			break;
		case DHTLIB_ERROR_TIMEOUT: 
			return -2; 
			break;
		default: 
			return -3; 
			break;
	}
	Humidity = DHT.humidity;
	Temperature = DHT.temperature;	
	return 0;
}
double SensorDHT::getHumidity(){
	return Humidity+OffsetH;
}
double SensorDHT::getTemperature(){
	return Temperature+OffsetT;
}
SensorDHT::~SensorDHT(void)
{
}
