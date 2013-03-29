/*
 * Point.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef POINT_H_
#define POINT_H_

#include "DesignByContract.h"
#include <iostream>

class Point {
public:
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Point& pointobject);
	// write the coordinates to the output
	// 	REQUIRE(pointobject.isInitialized(), "Point is initialized");

	friend bool operator== (Point& p1, Point& p2);
	// is equal operator overloading
	// REQUIRE(p1.isInitialized(), "Point is initialized");
	// REQUIRE(p2.isInitialized(), "Point is initialized");

	friend bool operator!= (Point& p1, Point& p2);
	// is not equal operator overloading
	// REQUIRE(p1.isInitialized(), "Point is initialized");
	// REQUIRE(p2.isInitialized(), "Point is initialized");

	Point(int x, int y);
	// Constructor
	// REQUIRE(x >= 0, "x >= 0");
	// REQUIRE(y >= 0, "y >= 0");
	// ENSURE(this->fX == x, "X is set");
	// ENSURE(this->fY == y, "Y is set");
	// ENSURE(this->isInitialized(), "Point is initialized");

	Point(Point& p);
	// copy constructor
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// ENSURE(this->fX == p.fX, "X copied");
	// ENSURE(this->fY == p.fY, "Y copied");
	// ENSURE(this->isInitialized(), "Point is initialized");

	bool operator= (Point& p);
	// copy by assignment
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// ENSURE(this->fX == p.fX, "X copied");
	// ENSURE(this->fY == p.fY, "Y copied");

	bool set(int x, int y);
	// change the coordinates
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// REQUIRE(x >= 0, "x >= 0");
	// REQUIRE(y >= 0, "y >= 0");
	// ENSURE(this->fX == x, "X is set");
	// ENSURE(this->fY == y, "Y is set");

	unsigned int getX();
	// get the x-coordinate
	// REQUIRE(this->isInitialized(), "Point is initialized");

	unsigned int getY();
	// get the y-coordinate
	// REQUIRE(this->isInitialized(), "Point is initialized");

private:
	unsigned int fX;
	unsigned int fY;

	Point* fMyself;
};

#endif /* POINT_H_ */
