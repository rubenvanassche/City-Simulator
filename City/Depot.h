/*
 * Depot.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#ifndef DEPOT_H_
#define DEPOT_H_

#include "Building.h"
#include "DesignByContract.h"
#include "Vehicle.h"
#include <string>
#include <vector>

class Depot : public Building {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	Depot(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health);
	// constructor
	// REQUIRE(entrance.isInitialized(), "Point is initialized");

	// ENSURE(this->isInitialized(), "Depot is initialized");
	// ENSURE(this->fName == name, "Name is set");
	// ENSURE(this->fEntrance == entrance, "Entrance is set");

	Depot(const Depot& d);
	// copy constructor
	// REQUIRE(d.isInitialized(), "Depot is initialized");

	// ENSURE(this->isInitialized(), "Depot is initialized");
	// ENSURE(this->fName == d.fName, "Name is copied");
	// ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	// ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");

	void operator= (const Depot& d);
	// copy by assignment
	// REQUIRE(d.isInitialized(), "Depot is initialized");
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	// ENSURE(this->fName == d.fName, "Name is copied");
	// ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	// ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");

	void addVehicle(Vehicle* v);
	// add a vehicle
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	// ENSURE(this->fVehicles.back()->getName() == v->getName(), "Vehicle is added");

	unsigned int getNrVehicles() const;
	// gets the total amount of vehicles with this depot as base
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	unsigned int getAvailableVehicles() const;
	// get the amount of vehicles available in the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	std::string getName() const;
	// gets the name of the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");

	Point getEntrance() const;
	// get the entrance of the depot
	// REQUIRE(this->isInitialized(), "Depot is initialized");

private:
	std::vector<Vehicle*> fVehicles;
	std::string fName;
	Point fEntrance;

	Depot* fMyself;
};

#endif /* DEPOT_H_ */
