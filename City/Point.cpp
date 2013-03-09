/*
 * Point.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 2 March 2013
 * 
 */

#include "Point.h"
#include "DesignByContract.h"

std::ostream& operator<< (std::ostream& stream, Point& pointobject) {
	REQUIRE( pointobject.isInitialized(), "The Point object is not initialized properly");
	stream << "(" << pointobject.fX << ", " << pointobject.fY << ")";
	return stream;
}

bool operator== (Point& pointobject1, Point& pointobject2) {
	REQUIRE( (pointobject1.isInitialized() && pointobject2.isInitialized() ), "The Point objects are not initialized properly");
	if ( (pointobject1.fX == pointobject2.fX) && (pointobject1.fY == pointobject2.fY) ) {
			return true;
	}
	return false;
}

bool operator!= (Point& pointobject1, Point& pointobject2) {
	REQUIRE( (pointobject1.isInitialized() && pointobject2.isInitialized() ), "The Point objects are not initialized properly");
	if ( (pointobject1.fX != pointobject2.fX) || (pointobject1.fY == pointobject2.fY) ) {
			return true;
	}
	return false;
}

Point operator+ (Point& pointobject1, Point& pointobject2) {
	REQUIRE( (pointobject1.isInitialized() && pointobject2.isInitialized() ), "The Point objects are not initialized properly");
	int x = pointobject1.fX + pointobject2.fX;
	int y = pointobject1.fY + pointobject2.fY;

	Point p(x, y);
	return p;
}

Point operator- (Point& pointobject1, Point& pointobject2) {
	REQUIRE( (pointobject1.isInitialized() && pointobject2.isInitialized() ), "The Point objects are not initialized properly");
	int x = pointobject1.fX - pointobject2.fX;
	int y = pointobject1.fY - pointobject2.fY;

	Point p(x, y);
	return p;
}

bool Point::isInitialized() {
	return this == Point::fMyself;
}

Point::Point(const int& x, const int& y) {
	REQUIRE( ( (x >= 0) && (y >= 0) ), "Invalid xy-coordinates.");

	Point::fX = x;
	Point::fY = y;
	Point::fMyself = this;

	ENSURE(isInitialized(), "Point object is not initialized properly.");
	ENSURE( ( (this->fX == x) && (this->fY == y) ), "Point object has not the given coordinates");
}

Point::Point(const Point& p) {
	Point::fMyself = this;
	Point::fX = p.fX;
	Point::fY = p.fY;
}

Point& Point::operator= (const Point& pointobject) {
	Point::fX = pointobject.fX;
	Point::fY = pointobject.fY;
	return *this;
}

bool Point::set(const int& x, const int& y) {
	 REQUIRE(this->isInitialized(), "The Point object is not initialized properly");
	 REQUIRE( ( (x >= 0) && (y >= 0) ), "Invalid xy-coordinates.");

	 Point::fX = x;
	 Point::fY = y;

	 ENSURE( ( (x == this->fX) && (y == this->fY) ), "Point object has not the given coordinates");
	 return true;
}

int* Point::getX() {
	REQUIRE(this->isInitialized(), "The Point object is not initialized properly");
	ENSURE(this->fX >= 0, "Returned x-coordinate is invalid");
	return &(Point::fX);
}

int* Point::getY() {
	REQUIRE(this->isInitialized(), "The Point object is not initialized properly");
	ENSURE(this->fY >= 0, "Returned x-coordinate is invalid");
	return &(Point::fY);
}
