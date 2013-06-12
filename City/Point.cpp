/*
 * Point.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Point.h"
#include "DesignByContract.h"

bool Point::isInitialized() const {
	return this == Point::fMyself;
}

std::ostream& operator<< (std::ostream& stream, const Point& pointobject) {
	REQUIRE(pointobject.isInitialized(), "Point object is initialized properly");

	stream << "(" << pointobject.fX << ", " << pointobject.fY << ")";
	return stream;
}

bool operator== (const Point& p1, const Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	if ( (p1.fX == p2.fX) && (p1.fY == p2.fY) ) {
		return true;
	}
	return false;
}

bool operator!= (const Point& p1, const Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	if ( (p1.fX == p2.fX) && (p1.fY == p2.fY) ) {
		return false;
	}
	return true;
}

Point::Point() {

	fMyself = this;
	fX = 0;
	fY = 0;

	ENSURE(this->isInitialized(), "Point is initialized");
	ENSURE(this->getX() == 0, "Default x is 0");
	ENSURE(this->getY() == 0, "Default y is 0");
}

Point::Point(const int& x, const int& y) {
	REQUIRE(x >= 0, "x >= 0");
	REQUIRE(y >= 0, "y >= 0");

	fMyself = this;
	fX = x;
	fY = y;

	ENSURE(this->getX() == x, "X is initizialized");
	ENSURE(this->getY() == y, "Y is initialized");
	ENSURE(this->isInitialized(), "Point is initialized");
}

Point::Point(const Point& p) {
	REQUIRE(p.isInitialized(), "Point is initialized");

	fMyself = this;
	fX = p.fX;
	fY = p.fY;

	ENSURE(this->getX() == p.fX, "X copied");
	ENSURE(this->getY() == p.fY, "Y copied");
	ENSURE(this->isInitialized(), "Point is initialized");
}

void Point::operator= (const Point& p) {
	REQUIRE(p.isInitialized(), "Point is initialized");
	REQUIRE(this->isInitialized(), "Point is initialized");

	fX = p.fX;
	fY = p.fY;

	ENSURE(this->getX() == p.fX, "X copied");
	ENSURE(this->getY() == p.fY, "Y copied");
	return;
}


void Point::setX(const int& x) {
	REQUIRE(this->isInitialized(), "Point is initialized");
	REQUIRE(x >= 0, "x >= 0");

	fX = x;

	ENSURE(this->getX() == x, "X is set");
	return;
}

void Point::setY(const int& y) {
	REQUIRE(this->isInitialized(), "Point is initialized");
	REQUIRE(y >= 0, "y >= 0");

	fY = y;

	ENSURE(this->getY() == y, "Y is set");
}

void Point::set(const int& x, const int& y) {
	REQUIRE(this->isInitialized(), "Point is initialized");
	REQUIRE(x >= 0, "x >= 0");
	REQUIRE(y >= 0, "y >= 0");

	fX = x;
	fY = y;

	ENSURE(this->getX() == x, "X is set");
	ENSURE(this->getY() == y, "Y is set");
	return;
}

unsigned int Point::getX() const {
	REQUIRE(this->isInitialized(), "Point is initialized");
	return fX;
}

unsigned int Point::getY() const {
	REQUIRE(this->isInitialized(), "Point is initialized");
	return fY;
}
