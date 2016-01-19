#include "SensorDS.h"

void SensorDS::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
SensorDS::SensorDS(const char* name, int _id, OneWire* _oneWire)
	: Sensor(name,ST_DS18B20), ds(_oneWire)
{ 
  pin = ONEWIRE_PIN;
	Temperature = -1;
	id = _id;
}
int SensorDS::Init(){		
	OffsetT = -0.5; //measured against melting water.
  ds.begin();
	ds.getAddress(address, id);	
	ds.setResolution(address,11);
	return ds.getDeviceCount() > 0;
}

int SensorDS::updateValue(){
	ds.requestTemperatures(); 
	Temperature = ds.getTempC(address);
	return 0;
}
double SensorDS::getTemperature(){
	return Temperature+OffsetT;
}
SensorDS::~SensorDS(void)
{
}
