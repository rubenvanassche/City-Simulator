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

House::House(Point& location, Size& size, int health)
	: Building(location, size) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");

	House::fMyself = this;
	House::fIsBurning = false;
	House::fHealth = health;

	ENSURE(this->isInitialized(), "House is initialized");
	ENSURE(this->fHealth == health, "Health points is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
}

House::House(House& h)
	: Building(h.getLocation(), h.getSize()) {
	REQUIRE(h.isInitialized(), "House is initialized");

	House::fMyself = this;
	House::fIsBurning = h.fIsBurning;
	House::fHealth = h.fHealth;

	ENSURE(this->isInitialized(), "House is initialized");
	ENSURE(this->fIsBurning == h.fIsBurning, "Burning copied");
	ENSURE(this->fHealth == h.fHealth, "Health copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location copied");
	ENSURE(this->getSize() == h.getSize(), "Size copied");
}

bool House::operator= (House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");
	REQUIRE(this->isInitialized(), "House is initialized");

	House::fIsBurning = h.fIsBurning;
	House::fHealth = h.fHealth;

	ENSURE(this->fIsBurning == h.fIsBurning, "Burning copied");
	ENSURE(this->fHealth == h.fHealth, "Health copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location copied");
	ENSURE(this->getSize() == h.getSize(), "Size copied");
	return true;
}

bool House::isBurning() {
	REQUIRE(this->isInitialized(), "House is initialized");
	return House::fIsBurning;
}

bool House::setFire() {
	REQUIRE(this->isInitialized(), "House is initialized");

	House::fIsBurning = true;

	ENSURE(this->fIsBurning == true, "House is set on fire");
	return true;
}

bool House::stopFire() {
	REQUIRE(this->isInitialized(), "House is initialized");

	House::fIsBurning = false;

	ENSURE(this->fIsBurning == false, "House is set on fire");
	return true;
}

bool House::setHealth(int health) {
	REQUIRE(this->isInitialized(), "House is initialized");
	REQUIRE(health >= 0, "Health points is positive");

	House::fHealth = health;

	ENSURE(this->fHealth == health, "Health is set");
	return true;
}

unsigned int House::getHealth() {
	REQUIRE(this->isInitialized(), "House is initialized");
	return House::fHealth;
}

bool House::check(int substracter) {
	REQUIRE(this->isInitialized(), "House is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fHealth != 0, "Health is not 0");

	House::fHealth -= substracter;

	return true;
}
