/*
 * Street.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef STREET_H_
#define STREET_H_

#include <iostream>
#include "Point.h"

class Street {
public:
	friend std::ostream& operator<< (std::ostream& stream, Street& objectStreet);
	/*
	 * REQUIRE( objectStreet.isInitialized(), "The Street object is not initialized properly")
	 */

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	Street(Point& startPoint, Point& endPoint, std::string name);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (startPoint.isInitialized()) && (endPoint.isInitialized()) ), "Points are not valid")
	 * ENSURE(isInitialized(), "The Street object is not initialized properly")
	 */

	Street(const Street& s);
	/*
	 * Copy by initializing
	 */

	Street& operator= (const Street& s);
	/*
	 * Copy by assignment
	 */

	bool setEndPoint(Point& end);
	/*
	 * Set the end of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * REQUIRE(end.isInitialized(), "The endPoint is not valid")
	 * ENSURE(this->fEndPoint == end, "The end is not set")
	 */

	Point* getEndPoint();
	/*
	 * Get the endpoint of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 */

	bool setStartPoint(Point& start);
	/*
	 * Set the start of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * REQUIRE(start.isInitialized(), "The startpoint is not valid")
	 * ENSURE(this->fStartPoint == start, "The startpoint is not set")
	 */

	Point* getStartPoint();
	/*
	 * Get the startpoint of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 */

	bool setName(const std::string& name);
	/*
	 * Set the name of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * ENSURE(this->fName == name, "The name is not set")
	 */

	std::string* getName();
	/*
	 * Get the name of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 */

private:
	Point fStartPoint;	// the start of the street
	Point fEndPoint;	// the end of the street
	std::string fName;	// the name of the street

	Street* fMyself;	// a pointer to myself for initialize checking
};


#endif /* STREET_H_ */
