/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void initEthernet();
void checkForHTTPConnections();
void processEvents();
void initEvents();
void sortEvents();
extern int getMoonlightStrength(double prog);
extern int getSunlightStrength(double prog);
double increase(double prog, double span, double time, double min, double max);
double decrease(double prog, double span, double time, double min, double max);
double normalize(double v);
extern double getMoonPhase(int Y, int M, int D);
void *safeMalloc(size_t size);
void safeFree(void *block);
void fr(const char* text);
void initScreen();
char* substr(const char* str, int start, int number);
unsigned int getStrWidth(const char *s);
void draw();
int drawStatusMessage(const char* msg);
void frameStatusMessage(const char* msg);
void frame();
void initTime();
time_t getTime(boolean forceNTP);
time_t getTime();
void sendNTPpacket(IPAddress& address);
time_t readNTPpacket();
double getDayProgress();
time_t lnow();
time_t ltime(time_t t);
int lhour();
int lminute();
int lsecond();
int lyear();
int lmonth();
int lday();
int lweekday();
int lhour(time_t t);
int lminute(time_t t);
int lsecond(time_t t);
int lyear(time_t t);
int lmonth(time_t t);
int lday(time_t t);
int lweekday(time_t t);
void digitalClockDisplay();
void printDigits(int digits);

#include "F:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "F:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\FTMS.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Configuration.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Configuration.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Definitions.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Director.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Director.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\EthernetFunctions.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\EthernetFunctions.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Event.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Event.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Events.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Events.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\LightCurves.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\MemoryFunctions.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Pins.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Program.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\ScreenFunctions.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Sensor.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\Sensor.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorDHT.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorDHT.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorDS.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorDS.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorpHProbe.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\SensorpHProbe.ino"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\TimeFunctions.h"
#include "C:\Users\Erwin\Documents\GitHub\FTMS\FTMS\TimeFunctions.ino"
#endif
