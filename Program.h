#ifndef PROGRAM_H
#define PROGRAM_H

//Definitions of all the programs.
struct Program{
	unsigned int ProgramID;	
	unsigned int duration;
	Event events[];
};
#endif