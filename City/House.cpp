/*
 * House.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	Friday 15 March 2013
 * @date:		1.0
 * 
 */

#include "House.h"

bool House::isInitialized() const {
	return fMyself == this;
}

std::ostream& operator<< (std::ostream& stream, House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");

	stream << "Huis op locatie " << h.getLocation();
	return stream;
}

House::House(const Point& location, const double& health)
	: Building(location, 2, health) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");

	fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
}

House::House(const House& h)
	: Building(h.getLocation(), 2, h.getHealth() ) {
	REQUIRE(h.isInitialized(), "House is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
	ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	ENSURE(this->getSize() == h.getSize(), "Size is copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location is copied");
}

bool House::operator= (const House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");
	REQUIRE(this->isInitialized(), "House is initialized");

	fLocation = h.getLocation();
	fSize = h.fSize;
	fHealth = h.getHealth();

	ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	ENSURE(this->getSize() == h.getSize(), "Size is copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location is copied");
	return true;
}
