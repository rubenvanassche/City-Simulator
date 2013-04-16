/*
 * PoliceDepot.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "PoliceDepot.h"

bool PoliceDepot::isInitialized(){
	return this == PoliceDepot::fMyself;
}


std::ostream& operator<< (std::ostream& stream, PoliceDepot& p){
	REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	stream << "Politiekantoor " << p.getName();
	return stream;
}


PoliceDepot::PoliceDepot(Point& location, Point& entrance, Size& size, std::string name, double health)
: Depot(location, entrance, size, name, health){

	PoliceDepot::fMyself = this;

	ENSURE(this->isInitialized(), "PoliceDepot is initialized");
	ENSURE(this->getName() == name, "Name is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
	ENSURE(this->getEntrance() == entrance, "Entrance is set");
	ENSURE(this->getHealth() == health, "Health is set");
}


PoliceDepot::PoliceDepot(PoliceDepot& p)
: Depot(p){
	REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	PoliceDepot::fMyself = this;

	ENSURE(this->isInitialized(), "PoliceDepot is initialized");
	ENSURE(this->getName() == p.getName(), "Name is copied");
	ENSURE(this->getLocation() == p.getLocation(), "Location is copied");
	ENSURE(this->getSize() == p.getSize(), "Size is copied");
	ENSURE(this->getEntrance() == p.getEntrance(), "Entrance is copied");
	ENSURE(this->getNrVehicles() == p.getNrVehicles(), "Trucks copied");
	ENSURE(this->getHealth() == p.getHealth(), "Health is copied");
}

