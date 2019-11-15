/*
 * Event.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include <iostream>
#include "Event.h"

Event::Event(float start){
	startTime = start;
}

Event::~Event(){}

/**Gets the type of event
 * @return An integer representing the type of event
 */
int Event::typeEvent(){
	return 0;
}

/**Gets the start time of the event
 * @return The starting time
 */
float Event::getStart(){
	return startTime;
}

