#ifndef DIRECTOR_H
#define DIRECTOR_H
/// <summary>
///	Class that will direct all actions of the arduino and store its status.
/// </summary>
class Director{
	//Class discription
public:
	Director();
    Director(unsigned int pid);
	void Init();
	void Tick();
	int doSpecialRoutine();
private:
	unsigned int program_id;

};
#endif