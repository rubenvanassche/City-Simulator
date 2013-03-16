/*
 * Vehicle.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "DesignByContract.h"
#include "Point.h"

class Vehicle {
public:
	bool isInitialized();

	Vehicle(std::string& name, Point& curPos, Point& destination);
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is initialized");
	// ENSURE(this->fDestination == destination, "Destination is initialized");
	// ENSURE(this->fPosition == curPos, "Position is initialized");

	Vehicle(Vehicle& v);
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is initialized");
	// ENSURE(this->fDestination == v.fDestination, "Destination is initialized");
	// ENSURE(this->fPosition == v.fPosition, "Position is initialized");

	bool operator= (Vehicle& v);
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is initialized");
	// ENSURE(this->fDestination == v.fDestination, "Destination is initialized");
	// ENSURE(this->fPosition == v.fPosition, "Position is initialized");

	bool setPosition(Point& p);
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// ENSURE(this->fPosition == p, "Position is set");

	Point& getPosition();
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setDestination(Point& destination);
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->fDestination == destination, "Destination is set");

	Point& getDestination();
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setName(std::string& name);
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is set");

	std::string& getName();
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

private:
	Point fPosition;
	Point fDestination;
	std::string fName;

	Vehicle* fMyself;
};

#endif /* VEHICLE_H_ */
