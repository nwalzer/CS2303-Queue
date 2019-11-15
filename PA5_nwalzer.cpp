#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include "Customer.h"
#include "Teller.h"
#include "Event.h"
#include "CEvent.h"
#include "TEvent.h"
#include "EventQueue.h"
#include "TellerQueue.h"

/**Gets the index of the lowest value in an array
 * @param arr The int array to look at
 * @param len The length of the array
 * @return The index of the lowest value
 */
int getMinIdx(int* arr, int len) {
	int min = arr[0];
	int minIdx = 0;
	for (int x = 0; x < len; x++) {
		if (arr[x] < min) {
			min = arr[x];
			minIdx = x;
		}
	}
	return minIdx;
}

/**Checks whether all elements in a given array are 0
 * @param arr The int array to check
 * @param len The length of the array
 * @return True if all 0, false otherwise
 */
bool allEmpty(int* arr, int len) {
	for (int x = 0; x < len; x++) {
		if (arr[x]) {
			return false;
		}
	}
	return true;
}

/**Runs the simulation where there is only a single line between all tellers
 * @param argc The length of the command line arguments
 * @param argv The command line arguments
 * @return EXIT_SUCCESS if simulation run successfully, EXIT_FAILURE otherwise
 */
int singleLine(int argc, char **argv) {
	const int CUSTARR = 0;
	const int CUSTLEAVE = 1;
	const int TELLSERV = 2;

	int numCustomers;
	int numTellers;
	float simTime;
	float avgServiceTime;

	int i;
	float timeForService = 0;
	float avgTimeInBank = 0;
	float maxWait = 0;
	float idleTime = 0;
	float globalClock = 0;
	float stdDev = 0;
	EventQueue toCome;
	Teller* tellers;
	int tellerLength = 0;
	float* bankTimes;

	if (argc < 5 || argc > 6) {
		printf("Incorrect argument line:\n");
		printf(
				"./qSim #customers #tellers simulationTime avgServiceTime <seed>\n");
		return EXIT_FAILURE;
	}

	numCustomers = atoi(argv[1]);
	numTellers = atoi(argv[2]);
	simTime = atof(argv[3]);
	avgServiceTime = atof(argv[4]);

	for (i = 0; i < numCustomers; i++) { //put a cust event with a random start time
										 //in the eventQueue for each customer
		Customer* guy = new Customer(simTime);
		CEvent* guyEv = new CEvent(CUSTARR, guy);
		toCome.addEvent(guyEv);
	}

	//printf("Length: %d\n\n", toCome.giveLength());
	//toCome.printTimes();

	tellers = (Teller*) malloc(numTellers * sizeof(Teller));
	if (!tellers) {
		printf("Failed to allocate tellers\n\n");
		return EXIT_FAILURE;
	}
	bankTimes = (float*) malloc(numCustomers * sizeof(float));
		if (!bankTimes) {
			printf("Failed to allocate bankTimes\n\n");
			return EXIT_FAILURE;
		}

	for (i = 0; i < numTellers; i++) {
		TEvent* tellE = new TEvent(i, 0.0);
		toCome.addEvent(tellE);
		Teller guy;
		tellers[i] = guy;
	}
	//printf("Length: %d\n\n", toCome.giveLength());
	//toCome.printTimes();

	globalClock = toCome.getFirstTime();
	int x = 0;
	while (toCome.custInBank() || tellerLength) {//while there is a CEvent in the eventQueue OR a customer waiting to be served
		globalClock = toCome.getFirstTime();	//move globalClock to next event
		Event* currEvent = toCome.popEvent();	//get first event
		int type = currEvent->typeEvent();
		if (type == CUSTARR) { //if the event is customer arrival
			Customer* currCust = static_cast<CEvent*>(currEvent)->giveCust();
			tellers[0].addCust(currCust);	//cust added to shortest line
			tellerLength++;	//shortest line length incremented
			delete currEvent;
			//printf("\nCustomer arrived, placed in: %d\n", 0);
		} else if (type == CUSTLEAVE) { //if the event is a customer leaving
			Customer* guy = static_cast<CEvent*>(currEvent)->giveCust();
			float custWaitTime = globalClock - guy->getArrival();
			avgTimeInBank += custWaitTime; //increase the avg time spent in bank
			delete currEvent;
			//printf("\nCustomer left\n");
		} else if (type == TELLSERV) {
			int tell = static_cast<TEvent*>(currEvent)->giveTeller();
			delete currEvent;

			if (tellerLength == 0) { //if no one is in the single teller line go on break
				float breakFor = tellers[tell].getIdleTime() / 60.0; //convert seconds to minutes
				idleTime += breakFor; //add the duration of the break to idleTime
				//printf("\nTeller %d went on break for %f\n", tell, breakFor);
				breakFor += globalClock; //sets break end into the future
				TEvent* tellEv = new TEvent(tell, breakFor);
				toCome.addEvent(tellEv); //add break to eventQueue
			} else { //If the line has someone in it
				Customer* guy = tellers[0].getFirst(); //get the first customer
				tellerLength--; //subtract one from length of line

				float serviceTime = globalClock - guy->getArrival(); //get cust wait time

				if (serviceTime > maxWait) { //if cust has waited the longest
					maxWait = serviceTime;
				}
				serviceTime = 2 * avgServiceTime * rand() / float(RAND_MAX); //gen service time
				timeForService += serviceTime; //increase total service time
				serviceTime += globalClock; //set that far ahead in the future
				CEvent* guyEv = new CEvent(CUSTLEAVE, guy, serviceTime); //customer leaving the bank
				TEvent* tellEv = new TEvent(tell, serviceTime); //teller servicing new customer, after other cust leaves
				toCome.addEvent(guyEv);
				toCome.addEvent(tellEv);
				//printf("\nTeller %d is serving a customer\n", tell);
			}
		}
	}
	//toCome.printTimes();

	while (toCome.giveLength() != 0) { //goes through the final
									   //breaks that each teller encounters
		Event* currEvent = toCome.popEvent();
		if (currEvent->getStart() < simTime) {
			//if the break ends before the end of the simlation, bump the idleTime
			//up by the difference between simTime and break end
			idleTime += (globalClock - currEvent->getStart());
		}
		delete currEvent;
	}

	avgTimeInBank = avgTimeInBank / numCustomers;
		for(x = 0; x < numCustomers; x++){
			float temp = bankTimes[x] - avgTimeInBank;
			stdDev += (temp * temp);
		}
		stdDev = stdDev / numCustomers;
		stdDev = sqrt(stdDev);
		printf("\n\nSingle Shared Queue:\n\n");
		printf("A total of %d customers were served in a total of %f minutes\n", numCustomers, timeForService);
		printf("There were %d tellers utilizing a shared queue\n", numTellers);
		printf("On average a customer spent %f minutes in the bank. The standard deviation is %f\n", avgTimeInBank, stdDev);
		printf("The maximum wait time for a customer was %f\n", maxWait);
		printf("The tellers served for a total of %f minutes and were idle for a total of %f minutes", timeForService, idleTime);

	return EXIT_SUCCESS;
}

