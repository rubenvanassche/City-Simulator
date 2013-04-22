/*
 * Shop.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Shop.h"

bool Shop::isInitialized() const {
	return fMyself == this;
}

std::ostream& operator<< (std::ostream& stream, Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");

	stream << "Winkel op locatie " << s.getLocation();
	return stream;
}


Shop::Shop(const Point& location, const Size& size, const double& health, const int& security)
: Building(location, size, health) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");
	REQUIRE(security >= 0, "Positive Security");

	fMyself = this;
	fSecurityLevel = security;
	fIsRobbing = false;

	ENSURE(this->isInitialized(), "Shop is initialized");
}



Shop::Shop(const Shop& s)
: Building(s.getLocation(), s.getSize(), s.getHealth() ) {
	REQUIRE(s.isInitialized(), "Shop is initialized");

	fMyself = this;
	fSecurityLevel = s.getSecurity();
	fIsRobbing = false;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->getSize() == s.getSize(), "Size is copied");
	ENSURE(this->getLocation() == s.getLocation(), "Location is copied");
}



bool Shop::operator= (const Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");
	REQUIRE(this->isInitialized(), "Shop is initialized");

	fLocation = s.getLocation();
	fSize = s.getSize();
	fHealth = s.getHealth();
	fSecurityLevel = s.getSecurity();

	ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->getSize() == s.getSize(), "Size is copied");
	ENSURE(this->getLocation() == s.getLocation(), "Location is copied");
	return true;
}

int Shop::getSecurity() const{
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return this->fSecurityLevel;
}

bool Shop::isRobbing() const {
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fIsRobbing;
}


bool Shop::StartRobbing(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->getSecurity() > 0, "Security Level is positive");

	fIsRobbing = true;

	ENSURE(this->fIsRobbing == true, "Robbery started");
	return true;
}


bool Shop::rob(int substracter){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsRobbing, "Robbery is going on");

	if(this->isRobbing() == true){
		fSecurityLevel -= substracter;
	}

	if (fSecurityLevel <= 0) {
		fIsRobbing = false;
	}

	return true;

}


bool Shop::StopRobbing(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	fIsRobbing = false;

	ENSURE(this->fIsRobbing == false, "The building is not being robbed anymore");

	return true;
}
