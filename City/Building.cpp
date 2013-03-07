/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */
#include "Building.h"
bool Building::isInitialized(){
	return this == Building::fMyself;
}

Building::Building(const Point& location, const Size& size){
	REQUIRE(location.isInitialized(), "The location is not initialized properly");
	REQUIRE(size.isInitialized(), "The size is not initialized properly");

	fLocation = location;
	fSize = size;

	ENSURE(isInitialized(), "The Building object is not initialized properly");
}


bool Building::setLocation(const Point& location){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	fLocation = location;

	ENSURE(this->fLocation == location, "The location is not set properly");
}

Point Building::getLocation(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	ENSURE(this->fLocation.isInitialized(), "The returned location is invalid");

	return fLocation;
}

bool Building::setSize(const Size& size){
	REQUIRE(size.isInitialized(), "The size is not initialized properly");
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");

	fSize = size;

	ENSURE(this->fSize == size, "The size is not set");
}


Size Building::getSize(){
	REQUIRE(this->isInitialized(), "The Building object is not initialized properly");
	ENSURE(this->fSize.isInitialized(), "The returned size is invalid");

	return fSize;
}



