/*
 * Hospital.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Hospital.h"

bool Hospital::isInitialized() const {
	return this == fMyself;
}


std::ostream& operator<< (std::ostream& stream, Hospital& h){
	REQUIRE(h.isInitialized(), "Hospital is initialized");

	stream << "Ziekenhuis " << h.getName();
	return stream;
}


Hospital::Hospital(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health)
: Depot(location, entrance, size, name, health){

	fMyself = this;

	ENSURE(this->isInitialized(), "Hospital is initialized");
}

Hospital::Hospital(const Hospital& h)
: Depot(h){
	REQUIRE(h.isInitialized(), "Hospital is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "Hospital is initialized");
}

void Hospital::operator= (const Hospital& h) {
	REQUIRE(h.isInitialized(), "Hospital is initialized");
	REQUIRE(this->isInitialized(), "Hospital is initialized");

	// nothing to do here

	ENSURE(this->isInitialized(), "Hospital is initialized");
	return;
}

char Hospital::getSymbol() const {
	REQUIRE(this->isInitialized(), "Hospital is initialized");

	if (this->isBurning() ){
		return '#';
	}
	else{
		return 'Z';
	}
}
