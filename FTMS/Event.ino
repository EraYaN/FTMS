#include "Event.h"
#include "Definitions.h"
#include "TimeFunctions.h"

Event::Event(){
	//nothing
}
Event::Event(const char* _name, EventType _type, double _occurDouble, unsigned int _pin, byte _pinValue)
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
Event::Event(const char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)())
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
		analogWrite(pin,pinValue);
		lastExecution = now();
	} else {
		nonSimpleExecute();
		lastExecution = now();
	}
}

int Event::check(){
	switch(type){
		case EventTime:			
			if(time>getDayProgress()){
				Serial.print("Executed timed event: ");
				Serial.println(name);
				execute();
			}
		break;
		case EventInterval:
			if(interval>(now()-lastExecution)){
				Serial.print("Executed interval event: ");
				Serial.println(name);
				execute();
			}			
		break;
		case EventRandom:
			double per = (1/frequency)*SECONDS_IN_DAY;
			long tmp = random(round(per*SECONDS_IN_DAY), round(per*SECONDS_IN_DAY*MAX_DIFF_RANDOM_EVENTS));
			if((now()-lastExecution)>tmp){
				Serial.print("Executed random event: ");
				Serial.println(name);
				execute();
			}			
		break;	
	}
}
