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
	switch(_type){
		case EventTime:
			time = _occurDouble;
			interval = 0;
			frequency = 0;
		break;
		case EventInterval:
			interval = _occurDouble;
			time = -1;
			frequency = 0;
		break;
		case EventRandom:
			frequency = _occurDouble;
			time = -2;
			interval = 0;
		break;	
	}
	pin = _pin;
	pinValue = _pinValue;
	simple = true;
	lastExecution = 0;
}
Event::Event(const char* _name, EventType _type, double _occurDouble, int (*_nonSimpleExecute)())
{
	name = _name;
	type = _type;
	switch(_type){
		case EventTime:
			time = _occurDouble;
			interval = 0;
			frequency = 0;
		break;
		case EventInterval:
			interval = _occurDouble;
			time = -1;
			frequency = 0;
		break;
		case EventRandom:
			frequency = _occurDouble;
			time = -2;
			interval = 0;
		break;	
	}
	nonSimpleExecute = _nonSimpleExecute;
	simple = false;
	lastExecution = 0;
}
Event::~Event(void)
{
}

void Event::execute(){
	if(simple){
		if(digitalPinHasPWM(pin)){
			analogWrite(pin,pinValue);
		} else {
			digitalWrite(pin,pinValue);
		}		
		lastExecution = now();
	} else {
		nonSimpleExecute();
		lastExecution = now();
	}
}

void Event::check(){
	switch(type){
		case EventTime:			
			if(time<=getDayProgress()){
				//Serial.print("Executed timed event: ");
				//Serial.println(name);
				execute();
			}
		break;
		case EventInterval:
			if(interval<=(now()-lastExecution)){
				//Serial.print("Executed interval event: ");
				//Serial.println(name);
				execute();
			}			
		break;
		case EventRandom:
			double per = (1/frequency)*SECONDS_IN_DAY;
			unsigned long tmp = random(round(per*SECONDS_IN_DAY), round(per*SECONDS_IN_DAY*MAX_DIFF_RANDOM_EVENTS));
			if((now()-lastExecution)>=tmp){
				//Serial.print("Executed random event: ");
				//Serial.println(name);
				execute();
			}			
		break;	
	}
}
