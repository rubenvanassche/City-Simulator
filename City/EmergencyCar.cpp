/*
 * EmergencyCar.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "EmergencyCar.h"

bool EmergencyCar::isInitialized() const {
	return this == fMyself;
}

EmergencyCar::EmergencyCar(const std::string& name, Depot* base)
	: Vehicle(name, base->getLocation()) {
	REQUIRE(base->isInitialized(), "FireDepot is initialized");

	fMyself = this;
	fBase = base;
	fBuilding = NULL;

	ENSURE(this->isInitialized(), "EmergencyCar is initialized");
	ENSURE(this->fBase == base, "Base is set");
	ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "EmergencyCar does not have a building yet");
}

EmergencyCar::EmergencyCar(const EmergencyCar& f)
	: Vehicle(f.getName(), f.getPosition()) {
	REQUIRE(f.isInitialized(), "EmergencyCar is initialized");

	fMyself = this;
	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "EmergencyCar is initialized");
	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
}

void EmergencyCar::operator= (const EmergencyCar& f) {
	REQUIRE(f.isInitialized(), "EmergencyCar is initialized");
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
	return;
}

Depot* EmergencyCar::getBase() const {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	return fBase;
}

Building* EmergencyCar::getBuilding() const {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	return fBuilding;
}

bool EmergencyCar::isInDepot() const {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	return this->getPosition() == fBase->getLocation();
}

void EmergencyCar::send(Building* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "EmergencyCar is in depot");

	fBuilding = building;
	this->setDestination(destination);
	this->setPosition(EmergencyCar::fBase->getEntrance());

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->getPosition() == this->fBase->getEntrance(), "EmergencyCar is at the entrance");
	return;
}

void EmergencyCar::sendBack() {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	fBuilding = NULL;
	this->setDestination(EmergencyCar::fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return;
}

bool EmergencyCar::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	return this->getPosition() == fBase->getEntrance();
}

void EmergencyCar::enterDepot() {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "EmergencyCar is at entrance");

	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->getPosition() == this->fBase->getLocation(), "EmergencyCar is now in depot");
	ENSURE(this->getDestination() == this->fBase->getLocation(), "EmergencyCar is now in depot");
	return;
}
