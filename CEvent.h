/*
 * CEvent.h
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#ifndef CEVENT_H_
#define CEVENT_H_

#include "Event.h"
#include "Customer.h"

class CEvent: public Event{
public:
	CEvent(int type, Customer* person);
	CEvent(int type, Customer* person, float start);
	~CEvent();

	virtual int typeEvent();
	Customer* giveCust();

private:
	int kind;
	Customer* cust;
};



#endif /* CEVENT_H_ */
