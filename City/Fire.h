/*
 * Fire.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef FIRE_H_
#define FIRE_H_

#include <iostream>
#include "Point.h"
#include "Size.h"
#include <vector>
#include "Building.h"
#include "Vehicle.h"

class FireTruck;

class FireDepot : public Building {
public:
	friend std::ostream& operator<< (std::ostream& stream, FireDepot& objectDepot);

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	FireDepot(std::string& name, Point& entrance, Point& location);
	/*
	 * Constructor
	 *
	 * REQUIRE(entrance.isInitialized(), "The entrance location is not initialized properly")
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * ENSURE(isInitialized(), "The FireDepot object is not initialized properly")
	 */

	bool addFireTruck(FireTruck& truck);
	/*
	 * Add a firetruck to a fire depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 * REQUIRE(truck.isInitialized(), "The Truck object is not initialized properly")
	 * ENSURE(this->fTrucks.back().getName() == truck.getName(), "The FireTruck is not added")
	 */

	 int getNrTrucks();
	/*
	 * Get the amount of FireTrucks in the depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 */

	std::string* getName();
	/*
	 * Get the name of the depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 */

	Point* getEntrance();
	/*
	 * Get the entrance of the fire depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 */

private:
	std::vector<FireTruck> fTrucks;	// the vector of FireTrucks in depot
	std::string fName;	// the name of the depot
	Point fEntrance;	// the entrance of the depot

	FireDepot* fMyself;	// a pointer to myself to check if I'm initialized properly
};

class FireTruck : public Vehicle {
public:
	friend std::ostream& operator<< (std::ostream& stream, FireTruck& firetruck);

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	FireTruck(Point& cur_pos, Point& destination, std::string& name, FireDepot* base=NULL);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist")
	 * ENSURE(isInitialized(), "The FireTruck is not initialized properly")
	 */

	bool setBase(FireDepot* base);
	/*
	 * Set the base of the firetruck
	 *
	 * REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly")
	 * REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist")
	 * ENSURE(this->fBase == base, "The base is not set")
	 */

	FireDepot* getBase();
	/*
	 * Get the reference to his base
	 *
	 * REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly")
	 */

private:
	FireDepot* fBase;	// The base of the FireTruck

	FireTruck* fMyself;	// a pointer to myself for initialize check
};


#endif /* FIRE_H_ */
