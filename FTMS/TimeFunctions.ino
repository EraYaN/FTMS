#include "TimeFunctions.h"
#include <Time.h>
#include <Timezone.h>
#include <EthernetUdp.h>
#include <RTClib.h>

const int NTP_PACKET_SIZE= 48;
const unsigned long seventyYears = 2208988800UL; 
unsigned int localPort = 8888;
int needNTPrefreshin = 0;
time_t prevTime = 0;
const int secondsBeforeSync = 600;
const int cyclesBeforeNTPReq = 288;
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void initTime(){
		Udp.begin(localPort); //TODO ethernetshield?
	 setSyncProvider(getTime);
	 setSyncInterval(secondsBeforeSync);  
  while(timeStatus()== timeNotSet)   
  ; // wait until the time is set by the sync provider
}
//base time update function it requests internet time once every 288 times (should not be more than once every 4 seconds, is once a day now)
time_t getTime(boolean forceNTP){
	Serial.print("Sync time, in "); 
	Serial.print(needNTPrefreshin*secondsBeforeSync/60); 
	Serial.println(" minutes will the time be requested from the internet."); 
	//TODO remove next line
	//return (time_t)1360450800;
	time_t t = 0;
	if(!RTC.isrunning()){
		needNTPrefreshin = 0;
	}
	if(needNTPrefreshin<=0||forceNTP){		
		Serial.println("NTP request.."); 
		sendNTPpacket(timeServer); // send an NTP packet to a time server
		// wait to see if a reply is available
		delay(1000);
		if ( Udp.parsePacket() ) { 
			t = readNTPpacket();
			RTC.adjust(DateTime(t));
		} else {
			//backupplan
			Serial.println("NTP backup request.."); 
			sendNTPpacket(timeServerBackup); // send an NTP packet to a time server
			// wait to see if a reply is available
			delay(1000); 
			if ( Udp.parsePacket() ) { 
				t = readNTPpacket();
				RTC.adjust(DateTime(t));
			} else {
				Serial.println("Both NTP requests failed.."); 
			}
		}
		needNTPrefreshin = cyclesBeforeNTPReq;
	}
	if(RTC.isrunning() && t==0 ){
		Serial.println("Got time from RTC request.."); 
		t = RTC.now().unixtime();
	}
	needNTPrefreshin--;
	return t;
}
//Overload for sync provider
time_t getTime(){
	return getTime(false);
}
// send an NTP request to the time server at the given address 
void sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}

time_t readNTPpacket(){
	Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer
	//the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, esxtract the two words:

	unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
	unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord; 
	// Unix time starts on Jan 1 1970. In seconds, that's 2208988800
	// subtract seventy years:
	unsigned long epoch = secsSince1900 - seventyYears;  
	// return Unix time:
	return (time_t)epoch; 
}


//time helper functions
double getDayProgress(){
	time_t t = lnow();
	return (((double)hour(t)*SECONDS_IN_HOUR+(double)minute(t)*60UL+(double)second(t))/SECONDS_IN_DAY);
}
time_t lnow(){
	return tz.toLocal(now());
}
time_t ltime(time_t t){
	return tz.toLocal(t);
}
//local time function using now
int lhour(){
	return hour(lnow());
}
int lminute(){
	return minute(lnow());
}
int lsecond(){
	return second(lnow());
}
int lyear(){
	return year(lnow());
}
int lmonth(){
	return month(lnow());
}
int lday(){
	return day(lnow());
}
int lweekday(){
	return weekday(lnow());
}
//local time functions with a given time (UTC).
int lhour(time_t t){
	return hour(ltime(t));
}
int lminute(time_t t){
	return minute(ltime(t));
}
int lsecond(time_t t){
	return second(ltime(t));
}
int lyear(time_t t){
	return year(ltime(t));
}
int lmonth(time_t t){
	return month(ltime(t));
}
int lday(time_t t){
	return day(ltime(t));
}
int lweekday(time_t t){
	return weekday(ltime(t));
}
//debug functions
void digitalClockDisplay(){
  // digital clock display of the time
time_t t = lnow();
  Serial.print(hour(t));
  printDigits(minute(t));
  printDigits(second(t));
  Serial.print(" ");
  Serial.print(day(t));
  Serial.print(" ");
  Serial.print(month(t));
  Serial.print(" ");
  Serial.print(year(t));
  Serial.print(" (");
  Serial.print(getDayProgress(),6);
  Serial.println(")");
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}