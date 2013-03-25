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
#include "House.h"

class FireDepot: public Building {
public:
	bool isInitialized();

	friend std::ostream& operator<< (std::ostream& stream, FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot(std::string& name, Point& location, Size& size, Point& entrance, double health);
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(entrance.isInitialized(), "Point is initialized");
	// REQUIRE(health >= 0, "Health is positive");
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
	// ENSURE(this->fTrucks[index]->getName() == f.fTrucks[index]->getName(), "Vector is copied");

	bool operator= (FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is initialized");
	// ENSURE(this->getLocation() == f.getLocation, "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	// ENSURE(this->fTrucks[index]->getName() == f.fTrucks[index]->getName(), "Vector is copied");

	bool addFireTruck(FireTruck& f);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fTrucks.back()->getName() == f.getName(), "FireTruck is added");

	std::string& getName();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	Point& getEntrance();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	~FireDepot();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->fTrucks.empty(), "No trucks in depot")

	unsigned int getNrTrucks();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	unsigned int getAvailableTrucks();
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");

	bool extinguish();

	bool updateTrucks();


	bool sendTruck(Point& location, Building* house);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// REQUIRE(location.isInitialized(), "Point is initialized");

	bool alreadySend(Point& location);
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// REQUIRE(location.isInitialized(), "Point is initialized");

private:
	std::vector<FireTruck*> fTrucks;
	std::string fName;
	Point fEntrance;

	FireDepot* fMyself;
};

#endif /* FIREDEPOT_H_ */
