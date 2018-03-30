#include "Timer.h"
#include <iostream>
using namespace std;

/****************************************************************************************
 * Customer class creates a Customer that has a specified time he or she can come to
 * check out and a specified time that a cashier can service this customer.
 ***************************************************************************************/
class Customer
{
public:
	typedef int value_type;
	typedef std::size_t size_type;

	Customer();
	Customer(const Timer & arrivalTime, value_type serviceTime);
	void setServiceTime(value_type serviceTime);
	value_type getArrivalTime();
	value_type & getServiceTime();
private:
	value_type arrivalTime; // Time the customer arrived
	value_type serviceTime; // Time the customer is serviced
};
