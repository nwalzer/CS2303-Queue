/*
 * TEvent.h
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#ifndef TEVENT_H_
#define TEVENT_H_

#include "Event.h"

class TEvent: public Event{
public:
	TEvent(int teller, float start);
	~TEvent();

	virtual int typeEvent();
	int giveTeller();

private:
	int teller;

};



#endif /* TEVENT_H_ */
