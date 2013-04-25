/*
 * FireTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
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
	ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "FireTruck doesn't have a building (yet)");
}

FireTruck::FireTruck(const FireTruck& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");

	fMyself = this;
	fBuilding = f.fBuilding;
	fBase = f.fBase;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is set");
	ENSURE(this->getPosition() == f.fBase->getLocation(), "Position is set");
	ENSURE(this->getDestination() == f.fBase->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "FireTruck doesn't have a building (yet)");
}

void FireTruck::operator= (const FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is set");
	ENSURE(this->getPosition() == f.fBase->getLocation(), "Position is copied");
	ENSURE(this->getDestination() == f.fBase->getLocation(), "Destination is copied");
	ENSURE(this->fBuilding == NULL, "FireTruck doesn't have a building (yet)");
	return;
}

FireDepot* FireTruck::getBase() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return fBase;
}

Building* FireTruck::getBuilding() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return fBuilding;
}

bool FireTruck::isInDepot() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return this->getPosition() == fBase->getLocation();
}

void FireTruck::send(Building* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(building->isBurning(), "Building is on fire");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "FireTruck is in depot");

	fBuilding = building;
	this->setDestination(destination);
	this->setPosition(fBase->getEntrance());

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at the entrance");
	return;
}

void FireTruck::sendBack() {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(this->fBuilding->isBurning() == false, "Building is not on fire anymore");

	fBuilding = NULL;
	this->setDestination(fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return;
}

bool FireTruck::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	return this->getPosition() == fBase->getEntrance();
}

void FireTruck::enterDepot() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at entrance");

	if (fBase->isBurning()) {
		// then extinguish
		fBase->stopFire();
	}

	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->getPosition() == this->fBase->getLocation(), "FireTruck is now in depot");
	ENSURE(this->getDestination() == this->fBase->getLocation(), "FireTruck is now in depot");
	return;
}

char FireTruck::getSymbol() const {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	return '*';
}
