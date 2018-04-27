#ifndef SIMULATION_H
#define SIMULATION_H


#include "Customer.h"
#include <vector>
#include <queue> // Provides the queue template class

#include <ctime>
#include <iostream>
using namespace std;

/************************************
* Simulation.h grocery store.
************************************/
const int MAX = 5; // a number of cashiers

class Simulation
{
public:
        typedef int value_type;
	typedef std::size_t size_type;
        
	Simulation(); // Default Constructor
	~Simulation(); // Default Destructor.

	void startSimulation();
	void service(value_type & busyTimeRemaining, value_type cashier);
	void customersCheckoutAndEnterShortest();
	void display(ostream &out);

private:
	// Inputs
	double  arrivalRate;
        int     numCashiers; // numbers of cashiers, set at runtime
        int     lengthOfSimulation;
	
	// Tracking variables
	int totalServiceTime;
	int totalCustomerWaitingTime;
	int totalCashierIdleTime;
	int totalNumberOfCustomers;
	int customersRemaining;

	// Outputs
	double avgCustomerServiceTime;
	double avgCustomerWaitingTime;
	double avgCashierIdleTime;

	// Countdown timer
	Timer myTimer;

        // Declare 5 lines of Customers using queue template.
        // Vector of queues of an Customer object.
        vector<queue<Customer>> allCashiers; // customer lines
      
        
        int servicePercent[5];
        
        
};



#endif /* SIMULATION_H */