/**Runs the simulation using one line for each teller
 * @param argc The length of the command line arguments
 * @param argv The command line arguments
 * @return EXIT_SUCCESS if program runs successully, EXIT_FAILURE otherwise
 */
int multiLine(int argc, char **argv) {
	const int CUSTARR = 0;
	const int CUSTLEAVE = 1;
	const int TELLSERV = 2;

	int numCustomers;
	int numTellers;
	float simTime;
	float avgServiceTime;
	int seed = 0;

	int i;
	float timeForService = 0;
	float avgTimeInBank = 0;
	float maxWait = 0;
	float idleTime = 0;
	float globalClock = 0;
	float stdDev = 0;
	EventQueue toCome;
	Teller* tellers;
	int* tellerLength;
	float* bankTimes;

	if (argc < 5 || argc > 6) {
		printf("Incorrect argument line:\n");
		printf(
				"./qSim #customers #tellers simulationTime avgServiceTime <seed>\n");
		return EXIT_FAILURE;
	}

	numCustomers = atoi(argv[1]);
	numTellers = atoi(argv[2]);
	simTime = atof(argv[3]);
	avgServiceTime = atof(argv[4]);

	if (argc == 6) {
		seed = atoi(argv[5]);
	}

	if (seed == 0) {
		srand(time(0));
	} else {
		srand(seed);
	}

	for (i = 0; i < numCustomers; i++) {
		Customer* guy = new Customer(simTime);
		CEvent* guyEv = new CEvent(CUSTARR, guy);
		toCome.addEvent(guyEv);
	}

	//printf("Length: %d\n\n", toCome.giveLength());
	//toCome.printTimes();

	tellers = (Teller*) malloc(numTellers * sizeof(Teller));
	if (!tellers) {
		printf("Failed to allocate tellers\n\n");
		return EXIT_FAILURE;
	}
	tellerLength = (int*) malloc(numTellers * sizeof(int));
	if (!tellerLength) {
		printf("Failed to allocate tellerLength\n\n");
		return EXIT_FAILURE;
	}
	bankTimes = (float*) malloc(numCustomers * sizeof(float));
	if (!bankTimes) {
		printf("Failed to allocate bankTimes\n\n");
		return EXIT_FAILURE;
	}
	for (i = 0; i < numTellers; i++) {
		TEvent* tellE = new TEvent(i, 0.0);
		toCome.addEvent(tellE);
		Teller guy;
		tellers[i] = guy;
		tellerLength[i] = 0;
	}
	//printf("Length: %d\n\n", toCome.giveLength());
	//toCome.printTimes();

	globalClock = toCome.getFirstTime();
	int x = 0;
	while (toCome.custInBank() || !allEmpty(tellerLength, numTellers)) {//while there is a CEvent in the eventQueue OR a customer waiting to be served
		globalClock = toCome.getFirstTime();	//move globalClock to next event
		Event* currEvent = toCome.popEvent();	//get first event
		int type = currEvent->typeEvent();
		if (type == CUSTARR) {
			int shortest = getMinIdx(tellerLength, numTellers);	//get the idx of the shortest line
			Customer* currCust = static_cast<CEvent*>(currEvent)->giveCust();
			tellers[shortest].addCust(currCust);//cust added to shortest line
			tellerLength[shortest]++;	//shortest line length incremented
			delete currEvent;
			//printf("\nCustomer arrived, placed in: %d\n", shortest);
		} else if (type == CUSTLEAVE) {
			Customer* guy = static_cast<CEvent*>(currEvent)->giveCust();
			float custWaitTime = globalClock - guy->getArrival();
			bankTimes[x] = custWaitTime;
			x++;
			avgTimeInBank += custWaitTime;
			delete currEvent;
			//printf("\nCustomer left\n");
		} else if (type == TELLSERV) {
			int tell = static_cast<TEvent*>(currEvent)->giveTeller();
			bool allEmp = true;

			if (tellerLength[tell] == 0) { //if no one is in the teller's line

				for (i = 0; i < numTellers; i++) { //go through all other tellers

					if (tellerLength[i] != 0) { //if one of them has a customer waiting

						allEmp = false; //not all of them are empty
						Customer* guy = tellers[i].getFirst(); //get the first customer of that teller's line
						tellerLength[i]--; //take one of his line length

						float serviceTime = globalClock - guy->getArrival(); //time to get served

						if (serviceTime > maxWait) { //if the current customer has waited longer than anyone else
							maxWait = serviceTime;
						}
						serviceTime = 2 * avgServiceTime * rand()
								/ float(RAND_MAX); //teller will service for this amount of time
						timeForService += serviceTime; //total service time adds on this service
						serviceTime = globalClock + serviceTime; //adjusts the time for service to be that far ahead in the future
						CEvent* guyEv = new CEvent(CUSTLEAVE, guy, serviceTime); //Customer leaving
						TEvent* tellEv = new TEvent(tell, serviceTime); //teller servicing new customer, after other cust leaves
						toCome.addEvent(guyEv);
						toCome.addEvent(tellEv);
						//printf("\nTeller %d is serving a customer\n", tell);
						break;
					}
				}

			} else { //If the current teller has someone in line
				allEmp = false; //not everything is empty
				Customer* guy = tellers[tell].getFirst(); //get the first customer
				tellerLength[tell]--; //subtract one from length of line

				float serviceTime = globalClock - guy->getArrival(); //get cust wait time

				if (serviceTime > maxWait) { //if cust has waited the longest
					maxWait = serviceTime;
				}
				serviceTime = 2 * avgServiceTime * rand() / float(RAND_MAX); //gen service time
				timeForService += serviceTime; //increase total service time
				serviceTime += globalClock; //set that far ahead in the future
				CEvent* guyEv = new CEvent(CUSTLEAVE, guy, serviceTime);
				TEvent* tellEv = new TEvent(tell, serviceTime); //teller servicing new customer, after other cust leaves
				toCome.addEvent(guyEv);
				toCome.addEvent(tellEv);
				//printf("\nTeller %d is serving a customer\n", tell);
			}

			if (allEmp) { //if no customers are in the bank, go on a break
				float breakFor = tellers[tell].getIdleTime() / 60.0;
				idleTime += breakFor; //add the duration of the break to idleTime
				//printf("\nTeller %d went on break for %f\n", tell, breakFor);
				breakFor += globalClock;		//sets break end into the future
				TEvent* tellEv = new TEvent(tell, breakFor);
				toCome.addEvent(tellEv);			//add break to eventQueue
			}
		}
	}
	//toCome.printTimes();

	while (toCome.giveLength() != 0) { //goes through the final
										   //breaks that each teller encounters
			Event* currEvent = toCome.popEvent();
			if (currEvent->getStart() < simTime) {
				//if the break ends before the end of the simlation, bump the idleTime
				//up by the difference between simTime and break end
				idleTime += (globalClock - currEvent->getStart());
			}
			delete currEvent;
		}

	avgTimeInBank = avgTimeInBank / numCustomers;
	for(x = 0; x < numCustomers; x++){
		float temp = bankTimes[x] - avgTimeInBank;
		stdDev += (temp * temp);
	}
	stdDev = stdDev / numCustomers;
	stdDev = sqrt(stdDev);
	printf("One Queue per Teller:\n\n");
	printf("A total of %d customers were served in a total of %f minutes\n", numCustomers, timeForService);
	printf("There were %d tellers utilizing one queue per teller\n", numTellers);
	printf("On average a customer spent %f minutes in the bank. The standard deviation is %f\n", avgTimeInBank, stdDev);
	printf("The maximum wait time for a customer was %f\n", maxWait);
	printf("The tellers served for a total of %f minutes and were idle for a total of %f minutes", timeForService, idleTime);


	return EXIT_SUCCESS;
}
int main(int argc, char **argv) {
	int status = multiLine(argc, argv);
	if (status == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	status = singleLine(argc, argv);
	if (status == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
}
