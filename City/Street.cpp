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

bool operator== (Street& s, Street& p) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(p.isInitialized(), "Street is initialized");

	if ( (s.fEndPoint == p.fEndPoint) && (s.fStartPoint == p.fStartPoint) ) {
		return true;
	}
	return false;
}

std::ostream& operator<< (std::ostream& stream, Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	stream << s.fName << " [van " << s.fStartPoint << " naar " <<  s.fEndPoint << "]";
	return stream;
}

bool isCrossing(Street& str, Street& astr) {
	REQUIRE(str.isInitialized(), "Street is initialized");
	REQUIRE(astr.isInitialized(), "Street is initialized");

	for (unsigned int indexStr=0; indexStr < str.fPoints.size(); indexStr++) {
		for (unsigned int indexAstr=0; indexAstr < astr.fPoints.size(); indexAstr++) {
			if ( *str.fPoints[indexStr] == *astr.fPoints[indexAstr] ) {
				return true;
			}
		}
	}
	return false;
}

bool isParallel(Street& str, Street& astr) {
	REQUIRE(str.isInitialized(), "Street is initialized");
	REQUIRE(astr.isInitialized(), "Street is initialized");

	if (str.isVertical() && astr.isVertical() ) {
		return true;
	}
	else if (str.isHorizontal() && astr.isHorizontal() ) {
		return true;
	}
	else {
		return false;
	}
}

Point* getCrosspoint(Street& destStr, Street& curStr) {
	REQUIRE(destStr.isInitialized(), "Street is initialized");
	REQUIRE(curStr.isInitialized(), "Street is initialized");

	if (isCrossing(curStr, destStr) ) {	// streets are crossing
		// then find the crosspoint
		for (unsigned int indexStr=0; indexStr < curStr.fPoints.size(); indexStr++) {
			for (unsigned int indexAstr=0; indexAstr < destStr.fPoints.size(); indexAstr++) {
				if ( *(curStr.fPoints[indexStr]) == *(destStr.fPoints[indexAstr]) ) {
					return curStr.fPoints[indexStr];
				}
			}
		}
	}

	return NULL;
}

Street::Street(std::string& name, Point& start, Point& end)
	: fStartPoint(start), fEndPoint(end) {
	REQUIRE(start.isInitialized(), "Startpoint is initialized");
	REQUIRE(end.isInitialized(), "Endpoint is initialized");

	Street::fMyself = this;
	Street::fName = name;

	if (start.getX() == end.getX() ) {
		if (start.getY() < end.getY() ) {
			for (unsigned int y=start.getY(); y <= end.getY(); y++) {
				Point* p = new Point(start.getX(), y);
				Street::fPoints.push_back(p);
			}
		}
		else {
			for (unsigned int y=end.getY(); y <= start.getY(); y++) {
				Point* p = new Point(start.getX(), y);
				Street::fPoints.push_back(p);
			}
		}
	}
	else if (start.getY() == end.getY() ) {
		if (start.getX() < end.getX() ) {
			for (unsigned int x=start.getX(); x <= end.getX(); x++) {
				Point* p = new Point(x, start.getY());
				Street::fPoints.push_back(p);
			}
		}
		else {
			for (unsigned int x=end.getX(); x <= start.getX(); x++) {
				Point* p = new Point(x, start.getY() );
				Street::fPoints.push_back(p);
			}
		}
	}
	else  {
		std::cerr << "Inconsistent street: " << name << " is not vertical or horizontal." << std::endl;
	}

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fStartPoint == start, "Startpoint is set");
	ENSURE(this->fEndPoint == end, "Endpoint is set");
	ENSURE(this->fName == name, "Name is set");
}

Street::~Street() {
	REQUIRE(this->isInitialized(), "Street is initialized");

	for (unsigned int index=0; index < Street::fPoints.size(); index++) {
		delete Street::fPoints[index];
	}
	Street::fPoints.clear();

	ENSURE(this->fPoints.empty(), "Points are empty'd");
}

Street::Street(Street& s)
	: fStartPoint(s.fStartPoint), fEndPoint(s.fEndPoint) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	Street::fMyself = this;
	Street::fName = s.fName;

	for (unsigned int index=0; index < s.fPoints.size(); index++) {
		Point* p = new Point( *(s.fPoints[index]) );
		Street::fPoints.push_back(p);
	}

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	ENSURE(this->fName == s.fName, "Name is copied");
	ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");
}

bool Street::operator= (Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(this->isInitialized(), "Street is initialized");

	Street::fStartPoint = s.fStartPoint;
	Street::fEndPoint = s.fEndPoint;
	Street::fName = s.fName;

	for (unsigned int index=0; index < s.fPoints.size(); index++) {
		delete Street::fPoints[index];
		Point* p = new Point( *(s.fPoints[index]) );
		Street::fPoints[index] = p;
	}

	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	ENSURE(this->fName == s.fName, "Name is copied");
	ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");
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

bool Street::isVertical() {
	REQUIRE(this->isInitialized(), "Street is initialized");

	if (Street::fStartPoint.getX() == Street::fEndPoint.getX() ) {
		return true;
	}
	return false;
}

bool Street::isHorizontal() {
	REQUIRE(this->isInitialized(), "Street is initialized");

	if (Street::fStartPoint.getY() == Street::fEndPoint.getY() ) {
		return true;
	}
	return false;
}

bool Street::isElement(Point& p) {
	REQUIRE(this->isInitialized(), "Street is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	for (unsigned int index=0; index < Street::fPoints.size(); index++) {
		if ( *(Street::fPoints[index]) == p ) {
			return true;
		}
	}
	return false;
}

std::vector<Point*> Street::calculatePoints(){
	REQUIRE(this->isInitialized(), "Street is initialized");

	int x1 = this->getStartPoint().getX();
	int y1 = this->getStartPoint().getY();
	int x2 = this->getEndPoint().getX();
	int y2 = this->getEndPoint().getY();

	std::vector<Point*> out;

	// Do we have an vertical or horizontal street?
	if(x1 == x2){
		// Vertical
		for(int i = std::min(y1, y2);i < std::max(y1, y2);i++){
			Point* p = new Point(x1, i);
			out.push_back(p);
		}
	}else if(y1 == y2){
		// Horizontal
		for(int i = std::min(x1, x2);i < std::max(x1, x2);i++){
			Point* p = new Point(i, y1);
			out.push_back(p);
		}
	}else{
		// Now we're having a serious issue
	}

	ENSURE(out.size() > 0, "There are no points given as output");
	return out;
}
