#include "Simulation.h"

/**
    Simulation.cpp
    Purpose: 
    Use a vector of queues to simulate the lines. 
    Assume that there are five cashier lines at the grocery store. 
    Customers enter randomly to check out, and then enter the shortest line.

    @author Xuan Do
    @author Jason Pagotaisidro
    @version 1.1 05/01/18 
*/

Simulation::Simulation()
{
	// Tracking variables
	totalServiceTime            = 0;
	totalCustomerWaitingTime    = 0;
	totalCashierIdleTime        = 0;
	totalNumberOfCustomers      = 0;
	customersRemaining          = 0;

	// Outputs
	avgCustomerServiceTime      = 0;
	avgCustomerWaitingTime      = 0;
	avgCashierIdleTime          = 0;
	
	// Get inputs for simulation
	cout << "Please enter the average arrival rate of customers in number per minute: " << endl;
	cin >> arrivalRate;

	cout << "Please enter the number of cashiers: " << endl;
	cin >> numCashiers;
        

	// Add new queues to vector 
	for ( int i = 0; i < numCashiers; i++ )
	{
                allCustomers.push_back( queue<Customer>( ) );
	}

        // Get inputs for simulation
	cout << "Please enter the length of time to run the simulation in minutes: " << endl;
	cin >> lengthOfSimulation;
        
        // Set the countdown timer
	myTimer.setTime( lengthOfSimulation );
       
     
        // Used for customers entered random to check out.
        // Set the service percent to the correct percent which is 20 for each
        // cashier.
	int percent = 0;
	int sum     = 0;
	for ( int i = 0; i < MAX; i++ )
	{
		servicePercent[i] = 20 + sum;
		sum += 20;
	}

        // Double check to make sure the service percent is added up correctly.
	while ( sum != 100 )
	{
		cout << "Invalid distribution. Must add up to 100!" << endl; 
		sum = 0;
		for ( int i = 0; i < MAX; i++ )
		{
			cout << " <= " << i + 1 << " minute. ";   
                        cin >> percent;
			servicePercent[i] = percent;
			sum += percent;
			cout << "sum: " << sum << endl;
		}
	}

}

Simulation::~Simulation()
// Deletes all dynamically created elements of allCashiers[].
// Deletes dynamically created member arrays.
{
	for( int i = 0; i < numCashiers; i++ )
	{
		delete & allCustomers[i];
	}
	allCustomers.clear();
}

void Simulation::startSimulation()
{
    // Not end of the simulation. Continue to serve customers.
	while ( myTimer.timeRemaining() > 0 )
	{
            // Go through each cashier and run the service function which will 
            // check if their customer is ready to check out and do so if able.

		for ( int i = 0; i < numCashiers; i++ )
		{
                        // If there are still more customers.
			if ( !allCustomers[i].empty( ) )
			{
                                // Get the remaining service time of the customer in the front of the line.
				int remainingServiceTime = allCustomers[i].front( ).getServiceTime( );
				service( remainingServiceTime, i );
			} else {
                            totalCashierIdleTime++;
                        }
		}
                customersCheckoutAndEnterShortest( );
                myTimer.tick( );
	}
        display(cout);
}

void Simulation::service( Simulation::value_type & busyTimeRemaining, Simulation::value_type customer )
// Pass the remaining service time of the customer in the front of the line
// as well as the customer is in the line.
{
	// Check if the front customer still needs to wait.
        // This loop is used to calculate the total customer waiting time.
	if ( busyTimeRemaining > 0 )
	{
		busyTimeRemaining--;
		allCustomers[customer].front( ).setServiceTime( busyTimeRemaining );

		// Add the waiting time of the customers in line to the total.
		totalCustomerWaitingTime += allCustomers[customer].size( ) - 1;

		return;
	}
	else
	{
		if ( !allCustomers[customer].empty( ) ) // Check to see if a customer is available 
		{
			allCustomers[customer].pop( ); // Let the customer already be served to go first.
                        
                        // Check to see if we have a next customer 
			if ( !allCustomers[customer].empty( ) )
			{
				Customer nextCustomer = allCustomers[customer].front( );
				busyTimeRemaining = nextCustomer.getServiceTime( );
			}
                        
                        // Decrease customers by 1
			customersRemaining--;
		}
	}
}



