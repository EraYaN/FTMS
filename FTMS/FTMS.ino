#include <SPI.h>
#include "Definitions.h"
#include <Wire.h>

#include "Pins.h"
#include "Sensor.h"
#include "Director.h"
#include "Communication.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <U8glib.h>

Director drctr;
Communication com;

OneWire oneWire(ONEWIRE_PIN);

unsigned long cycles = 0;
unsigned long cyclesSinceLastUpdate = 0;
unsigned long lastUpdateMicrosStart = 0;
unsigned long lastUpdateMicrosEnd = 0;
byte serialInByte = 0;

void setup()
{
	com.Init();
	com.DebugMessage("Communication ready!");
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	 //LED pin 
	initScreen();
	com.DebugMessage("Screen ready!");
	drctr.Init();
  com.DebugMessage("Director ready!");
}

void loop()
{	  
  com.CheckForData();
  unsigned long t1 = micros();
  if(cyclesSinceLastUpdate>=updateTime){
    lastUpdateMicrosStart = micros();
  	drctr.StartProgram();	    
    lastUpdateMicrosEnd = micros();
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
