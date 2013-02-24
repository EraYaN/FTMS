#ifndef EVENT_H
#define EVENT_H
#include "Definitions.h"
#include "TimeFunctions.h"
#pragma once
class Event
{
	
	
	unsigned int pin;
	bool simple;
	byte pinValue;
	int (*nonSimpleExecute)();
	time_t lastExecution;
	char* name;
public:
	char* getName();
	int execute();
	int check();
	EventType type;
	double interval; //in seconds..
	double time; //in day progress..
	double frequency; //per day.. (max)
	Event(void);
	Event(char* _name, EventType _type, double _occurDouble, unsigned int _pin, byte _pinValue);
	Event(char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)());
	~Event(void);
};

#endif