#include "Event.h"

/*int blah(){
	Serial.print("blah: ");
	Serial.println(now());
}*/


Event* events[] = {
	new Event("AquaLightsOn",EventTime,10/24.0,RELAY_TL1,LOW),
	new Event("AquaLightsOff",EventTime,22/24.0,RELAY_TL1,HIGH),
	new Event("TerraLightsOn",EventTime,10/24.0,RELAY_TERRA_LIGHT,LOW),
	new Event("TerraLightsOff",EventTime,22/24.0,RELAY_TERRA_LIGHT,HIGH),
	new Event("CO2On",EventTime,10/24.0,RELAY_CO2,LOW),
	new Event("CO2Off",EventTime,22/24.0,RELAY_CO2,HIGH),
	//new Event("Test",EventInterval,10.0,blah)
};
int eventcount = 6;


void processEvents(){
	for(int i=0;i<eventcount;i++){
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
    for(i=0;i<eventcount;i++)
    {
        for(j=0;j<i;j++)
        {
			if(events[i]->time>events[j]->time)
			{
				Event *temp=events[i]; //swap 
				events[i]=events[j];
				events[j]=temp;
			}
        }

    }

}