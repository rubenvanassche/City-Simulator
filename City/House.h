/*
 * House.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef HOUSE_H_
#define HOUSE_H_

#include "Building.h"
#include "DesignByContract.h"
#include <iostream>

class House: public Building {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, House& h);
	// output operator overloading
	// REQUIRE(h.isInitialized(), "House is initialized");

	House(const Point& location, const double& health);
	// constructor
	// ENSURE(this->isInitialized(), "House is initialized");

	House(const House& h);
	// copy constructor
	// REQUIRE(h.isInitialized(), "House is initialized");
	// ENSURE(this->isInitialized(), "House is initialized");

	void operator= (const House& h);
	// copy by assignment
	// REQUIRE(h.isInitialized(), "House is initialized");
	// REQUIRE(this->isInitialized(), "House is initialized");
	// ENSURE(this->isInitialized(), "House is initialized");

	char getSymbol();
	/* Returns the symbol of this instance in the city to be used with the graphical impression */

private:
	House* fMyself;
};

#endif /* HOUSE_H_ */
