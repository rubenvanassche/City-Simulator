/*
 * FireDepot.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef FIREDEPOT_H_
#define FIREDEPOT_H_

#include "Depot.h"
#include "DesignByContract.h"
#include <vector>
#include "FireTruck.h"
#include <iostream>


class FireDepot: public Depot {
public:
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireDepot& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot(Point& location, Point& entrance, Size& size, std::string name, double health);
	// constructor
	// REQUIRE(health >= 0, "Health is positive");
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(entrance.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == name, "Name is set");
	// ENSURE(this->getLocation() == location, "Location is set");
	// ENSURE(this->getSize() == size, "Size is set");
	// ENSURE(this->fEntrance == entrance, "Entrance is set");
	// ENSURE(this->getHealth() == health, "Health is set");

	FireDepot(FireDepot& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is copied");
	// ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	// ENSURE(this->fTrucks.size() == f.fTrucks.size(), "Trucks copied");
	// ENSURE(this->getHealth() == f.getHealth(), "Health is copied");


private:
	FireDepot* fMyself;
};

#endif /* FIREDEPOT_H_ */
