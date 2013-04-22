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
	bool isInitialized() const;
	// checks whether the object is initialized properly

	Vehicle(const std::string& name, const Point& curPos, const Point& destination);
	// constructor
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is set");
	// ENSURE(this->fDestination == destination, "Destination is set");
	// ENSURE(this->fPosition == curPos, "Position is set");

	Vehicle(const Vehicle& v);
	// copy constructor
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is copied");
	// ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	// ENSURE(this->fPosition == v.fPosition, "Position is copied");

	bool operator= (const Vehicle& v);
	// copy assignment operator overloading
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == v.fName, "Name is copied");
	// ENSURE(this->fDestination == v.fDestination, "Destination is copied");
	// ENSURE(this->fPosition == v.fPosition, "Position is copied");

	Point getPosition() const;
	// get the current position of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setDestination(const Point& destination);
	// change the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->fDestination == destination, "Destination is set");

	Point getDestination() const;
	// get the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	std::string getName() const;
	// get the name of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool setName(const std::string& name);
	// change the name
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->fName == name, "Name is set");

	bool isArrived() const;
	// checks whether the vehicle is arrived
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool isOnWay() const;
	// checks whether it's on way
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goLeft();
	// go left
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(this->fPosition.getX() != 0, "You can not fall of");

	bool goRight();
	// go right
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goUp();
	// go up
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	bool goDown();
	// go down
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	//REQUIRE(this->fPosition.getY() != 0, "You can not fall of");

private:
	Point fPosition;
	Point fDestination;
	std::string fName;

	Vehicle* fMyself;
};

#endif /* VEHICLE_H_ */
