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
	// checks whether the object is initialized properly

	Vehicle(std::string& name, Point& curPos, Point& destination);
	// constructor
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is set");
	// ENSURE(this->fDestination == destination, "Destination is set");
	// ENSURE(this->fPosition == curPos, "Position is set");

	Vehicle(Vehicle& v);
	// copy constructor
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is copied");
	// ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	// ENSURE(this->fPosition == v.fPosition, "Position is copied");

	bool operator= (Vehicle& v);
	// copy assignment operator overloading
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is copied");
	// ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	// ENSURE(this->fPosition == v.fPosition, "Position is copied");

	Point& getPosition();
	// get the current position of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setDestination(Point& destination);
	// change the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->fDestination == destination, "Destination is set");

	Point& getDestination();
	// get the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool isArrived();
	// checks whether the vehicle is arrived
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool isOnWay();
	// checks whether it's on way
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goLeft();
	// go left
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goRight();
	// go right
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goUp();
	// go up
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goDown();
	// go down
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	std::string& getName();
	// get the name of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setName(std::string& name);
	// change the name
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is set");

	bool setPosition(Point& p);
	// change the position
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// ENSURE(this->fPosition == p, "Point is set");

private:
	Point fPosition;
	Point fDestination;
	std::string fName;

	Vehicle* fMyself;
};

#endif /* VEHICLE_H_ */
