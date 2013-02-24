#include "Event.h"

Event* events[] = {
	//TODO choose pins
	new Event("AquaLightsOn",EventTime,10/24.0,35,HIGH),
	new Event("AquaLightsOff",EventTime,22/24.0,35,LOW),
	new Event("TerraLightsOn",EventTime,10/24.0,36,HIGH),
	new Event("TerraLightsOff",EventTime,22/24.0,36,LOW),
	new Event("CO2On",EventTime,10/24.0,37,HIGH),
	new Event("CO2Off",EventTime,22/24.0,37,LOW)
};


void processEvents(){
	int count = 2; //TODO dynamic
	for(int i=0;i<count;i++){
		events[i]->check();		
	}
}
void initEvents(){
	sortEvents();
	processEvents();
}

void sortEvents()//Bubble sort function 
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<i;j++)
        {
			if(events[i]->type=EventTime){
				if(events[i]->time>events[j]->time)
				{
					Event *temp=events[i]; //swap 
					events[i]=events[j];
					events[j]=temp;
				}
			}

        }

    }

}