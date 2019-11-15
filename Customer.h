#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer{
public:
	Customer(float time);
	~Customer();
	float getArrival();

private:
	float arrival;
};

#endif
