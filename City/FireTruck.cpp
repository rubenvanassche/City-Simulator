/*
 * FireTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "FireTruck.h"

bool FireTruck::isInitialized() {
	return this == FireTruck::fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	stream << "Brandweerwagen " << f.getName() << " [basis: " << f.fBase->getName() << "]";
	return stream;
}

FireTruck::FireTruck(std::string& name, FireDepot* base)
	: Vehicle(name, base->getLocation(), base->getLocation()) {
	REQUIRE(base->isInitialized(), "FireDepot is initialized");

	FireTruck::fMyself = this;
	FireTruck::fBase = base;
	FireTruck::fBuilding = NULL;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->getName() == name, "Name is set");
	ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	ENSURE(this->fBase == base, "Base is set");
	ENSURE(this->fBuilding == NULL, "FireTruck has not a building to extinguish yet");
}

FireTruck::FireTruck(FireTruck& f)
	: Vehicle(f.getName(), f.getPosition(), f.getDestination() ) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");

	FireTruck::fMyself = this;
	FireTruck::fBase = f.fBase;
	FireTruck::fBuilding = f.fBuilding;
	this->setName(f.getName());
	this->setPosition(f.getPosition());
	this->setDestination(f.getDestination());

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->getName() == f.getName(), "Name is copied");
	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
}

bool FireTruck::operator= (FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	this->setName(f.getName());
	this->setPosition(f.getPosition());
	this->setDestination(f.getDestination());
	FireTruck::fBase = f.fBase;
	FireTruck::fBuilding = f.fBuilding;

	ENSURE(this->getName() == f.getName(), "Name is copied");
	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
	return true;
}

bool FireTruck::isAtEntranceDepot() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return this->getPosition() == FireTruck::fBase->getEntrance();
}

bool FireTruck::enterDepot() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at entrance");

	this->setPosition(FireTruck::fBase->getLocation());
	this->setDestination(FireTruck::fBase->getLocation());

	ENSURE(this->getPosition() == this->fBase->getLocation(), "FireTruck is now in depot");
	ENSURE(this->getDestination() == this->fBase->getLocation(), "FireTruck is now in depot");
	return true;
}

bool FireTruck::isInDepot() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return this->getPosition() == FireTruck::fBase->getLocation();
}

FireDepot* FireTruck::getBase() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	return FireTruck::fBase;
}

bool FireTruck::send(Building* building, Point& destination) {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	FireTruck::fBuilding = building;
	this->setDestination(destination);

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	return true;
}

Building* FireTruck::getBuilding() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return FireTruck::fBuilding;
}

bool FireTruck::sendBack() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	FireTruck::fBuilding = NULL;
	this->setDestination(FireTruck::fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "FireTruck has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return true;
}
