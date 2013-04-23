/*
 * PoliceDepot.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "PoliceDepot.h"

bool PoliceDepot::isInitialized() const {
	return this == fMyself;
}


std::ostream& operator<< (std::ostream& stream, PoliceDepot& p){
	REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	stream << "Politiekantoor " << p.getName();
	return stream;
}


PoliceDepot::PoliceDepot(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health)
: Depot(location, entrance, size, name, health){

	fMyself = this;

	ENSURE(this->isInitialized(), "PoliceDepot is initialized");
}


PoliceDepot::PoliceDepot(const PoliceDepot& p)
: Depot(p){
	REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "PoliceDepot is initialized");
}

void PoliceDepot::operator= (const PoliceDepot& p) {
	REQUIRE(p.isInitialized(), "PoliceDepot is initialized");
	REQUIRE(this->isInitialized(), "PoliceDepot is initialized");

	// nothing to do here

	ENSURE(this->isInitialized(), "PoliceDepot is initialized");
	return;
}
