#include "Customer.h"
#include "Queue.h" 
#include <ctime>
#include <iostream>
using namespace std;

/************************************
* Simulation.h grocery store.
************************************/
const int MAX = 5; // numbers of lines

class Simulation
{
public:
	Simulation(); // Default Constructor
	~Simulation(); // Default Destructor.

	void startSimulation();
	void service(int & busyTimeRemaining, int c);
	void customersCheckoutAndEnterShortest();
	void display(ostream & out);

private:
	// Inputs
	int lengthOfSimulation;
	double arrivalRate;
	int * servicePercent;

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

	// Numbers of cashiers, set at runtime
	int numCashiers;

	// Circular array of queues that store customers
	Queue<Customer> * allCashiers;
};

