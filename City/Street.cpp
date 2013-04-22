/*
 * Street.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
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

	if (start.getX() == end.getX() ) {
		if (start.getY() < end.getY() ) {
			for (unsigned int y=start.getY(); y <= end.getY(); y++) {
				Point* p = new Point(start.getX(), y);
				fPoints.push_back(p);
			}
		}
		else {
			for (unsigned int y=end.getY(); y <= start.getY(); y++) {
				Point* p = new Point(start.getX(), y);
				fPoints.push_back(p);
			}
		}
	}
	else if (start.getY() == end.getY() ) {
		if (start.getX() < end.getX() ) {
			for (unsigned int x=start.getX(); x <= end.getX(); x++) {
				Point* p = new Point(x, start.getY());
				fPoints.push_back(p);
			}
		}
		else {
			for (unsigned int x=end.getX(); x <= start.getX(); x++) {
				Point* p = new Point(x, start.getY() );
				fPoints.push_back(p);
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

	for (unsigned int index=0; index < fPoints.size(); index++) {
		delete fPoints[index];
	}
	fPoints.clear();

	ENSURE(this->fPoints.empty(), "Points are empty'd");
}

Street::Street(const Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");

	fStartPoint = s.fStartPoint;
	fEndPoint = s.fEndPoint;
	fMyself = this;
	fName = s.fName;

	for (unsigned int index=0; index < s.fPoints.size(); index++) {
		Point* p = new Point( *(s.fPoints[index]) );
		fPoints.push_back(p);
	}

	ENSURE(this->isInitialized(), "Street is initialized");
	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	ENSURE(this->fName == s.fName, "Name is copied");
	ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");
}

bool Street::operator= (const Street& s) {
	REQUIRE(s.isInitialized(), "Street is initialized");
	REQUIRE(this->isInitialized(), "Street is initialized");

	fStartPoint = s.fStartPoint;
	fEndPoint = s.fEndPoint;
	fName = s.fName;

	for (unsigned int index=0; index < Street::fPoints.size(); index++) {
		delete fPoints[index];
	}
	fPoints.clear();

	for (unsigned int index=0; index < s.fPoints.size(); index++) {
		Point* p = new Point( *(s.fPoints[index]) );
		fPoints.push_back(p);
	}

	ENSURE(this->fEndPoint == s.fEndPoint, "Endpoint is copied");
	ENSURE(this->fStartPoint == s.fStartPoint, "Startpoint is copied");
	ENSURE(this->fName == s.fName, "Name is copied");
	ENSURE(this->fPoints.size() == s.fPoints.size(), "Points is copied");
	return true;
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

	if (fStartPoint.getX() == fEndPoint.getX() ) {
		return true;
	}
	return false;
}

bool Street::isHorizontal() const {
	REQUIRE(this->isInitialized(), "Street is initialized");

	if (fStartPoint.getY() == fEndPoint.getY() ) {
		return true;
	}
	return false;
}

bool Street::isElement(const Point& p) {
	REQUIRE(this->isInitialized(), "Street is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");
	REQUIRE((this->isVertical()) || (this->isHorizontal()), "Street is horizontal or vertical");

	for (unsigned int index=0; index < fPoints.size(); index++) {
		if ( *(fPoints[index]) == p ) {
			return true;
		}
	}
	return false;
}

bool Street::isCrossing(Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");

	if (str.isVertical()) {
		if (this->isVertical()) {
			return false;	// parallel
		}
		else {
			for (unsigned int index = 0; index < fPoints.size(); index++) {
				if (str.isElement(Point( *(fPoints[index]) ) ) ) {
					return true;
				}
			}

			return false;
		}
	}
	else {
		if (this->isHorizontal()) {
			return false;	// parallel
		}
		else {
			for (unsigned int index = 0; index < fPoints.size(); index++) {
				if (str.isElement(Point( *(fPoints[index]) ) ) ) {
					return true;
				}
			}

			return false;
		}
	}
}

bool Street::isParallel(const Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");

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

Point* Street::getCrosspoint(Street& str) {
	REQUIRE(str.isInitialized(), "Street is initialized");

	for (unsigned int index = 0; index < fPoints.size(); index++) {
		if (str.isElement(Point( *(fPoints[index]) ) ) ) {
			return fPoints[index];
		}
	}

	return NULL;
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
