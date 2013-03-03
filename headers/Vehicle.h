/*
 * Vehicle.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "Point.h"

class Vehicle {
public:
	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */


	Vehicle(Point& cur_pos, Point& destination, std::string& name);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (cur_pos.isInitialized() ) && (destination.isInitialized()) ), "Points are invalid.")
	 * ENSURE(isInitialized(), "The Vehicle object is not initialized properly")
	 */

	bool setPosition(Point& point);
	/*
	 * Set the current position of the vehicle
	 *
	 * REQUIRE(point.isInitialized(), "The point is not initialized")
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 * ENSURE(this->fPosition == point, "The position is not set")
	 */

	Point getPosition();
	/*
	 * Get the current position of the vehicle
	 *
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 */

	bool setDestination(Point& point);
	/*
	 * set the destination of the vehicle
	 *
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 * REQUIRE(point.isInitialized(), "The point is not valid")
	 * ENSURE(this->fDestination == point, "Destination is not set")
	 */

	Point getDestination();
	/*
	 * get the destination of the vehicle
	 *
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 */

	bool setName(const std::string& name);
	/*
	 * Set the name of the vehicle
	 *
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 * ENSURE(this->fName == name, "The name is not set.")
	 */

	std::string getName();
	/*
	 * Get the name of the vehicle
	 *
	 * REQUIRE(this->isInitialized(), "The Vehicle object is not initialized properly")
	 */

private:
	Point fPosition;	// the current position of the vehicle
	Point fDestination;	// the destination of the vehicle
	std::string fName;	// the name of the vehicle

	Vehicle* fMyself;	// a pointer to myself to check whether I'm initialized properly
};


#endif /* VEHICLE_H_ */
