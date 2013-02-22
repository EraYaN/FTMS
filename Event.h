#include "Definitions.h"
#pragma once
class Event
{
	EventType type;
	double interval; //in day progress..
	double time; //in day progress..
	double frequency; //in day progress..
	unsigned int pin;
	bool simple;
	byte pinValue;
	int (*nonSimpleExecute)();
	time_t lastExecution;
	char* name;
public:
	char* getName();
	int execute();
	Event(void);
	Event(char* _name, EventType _type, double _occurDouble, unsigned int _pin, byte _pinValue);
	Event(char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)());
	~Event(void);
};

