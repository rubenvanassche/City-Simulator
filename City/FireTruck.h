/*
 * FireTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef FIRETRUCK_H_
#define FIRETRUCK_H_

#include "EmergencyCar.h"
#include "DesignByContract.h"
#include <iostream>
#include "Building.h"

class FireTruck: public EmergencyCar {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireTruck& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");

	FireTruck(const std::string& name, Depot* base);
	// constructor
	// ENSURE(this->isInitialized(), "FireTruck is initialized");

	FireTruck(const FireTruck& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");

	void operator= (const FireTruck& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");

	char getSymbol();
	/* Returns the symbol of this instance in the city to be used with the graphical impression */

private:
	FireTruck* fMyself;
};

#endif /* FIRETRUCK_H_ */
