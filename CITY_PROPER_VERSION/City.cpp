/*
 * City.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "City.h"
#include <iostream>

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

	for (unsigned int index=0; index < town.fTrucks.size(); index++) {
		FireTruck* f = new FireTruck( *(town.fTrucks[index]) );
		City::fTrucks.push_back(f);
	}

	for (unsigned int index=0; index < town.fStreets.size(); index++) {
		Street* s = new Street( *(town.fStreets[index]) );
		City::fStreets.push_back(s);
	}

	for (unsigned int index=0; index < town.fHouses.size(); index++) {
		House* h = new House( *(town.fHouses[index]) );
		City::fHouses.push_back(h);
	}

	for (unsigned int index=0; index < town.fFireDepots.size(); index++) {
		FireDepot* f = new FireDepot( *(town.fFireDepots[index]) );
		City::fFireDepots.push_back(f);
	}

	ENSURE(this->isInitialized(), "City is copied");
}

bool City::addFireDepot(FireDepot& depot) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(depot.isInitialized(), "FireDepot is initialized");

	FireDepot* d = new FireDepot(depot);
	City::fFireDepots.push_back(d);

	return true;
}

bool City::addFireTruck(FireTruck& truck) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(truck.isInitialized(), "FireTruck is initialized");

	FireTruck* f = new FireTruck(truck);
	City::fTrucks.push_back(f);

	return true;
}

bool City::addStreet(Street& street) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(street.isInitialized(), "Street is initialized");

	Street* s = new Street(street);
	City::fStreets.push_back(s);

	return true;
}

bool City::addHouse(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	House* h = new House(house);
	City::fHouses.push_back(h);

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


bool City::writeTrucksStatus(const char* filename) {
	ENSURE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		filestream << *(City::fTrucks[index]) << std::endl;
	}
	filestream.close();
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

bool City::writeHousesStatus(const char* filename) {
	ENSURE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		filestream << *(City::fHouses[index]) << std::endl;
	}
	filestream.close();
	return true;
}


bool City::writeDepotsStatus(const char* filename) {
	ENSURE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		filestream << *(City::fFireDepots[index]) << std::endl;
	}
	filestream.close();
	return true;
}

City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index--) {
		delete City::fFireDepots[index];
	}
	City::fFireDepots.clear();

	for (unsigned int index=0; index < City::fStreets.size(); index++) {
		delete City::fStreets[index];
	}
	City::fStreets.clear();
	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}
	City::fHouses.clear();

	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		delete City::fTrucks[index];
	}
	City::fTrucks.clear();

	ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	ENSURE(this->fStreets.empty() == true, "Street is empty'd");
	ENSURE(this->fHouses.empty() == true, "Houses is empty'd");
}
