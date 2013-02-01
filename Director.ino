#include "Director.h"

//Function Declarations for Director
/// <summary>
///	Constructor of the Director class.
/// </summary>
/// <param name="pid">ID of the program to run.</param>
Director::Director(unsigned int pid = 0) {
	//contruct
	program_id = pid;
}
void Director::Init() {
  //contruct
	
}
void Director::Tick(){
	//runs every "loop()"
	//Update Time
	doTimeWork();
}
int Director::doSpecialRoutine(){
	//Pause all and execute task. Like calibrating the pH-probe.
}