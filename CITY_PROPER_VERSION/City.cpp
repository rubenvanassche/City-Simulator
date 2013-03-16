/*
 * City.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "City.h"

bool City::isInitialized() {
	return this == City::fMyself;
}

City::City() {
	City::fMyself = this;
	ENSURE(this->isInitialized(), "City is initialized");
}

bool City::addFireDepot(FireDepot& depot) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(depot.isInitialized(), "FireDepot is initialized");

	// do something useful here

	return true;
}

bool City::addFireTruck(FireTruck& truck) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(truck.isInitialized(), "FireTruck is initialized");

	// do something useful here

	return true;
}

bool City::addStreet(Street& street) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(street.isInitialized(), "Street is initialized");

	// do something useful here

	return true;
}

bool City::addHouse(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	// do something useful here

	return true;
}

City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		delete City::fFireDepots[index];
	}

	for (unsigned int index=0; index < City::fStreets.size(); index++) {
		delete City::fStreets[index];
	}

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}

	ENSURE(this->fFireDepots.empty(), "FireDepots is empty'd");
	ENSURE(this->fStreets.empty(), "Street is empty'd");
	ENSURE(this->fHouses.empty(), "Houses is empty'd");
}
