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
	// checks whether the object is initialized properly

	Building(Point& location, Size& size, double health);
	// constructor
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Health point is positive");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == location, "Location is set");
	// ENSURE(this->fSize == size, "Size is set");
	// ENSURE(this->fIsBurning == false, "Building is initially not on fire");

	Building(Building& b);
	// copy constructor
	// REQUIRE(b.isInitialized(), "Building is initialized");
	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is copied");
	// ENSURE(this->fSize == b.fSize, "Size is copied");
	// ENSURE(this->fHealth == b.fHealth, "Health is copied");
	// ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");

	bool operator= (Building& b);
	// copy by assignment overloading
	// REQUIRE(b.isInitialized(), "Building is initialized");
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fLocation == b.fLocation, "Location is copied");
	// ENSURE(this->fSize == b.fSize, "Size is copied");
	// ENSURE(this->fHealth == b.fHealth, "Health is copied");
	// ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");

	Point& getLocation();
	// get the location of the building
	// REQUIRE(this->isInitialized(), "Building is initialized");

	Size& getSize();
	// get the size of the building
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool isElement(Point& p);
	// checks whether the point is a part of the building
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	std::vector<Point*> calculatePoints();
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(out.size() > 0, "There are no points given as output");

	bool isBurning();
	// checks whether the building is burning
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool setFire();
	// set the building on fire
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->fHealth > 0, "Health point is positive");
	// ENSURE(this->fIsBurning == true, "Building is set on fire");

	bool burningDown(int substracter=1);
	// substract the house its health by a given value
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(substracter >= 0, "Substracter is positive");
	// REQUIRE(this->fIsBurning, "Building is on fire");

	bool stopFire();
	// stop the fire
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fIsBurning == true, "Building is not on fire anymore");

	double getHealth();
	// get the health points
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool isDead();
	// if health points <= 0
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool setSize(Size& s);
	// set the size
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// ENSURE(this->fSize == s, "Size is set");

	bool setLocation(Point& p);
	// set the location
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// ENSURE(this->fLocation == p, "Location is set");

	bool setHealth(int h);
	// set the health points
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(h >= 0, "Health is positive");
	// ENSURE(this->fHealth == h, "Health is set");

private:
	Size fSize;
	Point fLocation;
	bool fIsBurning;
	double fHealth;

	Building* fMyself;
};

#endif /* BUILDING_H_ */
