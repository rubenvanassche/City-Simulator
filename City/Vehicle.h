/*
 * Vehicle.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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

	Vehicle(const std::string& name, const Point& curPos);
	// constructor
	// REQUIRE(curPos.isInitialized(), "Point is initialized");

	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->getName() == name, "Name is set");
	// ENSURE(this->getDestination() == curPos, "Destination is set");
	// ENSURE(this->getPosition() == curPos, "Position is set");

	Vehicle(const Vehicle& v);
	// copy constructor
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");

	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->getName() == v.getName(), "Name is copied");
	// ENSURE(this->getDestination() == v.getDestination(), "Destination is copied");
	// ENSURE(this->getPosition() == v.getPosition(), "Position is copied");

	void operator= (const Vehicle& v);
	// copy assignment operator overloading
	// REQUIRE(v.isInitialized(), "Vehicle is initialized");
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	// ENSURE(this->isInitialized(), "Vehicle is initialized");
	// ENSURE(this->getName() == v.getName(), "Name is copied");
	// ENSURE(this->getDestination() == v.getDestination(), "Destination is copied");
	// ENSURE(this->getPosition() == v.getPosition(), "Position is copied");

	Point getPosition() const;
	// get the current position of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	Point getDestination() const;
	// get the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	std::string getName() const;
	// get the name of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	void setDestination(const Point& destination);
	// change the destination of the vehicle
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");

	// ENSURE(this->getDestination() == destination, "Destination is set");

	void setPosition(const Point& pos);
	// change the current position of the vehicle (rare use, you should better use the driving functions)
	//REQUIRE(this->isInitialized(), "Vehicle is initialized");
	//REQUIRE(pos.isInitialized(), "Point is initialized");

	//ENSURE(this->getPosition() == pos, "Position is set");

	bool isOnWay() const;
	// checks whether it's on way
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

	void goLeft(const int& units = 1);
	// go left
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(units > 0, "Positive units");
	// REQUIRE(this->getPosition().getX() != 0, "You can not fall of");

	void goRight(const int& units = 1);
	// go right
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(units > 0, "Positive units");

	void goUp(const int& units = 1);
	// go up
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(units > 0, "Positive units");

	void goDown(const int& units = 1);
	// go down
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");
	// REQUIRE(units > 0, "Positive units");
	// REQUIRE(this->getPosition().getY() != 0, "You can not fall of");

	bool isArrived() const;
	// checks whether the vehicle is arrived
	// REQUIRE(this->isInitialized(), "Vehicle is initialized");

private:
	Point fPosition;
	Point fDestination;
	std::string fName;

	Vehicle* fMyself;
};

#endif /* VEHICLE_H_ */
