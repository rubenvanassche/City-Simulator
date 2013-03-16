/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "DesignByContract.h"
#include "Point.h"
#include "Size.h"

class Building {
public:
	bool isInitialized();

	Building(Point& location, Size& size);
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == location, "Location is set");
	// ENSURE(this->fSize == size, "Size is set");

	Building(Building& b);
	// REQUIRE(b.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is set");
	// ENSURE(this->fSize == b.fSize, "Size is set");

	bool operator= (Building& b);
	// REQUIRE(b.isInitialized(), "Building is initialized");
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is set");
	// ENSURE(this->fSize == b.fSize, "Size is set");

	bool setLocation(Point& location);
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == location, "Locations is set");

	bool setSize(Size& size);
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fSize == size, "Size is set");

	Point& getLocation();
	// REQUIRE(this->isInitialized(), "Building is initialized");

	Size& getSize();
	// REQUIRE(this->isInitialized(), "Building is initialized");

private:
	Size fSize;
	Point fLocation;

	Building* fMyself;
};

#endif /* BUILDING_H_ */
