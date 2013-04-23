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
	bool isInitialized() const;
	// check whether the Point is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, const Point& pointobject);
	// REQUIRE(pointobject.isInitialized(), "Point object is initialized");

	friend bool operator== (const Point& p1, const Point& p2);
	//REQUIRE(p1.isInitialized(), "Point is initialized");
	//REQUIRE(p2.isInitialized(), "Point is initialized");

	friend bool operator!= (const Point& p1, const Point& p2);
	// REQUIRE(p1.isInitialized(), "Point is initialized");
	// REQUIRE(p2.isInitialized(), "Point is initialized");

	Point();
	// default constructor
	//ENSURE(this->isInitialized(), "Point is initialized");
	//ENSURE(this->fX == 0, "Default x is 0");
	//ENSURE(this->fY == 0, "Default y is 0");

	Point(const int& x, const int& y);
	// Constructor
	//REQUIRE(x >= 0, "x >= 0");
	//REQUIRE(y >= 0, "y >= 0");
	//ENSURE(this->fX == x, "X is initialized");
	//ENSURE(this->fY == y, "Y is initialized");
	//ENSURE(this->isInitialized(), "Point is initialized");

	Point(const Point& p);
	// copy constructor
	//REQUIRE(p.isInitialized(), "Point is initialized");
	//ENSURE(this->fX == p.fX, "X copied");
	//ENSURE(this->fY == p.fY, "Y copied");
	//ENSURE(this->isInitialized(), "Point is initialized");

	void operator= (const Point& p);
	// copy by assignment
	// REQUIRE(p.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// ENSURE(this->fX == p.fX, "X copied");
	// ENSURE(this->fY == p.fY, "Y copied");

	void setX(const int& x);
	// change the x coordinates only
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// REQUIRE(x >= 0, "x >= 0");
	// ENSURE(this->fX == x, "X is set");

	void setY(const int& y);
	// change the y coordinates only
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// REQUIRE(y >= 0, "y >= 0");
	// ENSURE(this->fY == y, "Y is set");

	void set(const int& x, const int& y);
	// change the x and y coordinates
	// REQUIRE(this->isInitialized(), "Point is initialized");
	// REQUIRE(x >= 0, "x >= 0");
	// REQUIRE(y >= 0, "y >= 0");
	// ENSURE(this->fX == x, "X is set");
	// ENSURE(this->fY == y, "Y is set");

	unsigned int getX() const;
	// get the x coordinate
	// REQUIRE(this->isInitialized(), "Point is initialized");

	unsigned int getY() const;
	// get the y coordinate
	// REQUIRE(this->isInitialized(), "Point is initialized");

private:
	unsigned int fX;
	unsigned int fY;

	Point* fMyself;
};

#endif /* POINT_H_ */
