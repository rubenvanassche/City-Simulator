/*
 * Building.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Building.h"

bool Building::isInitialized() {
	return Building::fMyself == this;
}

Building::Building(Point& location, Size& size)
	: fSize(size), fLocation(location) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");

	Building::fMyself = this;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == location, "Location is set");
	ENSURE(this->fSize == size, "Size is set");
}

Building::Building(Building& b)
	: fSize(b.fSize), fLocation(b.fLocation) {
	REQUIRE(b.isInitialized(), "Point is initialized");

	Building::fMyself = this;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == b.fLocation, "Location is set");
	ENSURE(this->fSize == b.fSize, "Size is set");
}

bool Building::operator= (Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fLocation = b.fLocation;
	Building::fSize = b.fSize;

	ENSURE(this->fLocation == b.fLocation, "Location is set");
	ENSURE(this->fSize == b.fSize, "Size is set");
	return true;
}

bool Building::setLocation(Point& location) {
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fLocation = location;

	ENSURE(this->fLocation == location, "Location is set");
	return true;
}

bool Building::setSize(Size& size) {
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fSize = size;

	ENSURE(this->fSize == size, "Size is set");
	return true;
}

Point& Building::getLocation() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return Building::fLocation;
}

Size& Building::getSize() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return Building::fSize;
}
