#ifndef TIMEFUNCTIONS_H
#define TIMEFUNCTIONS_H
#define SECONDS_IN_DAY = 86400UL
#define SECONDS_IN_HOUR = 3600UL
#define MAX_DIFF_RANDOM_EVENTS = 1.5;
#include <Time.h>
#include <Timezone.h>
#include <EthernetUdp.h>
#include <RTClib.h> 

TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, +120};  //UTC + 2 hours
TimeChangeRule CET = {"CET", Last, Sun, Oct, 2, +60};   //UTC + 1 hours
Timezone tz(CEST, CET);

IPAddress timeServer(194, 109, 22, 18);//ntp.xs4all.nl (194.109.22.18)
IPAddress timeServerBackup(194, 109, 20, 18);//ntp2.xs4all.nl (194.109.20.18)


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
#endif