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

City::City(const City& town) {
	//REQUIRE(town.isInitialized(), "City is initialized");

	City::fMyself = this;
	City::fTrucks = town.fTrucks;
	City::fStreets = town.fStreets;
	City::fHouses = town.fHouses;
	City::fFireDepots = town.fFireDepots;

	ENSURE(this->isInitialized(), "City is copied");
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

bool City::trucksOnWay() {
	ENSURE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		if (City::fTrucks[index]->getPosition() == City::fTrucks[index]->getDestination()) {
			continue;
		}
		else {
			return true;
		}
	}
	return false;
}


bool City::writeTrucksStatus(std::fstream& filestream) {
	ENSURE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		filestream << *(City::fTrucks[index]) << std::endl;
	}

	return true;
}

bool City::housesOnFire() {
	ENSURE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning()) {
			return true;
		}
		continue;
	}
	return false;
}

bool City::writeHousesStatus(std::fstream& filestream) {
	ENSURE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		filestream << *(City::fHouses[index]) << std::endl;
	}

	return true;
}


bool City::writeDepotsStatus(std::fstream& filestream) {
	ENSURE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		filestream << *(City::fFireDepots[index]) << std::endl;
	}
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
