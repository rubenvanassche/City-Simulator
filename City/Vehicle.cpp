/*
 * Vehicle.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Vehicle.h"

bool Vehicle::isInitialized() {
	return this == Vehicle::fMyself;
}

Vehicle::Vehicle(std::string& name, Point& curPos, Point& destination)
	: fPosition(curPos), fDestination(destination) {
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	Vehicle::fMyself = this;
	Vehicle::fName = name;

	ENSURE(this->isInitialized(), "Vehicle is initialized");
	ENSURE(this->fName == name, "Name is initialized");
	ENSURE(this->fDestination == destination, "Destination is initialized");
	ENSURE(this->fPosition == curPos, "Position is initialized");
}

Vehicle::Vehicle(Vehicle& v)
	: fPosition(v.fPosition), fDestination(v.fDestination) {
	REQUIRE(v.isInitialized(), "Vehicle is initialized");

	Vehicle::fMyself = this;
	Vehicle::fName = v.fName;

	ENSURE(this->isInitialized(), "Vehicle is initialized");
	ENSURE(this->fName == v.fName, "Name is initialized");
	ENSURE(this->fDestination == v.fDestination, "Destination is initialized");
	ENSURE(this->fPosition == v.fPosition, "Position is initialized");
}

bool Vehicle::operator= (Vehicle& v) {
	REQUIRE(v.isInitialized(), "Vehicle is initialized");
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fPosition = v.fPosition;
	Vehicle::fDestination = v.fDestination;
	Vehicle::fName = v.fName;

	ENSURE(this->fName == v.fName, "Name is initialized");
	ENSURE(this->fDestination == v.fDestination, "Destination is initialized");
	ENSURE(this->fPosition == v.fPosition, "Position is initialized");
	return true;
}

bool Vehicle::setPosition(Point& p) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	Vehicle::fPosition = p;

	ENSURE(this->fPosition == p, "Position is set");
	return true;
}

Point& Vehicle::getPosition() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return Vehicle::fPosition;
}

bool Vehicle::setDestination(Point& destination) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	Vehicle::fDestination = destination;

	ENSURE(this->fDestination == destination, "Destination is set");
	return true;
}

Point& Vehicle::getDestination() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return Vehicle::fDestination;
}

bool Vehicle::setName(std::string& name) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fName = name;

	ENSURE(this->fName == name, "Name is set");
	return true;
}

std::string& Vehicle::getName() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return Vehicle::fName;
}

bool Vehicle::isArrived() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return Vehicle::fPosition == Vehicle::fDestination;
}

bool Vehicle::isOnWay() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return Vehicle::fPosition != Vehicle::fDestination;
}

bool Vehicle::goLeft() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fPosition.set( Vehicle::fPosition.getX() - 1, Vehicle::fPosition.getY() );
	return true;
}

bool Vehicle::goRight() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fPosition.set( Vehicle::fPosition.getX() + 1, Vehicle::fPosition.getY() );
	return true;
}

bool Vehicle::goUp() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fPosition.set( Vehicle::fPosition.getX(), Vehicle::fPosition.getY() + 1);
	return true;
}

bool Vehicle::goDown() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Vehicle::fPosition.set( Vehicle::fPosition.getX(), Vehicle::fPosition.getY()  - 1);
	return true;
}
