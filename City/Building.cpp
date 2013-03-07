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

Building::Building(Point& location){
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Building::fLocation = location;
	Building::fSize = Size(1);

	ENSURE(isInitialized(), "The Building object is not initialized properly");
}


Building::Building(Point& location, Size& size){
	REQUIRE(location.isInitialized(), "The location is not initialized properly");
	REQUIRE(size.isInitialized(), "The size is not initialized properly");

	Building::fLocation = location;
	Building::fSize = size;

	ENSURE(isInitialized(), "The Building object is not initialized properly");
}


bool Building::setLocation(Point& location){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Building::fLocation = location;

	ENSURE(this->fLocation == location, "The location is not set properly");
}

Point Building::getLocation(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	ENSURE(this->fLocation.isInitialized(), "The returned location is invalid");

	return fLocation;
}

bool Building::setSize(Size& size){
	REQUIRE(size.isInitialized(), "The size is not initialized properly");
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");

	Building::fSize = size;

	ENSURE(this->fSize == size, "The size is not set");
}


Size Building::getSize(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	ENSURE(this->fSize.isInitialized(), "The returned size is invalid");

	return fSize;
}


