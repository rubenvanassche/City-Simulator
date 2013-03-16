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

	House(Point& location, Size& size, int health);
	// REQUIRE(location.isInitialized(), "Location is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Positive healthpoints");
	// ENSURE(this->isInitialized(), "House is initialized");
	// ENSURE(this->fHealth == health, "Health points is set");
	// ENSURE(this->getLocation() == location, "Location is set");
	// ENSURE(this->getSize() == size, "Size is set");

	House(House& h);
	// REQUIRE(h.isInitialized(), "House is initialized");
	// ENSURE(this->isInitialized(), "House is initialized");
	// ENSURE(this->fIsBurning == h.fIsBurning, "Burning copied");
	// ENSURE(this->fHealth == h.fHealth, "Health copied");
	// ENSURE(this->getLocation() == h.getLocation(), "Location copied");
	// ENSURE(this->getSize() == h.getSize(), "Size copied");

	bool operator= (House& h);
	// REQUIRE(h.isInitialized(), "House is initialized");
	// REQUIRE(this->isInitialized(), "House is initialized");
	// ENSURE(this->fIsBurning == h.fIsBurning, "Burning copied");
	// ENSURE(this->fHealth == h.fHealth, "Health copied");
	// ENSURE(this->getLocation() == h.getLocation(), "Location copied");
	// ENSURE(this->getSize() == h.getSize(), "Size copied");

	bool isBurning();
	// REQUIRE(this->isInitialized(), "House is initialized");

	bool setFire();
	// REQUIRE(this->isInitialized(), "House is initialized");
	// ENSURE(this->fIsBurning == true, "House is set on fire");

	bool stopFire();
	// REQUIRE(this->isInitialized(), "House is initialized");
	// ENSURE(this->fIsBurning == false, "House is set on fire");

	bool setHealth(int health);
	// REQUIRE(this->isInitialized(), "House is initialized");
	// REQUIRE(health >= 0, "Health points is positive");
	// ENSURE(this->fHealth == health, "Health is set");

	unsigned int getHealth();
	// REQUIRE(this->isInitialized(), "House is initialized");

	bool check(int substracter = 1);
	// REQUIRE(this->isInitialized(), "House is initialized");
	// REQUIRE(substracter >= 0, "Substracter is positive");
	// REQUIRE(this->fHealth != 0, "Health is not 0");

private:
	bool fIsBurning;
	unsigned int fHealth;

	House* fMyself;
};

#endif /* HOUSE_H_ */
