#include "Timer.h"
#include <cassert>

// Default constructor
Timer::Timer()
{
	seconds = 0;
}

// Set minutes to the passed value
void Timer::setSeconds(Timer::value_type s)
{
	assert(s >= 0);
	seconds = s;
}

void Timer::tick()
{
	seconds--;
}

Timer::value_type Timer::timeRemaining() const
// Return the number of minutes remaining in the simulation
{
	return seconds;
}
