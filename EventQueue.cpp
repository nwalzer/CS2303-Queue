/*
 * EventQueue.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include <iostream>
#include "EventQueue.h"
#include "Event.h"

const int CUSTARR = 0;
const int CUSTLEAVE = 1;
const int TELLSERV = 2;

EventQueue::EventQueue() {
	head = NULL;
	length = 0;
}

EventQueue::~EventQueue() {
	Node *nxt = head;

	while (nxt) { //delete all of the nodes in the queue
		Node* toDel = nxt;
		nxt = nxt->next;
		delete toDel;
	}
}

/**Adds an event to the event queue, sorted by arrival time
 * @param toAdd The event to add to the queue
 * @return void
 */
void EventQueue::addEvent(Event* toAdd) {
	length++; //add one to the length

	Node* newEvent = new Node();
	newEvent->event = toAdd;
	newEvent->start = toAdd->getStart();

	if (head == NULL) { //if the head is null, this event is new head
		head = newEvent;
		return;
	} else if (head->event->getStart() > newEvent->start){
		//if the head's start is greater than the new event's start, new event is head
		newEvent->next = head;
		head = newEvent;
		return;
	}

	Node *curr = head;

	while (curr->next != NULL
			&& curr->next->event->getStart() <= newEvent->start) {
		//while the next event isn't null and isn't later than the new event
		curr = curr->next;
	}
	newEvent->next = curr->next;
	curr->next = newEvent;
}

/**Removes and returns the head of the queue
 * @return The first event in the queue
 */
Event* EventQueue::popEvent() {
	length--; //subtract from the length
	Node* toPop = head;
	head = head->next;
	return toPop->event;
}

/**Gets the start time of the first event
 * @return The start time of the first event
 */
float EventQueue::getFirstTime() {
	return head->start;
}

/**Gets the length of the queue
 * @return The length of the queue
 */
int EventQueue::giveLength() {
	return length;
}

/**Prints all of the times in the queue (mainly used for debugging)
 * @return void
 */
void EventQueue::printTimes() {
	Node *nxt = head;

	while (nxt) {
		printf("%f\n", nxt->start);
		nxt = nxt->next;
	}
}

/**Determines if a CEvent is in the queue
 * @return True if at least one CEvent is in the queue, false otherwise
 */
bool EventQueue::custInBank(){
	Node* n = head;

	while(n){
		int kind = n->event->typeEvent();
		if(kind == CUSTARR || kind == CUSTLEAVE){
			return true;
		}
		n = n->next;
	}

	return false;
}
