#include <SPI.h>
#include <Time.h> 
#include <Ethernet.h>
#include "Definitions.h"
#include "Director.h"
#include "Pins.h"
#include <Wire.h>
#include <EthernetUdp.h>
#include <Metro.h>
#include <RTClib.h> 
#include <SD.h>
#include <dht.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
RTC_DS1307 RTC;
Director drctr;

void setup()
{
	drctr.Init();
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(SDCARD_SLAVESELECT_PIN_ORIG, OUTPUT);  // set the SS pin as an output (necessary!)
	digitalWrite(SDCARD_SLAVESELECT_PIN_ORIG, HIGH);  // Disables W5100 chip?
	if (!SD.begin(SDCARD_SLAVESELECT_PIN)) {
		// Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	  }
	if (Ethernet.begin(mac) == 0) {
		// no point in carrying on, so do nothing forevermore:
		for(;;)
		  ;
	}
	Wire.begin();
	RTC.begin();
	if(!RTC.isrunning()){
		getTime(true);
	}
	randomSeed(RTC.now().unixtime());
}

void loop()
{
	drctr.StartProgram();
}
