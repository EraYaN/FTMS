#ifndef DEFINITIONS_H
#define DEFINITIONS_H
/*Define shit here*/

enum SensorType : byte
{
	ST_Unknown,
	ST_DHT11,
	ST_DHT22,
	ST_pHProbe,
	ST_DS18B20,
	ST_WaterLevel	
};

const int tickTime = 5000; //in us
const int updateTime = 200; //in multiples of tickTime

#endif
