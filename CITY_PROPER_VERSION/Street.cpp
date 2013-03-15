/*
 * Street.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Street.h"

bool Street::isInitialized() {
	return Street::fMyself == this;
}

std::ostream& operator<< (std::ostream& stream, Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	stream << s.fName << " [van " << s.fStartPoint << "naar " <<  s.fEndPoint << "]" << std::endl;
	return stream;
}

Street::Street(std::string& name, Point& start, Point& end)
	: fStartPoint(start), fEndPoint(end) {
	REQUIRE(start.isInitialized(), "Startpoint is initialized");
	REQUIRE(end.isInitialized(), "Endpoint is initialized");

	Street::fMyself = this;
	Street::fName = name;

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fStartPoint == start, "Startpoint is set");
	ENSURE(this->fEndPoint == end, "Endpoint is set");
	ENSURE(this->fName == name, "Name is set");
}

Street::Street(Street& s)
	: fStartPoint(s.fStartPoint), fEndPoint(s.fEndPoint) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	Street::fMyself = this;
	Street::fName = s.fName;

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is set");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is set");
	ENSURE(this->fName == s.fName, "Name is set");
}

bool Street::operator= (Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(this->isInitialized(), "Street is initialized");

	Street::fStartPoint = s.fStartPoint;
	Street::fEndPoint = s.fEndPoint;
	Street::fName = s.fName;

	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is set");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is set");
	ENSURE(this->fName == s.fName, "Name is set");
	return true;
}

bool Street::setStartPoint(Point& start) {
	REQUIRE(start.isInitialized(), "Point is initialized");

	Street::fStartPoint = start;

	REQUIRE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fStartPoint == start, "Startpoint is set");
	return true;
}

bool Street::setEndPoint(Point& end) {
	REQUIRE(end.isInitialized(), "Point is initialized");
	REQUIRE(this->isInitialized(), "Street is initialized");

	Street::fEndPoint = end;

	ENSURE(this->fEndPoint == end, "Endpoint is set");
	return true;
}

bool Street::setName(std::string& name) {
	REQUIRE(this->isInitialized(), "Street is initialized");

	Street::fName = name;

	ENSURE(this->fName == name, "Name is set");
	return true;
}

Point& Street::getStartPoint() {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return Street::fStartPoint;
}

Point& Street::getEndPoint() {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return Street::fEndPoint;
}

std::string& Street::getName() {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return Street::fName;
}
