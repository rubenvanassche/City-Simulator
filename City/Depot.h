/*
 * Depot.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#ifndef DEPOT_H_
#define DEPOT_H_

#include "Building.h"
#include "Point.h"
#include "Size.h"
#include "DesignByContract.h"
#include "Vehicle.h"
#include <String>

class Depot : public Building {
public:
	Depot(Point& location, Point& entrance, Size& size, std::string name, double health);

	Depot(Depot& d);

	bool operator= (Depot& d);

	bool isInitialized();
	// checks whether the object is initialized properly

	bool addVehicle(Vehicle* v);
	// add a vehicle
	// REQUIRE(this->isInitialized(), "Depot is initialized");
	// ENSURE(this->fTrucks.back()->getName() == f->getName(), "FireTruck is added");

	unsigned int getNrVehicles();
	// gets the total amount of vehicles with this depot as base
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	unsigned int getAvailableVehicles();
	// get the amount of vehicles available in the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	std::string& getName();
	// gets the name of the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	Point& getEntrance();
	// get the entrance of the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");
private:
	std::vector<Vehicle*> fVehicles;
	std::string fName;
	Point fEntrance;

	Depot* fMyself;
};

#endif /* DEPOT_H_ */
