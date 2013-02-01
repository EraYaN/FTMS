#ifndef DIRECTOR_H
#define DIRECTOR_H
/// <summary>
///	Class that will direct all actions of the arduino and store its status.
/// </summary>
class Director{
	//Class discription
public:
    Director(unsigned int pid = 0);
	void Init();
	void Tick();
	int doSpecialRoutine();
private:
	unsigned int progam_id;

};
#endif