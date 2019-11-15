/*
 * TEvent.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */
#include <iostream>
#include "TEvent.h"

TEvent::TEvent(int person, float start) : Event(start){
	teller = person;
}

TEvent::~TEvent(){}

int TEvent::typeEvent(){
	return 2;
}

/**Gets the number of the associated teller
 * @return The number of the teller
 */
int TEvent::giveTeller(){
	return teller;
}

