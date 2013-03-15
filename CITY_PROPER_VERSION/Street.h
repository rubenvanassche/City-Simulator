/*
 * Street.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef STREET_H_
#define STREET_H_

#include "Point.h"
#include "DesignByContract.h"
#include <iostream>

class Street {
public:
	bool isInitialized();

	friend std::ostream& operator<< (std::ostream& stream, Street& s);
	// REQUIRE(s.isInitialized(), "Street is initialized");

	Street(std::string& name, Point& start, Point& end);
	// REQUIRE(start.isInitialized(), "Startpoint is initialized");
	// REQUIRE(end.isInitialized(), "Endpoint is initialized");
	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fStartPoint == start, "Startpoint is set");
	// ENSURE(this->fEndPoint == end, "Endpoint is set");
	// ENSURE(this->fName == name, "Name is set");

	Street(Street& s);
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is set");
	// ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is set");
	// ENSURE(this->fName == s.fName, "Name is set");


	bool operator= (Street& s);
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is set");
	// ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is set");
	// ENSURE(this->fName == s.fName, "Name is set");

	bool setStartPoint(Point& start);
	// REQUIRE(start.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fStartPoint == start, "Startpoint is set");

	bool setEndPoint(Point& end);
	// REQUIRE(end.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fEndPoint == end, "Endpoint is set");

	bool setName(std::string& name);
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fName == name, "Name is set");

	Point& getStartPoint();
	// REQUIRE(this->isInitialized(), "Street is initialized");

	Point& getEndPoint();
	// REQUIRE(this->isInitialized(), "Street is initialized");

	std::string& getName();
	// REQUIRE(this->isInitialized(), "Street is initialized");

private:
	Point fStartPoint;
	Point fEndPoint;
	std::string fName;

	Street* fMyself;
};

#endif /* STREET_H_ */
