#ifndef DEFINITIONS_H
#define DEFINITIONS_H
/*Define shit here*/

enum EventType {
  Interval,
  Time,
  Random
}; 
struct Event{
	EventType type;
	unsigned long interval;
	unsigned int hour;
	unsigned int minute;
	unsigned long frequency;
	DateTime lastExecution;
	char* name;
};

#endif
