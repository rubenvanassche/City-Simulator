/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "Point.h"
#include "Size.h"

class Building {
public:
	bool isInitialized();
	/*
	 * Checks if i'm initialized properly
	 */

	Building(Point& location);
	/*
	 * Create a new building
	 *
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * ENSURE(isInitialized(), "The Building object is not initialized properly")
	 */

	Building(Point& location, Size& size);
	/*
	 * Create a new building
	 *
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * REQUIRE(size.isInitialized(), "The size is not initialized properly")
	 * ENSURE(isInitialized(), "The Building object is not initialized properly")
	 */

	bool setLocation(Point& location);
	/*
	 * Set the location of the building
	 *
	 * REQUIRE(this->isInitialized(), "The Building object is not initialized properly")
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * ENSURE(this->fLocation == location, "The location is not set properly")
	 */

	Point getLocation();
	/*
	 * Returns a the location
	 *
	 * REQUIRE(this->isInitialized(), "The Building object is not initialized properly")
	 * ENSURE(this->fLocation.isInitialized(), "The returned location is invalid")
	 */

	bool setSize(Size& size);
	/*
	 * Set the size of the building
	 *
	 * REQUIRE(size.isInitialized(), "The size is not initialized properly")
	 * REQUIRE(this->isInitialized(), "The Building object is not initialized properly")
	 * ENSURE(this->fSize == size, "The size is not set")
	 */

	Size getSize();
	/*
	 * Get the size of the building
	 *
	 * REQUIRE(this->isInitialized(), "The Building object is not initialized properly")
	 * ENSURE(this->fSize.isInitialized(), "The returned size is invalid")
	 */

private:
	Size fSize;	// the size of the building
	Point fLocation;	// the location of the building

	Building* fMyself;	// a pointer to myself to check if I'm initialized properly
};


#endif /* BUILDING_H_ */
