#include <Time.h> 
#include <EthernetUdp.h>
#include <Metro.h>
#include <RTClib.h> 

const int NTP_PACKET_SIZE= 48;
const unsigned long seventyYears = 2208988800UL; 
unsigned int localPort = 8888;
int needNTPrefreshin = 0;
time_t prevTime = 0;

IPAddress timeServer(194, 109, 22, 18);//ntp.xs4all.nl (194.109.22.18)
IPAddress timeServerBackup(194, 109, 20, 18);//ntp2.xs4all.nl (194.109.20.18)

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void init_Time(){
	Udp.begin(localPort);
	 setSyncProvider(getTime);
	 setSyncInterval(600);  
  while(timeStatus()== timeNotSet)   
     ; // wait until the time is set by the sync provider
}
//base time update function it requests internet time once every 288 times (should not be more than once every 4 seconds, is once a day now)
time_t getTime(boolean forceNTP){
	time_t t = 0;
	if(!RTC.isrunning()){
		needNTPrefreshin = 0;
	}
	if(needNTPrefreshin<=0||forceNTP){		
		sendNTPpacket(timeServer); // send an NTP packet to a time server
		// wait to see if a reply is available
		delay(1000);
		if ( Udp.parsePacket() ) { 
			t = readNTPpacket();
			RTC.adjust(DateTime(t));
		} else {
			//backupplan
			sendNTPpacket(timeServerBackup); // send an NTP packet to a time server
			// wait to see if a reply is available
			delay(1000); 
			if ( Udp.parsePacket() ) { 
				t = readNTPpacket();
				RTC.adjust(DateTime(t));
			}
		}
		needNTPrefreshin = 288;
	}
	if(RTC.isrunning() && t==0 ){
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
/*unsigned long*/ void sendNTPpacket(IPAddress& address)
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

void doTimeWork(){
	if(now()!=prevTime){
		timeChanged();
	}
}

void timeChanged(){
	//TODO: display change
	//check events about to happen.
}
// Adapted from Stephen R. Schmitt's Lunar phase computation program.
// Originally written for the Zeno programming language.
// http://home.att.net/~srschmitt/lunarphasecalc.html
double normalize(double v) {           // normalize moon calculation between 0-1 (per unage)
    v = v - floor(v);
    if (v < 0)
        v = v + 1;
    v = fabs(v-0.5)/0.5;
    return v;
}
double getPhase(int Y, int M, int D) {
  double  IP;  
  long YY, MM, K1, K2, K3, JD;
  YY = Y - floor((12 - M) / 10);
  MM = M + 9;
  if(MM >= 12)
    MM = MM - 12;
  
  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;

  JD = K1 + K2 + D + 59;
  if(JD > 2299160)
    JD = JD -K3;
  
  IP = normalize((JD - 2451550.1) / 29.530588853);  
  return IP;    
}