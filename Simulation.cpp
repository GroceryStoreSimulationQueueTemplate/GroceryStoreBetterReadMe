#include "Simulation.h"

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
	cout << "Please enter the average arrival rate of customers in number per second: " << endl;
	cin >> arrivalRate;

	cout << "Please enter the number of cashiers: " << endl;
	cin >> numCashiers;
        

	// Add new queues to vector 
	for ( int i = 0; i < numCashiers; i++ )
	{
                allCashiers.push_back( queue<Customer>( ) );
	}

        // Get inputs for simulation
	cout << "Please enter the length of time to run the simulation in seconds: " << endl;
	cin >> lengthOfSimulation;
        
        // Set the countdown timer
	myTimer.setSeconds( lengthOfSimulation );
        

        
     

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
			cout << " <= " << i + 1 << " second. ";   
                        cin >> percent;
			servicePercent[i] = percent;
			sum += percent;
			cout << "sum: " << sum << endl;
		}
	}

	// Initialize random number generator.
	// Use current time as seed for random generator.
        // TO-DO:
        // This is a weak random number generator; it is not useful for security purposes.
        //srand( time( 0 ) );
}

Simulation::~Simulation()
{
	for( int i = 0; i < numCashiers; i++ )
	{
		delete & allCashiers[i];
	}

	allCashiers.clear();
	delete[] servicePercent;
}

void Simulation::startSimulation()
// Deletes all dynamically created elements of allCashiers[].
// Deletes dynamically created member arrays.
{
        // TO-DO: I got an infinite loop here because the timeRemaining is always > 0.
        // Needed to find a way to use the tick() method.
	while ( myTimer.timeRemaining() > 0 )
	{
            // Go through each cashier and run the service function which will 
            // check if their customer is ready to check out and do so if able.

		for ( int i = 0; i < numCashiers; i++ )
		{
                        customersCheckoutAndEnterShortest();
			if ( !allCashiers[i].empty( ) )
			{
                            
                                
                                
                            
                                // Get the remaining service time of the customer in the front of the line.
				int remainingServiceTime = allCashiers[i].front().getServiceTime();
				service( remainingServiceTime, i );
			}
		}
                myTimer.tick();
	}
}

void Simulation::service( Simulation::value_type & busyTimeRemaining, Simulation::value_type cashier )
// Pass the remaining service time of the customer in the front of the line
// as well as the cashier of the customer is the line for.
{
	// The front customer still has more service time to process.
	if ( busyTimeRemaining > 0 )
	{
		busyTimeRemaining--;
		allCashiers[cashier].front().setServiceTime( busyTimeRemaining );

		// Add the waiting time of the customers in line to the total.
		totalCustomerWaitingTime += allCashiers[cashier].size() - 1;

		return;
	}
	else
	{
		if ( !allCashiers[cashier].empty() ) // Check to see if this cashier are available 
		{
			int arrivalTime = allCashiers[cashier].front().getArrivalTime();
			allCashiers[cashier].pop(); // Done. Let the customer go.
			if ( !allCashiers[cashier].empty() )
			{
				Customer nextCustomer = allCashiers[cashier].front();
				busyTimeRemaining = nextCustomer.getServiceTime();
			}
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

		while ( r > randomServiceTime )
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

		int seconds = 9999999;
                
                
		int shortestLine = 0;
                              
                
                // Find the shortest line.
		for ( int i = 0; i < numCashiers; i++ )
		{
                        // For the first time, allCashiers[i].size() should return 0.
			if ( allCashiers[i].size() < seconds )
			{
				seconds = allCashiers[i].size();
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

			totalServiceTime += serviceTime + 1;

			// Customers enter randomly to check out, and then enter the shortest line.
			Customer newCustomer( myTimer, serviceTime + 1 );
			totalNumberOfCustomers++;
			customersRemaining++;

			int seconds = 9999999;
			int shortestLine = 0;

			for ( int i = 0; i < numCashiers; i++ )
			{
				if ( allCashiers[i].size() < seconds )
				{
					seconds = allCashiers[i].size();
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
void Simulation::display( ostream & out )
{

	cout << "\nTotal number of customers: "     << totalNumberOfCustomers << endl;
	cout << "\nTotal service time: "            << totalServiceTime << endl;
	cout << "\nTotal customer waiting time: "   << totalCustomerWaitingTime << endl;
	cout << "\nTotal cashier processing time: " << totalCashierIdleTime << endl;


	avgCustomerServiceTime = ( double ) totalServiceTime / totalNumberOfCustomers;
	avgCustomerWaitingTime = ( double ) totalCustomerWaitingTime / totalNumberOfCustomers;
	avgCashierIdleTime     = ( double ) totalCashierIdleTime / numCashiers;


	cout << "\nThe average customer service time was: " << avgCustomerServiceTime << "minutes";
	cout << "\nThe average customer waiting time was: " << avgCustomerWaitingTime << " minutes";
	cout << "\nThe average cashier idle time was: "     << avgCashierIdleTime << " minutes";

}