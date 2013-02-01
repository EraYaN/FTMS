#include "Director.h"
#include "Program.h"
#include <Time.h>

//Function Declarations for Director
/// <summary>
///	Constructor of the Director class.
/// </summary>
/// <param name="pid">ID of the program to run.</param>
Director::Director(unsigned int pid) {
	//contruct
	program_id = pid;
}
/// <summary>
///	Constructor of the Director class. Run default program.
/// </summary>
Director::Director() {
	Director(0);
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
	return 0;
}