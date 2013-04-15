/*
 * FireTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef FIRETRUCK_H_
#define FIRETRUCK_H_

#include "Vehicle.h"
#include "DesignByContract.h"
#include <iostream>
#include "Building.h"
#include "FireDepot.h"

class FireDepot;

class FireTruck: public Vehicle {
public:
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireTruck& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");

	FireTruck(std::string& name, FireDepot* base);
	// constructor
	// REQUIRE(base->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == name, "Name is set");
	// ENSURE(this->getPosition() == curPos, "Position is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->fBase == base, "Base is set");

	FireTruck(FireTruck& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == f.getName(), "Name is copied");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	bool operator= (FireTruck& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == f.getName(), "Name is copied");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	bool isAtEntranceDepot();
	// checks whether the firetruck is at the entrance of its base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	bool enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at entrance");
	// ENSURE(this->getPosition() == this->fBase->getLocation(), "FireTruck is now in depot");
	// ENSURE(this->getDestination() == this->fBase->getLocation(), "FireTruck is now in depot");

	bool isInDepot();
	// checks whether the truck is in the depot now
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	FireDepot* getBase();
	// get the firetruck its base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	bool send(Building* building, Point& destination);
	// send the truck to the building that's on fire
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->fBuilding == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->getPosition() == this->fBase->getEntrance(), "FireTruck is at the entrance");

	Building* getBuilding();
	// get the building that the firetruck has to extinguish
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	bool sendBack();
	// send the truck back to it's base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->fBuilding == NULL, "FireTruck has not a building to extinguish anymore");
	// ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");

private:
	Building* fBuilding;	// a pointer to a building the truck has to extinguish
	FireDepot* fBase;	// a pointer to its base

	FireTruck* fMyself;
};

#endif /* FIRETRUCK_H_ */
