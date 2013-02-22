#include "Event.h"
#include "Definitions.h"

Event::Event(){
	//nothing
}
Event::Event(char* _name, EventType _type, double _occurDouble, unsigned int _pin, byte _pinValue)
{
	name = _name;
	type = _type;
	switch(type){
		case EventTime:
			time = _occurDouble;
		break;
		case EventInterval:
			interval = _occurDouble;
		break;
		case EventRandom:
			frequency = _occurDouble;
		break;	
	}
	pin = _pin;
	pinValue = _pinValue;
	simple = true;
}
Event::Event(char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)())
{
	name = _name;
	type = _type;
	switch(type){
		case EventTime:
			time = _occurDouble;
		break;
		case EventInterval:
			interval = _occurDouble;
		break;
		case EventRandom:
			frequency = _occurDouble;
		break;	
	}
	nonSimpleExecute = _nonSimpleExecute;
}
Event::~Event(void)
{
}

int Event::execute(){
	if(simple){
		
	}
}
