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
	Vehicle(const Point& cur_pos, const Point& destination, const std::string& name);
	/*
	 * Constructor
	 *
	 * REQUIRE:	Points are valid
	 * ENSURE:	The Vehicle is set properly
	 */

	bool setPosition(const Point& point);
	/*
	 * Set the current position of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * 			The Point is valid
	 * ENSURE:	The Vehicle is set properly
	 */

	Point getPosition() const;
	/*
	 * Get the current position of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * ENSURE:	The given point is valid
	 */

	bool setDestination(const Point& point);
	/*
	 * set the destination of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * 			The Point is valid
	 * ENSURE:	The Vehicle is set properly
	 */

	Point getDestination() const;
	/*
	 * get the destination of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * ENSURE:	The given point is valid
	 */

	bool setName(const std::string& name);
	/*
	 * Set the name of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * ENSURE:	The Vehicle is set properly
	 */

	std::string getName() const;
	/*
	 * Get the name of the vehicle
	 *
	 * REQUIRE:	The Vehicle is set properly
	 * ENSURE:	A string is returned
	 */

private:
	Point fPosition;	// the current position of the vehicle
	Point fDestination;	// the destination of the vehicle
	std::string fName;	// the name of the vehicle
};


#endif /* VEHICLE_H_ */
