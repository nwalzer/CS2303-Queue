/*
 * Teller.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include <iostream>
#include "Teller.h"

Teller::Teller(){
	line = new TellerQueue;
}

Teller::~Teller(){}

/**Generates a random break time
 * @return A random integer 1-600
 */
int Teller::getIdleTime(){
	return rand()%600 + 1;
}

/**Gets the length of the teller's queue
 * @return The length of the queue
 */
int Teller::lengthOfLine(){
	return line->giveLength();
}

/**Adds a customer to the end of the teller's line
 * @param cust The customer to add
 * @return void
 */
void Teller::addCust(Customer* cust){
	line->pushCust(cust);
}

/**Gets the first customer in the line
 * @return The first customer in the line
 */
Customer* Teller::getFirst(){
	return line->popCust();
}
