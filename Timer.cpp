#include "Timer.h"
#include <cassert>

// Default constructor
Timer::Timer()
{
	minutes = 0;
}

// Set minutes to the passed value
void Timer::setMinutes(Timer::value_type m)
{
	assert(m >= 0);
	minutes = m;
}

void Timer::tick()
{
	minutes--;
}

Timer::value_type Timer::timeRemaining() const
// Return the number of minutes remaning in the simulation
{
	return minutes;
}
