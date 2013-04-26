/*
 * Building.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "Building.h"

bool Building::isInitialized() const {
	return fMyself == this;
}

Building::Building(const Point& location, const Size& size, const double& health, const double& reducer) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Health point is positive");
	REQUIRE(reducer >= 0, "reducer point is positive");

	fSize = size;
	fLocation = location;
	fMyself = this;
	fHealth = health;
	fHealthNormal = health;
	fIsBurning = false;
	fReducer = reducer;
	fFireTruckAssigned = false;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == location, "Location is set");
	ENSURE(this->fSize == size, "Size is set");
	ENSURE(this->fIsBurning == false, "Building is initially not on fire");
	ENSURE(this->fHealthNormal == health, "HealthNormal is set");
	ENSURE(this->fHealth == health, "Health is set");
	ENSURE(this->fReducer ==  reducer, "reducer is set");
	ENSURE(this->fFireTruckAssigned == false, "There is no FireTruck assigned (yet)");
}

Building::Building(const Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");

	fSize = b.fSize;
	fLocation = b.fLocation;
	fMyself = this;
	fHealth = b.fHealth;
	fHealthNormal = b.fHealth;
	fIsBurning = b.fIsBurning;
	fReducer = b.fReducer;
	fFireTruckAssigned = b.fFireTruckAssigned;

	ENSURE(this->isInitialized(), "Building is initialized");
	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
	ENSURE(this->fHealthNormal == b.fHealthNormal, "HealthNormal is copied");
	ENSURE(this->fReducer == b.fReducer, "Reducer is copied");
	ENSURE(this->fFireTruckAssigned ==  b.fFireTruckAssigned, "FireTruckAssigned is copied");
}

void Building::operator= (const Building& b) {
	REQUIRE(b.isInitialized(), "Building is initialized");
	REQUIRE(this->isInitialized(), "Building is initialized");

	fLocation = b.fLocation;
	fSize = b.fSize;
	fHealth = b.fHealth;
	fHealthNormal = b.fHealth;
	fIsBurning = b.fIsBurning;
	fReducer = b.fReducer;
	fFireTruckAssigned = b.fFireTruckAssigned;

	ENSURE(this->fLocation == b.fLocation, "Location is copied");
	ENSURE(this->fSize == b.fSize, "Size is copied");
	ENSURE(this->fHealth == b.fHealth, "Health is copied");
	ENSURE(this->fIsBurning == b.fIsBurning, "Burning is copied");
	ENSURE(this->fHealthNormal == b.fHealthNormal, "HealthNormal is copied");
	ENSURE(this->fReducer == b.fReducer, "Reducer is copied");
	ENSURE(this->fFireTruckAssigned ==  b.fFireTruckAssigned, "FireTruckAssigned is copied");
	return;
}

Point Building::getLocation() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return fLocation;
}

Size Building::getSize() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return fSize;
}

double Building::getHealth() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	return fHealth;
}

void Building::setFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fHealth > 0, "Health point is positive");

	fIsBurning = true;

	ENSURE(this->fIsBurning == true, "Building is set on fire");
	return;
}

bool Building::isBurning() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fIsBurning;
}

void Building::burningDown() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fIsBurning, "Building is on fire");

	fHealth -= this->fReducer;	// use the predefined reducer

	ENSURE(this->fHealth < this->fHealthNormal, "There is at least one point substracted");
	return;
}

void Building::stopFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fIsBurning == true, "Building is on fire");

	fIsBurning = false;

	ENSURE(this->fIsBurning == false, "Building is not on fire anymore");
	return;
}

bool Building::isDead() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fHealth <= 0;
}

bool Building::startSpreadingFire() const {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fHealthNormal >= this->fHealth, "Health points are valid");

	// if the building is not on fire, then the fire cannnot spread
	if( (!fIsBurning) || (this->isDead()) ) {
		return false;
	}

	if ( (fHealthNormal - fHealth) >= 3){
		return true;
	}

	return false;
}

bool Building::startRepair() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	// you can not repair a building while it's burning or it is dead
	if ( (fIsBurning) || (this->isDead() ) ) {
		return false;
	}

	if (fHealthNormal == fHealth) {
		return false;
	}

	return true;
}

void Building::repair(){
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->startRepair(), "You may repair that building");

	fHealth += 0.5;
	return;
}

bool Building::isFireTruckAssigned() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fFireTruckAssigned;
}

void Building::assignFireTruck() {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->isBurning(), "The building is on fire");
	REQUIRE(this->fFireTruckAssigned == false, "There's not already a firetruck assigned");

	fFireTruckAssigned = true;

	ENSURE(this->fFireTruckAssigned == true, "A firetruck is assigned to the house");
	return;
}

void Building::withdrawFireTruckAssignment(){
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->isBurning() == false, "The Building is not on fire anymore");
	REQUIRE(this->fFireTruckAssigned == true, "There is a firetruck assigned previously");

	fFireTruckAssigned = false;

	ENSURE(this->fFireTruckAssigned == false, "A firetruck is withdrawed from the building");
}

std::vector<Point> Building::calculatePoints(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	int width = this->getSize().getWidth();
	int height = this->getSize().getHeight();
	Point location = this->getLocation();

	std::vector<Point> out;

	for(int i = location.getX();i < location.getX() + width;i++){
		for(int j = location.getY(); j != location.getY() - height;j--){
			Point p(i, j);
			out.push_back(p);
		}
	}


	ENSURE(out.size() > 0, "There are no points given as output");
	return out;
}

std::vector<Point> Building::calculateSurroundingPoints(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	std::vector<Point> points;

	for(int i = 0;i < this->fSize.getWidth();i++){
		for(int j = 0;j < this->fSize.getHeight();j++){
			int x = 0;
			int y = 0;

			if(i == 0 and j == 0){
				continue;
			}

			if(i == 0 and j == this->fSize.getHeight()){
				continue;
			}

			if(i == this->fSize.getWidth() and j == 0){
				continue;
			}

			if(i == this->fSize.getWidth() and j == this->fSize.getHeight()){
				continue;
			}

			if(i == 0){
				x = this->fLocation.getX() -1 ;
				y = this->fLocation.getY() - j;
			}

			if(i == this->fSize.getWidth()){
				x = this->fLocation.getX() + 1;
				y = this->fLocation.getY() - j;
			}

			if(j == 0){
				x = this->fLocation.getX() + i;
				y = this->fLocation.getY() + 1;
			}

			if(j == this->fSize.getHeight()){
				x = this->fLocation.getX() + i;
				y = this->fLocation.getY() + 1;
			}

			Point newPoint(x, y);
			points.push_back(newPoint);
		}
	}

	return points;
}
