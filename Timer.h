#include <iostream>
using namespace std;

/******************************************************************
 * Timer class keeps track of time in this Simulation.
 * The "minute" time unit is used in this Simulation.
 *****************************************************************/
class Timer
{
public:
	typedef int value_type;
	typedef std::size_t size_type;

	Timer();
	void setMinutes(value_type m); // Set minutes to the passed value
	void tick();
	value_type timeRemaining() const;
private:
	value_type minutes;
};
