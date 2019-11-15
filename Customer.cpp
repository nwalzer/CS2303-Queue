#include <iostream>
#include "Customer.h"


Customer::Customer(float total){
	arrival = total * rand()/float(RAND_MAX);
}

Customer::~Customer(){};

/**Gets the arrival time of the customer
 * @return The arrival time
 */
float Customer::getArrival(){
	return arrival;
}

