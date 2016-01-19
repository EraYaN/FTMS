#include "Director.h"

//Function Declarations for Director
/// <summary>
///	Constructor of the Director class.
/// </summary>
/// <param name="pid">ID of the program to run.</param>
Director::Director()
	:s_DHT11("Kast",ST_DHT11,DHT11_PIN),
	s_DS18B20("Water",0,&oneWire),
	s_pHProbe()
{

}
/// <summary>
///	Constructor of the Director class. Run default program.
/// </summary>
/*Director::Director() {
Director(0);
}*/
void Director::Init() {
	//contruct
	s_pHProbe.Init();
	s_DHT11.Init();
	s_DS18B20.Init();
	//set Pin Modes
	for(int pin=0;pin<pincount;pin++){
		pinMode(pins[pin][0],pins[pin][1]);
		if(pins[pin][1]==OUTPUT){
			if(digitalPinHasPWM(pins[pin][1])){
				analogWrite(pins[pin][0],pins[pin][2]);
			} else {
				digitalWrite(pins[pin][0],pins[pin][2]);
			}
		}
	}
}
void Director::Tick(){
	//runs every "loop()"
	//Update Time
	//doTimeWork();
}
int Director::SpecialRoutine(){
	//Pause all and execute task. Like calibrating the pH-probe.
	return 0;
}
void Director::StartProgram(){  
	//start the program.
	int errCode = 0;
	//update all sensor values
  unsigned long t1 = millis();
	if((errCode=s_DHT11.updateValue())!=0) Serial.println("E: DHT11 update error 0"+errCode);
  unsigned long t2 = millis();
	if((errCode=s_DS18B20.updateValue())!=0) Serial.println("E: DS18B20 update error 0"+errCode);
  unsigned long t3 = millis();
	if((errCode=s_pHProbe.updateValue(s_DS18B20.getTemperature()))!=0) Serial.println("E: pHProbe update error 0"+errCode);
  unsigned long t4 = millis();
	//draw screen
	frame();
  unsigned long t5 = millis();
  Serial.println("Sensors");
  Serial.println(t2-t1);
  Serial.println(t3-t2);
  Serial.println(t4-t3);
  Serial.println("Screen");
  Serial.println(t5-t4);
  Serial.println("Total");
  Serial.println(t5-t1);
}
