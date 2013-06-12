/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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
	bool isInitialized() const;
	// check whether the object is initialized properly

	Building(const Point& location, const Size& size, const double& health, const double& reducer);
	// constructor
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Health point is positive");
	// REQUIRE(reducer >= 0, "reducer point is positive");

	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->getLocation() == location, "Location is set");
	// ENSURE(this->getSize() == size, "Size is set");
	// ENSURE(this->isBurning() == false, "Building is initially not on fire");
	// ENSURE(this->getHealth() == health, "Health is set");
	// ENSURE(this->isFireTruckAssigned() == false, "There is no FireTruck assigned (yet)");

	Building(const Building& b);
	// copy constructor
	// REQUIRE(b.isInitialized(), "Building is initialized");

	// ENSURE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->getLocation() == b.getLocation(), "Location is copied");
	// ENSURE(this->getSize() == b.getSize(), "Size is copied");
	// ENSURE(this->getHealth() == b.getHealth(), "Health is copied");
	// ENSURE(this->isBurning() == b.isBurning(), "Burning is copied");
	// ENSURE(this->isFireTruckAssigned() == b.isFireTruckAssigned(), "FireTruckAssigned is copied");

	void operator= (const Building& b);
	// copy by assignment overloading
	// REQUIRE(b.isInitialized(), "Building is initialized");
	// REQUIRE(this->isInitialized(), "Building is initialized");

	// ENSURE(this->getLocation() == b.getLocation(), "Location is copied");
	// ENSURE(this->getSize() == b.getSize(), "Size is copied");
	// ENSURE(this->getHealth() == b.getHealth(), "Health is copied");
	// ENSURE(this->isBurning() == b.isBurning(), "Burning is copied");
	// ENSURE(this->isFireTruckAssigned() == b.isFireTruckAssigned(), "FireTruckAssigned is copied");

	Point getLocation() const;
	// get the location of the building
	// REQUIRE(this->isInitialized(), "Building is initialized");

	Size getSize() const;
	// get the size of the building
	// REQUIRE(this->isInitialized(), "Building is initialized");

	double getHealth() const;
	// get the health points
	// REQUIRE(this->isInitialized(), "Building is initialized");

	void setFire();
	// set the building on fire
	// REQUIRE(this->isInitialized(), "Building is initialized");

	// ENSURE(this->isBurning() == true, "Building is set on fire");

	bool isBurning() const;
	// checks whether the building is burning
	// REQUIRE(this->isInitialized(), "Building is initialized");

	void burningDown();
	// substract the building its health by a predefined value (fReducer);
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->isBurning(), "Building is on fire");

	void stopFire();
	// stop the fire
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->isBurning() == true, "Building is on fire");

	// ENSURE(this->isBurning() == false, "Building is not on fire anymore");

	bool isDead() const;
	// if health points <= 0
	// REQUIRE(this->isInitialized(), "Building is initialized");

	bool startSpreadingFire() const;
	// checks whether you may spread the fire
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->fHealthNormal >= this->getHealth(), "Health points are valid");

	bool startRepair() const;
	// checks whether you may repair the building
	// REQUIRE(this->isInitialized(), "Building is initialized");

	void repair();
	// raises the health level with 0.5
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->startRepair(), "You may repair that building");

	bool isFireTruckAssigned() const;
	// checks whether a firetruck is assigned to this building (that's on fire);
	// REQUIRE(this->isInitialized(), "Building is initialized");

	void assignFireTruck();
	// call this function when a firetruck is assigned
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->isBurning(), "The building is on fire");
	// REQUIRE(this->fFireTrucksAssigned == false, "There's not already a firetruck assigned");

	// ENSURE(this->isFireTruckAssigned() == true, "A firetruck is assigned to the building");

	void withdrawFireTruckAssignment();
	// call this function when a firetruck is send back to the depot
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// REQUIRE(this->isBurning() == false, "The Building is not on fire anymore");
	// REQUIRE(this->isFireTruckAssigned() == true, "There is a firetruck assigned previously");

	// ENSURE(this->isFireTruckAssigned() == false, "A firetruck is withdrawed from the building");

	std::vector<Point> calculatePoints();
	// todo: what is this?
	// REQUIRE(this->isInitialized(), "Building is initialized");

	// ENSURE(out.size() > 0, "There are no points given as output");

	std::vector<Point> calculateSurroundingPoints();
	// Calculate the points surrounded by this building
	// REQUIRE(this->isInitialized(), "Building is initialized");

private:
	Size fSize;
	Point fLocation;
	bool fIsBurning;
	double fHealth;
	double fHealthNormal;
	double fReducer;
	bool fFireTruckAssigned;

	Building* fMyself;
};

#endif /* BUILDING_H_ */
