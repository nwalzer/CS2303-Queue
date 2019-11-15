/*
 * Event.h
 *
 *  Created on: Oct 6, 2018
 *      Author: nwalzer
 */

#ifndef EVENT_H_
#define EVENT_H_

class Event{
public:
	Event(float start);
	virtual ~Event();

	virtual int typeEvent();
	float getStart();

private:
	float startTime;
};



#endif /* EVENT_H_ */
