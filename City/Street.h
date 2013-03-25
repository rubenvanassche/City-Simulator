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
	bool isInitialized();	// checks whether it's initialized

	friend bool operator== (Street& s, Street& p);
	// compares according to start- and endpoint
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Street is initialized");

	friend std::ostream& operator<< (std::ostream& stream, Street& s);
	// REQUIRE(s.isInitialized(), "Street is initialized");

	friend bool isCrossing(Street& str, Street& astr);
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(astr.isInitialized(), "Street is initialized");

	friend Point* findCrossPoint(Street& str, Street& astr);
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(astr.isInitialized(), "Street is initialized");
	// REQUIRE(isCrossing(str, astr), "Street are not crosssing");

	friend bool isParallel(Street& str, Street& astr);
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(astr.isInitialized(), "Street is initialized");

	Street(std::string& name, Point& start, Point& end);
	// REQUIRE(start.isInitialized(), "Startpoint is initialized");
	// REQUIRE(end.isInitialized(), "Endpoint is initialized");
	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fStartPoint == start, "Startpoint is set");
	// ENSURE(this->fEndPoint == end, "Endpoint is set");
	// ENSURE(this->fName == name, "Name is set");

	~Street();
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->fPoints.empty(), "Points are empty'd");

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

	bool isVertical();
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isHorizontal();
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isElement(Point& p);
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
