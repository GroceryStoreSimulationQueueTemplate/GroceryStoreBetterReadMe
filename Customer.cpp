#include "Customer.h"

Customer::Customer()
{
	arrivalTime = 0;
	serviceTime = 0;
}

Customer::Customer(const Timer & arrival_time, Customer::value_type service_time)
{
	arrivalTime = arrival_time.timeRemaining();
	serviceTime = service_time;
}

void Customer::setServiceTime(Customer::value_type service_time)
{
	serviceTime = service_time;
}

Customer::value_type Customer::getArrivalTime()
{
	return arrivalTime;
}

Customer::value_type & Customer::getServiceTime()
{
	return serviceTime;
}
