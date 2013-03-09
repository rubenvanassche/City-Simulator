/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */
#include "Building.h"
#include "DesignByContract.h"
 
bool Building::isInitialized(){
	return this == Building::fMyself;
}

Building::Building(Point& location) : fSize(1) {
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Building::fMyself = this;
	Building::fLocation = location;

	ENSURE(isInitialized(), "The Building object is not initialized properly");
}

Building::Building(Point& location, Size& size) : fSize(1) {
	REQUIRE(location.isInitialized(), "The location is not initialized properly");
	REQUIRE(size.isInitialized(), "The size is not initialized properly");

	Building::fMyself = this;
	Building::fLocation = location;
	Building::fSize = size;

	ENSURE(isInitialized(), "The Building object is not initialized properly");
}

Building::Building(Building& b) : fSize(1) {
	Building::fMyself = this;
	Building::fSize = b.fSize;
	Building::fLocation = b.fLocation;
}

Building& Building::operator= (Building& b) {
	Building::fSize = b.fSize;
	Building::fLocation = b.fLocation;
	return *this;
}

bool Building::setLocation(Point& location){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Building::fLocation = location;

	ENSURE(this->fLocation == location, "The location is not set properly");
	return true;
}

Point* Building::getLocation(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");

	return &(Building::fLocation);
}

bool Building::setSize(Size& size){
	REQUIRE(size.isInitialized(), "The size is not initialized properly");
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");

	Building::fSize = size;

	ENSURE(this->fSize == size, "The size is not set");
	return true;
}


Size* Building::getSize(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	return &(Building::fSize);
}
