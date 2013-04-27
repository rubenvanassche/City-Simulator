/*
 * FireTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "FireTruck.h"

bool FireTruck::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	stream << "Brandweerwagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

FireTruck::FireTruck(const std::string& name, FireDepot* base)
	: Vehicle(name, base->getLocation()) {
	REQUIRE(base->isInitialized(), "FireDepot is initialized");

	fMyself = this;
	fBuilding = NULL;
	fBase = base;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->fBase == base, "Base is set");
	ENSURE(this->isInDepot(), "FireTruck is in depot");
	ENSURE(this->fBuilding == NULL, "FireTruck doesn't have a building (yet)");
}

FireTruck::FireTruck(const FireTruck& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");

	fMyself = this;
	fBuilding = f.fBuilding;
	fBase = f.fBase;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
}

void FireTruck::operator= (const FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
	return;
}

FireDepot* FireTruck::getBase() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	ENSURE(this->fBase != NULL, "There must be an existing base");
	return fBase;
}

Building* FireTruck::getBuilding() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return fBuilding;
}

bool FireTruck::isInDepot() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	// check whether it's position correspond to the base's location
	return this->getPosition() == fBase->getLocation();
}

void FireTruck::send(Building* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(building->isBurning(), "Building is on fire");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "FireTruck is in depot");

	fBuilding = building;	// first set the building
	this->setDestination(destination);	// then set the destination (may be different from building's location
	this->setPosition(fBase->getEntrance());	// then put the car at the entrance of it's base

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->isAtEntranceDepot(), "FireTruck is at the entrance of it's base");
	return;
}

void FireTruck::sendBack() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(this->fBuilding->isBurning() == false, "Building is not on fire anymore");

	fBuilding = NULL;
	this->setDestination(fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "FireTruck has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to the base's entrance");
	return;
}

bool FireTruck::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	// check whether it's position correspond to the base's entrance
	return this->getPosition() == fBase->getEntrance();
}

void FireTruck::enterDepot() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at entrance");
	REQUIRE(this->fBase->isBurning() == false, "The base is not on fire");
	REQUIRE(this->fBase->isDead() == false, "The base is not burnt down");

	// set both position and destination to the location of the depot
	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->isInDepot(), "FireTruck is now in depot");
	return;
}

char FireTruck::getSymbol() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	return '*';
}
