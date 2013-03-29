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

Building::Building(Point& location, Size& size, double health)
	: fSize(size), fLocation(location) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Health point is positive");

	Building::fMyself = this;
	Building::fHealth = health;
	Building::fIsBurning = false;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == location, "Location is set");
	ENSURE(this->fSize == size, "Size is set");
	ENSURE(this->fIsBurning == false, "Building is initially not on fire");
}

Building::Building(Building& b)
	: fSize(b.fSize), fLocation(b.fLocation) {
	REQUIRE(b.isInitialized(), "Building is initialized");

	Building::fMyself = this;
	Building::fHealth = b.fHealth;
	Building::fIsBurning = b.fIsBurning;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
}

bool Building::operator= (Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fLocation = b.fLocation;
	Building::fSize = b.fSize;
	Building::fHealth = b.fHealth;
	Building::fIsBurning = b.fIsBurning;

	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
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


bool Building::isBurning() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return Building::fIsBurning;
}

bool Building::setFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fHealth > 0, "Health point is positive");

	Building::fIsBurning = true;

	ENSURE(this->fIsBurning == true, "Building is set on fire");
	return true;
}

bool Building::burningDown(int substracter) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsBurning, "Building is on fire");

	if(this->isBurning() == true){
		Building::fHealth -= substracter;
	}

	if (Building::fHealth <= 0) {
		Building::fIsBurning = false;
	}

	return true;
}

bool Building::stopFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	Building::fIsBurning = false;

	ENSURE(this->fIsBurning == true, "Building is not on fire anymore");
	return true;
}

double Building::getHealth() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return Building::fHealth;
}

bool Building::isDead() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	if (Building::fHealth <= 0) {
		return true;
	}
	return false;
}

bool Building::setSize(Size& s) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(s.isInitialized(), "Size is initialized");

	Building::fSize = s;

	ENSURE(this->fSize == s, "Size is set");
	return true;
}

bool Building::setLocation(Point& p) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	Building::fLocation = p;

	ENSURE(this->fLocation == p, "Location is set");
	return true;
}

bool Building::setHealth(int h) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(h >= 0, "Health is positive");

	Building::fHealth = h;

	ENSURE(this->fHealth == h, "Health is set");
	return true;
}