void Simulation::customersCheckoutAndEnterShortest()
// Customers enter randomly to check out, and then enter the shortest line.
{
	// Activates a new customer procedure for each arrival per minute.

	// -------------------------------------------------------------------
	// CASE 1: arrivalRate > 1
	//
	// -------------------------------------------------------------------

	for ( int i = 0; i < arrivalRate; i++ )
	{
		// A new customer is ready to get in line.
		// Create random service time.

		int r = rand() % 100; // r in the range 0 to 99
		int serviceTime = 0;
		int randomServiceTime = servicePercent[serviceTime];

                // Generate random service time so when r is greater than the random service time.
                // Customers get served.
		while ( r > randomServiceTime )
		{
			randomServiceTime += servicePercent[serviceTime];
			serviceTime++;
		}

		totalServiceTime += serviceTime + 1;

		// Create a new customer and 
		// add the customer to the shortest line of a cashier.

		// Customers enter randomly to check out, 
		// and then enter the shortest line.

		Customer newCustomer( myTimer, serviceTime + 1 );
		totalNumberOfCustomers++;
		customersRemaining++;

                // Assign a really big number so that it runs through for the first time.
		int seconds = 9999999;
		int shortestLine = 0;
                              
                
                // Find the shortest line.
		for ( int i = 0; i < numCashiers; i++ )
		{
                        // For the first time, allCustomers[i].size() should return 0, 
                        // because there is no customers assigned to the line yet.
			if ( allCustomers[i].size() < seconds )
			{
				seconds = allCustomers[i].size( );
				shortestLine = i;
			}
		}
                
                // A new customer is added to the shortest line.
		allCustomers[shortestLine].push( newCustomer );
	}

	// -------------------------------------------------------------------
	// CASE 2: arrivalRate < 1
	//
	// -------------------------------------------------------------------

	if ( arrivalRate < 1 )
	{
		// Generate a random number between 0 and 99
		int randomInteger = rand() % 100;

		// Calculates the probability that a customer has arrived
		if ( randomInteger < ( 100 * arrivalRate ) )
		{
			// A new customer is ready to get in line.
			// Create random service time.

			int r = rand() % 100;
			int serviceTime = 0;
			int randomServiceTime = servicePercent[serviceTime];

			while ( r > randomServiceTime )
			{
				randomServiceTime += servicePercent[serviceTime];
				serviceTime++;
			}

                        // One more customer is served, increase the total
                        // service time by 1.
			totalServiceTime += serviceTime + 1;

			// Customers enter randomly to check out, and then enter the shortest line.
			Customer newCustomer( myTimer, serviceTime + 1 );
			totalNumberOfCustomers++;
			customersRemaining++;

                        // Assign a really big number so that it runs through for the first time.
			int seconds = 9999999;
			int shortestLine = 0;

                        // Search for the shortest line 
			for ( int i = 0; i < numCashiers; i++ )
			{
                                // For the first time, allCustomers[i].size() should return 0, 
                                // because there is no customers assigned to the line yet.
				if ( allCustomers[i].size() < seconds )
				{
					seconds = allCustomers[i].size( );
					shortestLine = i;
				}
			}

			// A new customer is added to the shortest line.
			allCustomers[shortestLine].push( newCustomer );
		}
	}
}

// Displays the average customer service and the waiting time 
// as well as the average cashier serving time.
void Simulation::display( ostream &out )
{

        cout << "\nTotal length of simulation:                                    "     << lengthOfSimulation          << " minutes.";
        cout << "\nAverage arrival rate of customers in number per minute:        "     << arrivalRate                 << " customer per minute.";
	cout << "\nTotal number of customers are served:                          "     << totalNumberOfCustomers      << " customers.";
        cout << "\nTotal number of cashiers:                                      "     << numCashiers                 << " cashiers."<< endl;

	cout << "\nTotal service time:          "        << totalServiceTime            << " minutes.";
	cout << "\nTotal customer waiting time: "        << totalCustomerWaitingTime    << " minutes.";
	cout << "\nTotal cashier idle time:     "        << totalCashierIdleTime        << " minutes." << endl;


	avgCustomerServiceTime = ( double ) totalServiceTime / totalNumberOfCustomers;
	avgCustomerWaitingTime = ( double ) totalCustomerWaitingTime / totalNumberOfCustomers;        
	avgCashierIdleTime     = ( double ) totalCashierIdleTime / numCashiers;
        
        
	cout << "\nThe average customer service time = totalServiceTime / totalNumberOfCustomers         = " << avgCustomerServiceTime   << " minutes";
	cout << "\nThe average customer waiting time = totalCustomerWaitingTime / totalNumberOfCustomers = " << avgCustomerWaitingTime   << " minutes";
        cout << "\nThe average cashier idle time     = totalCashierIdleTime / numCashiers                = " << avgCashierIdleTime       << " minutes" << endl;
	
}
