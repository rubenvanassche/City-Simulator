/*
 * Vehicle.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 3 March 2013
 * 
 */


#include "Vehicle.h"
#include "DesignByContract.h"
#include "Point.h"
#include <string>

bool Vehicle::isInitialized() {
	return this == Vehicle::fMyself;
}


Vehicle::Vehicle(Point& cur_pos, Point& destination, std::string& name) {
	REQUIRE( (cur_pos.isInitialized() && destination.isInitialized() ), "Points are invalid");

	Vehicle::fDestination = destination;
	Vehicle::fPosition = cur_pos;
	Vehicle::fName = name;
	Vehicle::fMyself = this;

	ENSURE(isInitialized(), "The Vehicle object is not initialized properly");
}

Vehicle::Vehicle(const Vehicle& v) {
	Vehicle::fMyself = this;
	Vehicle::fPosition = v.fPosition;
	Vehicle::fName = v.fName;
	Vehicle::fDestination = v.fDestination;
}

Vehicle& Vehicle::operator= (Vehicle& v) {
	Vehicle::fPosition = v.fPosition;
	Vehicle::fName = v.fName;
	Vehicle::fDestination = v.fDestination;
	return *this;
}

bool Vehicle::setPosition(Point& point) {
	REQUIRE(point.isInitialized(), "The point is not initialized");
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");

	Vehicle::fPosition = point;

	ENSURE(this->fPosition == point, "The position is not set");
	return true;
}

Point* Vehicle::getPosition() {
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");

	return &(Vehicle::fPosition);
}

bool Vehicle::setDestination(Point& point) {
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");
	REQUIRE(point.isInitialized(), "The point is not valid");

	Vehicle::fDestination = point;

	ENSURE(this->fDestination == point, "Destination is not set");
	return true;
}

Point* Vehicle::getDestination() {
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");

	return &(Vehicle::fDestination);
}

bool Vehicle::setName(const std::string& name) {
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");

	Vehicle::fName = name;

	ENSURE(this->fName == name, "The name is not set");
	return true;
}

std::string* Vehicle::getName() {
	REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly");

	return &(Vehicle::fName);
}
