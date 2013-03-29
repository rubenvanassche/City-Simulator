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

#include "Building.h"
#include "DesignByContract.h"
#include <vector>
#include "FireTruck.h"
#include <iostream>

class FireTruck;

class FireDepot: public Building {
public:
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireDepot& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot(Point& location, Size& size, double health, std::string& name, Point& entrance);
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

	bool operator= (FireDepot& f);
	// copy by assignment operator overloading
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is initialized");
	// ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	// ENSURE(this->fTrucks.size() == f.fTrucks.size(), "Trucks copied");
	// ENSURE(this->getHealth() == f.getHealth(), "Health is copied");

	bool addFireTruck(FireTruck* f);
	// add a firetruck
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fTrucks.back()->getName() == f->getName(), "FireTruck is added");

	unsigned int getNrTrucks();
	// gets the total amount of trucks with this depot as base
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	unsigned int getAvailableTrucks();
	// get the amount of trucks available in the depot
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	std::string& getName();
	// gets the name of the depot
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	Point& getEntrance();
	// get the entrance of the firedepot
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

private:
	std::vector<FireTruck*> fTrucks;
	std::string fName;
	Point fEntrance;

	FireDepot* fMyself;
};

#endif /* FIREDEPOT_H_ */
