#include "Director.h"
#include "Program.h"
#include <Time.h>

//Function Declarations for Director
/// <summary>
///	Constructor of the Director class.
/// </summary>
/// <param name="pid">ID of the program to run.</param>
Director::Director()
	:s_DHT11("Kast",DHT11,DHT11_PIN),
	s_DS18B20("Water",0),
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
	if(errCode=s_DHT11.updateValue()!=0) Serial.println("DHT11 update error 0"+errCode);
	//delay(100);
	if(errCode=s_DS18B20.updateValue()!=0) Serial.println("DS18B20 update error 0"+errCode);
	//delay(100);
	if(errCode=s_pHProbe.updateValue(s_DS18B20.getTemperature())!=0) Serial.println("pHProbe update error 0"+errCode);
	//
	//digitalClockDisplay();
	//draw screen
	frame();
	checkForHTTPConnections(); //check if any client has connected and respond.
	//delay(2000);
	//s_pHProbe.Calibrate();

}