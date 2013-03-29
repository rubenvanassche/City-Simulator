/*
 * House.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	Friday 15 March 2013
 * @date:		1.0
 * 
 */

#include "House.h"

bool House::isInitialized() {
	return House::fMyself == this;
}

std::ostream& operator<< (std::ostream& stream, House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");

	stream << "Huis op locatie " << h.getLocation();
	return stream;
}

House::House(Point& location, Size& size, double health)
	: Building(location, size, health) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");

	House::fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
}

House::House(House& h)
	: Building(h.getLocation(), h.getSize(), h.getHealth() ) {
	REQUIRE(h.isInitialized(), "House is initialized");

	House::fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
	ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	ENSURE(this->getSize() == h.getSize(), "Size is copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location is copied");
}

bool House::operator= (House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");
	REQUIRE(this->isInitialized(), "House is initialized");

	this->setLocation(h.getLocation());
	this->setSize(h.getSize());
	this->setHealth(h.getHealth());

	ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
	ENSURE(this->getSize() == h.getSize(), "Size is copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location is copied");
	return true;
}
