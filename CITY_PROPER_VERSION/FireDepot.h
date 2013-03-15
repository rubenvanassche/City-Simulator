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

class FireDepot: public Building {
public:
	bool isInitialized();

	friend std::ostream& operator<< (std::ostream& stream, FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot(std::string& name, Point& location, Size& size, Point& entrance);
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(entrance.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == name, "Name is initialized");
	// ENSURE(this->getLocation() == location, "Location is initialized");
	// ENSURE(this->getSize() == size, "Size is initialized");
	// ENSURE(this->fEntrance == entrance, "Entrance is initialized");

	FireDepot(FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is initialized");
	// ENSURE(this->getLocation() == f.getLocation, "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");

	bool operator= (FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is initialized");
	// ENSURE(this->getLocation() == f.getLocation, "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");

	bool addFireTruck(FireTruck& f);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fTrucks.back().getName() == f.getName(), "FireTruck is added");

	std::string& getAvailableTruck();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	bool popTruck();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	unsigned int getNrTrucks();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	std::string& getName();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	bool setName(std::string& name);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == name, "Name is set")

	Point& getEntrance();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	bool setEntrance(Point& entrance);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// REQUIRE(entrance.isInitialized(), "Point is initialized");
	// ENSURE(this->fEntrance == entrance, "Entrance is set");

private:
	std::vector<std::string> fTrucks;
	std::string fName;
	Point fEntrance;

	FireDepot* fMyself;
};

#endif /* FIREDEPOT_H_ */
