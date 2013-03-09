/*
 * Street.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 2 March 2013
 * 
 */

#include "Street.h"
#include "Point.h"
#include "DesignByContract.h"

std::ostream& operator<< (std::ostream& stream, Street& objectStreet) {
	REQUIRE( objectStreet.isInitialized(), "The Street object is not initialized properly");
	stream << objectStreet.fName << " [" << objectStreet.fStartPoint
			<< " -> " << objectStreet.fEndPoint << "]";
	return stream;
}

bool Street::isInitialized() {
	return this == Street::fMyself;
}

Street::Street(Point& startPoint, Point& endPoint, std::string name) {
	REQUIRE( ( startPoint.isInitialized() && endPoint.isInitialized() ), "Points are not valid");

	Street::fStartPoint = startPoint;
	Street::fEndPoint = endPoint;
	Street::fName = name;
	Street::fMyself = this;

	ENSURE(isInitialized(), "The Street object is not initialized properly");
}

Street::Street(const Street& s) {
	Street::fMyself = this;

	Street::fStartPoint = s.fStartPoint;
	Street::fEndPoint = s.fEndPoint;

	Street::fName = s.fName;
}

Street& Street::operator= (const Street& s) {
	Street::fStartPoint = s.fStartPoint;
	Street::fEndPoint = s.fEndPoint;
	Street::fName = s.fName;
	return *this;
}

bool Street::setEndPoint(Point& end) {
	REQUIRE(this->isInitialized(), "The Street object is not initialized properly");
	REQUIRE(end.isInitialized(), "The endPoint is not valid");

	Street::fEndPoint = end;

	ENSURE(this->fEndPoint == end, "The end is not set");
	return true;
}

Point* Street::getEndPoint() {
	 REQUIRE(this->isInitialized(), "The Street object is not initialized properly");
	 return &(Street::fEndPoint);
}

bool Street::setStartPoint(Point& start) {
	REQUIRE(this->isInitialized(), "The Street object is not initialized properly");
	REQUIRE(start.isInitialized(), "The startpoint is not valid");

	Street::fStartPoint = start;

	ENSURE(this->fStartPoint == start, "The startpoint is not set");
	return true;
}

Point* Street::getStartPoint() {
	 REQUIRE(this->isInitialized(), "The Street object is not initialized properly");
	 return &(Street::fStartPoint);
}

bool Street::setName(const std::string& name) {
	 REQUIRE(this->isInitialized(), "The Street object is not initialized properly");

	 Street::fName = name;

	ENSURE(this->fName == name, "The name is not set");
	return true;
}

std::string* Street::getName() {
	REQUIRE(this->isInitialized(), "The Street object is not initialized properly");
	return &(Street::fName);
}
