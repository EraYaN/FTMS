/*Define shit here*/

enum EventType {
  Interval,
  Time,
  Random
}; 
struct ScheduledEvent{
	EventType type;
	unsigned long interval;
	unsigned int hour;
	unsigned int minute;
	unsigned long frequency;
	char* name;
};
/// <summary>
///	Class that will direct all actions of the arduino and store it status.
/// </summary>
class Director{
	public:
    Director();
	int test;

};
