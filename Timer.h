#ifndef TIMER_H
#define TIMER_H

#include <iostream>
using namespace std;


/**
    Timer.h
    Purpose: Timer class keeps track of time in this Simulation.
    The "minute" time unit is used in this Simulation.

    @author Xuan Do
    @author Jason Pagotaisidro
    @version 1.1 05/01/18 
*/


class Timer
{
public:
	typedef int value_type;
	typedef std::size_t size_type;

	Timer( );
	void setTime( value_type t ); // Set minutes to the passed value
	void tick( );
	value_type timeRemaining( ) const;
private:
	value_type minutes;
};



#endif /* TIMER_H */

