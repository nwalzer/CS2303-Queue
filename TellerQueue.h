/*
 * TellerQueue.h
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */
#ifndef TELLERQUEUE_H
#define TELLERQUEUE_H

#include "Customer.h"

class TellerQueue{
	struct Node{
		Customer* cust;
		Node* next;
	};

public:
	TellerQueue();
	~TellerQueue();

	void pushCust(Customer* cust);
	Customer* popCust();
	int giveLength();

private:
	Node* head;
	int length;
};



#endif /* TELLERQUEUE_H_ */
