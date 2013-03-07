/*
 * FireDepot.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef FIREDEPOT_H_
#define FIREDEPOT_H_

#include <iostream>
#include "Point.h"
#include "Size.h"
#include "FireTruck.h"
#include <vector>
#include "Building.h"

class FireDepot : public Building {
public:
	friend std::ostream& operator<< (std::ostream& stream, FireDepot& objectDepot);

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	FireDepot::FireDepot(const std::string& name, const Point& entrance, const Point& location);
	/*
	 * Constructor
	 *
	 * REQUIRE(entrance.isInitialized(), "The entrance location is not initialized properly")
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * ENSURE(isInitialized(), "The FireDepot object is not initialized properly")
	 */

	bool addFireTruck(const FireTruck& truck);
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
	 * ENSURE(this->fTrucks.size >= 0, "The returned value is not valid")
	 */

	std::string getName();
	/*
	 * Get the name of the depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 */

	Point getEntrance();
	/*
	 * Get the entrance of the fire depot
	 *
	 * REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly")
	 * ENSURE(this->fEntrance.isInitialized(), "The Point object is not valid")
	 */

private:
	std::vector<FireTruck> fTrucks;	// the vector of FireTrucks in depot
	std::string fName;	// the name of the depot
	Point fEntrance;	// the entrance of the depot

	FireDepot* fMyself;	// a pointer to myself to check if I'm initialized properly
};


#endif /* FIREDEPOT_H_ */
