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

	friend std::ostream& operator<< (std::ostream& stream, House& h);
	// REQUIRE(h.isInitialized(), "House is initialized");

	House(Point& location, Size& size, double health);
	// REQUIRE(location.isInitialized(), "Location is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Positive healthpoints");
	// ENSURE(this->isInitialized(), "House is initialized");

	House(House& h);
	// REQUIRE(h.isInitialized(), "House is initialized");
	// ENSURE(this->isInitialized(), "House is initialized");

	bool operator= (House& h);
	// REQUIRE(h.isInitialized(), "House is initialized");
	// REQUIRE(this->isInitialized(), "House is initialized");

private:
	House* fMyself;
};

#endif /* HOUSE_H_ */
