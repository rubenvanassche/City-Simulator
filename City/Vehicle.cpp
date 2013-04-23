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

Vehicle::Vehicle(const std::string& name, const Point& curPos) {
	REQUIRE(curPos.isInitialized(), "Point is initialized");

	fPosition = curPos;
	fDestination = curPos;
	fMyself = this;
	fName = name;

	ENSURE(this->isInitialized(), "Vehicle is initialized");
	ENSURE(this->fName == name, "Name is set");
	ENSURE(this->fDestination == curPos, "Destination is set");
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

void Vehicle::operator= (const Vehicle& v) {
	REQUIRE(v.isInitialized(), "Vehicle is initialized");
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	fPosition = v.fPosition;
	fDestination = v.fDestination;
	fName = v.fName;

	ENSURE(this->fName == v.fName, "Name is copied");
	ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	ENSURE(this->fPosition == v.fPosition, "Position is copied");
	return;
}

Point Vehicle::getPosition() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fPosition;
}

Point Vehicle::getDestination() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fDestination;
}

std::string Vehicle::getName() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	return fName;
}

void Vehicle::setDestination(const Point& destination) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	fDestination = destination;

	ENSURE(this->fDestination == destination, "Destination is set");
	return;
}

void Vehicle::setPosition(const Point& pos)  {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(pos.isInitialized(), "Point is initialized");

	fPosition = pos;

	ENSURE(this->fPosition == pos, "Position is set");
}

bool Vehicle::isOnWay() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return fPosition != fDestination;
}

void Vehicle::goLeft(const int& units) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(this->fPosition.getX() != 0, "You can not fall of");
	REQUIRE(units > 0, "Positive units");

	fPosition.set( fPosition.getX() - units, fPosition.getY() );
	return;
}

void Vehicle::goRight(const int& units) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(units > 0, "Positive units");

	fPosition.set( fPosition.getX() + units, fPosition.getY() );
	return;
}

void Vehicle::goUp(const int& units) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(units > 0, "Positive units");

	fPosition.set( fPosition.getX(), fPosition.getY() + units);
	return;
}

void Vehicle::goDown(const int& units) {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");
	REQUIRE(this->fPosition.getY() != 0, "You can not fall of");
	REQUIRE(units > 0, "Positive units");

	fPosition.set( fPosition.getX(), fPosition.getY()  - units);
	return;
}

bool Vehicle::isArrived() const {
	REQUIRE(this->isInitialized(), "Vehicle is initialized");

	return fPosition == fDestination;
}
