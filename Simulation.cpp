#include "Simulation.h"

Simulation::Simulation()
{
	// Tracking variables
	totalServiceTime = 0;
	totalCustomerWaitingTime = 0;
	totalCashierIdleTime = 0;
	totalNumberOfCustomers = 0;
	customersRemaining = 0;

	// Outputs
	avgCustomerServiceTime = 0;
	avgCustomerWaitingTime = 0;
	avgCashierIdleTime = 0;

	// Inputs
	servicePercent = new int[MAX];
	allCashiers = new Queue<Customer>[numCashiers];

	// Get inputs for simulation

	cout << "Please enter the average arrival rate of customers in number per minute: " << endl;
	cin >> arrivalRate;

	cout << "Please enter the number of cashiers: " << endl;
	cin >> numCashiers;

	// TO-DO: Codes broken here
	// Create the correct number of cashiers
	for (int i = 0; i < numCashiers; i++)
	{
		allCashiers[i] = *new Queue<Customer>;
	}

	cout << "Please enter the length of time to run the simulation in minutes: " << endl;
	cin >> lengthOfSimulation;

	int percent = 0;
	int sum = 0;
	for (int i = 0; i < MAX; i++)
	{
		servicePercent[i] = 20 + sum;
		sum += 20;
	}

	while (sum != 100)
	{
		cout << "Invalid distribution. Must add up to 100 % old sum was: " << sum << endl;
		sum = 0;

		for (int i = 0; i < MAX; i++)
		{
			cout << " <= " << i + 1 << " min. ";   cin >> percent;
			servicePercent[i] = percent;
			sum += percent;
			cout << "sum: " << sum << endl;
		}
	}

	// Set the countdown timer
	myTimer.setMinutes(lengthOfSimulation);

	// Intialize random number generator
	long seed = long(time(0));
	srand(seed);
}

Simulation::~Simulation()
{
	for (int i = 0; i < numCashiers - 1; i++)
	{
		delete &allCashiers[i];
	}

	delete[] allCashiers;
	delete[] servicePercent;
}

void Simulation::startSimulation()
// Deletes all dynamically created elements of allCashiers[].
// Deletes dynamically created member arrays.
{
	while (myTimer.timeRemaining() > 0)
	{
		// Go through each cashier and run the service function which will check
		// if their customer is ready to check out and do so if able

		for (int i = 0; i < numCashiers; i++)
		{
			if (!allCashiers[i].empty())
			{
				int busyTimeLeft = allCashiers[i].front().getServiceTime();
				service(busyTimeLeft, i);
			}
		}
	}
}

void Simulation::service(int & busyTimeRemaining, int c)
// Pass the remaining service time of the customer in the front of the line
// as well as the cashier of the customer is the line for.
{
	// The front customer still has more service time to process.
	if (busyTimeRemaining > 0)
	{
		busyTimeRemaining--;
		allCashiers[c].front().setServiceTime(busyTimeRemaining);

		// Add the waiting time of the customers in line to the total.
		totalCustomerWaitingTime += allCashiers[c].size() - 1;

		return;
	}
	else
	{
		if (!allCashiers[c].empty()) // Check to see if this cashier are available 
		{
			int arrivalTime = allCashiers[c].front().getArrivalTime();
			allCashiers[c].pop(); // Done. Let the customer go.
			if (!allCashiers[c].empty())
			{
				Customer nextCustomer = allCashiers[c].front();
				busyTimeRemaining = nextCustomer.getServiceTime();
			}
			customersRemaining--;
		}
	}
}



void Simulation::customersCheckoutAndEnterShortest()
// Customers enter randomly to check out, and then enter the shortest line.
{
	// Activates a new customer proceduce for each arrival per minute.

	// -------------------------------------------------------------------
	// CASE 1: arrivalRate > 1
	//
	// -------------------------------------------------------------------

	for (int i = 0; i < arrivalRate; i++)
	{
		// A new customer is ready to get in line.
		// Create random service time.

		int r = rand() % 100;
		int serviceTime = 0;
		int randomServiceTime = servicePercent[serviceTime];

		while (r > randomServiceTime)
		{
			randomServiceTime += servicePercent[serviceTime];
			serviceTime++;
		}

		totalServiceTime += serviceTime + 1;

		// Create a new customer and 
		// add the customer to the shortest line of a cashier.

		// Customers enter randomly to check out, 
		// and then enter the shortest line

		Customer newCustomer(myTimer, serviceTime + 1);
		totalNumberOfCustomers++;
		customersRemaining++;

		int minutes = 9999999;
		int shortestLine = 0;
		for (int i = 0; i < numCashiers; i++)
		{
			if (allCashiers[i].size() < minutes)
			{
				minutes = allCashiers[i].size();
				shortestLine = i;
			}
		}

		// A new customer is added to the shortest line.
		allCashiers[shortestLine].push(newCustomer);
	}


	// -------------------------------------------------------------------
	// CASE 2: arrivalRate < 1
	//
	// -------------------------------------------------------------------

	if (arrivalRate < 1)
	{
		// Generate a random number between 0 and 99
		int randomInteger = rand() % 100;

		// Calculates the probability that a customer has arrived
		if (randomInteger < (100 * arrivalRate))
		{
			// A new customer is ready to get in line.
			// Create random service time.

			int r = rand() % 100;
			int serviceTime = 0;
			int randomServiceTime = servicePercent[serviceTime];

			while (r > randomServiceTime)
			{
				randomServiceTime += servicePercent[serviceTime];
				serviceTime++;
			}

			totalServiceTime += serviceTime + 1;

			// Customers enter randomly to check out, and then enter the shortest line.
			Customer newCustomer(myTimer, serviceTime + 1);
			totalNumberOfCustomers++;
			customersRemaining++;

			int minutes = 9999999;
			int shortestLine = 0;

			for (int i = 0; i < numCashiers; i++)
			{
				if (allCashiers[i].size() < minutes)
				{
					minutes = allCashiers[i].size();
					shortestLine = i;
				}
			}

			// A new customer is added to the shortest line.
			allCashiers[shortestLine].push(newCustomer);
		}
	}
}

// Displays the average customer service and wait time 
// as well as the average cashier serving time.
void Simulation::display(ostream & out)
{

	cout << "\nTotal number of customers: " << totalNumberOfCustomers << endl;
	cout << "\nTotal service time: " << totalServiceTime << endl;
	cout << "\nTotal customer waiting time: " << totalCustomerWaitingTime << endl;
	cout << "\nTotal cashier processing time: " << totalCashierIdleTime << endl;


	avgCustomerServiceTime = (double)totalServiceTime / totalNumberOfCustomers;
	avgCustomerWaitingTime = (double)totalCustomerWaitingTime / totalNumberOfCustomers;
	avgCashierIdleTime = (double)totalCashierIdleTime / numCashiers;


	cout << "\nThe average customer service time was: " << avgCustomerServiceTime << "minutes";
	cout << "\nThe average customer waiting time was: " << avgCustomerWaitingTime << " minutes";
	cout << "\nThe average cashier idle time was: " << avgCashierIdleTime << " minutes";

}
