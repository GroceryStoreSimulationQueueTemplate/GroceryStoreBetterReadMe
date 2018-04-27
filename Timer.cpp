#include "Timer.h"
#include <cassert>

// Default constructor
Timer::Timer()
{
	minutes = 0;
}

// Set minutes to the passed value
void Timer::setSeconds(Timer::value_type s)
{
	assert(s >= 0);
	minutes = s;
}

void Timer::tick()
{
	minutes--;
}

Timer::value_type Timer::timeRemaining() const
// Return the number of minutes remaining in the simulation
{
	return minutes;
}
