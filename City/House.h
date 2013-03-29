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
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, House& h);
	// output operator overloading
	// REQUIRE(h.isInitialized(), "House is initialized");

	House(Point& location, Size& size, double health);
	// constructor
	// REQUIRE(location.isInitialized(), "Location is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Positive healthpoints");
	// ENSURE(this->isInitialized(), "House is initialized");

	House(House& h);
	// copy constructor
	// REQUIRE(h.isInitialized(), "House is initialized");
	// ENSURE(this->isInitialized(), "House is initialized");
	// ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	// ENSURE(this->getSize() == h.getSize(), "Size is copied");
	// ENSURE(this->getLocation() == h.getLocation(), "Location is copied");

	bool operator= (House& h);
	// copy by assignment operator overloading
	// REQUIRE(h.isInitialized(), "House is initialized");
	// REQUIRE(this->isInitialized(), "House is initialized");
	// ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	// ENSURE(this->getSize() == h.getSize(), "Size is copied");
	// ENSURE(this->getLocation() == h.getLocation(), "Location is copied");

private:
	House* fMyself;
};

#endif /* HOUSE_H_ */
