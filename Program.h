
#ifndef PROGRAM_H
#define PROGRAM_H
#include "Event.h";
//Definitions of all the programs.
struct Program{
	unsigned int ProgramID;	
	Event events[];
};
#endif