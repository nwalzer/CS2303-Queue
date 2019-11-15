#ifndef TELLER_H
#define TELLER_H

#include "TellerQueue.h"

class Teller{
public:
	Teller();
	~Teller();
	int getIdleTime();
	int lengthOfLine();
	void addCust(Customer* cust);
	Customer* getFirst();

private:
	TellerQueue* line;
};

#endif
