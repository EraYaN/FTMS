#include <SPI.h>
#include "Definitions.h"
#include <Wire.h>


#include "Pins.h"
#include "Sensor.h"
#include "Director.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <U8glib.h>

Director drctr;

OneWire oneWire(ONEWIRE_PIN);

unsigned long cycles = 0;
unsigned long cyclesSinceLastUpdate = 0;
unsigned long lastUpdateMicrosStart = 0;
unsigned long lastUpdateMicrosEnd = 0;

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup!");
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(13, OUTPUT); //LED pin 
	initScreen();
	Serial.println("Screen ready!");
	drctr.Init();
 Serial.println("Director ready!");
}

void loop()
{	  
  unsigned long t1 = micros();
  if(cyclesSinceLastUpdate>=updateTime){
    Serial.println("Director executing!");
    lastUpdateMicrosStart = micros();
  	drctr.StartProgram();	    
    lastUpdateMicrosEnd = micros();
    Serial.println((lastUpdateMicrosEnd-lastUpdateMicrosStart)/1000);
    cyclesSinceLastUpdate = 0;
    cycles++;
    if(cycles>128){
      cycles=0;
    }    
  } else {
    cyclesSinceLastUpdate++;
  }
  unsigned long t2 = micros();
  if(t2>t1){
    long remaining = tickTime-(t2-t1);    
    if(remaining>0){
      delayMicroseconds(remaining);
    }
  } else {
    delayMicroseconds(tickTime);
  }
}
