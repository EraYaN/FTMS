#include <SPI.h>
#include <Time.h> 
#include <Timezone.h>
#include <Ethernet.h>
#include "Definitions.h"
#include "Director.h"
#include <Wire.h>
#include <EthernetUdp.h>
#include <Metro.h>
#include <RTClib.h> 
#include <SD.h>
#include <dht.h>
#include "Pins.h"
#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MemoryFree.h>
#include <U8glib.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };
IPAddress ip(192,168,178,3);
EthernetServer server(80);
RTC_DS1307 RTC;
Director drctr(0);
dht DHT;
//OneWire oneWire(ONEWIRE_PIN);
//int hte = 0, vte = 0;

void setup()
{

	Serial.begin(115200);
	Serial.println("Setup!");
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(SDCARD_SLAVESELECT_PIN_ORIG, OUTPUT);  // set the SS pin as an output (necessary!)
	digitalWrite(SDCARD_SLAVESELECT_PIN_ORIG, HIGH);  // Disables W5100 chip?
	if (!SD.begin(SDCARD_SLAVESELECT_PIN)) {
		Serial.println("Card failed, or not present");
		//don't do anything more:
		return;
	} else {
		Serial.println("SD card ready!");
	}
	Ethernet.begin(mac,ip);
	initEthernet();
	Serial.println("Ethernet ready!");
	initTime();
	Serial.println("Time ready!");
	//Wire.begin();
	/*Serial.print("RTC response: ");
	Serial.println(RTC.begin());
	if(!RTC.isrunning()){
		getTime(true);
	}*/
	randomSeed(lnow());
	pinMode(13, OUTPUT); //LED pin 
	initScreen();
	Serial.println("Screen ready!");
	//drctr.StartProgram();	
	drctr.Init();
	Serial.println("Director ready!");
}

void loop()
{
	//Serial.println(sizeof(u8g_uint_t));
	Serial.println(F("Starting program in 1 second..."));
	delay(1000);
	drctr.StartProgram();	

	Serial.println(F("Program done."));
	//delay(5000);
}
