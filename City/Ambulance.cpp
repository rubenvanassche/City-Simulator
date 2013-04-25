/*
 * Ambulance.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
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
	REQUIRE(base->isInitialized(), "Hospital is initialized");

	fMyself = this;
	fBuilding = NULL;
	fBase = base;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->fBase == base, "Base is set");
	ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	ENSURE(this->fBuilding == NULL, "Ambulance doesn't have building (yet)" );
}

Ambulance::Ambulance(const Ambulance& f)
	: Vehicle(f.getName(), f.getBase()->getLocation() ) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");

	fMyself = this;
	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
}

void Ambulance::operator= (const Ambulance& f) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	fBase = f.fBase;
	fBuilding = f.fBuilding;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	ENSURE(this->fBase == f.fBase, "Base is copied");
	ENSURE(this->fBuilding == f.fBuilding, "Building is copied");
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

	return this->getPosition() == fBase->getLocation();
}

void Ambulance::send(Building* building, const Point& destination) {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	REQUIRE(building->isInitialized(), "Building is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInDepot(), "Ambulance is in depot");

	fBuilding = building;
	this->setDestination(destination);
	this->setPosition(fBase->getEntrance());

	ENSURE(this->fBuilding == building, "Building is set");
	ENSURE(this->getDestination() == destination, "Destination is set");
	ENSURE(this->getPosition() == this->fBase->getEntrance(), "Ambulance is at the entrance");
	return;
}

void Ambulance::sendBack() {
	REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	fBuilding = NULL;
	this->setDestination(fBase->getEntrance());

	ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");
	return;
}

bool Ambulance::isAtEntranceDepot() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	return this->getPosition() == fBase->getEntrance();
}

void Ambulance::enterDepot() {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");
	REQUIRE(this->getPosition() == this->fBase->getEntrance(), "Ambulance is at entrance");

	this->setPosition(fBase->getLocation());
	this->setDestination(fBase->getLocation());

	ENSURE(this->getPosition() == this->fBase->getLocation(), "Ambulance is now in depot");
	ENSURE(this->getDestination() == this->fBase->getLocation(), "Ambulance is now in depot");
	return;
}

char Ambulance::getSymbol() const {
	REQUIRE(this->isInitialized(), "Ambulance is initialized");
	return '=';
}
