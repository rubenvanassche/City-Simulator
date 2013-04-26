/*
 * PoliceTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "PoliceTruck.h"

bool PoliceTruck::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, PoliceTruck& f) {
	REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	stream << "Brandweerwagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

PoliceTruck::PoliceTruck(const std::string& name, PoliceDepot* base)
	: Vehicle(name, base->getLocation()) {
	REQUIRE(base->isInitialized(), "PoliceDepot is initialized");

	fMyself = this;
	fBuilding = NULL;
	fBase = base;

	ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	ENSURE(this->fBase == base, "Base is set");
	ENSURE(this->isInDepot(), "PoliceTruck is in depot");
	ENSURE(this->fBuilding == NULL, "PoliceTruck doesn't have a shop (yet)");
}

PoliceTruck::PoliceTruck(const PoliceTruck& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "PoliceTruck is initialized");

	fMyself = this;
	fBuilding = f.fBuilding;
	fBase = f.fBase;

	ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is set");
	ENSURE(this->fBuilding == f.fBuilding, "Shop is copied");
}

void PoliceTruck::operator= (const PoliceTruck& f) {
	REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
	return;
}

PoliceDepot* PoliceTruck::getBase() const {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	return fBase;
}

Shop* PoliceTruck::getShop() const {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	return fBuilding;
}

bool PoliceTruck::isInDepot() const {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	// check whether it's position correspond to the base's location
	return this->getPosition() == fBase->getLocation();
}

void PoliceTruck::send(Shop* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(building->isRobbing() == true, "Shop is being robbed");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "PoliceTruck is in depot");

	fBuilding = building;	// first set the building
	this->setDestination(destination);	// then set the destination (may be different from the building's location
	this->setPosition(fBase->getEntrance());	// then set the PoliceTruck to the entrance

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->isAtEntranceDepot(), "PoliceTruck is at the entrance of it's base");
	return;
}

void PoliceTruck::sendBack() {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	REQUIRE(this->fBuilding->isRobbing() == false, "Shop is not being robbed anymore");

	fBuilding = NULL;
	this->setDestination(fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "PoliceTruck has not a shop to go anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return;
}

bool PoliceTruck::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	// check whether it's position corresponds to the base's entrance
	return this->getPosition() == fBase->getEntrance();
}

void PoliceTruck::enterDepot() {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	REQUIRE(this->isAtEntranceDepot(), "PoliceTruck is at entrance");
	REQUIRE(this->fBuilding->isBurning() == false, "It's base is not on fire");

	// change both position and location to the base's location
	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->isInDepot(), "PoliceTruck is now in depot");
	return;
}

char PoliceTruck::getSymbol() const {
	return '%';
}

