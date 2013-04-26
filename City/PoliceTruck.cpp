/*
 * PoliceTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
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
	ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "PoliceTruck doesn't have a building (yet)");
}

PoliceTruck::PoliceTruck(const PoliceTruck& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "PoliceTruck is initialized");

	fMyself = this;
	fBuilding = f.fBuilding;
	fBase = f.fBase;

	ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is set");
	ENSURE(this->getPosition() == f.fBase->getLocation(), "Position is set");
	ENSURE(this->getDestination() == f.fBase->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "PoliceTruck doesn't have a building (yet)");
}

void PoliceTruck::operator= (const PoliceTruck& f) {
	REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	ENSURE(this->fBase == f.fBase, "Base is set");
	ENSURE(this->getPosition() == f.fBase->getLocation(), "Position is copied");
	ENSURE(this->getDestination() == f.fBase->getLocation(), "Destination is copied");
	ENSURE(this->fBuilding == NULL, "PoliceTruck doesn't have a building (yet)");
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

	return this->getPosition() == fBase->getLocation();
}

void PoliceTruck::send(Shop* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(building->isRobbing() == true, "Shop is being robbed");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "PoliceTruck is in depot");

	fBuilding = building;
	this->setDestination(destination);
	this->setPosition(fBase->getEntrance());

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->getPosition() == this->fBase->getEntrance(), "PoliceTruck is at the entrance");
	return;
}

void PoliceTruck::sendBack() {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	fBuilding = NULL;
	this->setDestination(fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return;
}

bool PoliceTruck::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	return this->getPosition() == fBase->getEntrance();
}

void PoliceTruck::enterDepot() {
	REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "PoliceTruck is at entrance");

	if (fBase->isBurning() ) {
		return;	// if the building is on fire, then wait for the firetruck...
	}

	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->getPosition() == this->fBase->getLocation(), "PoliceTruck is now in depot");
	ENSURE(this->getDestination() == this->fBase->getLocation(), "PoliceTruck is now in depot");
	return;
}

char PoliceTruck::getSymbol() const {
	return '%';
}

