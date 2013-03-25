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
#include <vector>

class Building {
public:
	bool isInitialized();

	Building(Point& location, Size& size, double health);
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Health point is positive");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == location, "Location is set");
	// ENSURE(this->fSize == size, "Size is set");

	Building(Building& b);
	// REQUIRE(b.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is set");
	// ENSURE(this->fSize == b.fSize, "Size is set");
	// ENSURE(this->fHealth == b.fHealth, "Health is set");
	// ENSURE(this->fIsBurning == b.fIsBurning, "Burning is set");


	bool operator= (Building& b);
	// REQUIRE(b.isInitialized(), "Building is initialized");
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is set");
	// ENSURE(this->fSize == b.fSize, "Size is set");
	// ENSURE(this->fHealth == b.fHealth, "Health is set");
	// ENSURE(this->fIsBurning == b.fIsBurning, "Burning is set");

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

	bool isElement(Point& p);
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	std::vector<Point*> calculatePoints();
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(out.size() > 0, "There are no points given as output");

	bool isBurning();
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool setFire();
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fIsBurning == true, "Building is set on fire");

	bool stopFire();
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fIsBurning == true, "Building is not on fire anymore");

	double getHealth();
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool burningDown(int substracter=1);
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(substracter >= 0, "Substracter is positive");
	// REQUIRE(this->fIsBurning, "Building is on fire");

	bool isDead();
	// REQUIRE(this->isInitialized(), "Building is initialized");

private:
	Size fSize;
	Point fLocation;
	bool fIsBurning;
	double fHealth;

	Building* fMyself;
};

#endif /* BUILDING_H_ */
