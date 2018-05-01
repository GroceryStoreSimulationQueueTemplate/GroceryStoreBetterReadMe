#include "Customer.h"

/**
    Customer.cpp
    Purpose: Customer class creates a Customer that has a specified time he or 
    she can come to check out and a specified time that a cashier can service 
    this customer.

    @author Xuan Do
    @author Jason Pagotaisidro
    @version 1.1 05/01/18 
*/

// Default constructor
Customer::Customer( )
{
	arrivalTime = 0;
	serviceTime = 0;
}

// Parameterized constructor
Customer::Customer( const Timer & arrival_Time, Customer::value_type service_Time )
{
	arrivalTime = arrival_Time.timeRemaining( );
	serviceTime = service_Time;
}

// Set the service time for a customer
void Customer::setServiceTime( Customer::value_type service_Time )
{
	serviceTime = service_Time;
}

// Get the arrival time of a customer
Customer::value_type Customer::getArrivalTime( )
{
	return arrivalTime;
}

// Get the service time of a customer
Customer::value_type & Customer::getServiceTime( )
{
	return serviceTime;
}
