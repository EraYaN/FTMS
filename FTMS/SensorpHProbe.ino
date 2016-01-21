#include "SensorpHProbe.h"
#include <HardwareSerial.h>

SensorpHProbe::SensorpHProbe(void) 
	: Sensor("pHProbe",ST_pHProbe)
{
	pH = -1.0;
	Calibrating = false;
}
int SensorpHProbe::Init(){
	Serial3.begin(38400);
	delayMicroseconds(10000);
	Serial3.print("E\r");
	Serial3.flush();	
	Serial3.print("L1\r");
	Serial3.flush();
	while(Serial3.available()) Serial3.read(); //flush out recieved bytes
	return 0;
}
int SensorpHProbe::updateValue(double Temperature){
	if(!Calibrating){
    //Serial.println(Temperature,2);
		Serial3.print(Temperature,2);
		Serial3.print('\r');
		Serial3.flush();
    //Serial.println(Serial3.readStringUntil('\r'));
		pH = Serial3.parseFloat();
    //Serial.println(pH);
    pH = 0;
		return 0;
	} else {
		return 1;
	}
 pH = 7;
 return 0;
}
double SensorpHProbe::getpH(){
	return pH;
}
bool SensorpHProbe::isCalibrating(){
	return Calibrating;
}
int SensorpHProbe::Calibrate(){
	com.DebugMessage("Calibrating...");
	Calibrating = true;
	frameStatusMessage("Insert the probe in the pH 7 calibration solution.");
	delay(5000);
	frameStatusMessage("Going in continues modes..");
	delay(1000);
	//TODO make the waiting into a loop and based on actual time.
	frameStatusMessage("Waiting 2 minutes. (0 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (10 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (20 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (30 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (40 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (50 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (60 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (70 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (80 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (90 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (100 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (110 seconds)");
	delay(10000);
	frameStatusMessage("Waiting 2 minutes. (120 seconds)");
	delay(1000);
	frameStatusMessage("Sending S command to pH stamp.");
	delay(1000);
	frameStatusMessage("Step two (ph4). etc");
	//TODO Actually do a Serial.print("S\r")
	delay(1000);
	frameStatusMessage("Step three (ph10). etc");
	//TODO Finish the other pieces of the calibration program.
	delay(1000);
	frameStatusMessage("Calibraton complete.");
	delay(1000);
	Calibrating = false;
	return 0;
}
SensorpHProbe::~SensorpHProbe(void)
{
	Serial3.end();
}
/*
1. First place you're pH probe in the yellow pH 7 calibration solution.
2. Instruct the circuit to go into continues mode.
3. Wait 1 to 2 minutes.
4. TX the S command. Your pH Circuit is now calibrated for pH7.
5. Rinse off pH sensor, dry with paper towel.
6. Place pH sensor in the red pH 4 calibration solution.
7. Wait 1 to 2 minutes (Circuit should still be in continues mode).
8. TX the F command.
Your pH stamp is now calibrated for pH4.
9. Rinse off pH sensor, dry with paper towel.
10. Place pH sensor in the blue pH 10 calibration solution.
11. Wait 1 to 2 minutes (Circuit should still be in continues mode).
12. TX the T command. Your pH Circuit is now calibrated for pH10.
13. Transmit the E command.
14. The pH Circuit is now calibrated. The calibration data is stored in the EEPROM
and will be retained even if the stamp is powered off.
Source: Atlas Scientific
*/
