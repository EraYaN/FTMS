//Board = Arduino Mega 2560 or Mega ADK
#define ARDUINO 103
#define __AVR_ATmega2560__
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
#define __attribute__(x)
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
#define prog_void
#define PGM_VOID_P int
#define NOINLINE __attribute__((noinline))

typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {}

//already defined in arduno.h
//already defined in arduno.h
void initEthernet();
void checkForHTTPConnections();
extern int getMoonlightStrength(double prog);
extern int getSunlightStrength(double prog);
double increase(double prog, double span, double time, double min, double max);
double decrease(double prog, double span, double time, double min, double max);
double normalize(double v);
extern double getMoonPhase(int Y, int M, int D);
void fr(const char* text);
void initScreen();
char* substr(char* str, int start, int number);
unsigned int getStrWidth(const char *s);
void draw();
int drawStatusMessage(char* msg);
void frameStatusMessage(char* msg);
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
extern void *testMalloc(size_t size);
extern void testFree(void *block);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\Erwin\GitHub\FTMS\FTMS.ino"
#include "C:\Users\Erwin\GitHub\FTMS\Definitions.h"
#include "C:\Users\Erwin\GitHub\FTMS\Director.h"
#include "C:\Users\Erwin\GitHub\FTMS\Director.ino"
#include "C:\Users\Erwin\GitHub\FTMS\EthernetFunctions.h"
#include "C:\Users\Erwin\GitHub\FTMS\EthernetFunctions.ino"
#include "C:\Users\Erwin\GitHub\FTMS\Event.h"
#include "C:\Users\Erwin\GitHub\FTMS\Event.ino"
#include "C:\Users\Erwin\GitHub\FTMS\LightCurves.ino"
#include "C:\Users\Erwin\GitHub\FTMS\Pins.h"
#include "C:\Users\Erwin\GitHub\FTMS\Program.h"
#include "C:\Users\Erwin\GitHub\FTMS\ScreenFunctions.ino"
#include "C:\Users\Erwin\GitHub\FTMS\Sensor.h"
#include "C:\Users\Erwin\GitHub\FTMS\Sensor.ino"
#include "C:\Users\Erwin\GitHub\FTMS\SensorDHT.h"
#include "C:\Users\Erwin\GitHub\FTMS\SensorDHT.ino"
#include "C:\Users\Erwin\GitHub\FTMS\SensorpHProbe.h"
#include "C:\Users\Erwin\GitHub\FTMS\SensorpHProbe.ino"
#include "C:\Users\Erwin\GitHub\FTMS\TimeFunctions.h"
#include "C:\Users\Erwin\GitHub\FTMS\TimeFunctions.ino"
#include "C:\Users\Erwin\GitHub\FTMS\memfunctions.ino"
