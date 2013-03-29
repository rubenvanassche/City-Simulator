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
#include <vector>
#include <algorithm>

class Street {
public:
	bool isInitialized();
	// checks whether it's initialized

	friend bool operator== (Street& s, Street& p);
	// compares according to start- and endpoint
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Street is initialized");

	friend std::ostream& operator<< (std::ostream& stream, Street& s);
	// output operator overloading
	// REQUIRE(s.isInitialized(), "Street is initialized");

	friend bool isCrossing(Street& str, Street& astr);
	// checks whether the streets are crossing
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(astr.isInitialized(), "Street is initialized");

	friend bool isParallel(Street& str, Street& astr);
	// checks whether the streets are parallel
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(astr.isInitialized(), "Street is initialized");

	friend Point* getCrosspoint(Street& destStr, Street& curStr);
	// find the crosspoint of the given street
	// REQUIRE(desStr.isInitialized(), "Street is initialized");
	// REQUIRE(curStr.isInitialized(), "Street is initialized");

	Street(std::string& name, Point& start, Point& end);
	// constructor
	// REQUIRE(start.isInitialized(), "Startpoint is initialized");
	// REQUIRE(end.isInitialized(), "Endpoint is initialized");
	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fStartPoint == start, "Startpoint is set");
	// ENSURE(this->fEndPoint == end, "Endpoint is set");
	// ENSURE(this->fName == name, "Name is set");

	~Street();
	// destructor
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fPoints.empty(), "Points are empty'd");

	Street(Street& s);
	// copy constructor
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	// ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	// ENSURE(this->fName == s.fName, "Name is copied");
	// ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");

	bool operator= (Street& s);
	// copy by assignment
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	// ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	// ENSURE(this->fName == s.fName, "Name is copied");
	// ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");

	Point& getStartPoint();
	// get the startpoint of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	Point& getEndPoint();
	// get the endpoint of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	std::string& getName();
	// get the name of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isVertical();
	// checks whether the street is horizontal
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isHorizontal();
	// checks whether the street is vertical
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isElement(Point& p);
	// checks whether the given point is a part of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	std::vector<Point*> calculatePoints();
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(out.size() > 0, "There are no points given as output");

private:
	Point fStartPoint;
	Point fEndPoint;
	std::string fName;
	std::vector<Point*> fPoints;

	Street* fMyself;
};

#endif /* STREET_H_ */
