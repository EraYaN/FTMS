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
void init_Time();
time_t getTime(boolean forceNTP);
time_t getTime();
void sendNTPpacket(IPAddress& address);
time_t readNTPpacket();
void doTimeWork();
void timeChanged();
double normalize(double v);
double getPhase(int Y, int M, int D);

#include "F:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "F:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "F:\Users\Erwin\GitHub\FTMS\FTMS.ino"
#include "F:\Users\Erwin\GitHub\FTMS\Definitions.h"
#include "F:\Users\Erwin\GitHub\FTMS\Director.h"
#include "F:\Users\Erwin\GitHub\FTMS\Director.ino"
#include "F:\Users\Erwin\GitHub\FTMS\Pins.h"
#include "F:\Users\Erwin\GitHub\FTMS\Program.h"
#include "F:\Users\Erwin\GitHub\FTMS\ScreenFunctions.ino"
#include "F:\Users\Erwin\GitHub\FTMS\TimeFunctions.ino"
