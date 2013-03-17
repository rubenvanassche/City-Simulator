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
	stream << "Brandweerwagen " << f.getName() << " [basis: " << f.fBaseName << "]";
	return stream;
}

FireTruck::FireTruck(std::string& name, Point& curPos, Point& destination, std::string& basename)
	: Vehicle(name, curPos, destination) {
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	FireTruck::fMyself = this;
	FireTruck::fBaseName = basename;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->getName() == name, "Name is initialized");
	ENSURE(this->getPosition() == curPos, "Position is initialized");
	ENSURE(this->getDestination() == destination, "Destination is initialized");
	ENSURE(this->fBaseName == basename, "Base is initialized");
}

FireTruck::FireTruck(FireTruck& f)
	: Vehicle(f.getName(), f.getPosition(), f.getDestination() ) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");

	FireTruck::fMyself = this;
	FireTruck::fBaseName = f.fBaseName;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	ENSURE(this->getName() == f.getName(), "Name is initialized");
	ENSURE(this->getPosition() == f.getPosition(), "Position is initialized");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is initialized");
	ENSURE(this->fBaseName == f.fBaseName, "Base is initialized");
}

bool FireTruck::operator= (FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	this->setName(f.getName());
	this->setPosition(f.getPosition());
	this->setDestination(f.getDestination());
	FireTruck::fBaseName = f.fBaseName;

	ENSURE(this->getName() == f.getName(), "Name is initialized");
	ENSURE(this->getPosition() == f.getPosition(), "Position is initialized");
	ENSURE(this->getDestination() == f.getDestination(), "Destination is initialized");
	ENSURE(this->fBaseName == f.fBaseName, "Base is initialized");
	return true;
}

bool FireTruck::setBase(std::string& basename) {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	FireTruck::fBaseName = basename;

	ENSURE(this->fBaseName == basename, "Basename is set");
	return true;
}

std::string& FireTruck::getBase() {
	REQUIRE(this->isInitialized(), "FireTruck is initialized");
	return FireTruck::fBaseName;
}
