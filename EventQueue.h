/*
 * EventQueue.h
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include "Event.h"

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

class EventQueue{
	struct Node{
		Event* event;
		float start;
		Node* next;
	};

public:
	EventQueue();
	~EventQueue();

	void addEvent(Event* toAdd);
	Event* popEvent();
	float getFirstTime();
	int giveLength();
	void printTimes();
	bool custInBank();

private:
	Node* head;
	int length;
};



#endif /* EVENTQUEUE_H_ */
