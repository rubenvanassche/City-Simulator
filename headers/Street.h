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

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	Street(const Point& startPoint, const Point& endPoint, std::string name);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (startPoint.isInitialized()) && (endPoint.isInitialized()) ), "Points are not valid")
	 * ENSURE(isInitialized(), "The Street object is not initialized properly")
	 */

	bool setEndPoint(const Point& end);
	/*
	 * Set the end of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * REQUIRE(end.isInitialized(), "The endPoint is not valid")
	 * ENSURE(this->fEndPoint == end, "The end is not set")
	 */

	Point getEndPoint() const;
	/*
	 * Get the endpoint of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * ENSURE(this->fEndPoint.isInitialized(), "The returned endpoint is not valid")
	 */

	bool setStartPoint(const Point& start);
	/*
	 * Set the start of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * REQUIRE(start.isInitialized(), "The startpoint is not valid")
	 * ENSURE(this->fStartPoint == end, "The startpoint is not set")
	 */

	Point getStartPoint() const;
	/*
	 * Get the startpoint of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * ENSURE(this->fStartPoint.isInitialized(), "The returned startpoint is not valid")
	 */

	bool setName(const std::string& name);
	/*
	 * Set the name of the street
	 *
	 * REQUIRE(this->isInitialized(), "The Street object is not initialized properly")
	 * ENSURE(this->fName == name, "The name is not set")
	 */

	std::string getName() const;
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
