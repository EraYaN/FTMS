#ifndef EVENT_H
#define EVENT_H
#include "Definitions.h"
#include "TimeFunctions.h"
class Event
{
	
	
	unsigned int pin;
	bool simple;
	byte pinValue;
	int (*nonSimpleExecute)();
	time_t lastExecution;
	const char* name;
public:
	const char* getName();
	int execute();
	int check();
	EventType type;
	double interval; //in seconds..
	double time; //in day progress..
	double frequency; //per day.. (max)
	Event(void);
	Event(const char* _name, EventType _type, double _occurDouble, unsigned int _pin, byte _pinValue);
	Event(const char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)());
	~Event(void);
};

#endif