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
	ENSURE(this->fHealthNormal == health, "HealthNormal is set");
	ENSURE(this->fHealth == health, "Health is set");
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
	ENSURE(this->fHealthNormal == b.fHealthNormal, "HealthNormal is copied");
}

void Building::operator= (const Building& b) {
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
	ENSURE(this->fHealthNormal == b.fHealthNormal, "HealthNormal is copied");
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

void Building::burningDown(const int& substracter) {
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsBurning, "Building is on fire");

	if(this->isBurning() == true){
		fHealth -= substracter;
	}

	if (fHealth <= 0) {
		fIsBurning = false;
	}

	return;
}

void Building::stopFire() {
	REQUIRE(this->isInitialized(), "Building is initialized");

	fIsBurning = false;

	ENSURE(this->fIsBurning == false, "Building is not on fire anymore");
	return;
}

bool Building::isDead() const {
	REQUIRE(this->isInitialized(), "Building is initialized");

	return fHealth <= 0;
}

void Building::repair(){
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->fIsBurning == false, "The building is not on fire");

	if(fHealth != fHealthNormal){
		fHealth += 0.5;
		return;
	}

	return;

}
