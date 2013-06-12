/*
 * Street.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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
	bool isInitialized() const;
	// checks whether it's initialized

	friend bool operator== (const Street& s, const Street& p);
	// compares according to start- and endpoint
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Street is initialized");

	friend std::ostream& operator<< (std::ostream& stream, const Street& s);
	// output operator overloading
	// REQUIRE(s.isInitialized(), "Street is initialized");

	Street(const std::string& name, const Point& start, const Point& end);
	// constructor
	// REQUIRE(start.isInitialized(), "Startpoint is initialized");
	// REQUIRE(end.isInitialized(), "Endpoint is initialized");

	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->getStartPoint() == start, "Startpoint is set");
	// ENSURE(this->getEndPoint() == end, "Endpoint is set");
	// ENSURE(this->getName() == name, "Name is set");

	Street(const Street& s);
	// copy constructor
	// REQUIRE(s.isInitialized(), "Street is initialized");

	// ENSURE(this->isInitialized(), "Street is initialized");
	// ENSURE(this->getEndPoint() == s.getEndPoint(), "Endpoint is copied");
	// ENSURE(this->getStartPoint() == s.getStartPoint(), "Startpoint is copied");
	// ENSURE(this->getName() == s.getName(), "Name is copied");

	void operator= (const Street& s);
	// copy by assignment
	// REQUIRE(s.isInitialized(), "Street is initialized");
	// REQUIRE(this->isInitialized(), "Street is initialized");

	// ENSURE(this->getEndPoint() == s.getEndPoint(), "Endpoint is copied");
	// ENSURE(this->getStartPoint() == s.getStartPoint(), "Startpoint is copied");
	// ENSURE(this->getName() == s.getName(), "Name is copied");

	Point getStartPoint() const;
	// get the startpoint of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	Point getEndPoint() const;
	// get the endpoint of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	std::string getName() const;
	// get the name of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isVertical() const;
	// checks whether the street is horizontal
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isHorizontal() const;
	// checks whether the street is vertical
	// REQUIRE(this->isInitialized(), "Street is initialized");

	bool isElement(const Point& p);
	// checks whether the given point is a part of the street
	// REQUIRE(this->isInitialized(), "Street is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// REQUIRE((this->isVertical()) || (this->isHorizontal()), "Street is horizontal or vertical");

	bool isCrossing(Street& str);
	// checks whether the streets are crossing
	// REQUIRE(str.isInitialized(), "Street is initialized");

	bool isParallel(const Street& str);
	// checks whether the streets are parallel
	// REQUIRE(str.isInitialized(), "Street is initialized");

	Point getCrosspoint(Street& str);
	// find the crosspoint of the given street
	// REQUIRE(str.isInitialized(), "Street is initialized");
	// REQUIRE(this->isCrossing(str), "Streets are crossing);

	char getSymbol() const;
	// Returns the symbol of this instance in the city to be used with the graphical impression
	// REQUIRE(this->isInitialized(), "Street is initialized");

	std::vector<Point> calculatePoints();
	// todo: what is this?
	// REQUIRE(this->isInitialized(), "Street is initialized");

	// ENSURE(out.size() > 0, "There are no points given as output");

private:
	Point fStartPoint;
	Point fEndPoint;
	std::string fName;

	Street* fMyself;
};

#endif /* STREET_H_ */
