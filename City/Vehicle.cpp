/*
 * Vehicle.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Vehicle.h"

bool Vehicle::isInitialized() const {
	return this == fMyself;
}

Vehicle::Vehicle(const std::string& name, const Point& curPos, const Point& destination) {
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	fPosition = curPos;
	fDestination = destination;
	fMyself = this;
	fName = name;

	ENSURE(this->isInitialized(), "Vehicle is initialized");
	ENSURE(this->fName == name, "Name is set");
	ENSURE(this->fDestination == destination, "Destination is set");
	ENSURE(this->fPosition == curPos, "Position is set");
}

Vehicle::Vehicle(const Vehicle& v) {
	REQUIRE(v.isInitialized(), "Vehicle is initialized");

	fPosition = v.fPosition;
	fDestination = v.fDestination;
	fMyself = this;
	fName = v.fName;

	ENSURE(this->isInitialized(), "Vehicle is initialized");
	ENSURE(this->fName == v.fName, "Name is copied");
	ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	ENSURE(this->fPosition == v.fPosition, "Position is copied");
}

bool Vehicle::operator= (const Vehicle& v) {
	REQUIRE(v.isInitialized(), "Vehicle is initialized");
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	fPosition = v.fPosition;
	fDestination = v.fDestination;
	fName = v.fName;

	ENSURE(this->fName == v.fName, "Name is copied");
	ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	ENSURE(this->fPosition == v.fPosition, "Position is copied");
	return true;
}

Point Vehicle::getPosition() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fPosition;
}

bool Vehicle::setDestination(const Point& destination) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	fDestination = destination;

	ENSURE(this->fDestination == destination, "Destination is set");
	return true;
}

Point Vehicle::getDestination() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fDestination;
}

bool Vehicle::isArrived() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return fPosition == fDestination;
}

bool Vehicle::isOnWay() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return fPosition != fDestination;
}

bool Vehicle::goLeft() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(this->fPosition.getX() != 0, "You can not fall of");

	fPosition.set( fPosition.getX() - 1, fPosition.getY() );
	return true;
}

bool Vehicle::goRight() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	fPosition.set( fPosition.getX() + 1, fPosition.getY() );
	return true;
}

bool Vehicle::goUp() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	fPosition.set( fPosition.getX(), fPosition.getY() + 1);
	return true;
}

bool Vehicle::goDown() {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(this->fPosition.getY() != 0, "You can not fall of");

	fPosition.set( fPosition.getX(), fPosition.getY()  - 1);
	return true;
}

std::string Vehicle::getName() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fName;
}

bool Vehicle::setName(const std::string& name) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	fName = name;

	ENSURE(this->fName == name, "Name is set");
	return true;
}
