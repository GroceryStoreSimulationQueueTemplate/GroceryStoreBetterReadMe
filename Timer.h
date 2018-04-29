#ifndef TIMER_H
#define TIMER_H

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
	void setTime(value_type s); // Set minutes to the passed value
	void tick();
	value_type timeRemaining() const;
private:
	value_type minutes;
};



#endif /* TIMER_H */

