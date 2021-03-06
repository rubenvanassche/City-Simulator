/*
 * Street.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "Street.h"

bool Street::isInitialized() const {
	return fMyself == this;
}

bool operator== (const Street& s, const Street& p) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(p.isInitialized(), "Street is initialized");

	if ( (s.fEndPoint == p.fEndPoint) && (s.fStartPoint == p.fStartPoint) ) {
		return true;
	}
	return false;
}

std::ostream& operator<< (std::ostream& stream, const Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	stream << s.fName << " [van " << s.fStartPoint << " naar " <<  s.fEndPoint << "]";
	return stream;
}

Street::Street(const std::string& name, const Point& start, const Point& end) {
	REQUIRE(start.isInitialized(), "Startpoint is initialized");
	REQUIRE(end.isInitialized(), "Endpoint is initialized");

	fStartPoint = start;
	fEndPoint = end;
	fMyself = this;
	fName = name;

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->getStartPoint() == start, "Startpoint is set");
	ENSURE(this->getEndPoint() == end, "Endpoint is set");
	ENSURE(this->getName() == name, "Name is set");
}

Street::Street(const Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	fStartPoint = s.fStartPoint;
	fEndPoint = s.fEndPoint;
	fMyself = this;
	fName = s.fName;

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->getEndPoint() == s.getEndPoint(), "Endpoint is copied");
	ENSURE(this->getStartPoint() == s.getStartPoint(), "Startpoint is copied");
	ENSURE(this->getName() == s.getName(), "Name is copied");
}

void Street::operator= (const Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(this->isInitialized(), "Street is initialized");

	fStartPoint = s.fStartPoint;
	fEndPoint = s.fEndPoint;
	fName = s.fName;

	ENSURE(this->getEndPoint() == s.getEndPoint(), "Endpoint is copied");
	ENSURE(this->getStartPoint() == s.getStartPoint(), "Startpoint is copied");
	ENSURE(this->getName() == s.getName(), "Name is copied");
	return;
}

Point Street::getStartPoint() const {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return fStartPoint;
}

Point Street::getEndPoint() const {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return fEndPoint;
}

std::string Street::getName() const {
	REQUIRE(this->isInitialized(), "Street is initialized");
	return fName;
}

bool Street::isVertical() const {
	REQUIRE(this->isInitialized(), "Street is initialized");

	return fStartPoint.getX() == fEndPoint.getX();
}

bool Street::isHorizontal() const {
	REQUIRE(this->isInitialized(), "Street is initialized");

	return fStartPoint.getY() == fEndPoint.getY();
}

bool Street::isElement(const Point& p) {
	REQUIRE(this->isInitialized(), "Street is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");
	REQUIRE((this->isVertical()) || (this->isHorizontal()), "Street is horizontal or vertical");

	if (this->isHorizontal() ) {
		// then iterate over x
		unsigned int xMin = std::min(fStartPoint.getX(), fEndPoint.getX());
		unsigned int xMax = std::max(fStartPoint.getX(), fEndPoint.getX());

		for (unsigned int x = xMin; x <= xMax; x++) {
			// if you can find a point that is equal to the point given, then return true
			if (Point(x, fStartPoint.getY() ) == p) {
				return true;
			}
		}
		// if not any point is found, return false;
		return false;
	}
	else {
		// iterate over y
		unsigned int yMin = std::min(fStartPoint.getY(), fEndPoint.getY());
		unsigned int yMax = std::max(fStartPoint.getY(), fEndPoint.getY());

		for (unsigned int y = yMin; y <= yMax; y++) {
			// if you can find a point that is equal to the point given, then return true
			if (Point(fStartPoint.getX(), y) == p) {
				return true;
			}
		}
		// if not any point is found, return false;
		return false;
	}
}

bool Street::isCrossing(Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");

	if (this->isVertical()) {
		return str.isHorizontal();
	}
	else if (this->isHorizontal()) {
		return str.isVertical();
	}
	else {	// this is irregular, we assume then false
		return false;
	}
}

bool Street::isParallel(const Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");

	// this is simple: look whether both are vertical or horizontal
	if (str.isVertical() && this->isVertical() ) {
		return true;
	}
	else if (str.isHorizontal() && this->isHorizontal() ) {
		return true;
	}
	else {
		return false;
	}
}

Point Street::getCrosspoint(Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");
	REQUIRE(this->isCrossing(str), "Streets are crossing");

	unsigned int xMin = std::min(fStartPoint.getX(), fEndPoint.getX());
	unsigned int xMax = std::max(fStartPoint.getX(), fEndPoint.getX());
	unsigned int yMin = std::min(fStartPoint.getY(), fEndPoint.getY());
	unsigned int yMax = std::max(fStartPoint.getY(), fEndPoint.getY());

	for (unsigned int x = xMin; x <= xMax; x++) {
		for (unsigned int y = yMin; y <= yMax; y++) {

			if (str.isElement( Point(x, y) ) ) {
				return Point(x, y);
			}
		}
	}

	// you should never reach here
	return Point();
}

char Street::getSymbol() const {
	return ' ';
}

std::vector<Point> Street::calculatePoints(){
	REQUIRE(this->isInitialized(), "Street is initialized");

	int x1 = this->getStartPoint().getX();
	int y1 = this->getStartPoint().getY();
	int x2 = this->getEndPoint().getX();
	int y2 = this->getEndPoint().getY();

	std::vector<Point> out;

	// Do we have an vertical or horizontal street?
	if(x1 == x2){
		// Vertical
		for(int i = std::min(y1, y2);i < std::max(y1, y2);i++){
			Point p(x1, i);
			out.push_back(p);
		}
	}else if(y1 == y2){
		// Horizontal
		for(int i = std::min(x1, x2);i < std::max(x1, x2);i++){
			Point p(i, y1);
			out.push_back(p);
		}
	}else{
		// Now we're having a serious issue
	}

	ENSURE(out.size() > 0, "There are no points given as output");
	return out;
}
