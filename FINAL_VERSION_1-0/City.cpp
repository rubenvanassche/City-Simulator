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
#include <cstdlib>
#include <fstream>

bool City::isInitialized() {
	return this == City::fMyself;
}

City::City() {
	City::fMyself = this;

	WorldMap map;
	City::fMap = map;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::City(City& town) {
	//REQUIRE(town.isInitialized(), "City is initialized");

	City::fMyself = this;

	City::fMap = town.fMap;

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

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getName() == truck.getBase()) {
			truck.setPosition(City::fFireDepots[index]->getLocation());
			truck.setDestination(City::fFireDepots[index]->getLocation());
			City::fFireDepots[index]->addFireTruck(truck);
			return true;
		}
	}

	std::cout << "FireTruck " << truck.getName() << " has unknown base." << std::endl;
	return false;
}

bool City::addStreet(Street& street) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(street.isInitialized(), "Street is initialized");

	City::fMap.addStreet(street);

	return true;
}

bool City::addHouse(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	House* h = new House(house);
	City::fHouses.push_back(h);

	return true;
}

City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index--) {
		delete City::fFireDepots[index];
	}
	City::fFireDepots.clear();

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}
	City::fHouses.clear();

	ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	ENSURE(this->fHouses.empty() == true, "Houses is empty'd");
}

bool City::isDead() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (!City::fHouses[index]->isDead()) {
			return false;
		}
	}
	return true;
}

bool City::fireBreaksOut() {
	// REQUIRE( this->isDead() == false, "City is not dead");

	int index = std::rand() % City::fHouses.size();

	if ( (City::fHouses[index]->isBurning() ) || (City::fHouses[index]->isDead()) ) {
		return false;
	}

	City::fHouses[index]->setFire();

	ENSURE(City::fHouses[index]->isBurning(), "House is not set on fire");
	return true;
}

bool City::burningDown() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning()) {
			City::fHouses[index]->burningDown(1);
		}
	}
	return true;
}

bool City::driveTrucks() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (!City::fHouses[index]->isBurning()) {
			continue;
		}

		bool alreadySend = false;
		for (unsigned int i=0; i < City::fFireDepots.size(); i++) {
			if (City::fFireDepots[i]->alreadySend(City::fHouses[index]->getLocation() ) ) {
				alreadySend = true;
				break;
			}
		}

		if (alreadySend) {
			continue;	// go to the next house, a firetruck is on the way
		}

		// else we will send a firetruck;
		for (unsigned int i=0; i < City::fFireDepots.size(); i++) {
			if (City::fFireDepots[i]->getAvailableTrucks() > 0) {
				City::fFireDepots[i]->sendTruck(City::fHouses[index]->getLocation() );
				break;
			}
		}
	}

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->updateDrivingTrucks(City::fMap);
	}

	return true;
}

bool City::extinguish() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Point*> blushed;
	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		blushed = City::fFireDepots[index]->updateArrivedTrucks();
	}

	for (unsigned int index=0; index < blushed.size(); index++) {
		for (unsigned int i=0; i < City::fHouses.size(); i++) {
			if (City::fHouses[i]->getLocation() == *(blushed[index]) ) {
				City::fHouses[i]->stopFire();
				delete blushed[index];
				break;
			}
		}
	}

	blushed.clear();
	return true;
}

bool City::statusBurningHouses(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning() ) {
			filestream << "\t" << *(City::fHouses[index]) << " staat in brand en heeft nog "
					<< City::fHouses[index]->getHealth() << " health points." << std::endl;
		}
		else if (City::fHouses[index]->isDead() ) {
			filestream << "\t" << *(City::fHouses[index]) << " is volledig afgebrand." << std::endl;
		}
	}

	filestream.close();
	return true;
}

bool City::statusTrucksOnWay(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->statusTrucksOnWay(fileName);
	}
	filestream.close();
	return true;
}

bool City::statusAvailableTrucks(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->statusAvailableTrucks(fileName);
	}
	filestream.close();
	return true;
}

bool City::allTrucksBack() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getAvailableTrucks() != City::fFireDepots[index]->getNrTrucks() ) {
			return false;
		}
	}
	return true;
}
