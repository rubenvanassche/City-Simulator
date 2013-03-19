/*
 * Building.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Building.h"

bool Building::isInitialized() {
	return Building::fMyself == this;
}

Building::Building(Point& location, Size& size)
	: fSize(size), fLocation(location) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");

	Building::fMyself = this;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == location, "Location is set");
	ENSURE(this->fSize == size, "Size is set");
}

Building::Building(Building& b)
	: fSize(b.fSize), fLocation(b.fLocation) {
	REQUIRE(b.isInitialized(), "Point is initialized");

	Building::fMyself = this;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == b.fLocation, "Location is set");
	ENSURE(this->fSize == b.fSize, "Size is set");
}

bool Building::operator= (Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fLocation = b.fLocation;
	Building::fSize = b.fSize;

	ENSURE(this->fLocation == b.fLocation, "Location is set");
	ENSURE(this->fSize == b.fSize, "Size is set");
	return true;
}

bool Building::setLocation(Point& location) {
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fLocation = location;

	ENSURE(this->fLocation == location, "Location is set");
	return true;
}

bool Building::setSize(Size& size) {
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fSize = size;

	ENSURE(this->fSize == size, "Size is set");
	return true;
}

Point& Building::getLocation() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return Building::fLocation;
}

Size& Building::getSize() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return Building::fSize;
}

bool Building::isElement(Point& p) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	std::vector<Point*>::iterator it;

	bool good = false;
	std::vector<Point*> points = this->calculatePoints();
	for(it = points.begin();it != points.end();++it){
		if(**it == p){
			good = true;
		}else{
			continue;
		}
	}

	for(it = points.begin();it != points.end();++it){
		delete *it;
	}

	return good;
}

std::vector<Point*> Building::calculatePoints(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	int width = this->getSize().getWidth();
	int height = this->getSize().getHeight();
	Point location = this->getLocation();

	std::vector<Point*> out;

	for(int i = location.getX();i < location.getX() + width;i++){
		for(int j = location.getY(); j != location.getY() - height;j--){
			Point* p = new Point(i, j);
			out.push_back(p);
		}
	}


	ENSURE(out.size() > 0, "There are no points given as output");
	return out;

}
