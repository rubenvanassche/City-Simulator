/*
 * PoliceDepot.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#ifndef POLICEDEPOT_H_
#define POLICEDEPOT_H_

#include "Depot.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>

class PoliceDepot: public Depot {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, PoliceDepot& p);
	// output operator overloading
	// REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	PoliceDepot(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health);
	// constructor
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");

	PoliceDepot(const PoliceDepot& p);
	// copy constructor
	// REQUIRE(p.isInitialized(), "PoliceDepot is initialized");
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");

	void operator= (const PoliceDepot& p);
	// copy by assignment
	// REQUIRE(p.isInitialized(), "PoliceDepot is initialized");
	// REQUIRE(this->isInitialized(), "PoliceDepot is initialized");
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");

	char getSymbol();
	/* Returns the symbol of this instance in the city to be used with the graphical impression */

private:
	PoliceDepot* fMyself;
};

#endif /* POLICEDEPOT_H_ */
