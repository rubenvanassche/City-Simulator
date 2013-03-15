/*
 * Point.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Point.h"

bool Point::isInitialized() {
	return this == Point::fMyself;
}

std::ostream& operator<< (std::ostream& stream, Point& pointobject) {
	REQUIRE(pointobject.isInitialized(), "Point object is initialized properly");

	stream << "(" << pointobject.fX << ", " << pointobject.fY << ")" << std::endl;
	return stream;
}

bool operator== (Point& p1, Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	if ( (p1.fX == p2.fX) && (p1.fY == p2.fY) ) {
		return true;
	}
	return false;
}

bool operator!= (Point& p1, Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	if ( (p1.fX == p2.fX) && (p1.fY == p2.fY) ) {
		return false;
	}
	return true;
}

Point operator+ (Point& p1, Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	int x = p1.fX + p2.fX;
	int y = p1.fY + p2.fY;

	Point p(x, y);
	return p;
}

Point operator- (Point& p1, Point& p2) {
	REQUIRE(p1.isInitialized(), "Point is initialized");
	REQUIRE(p2.isInitialized(), "Point is initialized");

	int x = p1.fX - p2.fX;
	int y = p1.fY - p2.fY;

	Point p(x, y);
	return p;
}

Point::Point(int& x, int& y) {
	REQUIRE(x >= 0, "x >= 0");
	REQUIRE(y >= 0, "y >= 0");

	Point::fMyself = this;
	Point::fX = x;
	Point::fY = y;

	ENSURE(this->fX == x, "X is initizialized");
	ENSURE(this->fY == y, "Y is initialized");
	ENSURE(this->isInitialized(), "Point is initialized");
}

Point::Point(Point& p) {
	REQUIRE(p.isInitialized(), "Point is initialized");

	Point::fMyself = this;
	Point::fX = p.fX;
	Point::fY = p.fY;

	ENSURE(this->fX == p.fX, "X copied");
	ENSURE(this->fY == p.fY, "Y copied");
	ENSURE(this->isInitialized(), "Point is initialized");
}

bool Point::operator= (Point& p) {
	REQUIRE(p.isInitialized(), "Point is initialized");

	Point::fX = p.fX;
	Point::fY = p.fY;

	ENSURE(this->fX == p.fX, "X copied");
	ENSURE(this->fY == p.fY, "Y copied");
	return true;
}

bool Point::set(int& x, int& y) {
	REQUIRE(this->isInitialized(), "Point is initialized");
	REQUIRE(x >= 0, "x >= 0");
	REQUIRE(y >= 0, "y >= 0");

	Point::fX = x;
	Point::fY = y;

	ENSURE(this->fX == x, "X is set");
	ENSURE(this->fY == y, "Y is set");
	return true;
}

unsigned int Point::getX() {
	REQUIRE(this->isInitialized(), "Point is initialized");
	return Point::fX;
}

unsigned int Point::getY() {
	REQUIRE(this->isInitialized(), "Point is initialized");
	return Point::fY;
}
