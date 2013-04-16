/*
 * PoliceDepot.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#ifndef POLICEDEPOT_H_
#define POLICEDEPOT_H_

#include "Depot.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>

class PoliceDepot: public Depot {
public:
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, PoliceDepot& p);
	// output operator overloading
	// REQUIRE(p.isInitialized(), "PoliceDepot is initialized");

	PoliceDepot(Point& location, Point& entrance, Size& size, std::string name, double health);
	// constructor
	// REQUIRE(health >= 0, "Health is positive");
	// REQUIRE(location.isInitialized(), "Point is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(entrance.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");
	// ENSURE(this->fName == name, "Name is set");
	// ENSURE(this->getLocation() == location, "Location is set");
	// ENSURE(this->getSize() == size, "Size is set");
	// ENSURE(this->fEntrance == entrance, "Entrance is set");
	// ENSURE(this->getHealth() == health, "Health is set");

	PoliceDepot(PoliceDepot& p);
	// copy constructor
	// REQUIRE(p.isInitialized(), "PoliceDepot is initialized");
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");
	// ENSURE(this->fName == f.fName, "Name is copied");
	// ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	// ENSURE(this->getSize() == f.getSize(), "Size is copied");
	// ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	// ENSURE(this->fTrucks.size() == f.fTrucks.size(), "Trucks copied");
	// ENSURE(this->getHealth() == f.getHealth(), "Health is copied");

private:
	PoliceDepot* fMyself;
};

#endif /* POLICEDEPOT_H_ */
