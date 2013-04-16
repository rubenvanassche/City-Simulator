/*
 * Hospital.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Hospital.h"

bool Hospital::isInitialized(){
	return this == Hospital::fMyself;
}


std::ostream& operator<< (std::ostream& stream, Hospital& h){
	REQUIRE(h.isInitialized(), "Hospital is initialized");

	stream << "Ziekenhuis " << h.getName();
	return stream;
}


Hospital::Hospital(Point& location, Point& entrance, Size& size, std::string name, double health)
: Depot(location, entrance, size, name, health){

	Hospital::fMyself = this;

	ENSURE(this->isInitialized(), "Hospital is initialized");
	ENSURE(this->getName() == name, "Name is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
	ENSURE(this->getEntrance() == entrance, "Entrance is set");
	ENSURE(this->getHealth() == health, "Health is set");
}


Hospital::Hospital(Hospital& h)
: Depot(h){
	REQUIRE(h.isInitialized(), "Hospital is initialized");

	Hospital::fMyself = this;

	ENSURE(this->isInitialized(), "Hospital is initialized");
	ENSURE(this->getName() == h.getName(), "Name is copied");
	ENSURE(this->getLocation() == h.getLocation(), "Location is copied");
	ENSURE(this->getSize() == h.getSize(), "Size is copied");
	ENSURE(this->getEntrance() == h.getEntrance(), "Entrance is copied");
	ENSURE(this->getNrVehicles() == h.getNrVehicles(), "Trucks copied");
	ENSURE(this->getHealth() == h.getHealth(), "Health is copied");
}
