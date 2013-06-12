/*
 * Ambulance.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "Ambulance.h"

bool Ambulance::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, Ambulance& f) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");

	stream << "Ziekenwagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

Ambulance::Ambulance(const std::string& name, Hospital* base)
	: Vehicle(name, base->getLocation()) {
	REQUIRE(base != NULL, "base pointer must point to a hospital");
	REQUIRE(base->isInitialized(), "Hospital is initialized");

	fMyself = this;
	fBuilding = NULL;
	fBase = base;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->getBase() == base, "Base is set");
	ENSURE(this->isInDepot(), "Ambulance is in depot");
	ENSURE(this->getBuilding() == NULL, "Ambulance doesn't have building (yet)" );
}

Ambulance::Ambulance(const Ambulance& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");

	fMyself = this;
	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->getBase() == f.getBase(), "Base is copied");
	ENSURE(this->getBuilding() == f.getBuilding(), "Building is copied");
}

void Ambulance::operator= (const Ambulance& f) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->getBase() == f.getBase(), "Base is copied");
	ENSURE(this->getBuilding() == f.getBuilding(), "Building is copied");
	return;
}

Hospital* Ambulance::getBase() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	return fBase;
}

Building* Ambulance::getBuilding() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	return fBuilding;
}

bool Ambulance::isInDepot() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	return this->getPosition() == this->getBase()->getLocation();
}

void Ambulance::send(Building* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "Ambulance is in depot");

	fBuilding = building;	// first set the building
	this->setDestination(destination);	// then set the destination, (may be different from the building's location)
	this->setPosition(fBase->getEntrance());	// then set it to the entrance of it's depot

	ENSURE(this->getBuilding() == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->isAtEntranceDepot(), "Ambulance is at the entrance of it's depot");
	return;
}

void Ambulance::sendBack() {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	fBuilding = NULL;	// set the building to NULL
	this->setDestination(fBase->getEntrance());	// then set it's destination to the entrance of it's depot

	ENSURE(this->getBuilding() == NULL, "EmergencyCar has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->getBase()->getEntrance(), "Destination is set to the base's entrance");
	return;
}

bool Ambulance::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	return this->getPosition() == fBase->getEntrance();
}

void Ambulance::enterDepot() {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");
	REQUIRE(this->isAtEntranceDepot(), "Ambulance is at entrance of the depot");
	REQUIRE(this->getBase()->isBurning() == false, "The base is not on fire");
	REQUIRE(this->getBase()->isDead() == false, "The base is not burnt down");

	// set both position and destination to the base's location
	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->isInDepot(), "Ambulance is now in depot");
	return;
}

char Ambulance::getSymbol() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");
	return '=';
}
