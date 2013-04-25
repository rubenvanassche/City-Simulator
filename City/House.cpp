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
	: Building(location, 2, health, 1) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");

	fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
}

House::House(const House& h)
	: Building(h.getLocation(), 2, h.getHealth() , 1) {
	REQUIRE(h.isInitialized(), "House is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "House is initialized");
}

void House::operator= (const House& h) {
	REQUIRE(h.isInitialized(), "House is initialized");
	REQUIRE(this->isInitialized(), "House is initialized");

	// nothing to do here

	ENSURE(this->isInitialized(), "House is initialized");
	return;
}

char House::getSymbol(){
	if(this->isBurning()){
		return '#';
	}else{
		return 'H';
	}
}
