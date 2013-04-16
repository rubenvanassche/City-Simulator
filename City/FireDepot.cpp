/*
 * FireDepot.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "FireDepot.h"
#include <fstream>

bool FireDepot::isInitialized() {
	return this == FireDepot::fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");

	stream << "Brandweerkazerne " << f.getName();
	return stream;
}

FireDepot::FireDepot(Point& location, Point& entrance, Size& size, std::string name, double health)
: Depot(location, entrance, size, name, health){

	FireDepot::fMyself = this;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->getName() == name, "Name is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
	ENSURE(this->getEntrance() == entrance, "Entrance is set");
	ENSURE(this->getHealth() == health, "Health is set");
}

FireDepot::FireDepot(FireDepot& f)
: Depot(f){
	REQUIRE(f.isInitialized(), "PoliceDepot is initialized");

	FireDepot::fMyself = this;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->getName() == f.getName(), "Name is copied");
	ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	ENSURE(this->getSize() == f.getSize(), "Size is copied");
	ENSURE(this->getEntrance() == f.getEntrance(), "Entrance is copied");
	ENSURE(this->getNrVehicles() == f.getNrVehicles(), "Trucks copied");
	ENSURE(this->getHealth() == f.getHealth(), "Health is copied");
}

