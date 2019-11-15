/*
 * CEvent.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include <iostream>
#include "CEvent.h"

CEvent::CEvent(int type, Customer* person) : Event(person->getArrival()){
	kind = type;
	cust = person;
}

CEvent::CEvent(int type, Customer* person, float start) : Event(start){
	kind = type;
	cust = person;
}

CEvent::~CEvent(){}

int CEvent::typeEvent(){
	return kind;
}

/**Gets the customer associated with the event
 * @return The customer
 */
Customer* CEvent::giveCust(){
	return cust;
}
