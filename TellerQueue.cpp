/*
 * TelleQueue.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#include <iostream>
#include "TellerQueue.h"

TellerQueue::TellerQueue() {
	head = NULL;
	length = 0;
}

TellerQueue::~TellerQueue() {
	Node *nxt = head;

	while (nxt) {
		Node* toDel = nxt;
		nxt = nxt->next;
		delete toDel;
	}
}

/**Adds a customer to the end of the line
 * @param cust The customer to add
 * @return void
 */
void TellerQueue::pushCust(Customer* cust) {
	length++;

	Node* newCust = new Node();
	newCust->cust = cust;

	if(head == NULL){
		head = newCust;
		return;
	} //if head is null, newCust is head

	Node *nxt = head;

	while (nxt->next) {//while the next isn't NULL
		nxt = nxt->next;
	}
	nxt->next = newCust;
}

/**Removes and Returns the first customer in the line
 * @return The first customer in the line
 */
Customer* TellerQueue::popCust(){
	length--;
	Node* toPop = head;
	head = head->next;
	return toPop->cust;
}
 /**Gets the length of the queue
  * @return The length of the queue
  */
int TellerQueue::giveLength(){
	return length;
}

