#include "Timer.h"
#include <cassert>

/**
    Timer.cpp
    Purpose: Timer class keeps track of time in this Simulation.
    The "minute" time unit is used in this Simulation.

    @author Xuan Do
    @author Jason Pagotaisidro
    @version 1.1 05/01/18 
*/

// Default constructor
Timer::Timer()
{
	minutes = 0;
}

// Set minutes to the passed value
void Timer::setTime(Timer::value_type s)
{
	assert(s >= 0);
	minutes = s;
}

// Decrease the Timer by 1 minute
void Timer::tick()
{
	minutes--;
}

Timer::value_type Timer::timeRemaining() const
// Return the number of minutes remaining in the simulation
{
	return minutes;
}
