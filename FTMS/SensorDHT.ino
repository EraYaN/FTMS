#include "SensorDHT.h"


SensorDHT::SensorDHT(const char* name, SensorType type, int _pin)
	: Sensor(name,type), dht(DHT11_PIN,DHT11)
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
	OffsetH = 4; //confirm
	OffsetT = 0; //measured against others.
}
int SensorDHT::updateValue(){	
	//Humidity = dht.readHumidity();
	//Temperature = dht.readTemperature();
  Humidity = 55.6;
  Temperature = 22.5;
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
