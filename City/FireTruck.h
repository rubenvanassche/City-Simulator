/*
 * FireTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#ifndef FIRETRUCK_H_
#define FIRETRUCK_H_

#include "DesignByContract.h"
#include <iostream>
#include "Building.h"
#include "Vehicle.h"
#include "FireDepot.h"

class FireTruck: public Vehicle {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireTruck& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");

	FireTruck(const std::string& name, FireDepot* base);
	// constructor
	// REQUIRE(base->isInitialized(), "FireDepot is initialized");

	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->fBase == base, "Base is set");
	// ENSURE(this->isInDepot(), "FireTruck is in depot");
	// ENSURE(this->fBuilding == NULL, "FireTruck doesn't have building (yet)" );

	FireTruck(const FireTruck& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");

	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	void operator= (const FireTruck& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	FireDepot* getBase() const;
	// get it's base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	// ENSURE(this->fBase != NULL, "There must be an existing base");

	Building* getBuilding() const;
	// get the building that the FireTruck has to go
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	bool isInDepot() const;
	// Checks whether the FireTruck is in the depot now
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	void send(Building* building, const Point& destination);
	// send the FireTruck to the building that is on fire
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(building->isBurning(), "Building is on fire");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInDepot(), "FireTruck is in depot");

	// ENSURE(this->fBuilding == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->isAtEntranceDepot(), "FireTruck is at the entrance of it's base");

	void sendBack();
	// send the FireTruck back to it's base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->fBuilding->isBurning() == false, "Building is not on fire anymore");

	// ENSURE(this->fBuilding == NULL, "FireTruck has not a building to extinguish anymore");
	// ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to the base's entrance");

	bool isAtEntranceDepot() const;
	// checks whether the FireTruck is at the entrance of its base
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	void enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->isAtEntranceDepot(), "FireTruck is at entrance of it's base");
	// REQUIRE(this->fBase->isBurning() == false, "The base is not on fire");
	// REQUIRE(this->fBase->isDead() == false, "The base is not burnt down");

	// ENSURE(this->isInDepot(), "FireTruck is now in depot");

	char getSymbol() const;
	// for graphical impression
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

private:
	Building* fBuilding;
	FireDepot* fBase;

	FireTruck* fMyself;
};

#endif /* FIRETRUCK_H_ */
