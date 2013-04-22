/*
 * Building.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Building.h"

bool Building::isInitialized() const {
	return fMyself == this;
}

Building::Building(const Point& location, const Size& size, const double& health) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Health point is positive");

	fSize = size;
	fLocation = location;
	fMyself = this;
	fHealth = health;
	fHealthNormal = health;
	fIsBurning = false;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == location, "Location is set");
	ENSURE(this->fSize == size, "Size is set");
	ENSURE(this->fIsBurning == false, "Building is initially not on fire");
}

Building::Building(const Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");

	fSize = b.fSize;
	fLocation = b.fLocation;
	fMyself = this;
	fHealth = b.fHealth;
	fHealthNormal = b.fHealth;
	fIsBurning = b.fIsBurning;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
}

bool Building::operator= (const Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");
	REQUIRE(this->isInitialized(), "Building is initialized");

	fLocation = b.fLocation;
	fSize = b.fSize;
	fHealth = b.fHealth;
	fHealthNormal = b.fHealth;
	fIsBurning = b.fIsBurning;

	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
	return true;
}

Point Building::getLocation() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return fLocation;
}

Size Building::getSize() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return fSize;
}

bool Building::isElement(const Point& p) {
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


bool Building::isBurning() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fIsBurning;
}

bool Building::setFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fHealth > 0, "Health point is positive");

	fIsBurning = true;

	ENSURE(this->fIsBurning == true, "Building is set on fire");
	return true;
}

bool Building::burningDown(const int& substracter) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsBurning, "Building is on fire");

	if(this->isBurning() == true){
		fHealth -= substracter;
	}

	if (fHealth <= 0) {
		fIsBurning = false;
	}

	return true;
}

bool Building::stopFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	fIsBurning = false;

	ENSURE(this->fIsBurning == false, "Building is not on fire anymore");
	return true;
}

double Building::getHealth() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fHealth;
}

bool Building::isDead() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	if (fHealth <= 0) {
		return true;
	}
	return false;
}

bool Building::repair(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	if(this->isBurning() == true){
		return false;
	}

	if(fHealth != fHealthNormal){
		fHealth += 0.5;
		return true;
	}

	return false;

}
