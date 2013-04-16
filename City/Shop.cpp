/*
 * Shop.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Shop.h"

bool Shop::isInitialized(){
	return Shop::fMyself == this;
}

std::ostream& operator<< (std::ostream& stream, Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");

	stream << "Winkel op locatie " << s.getLocation();
	return stream;
}


Shop::Shop(Point& location, Size& size, double health, int security)
: Building(location, size, health) {
	REQUIRE(location.isInitialized(), "Location is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(health >= 0, "Positive healthpoints");
	REQUIRE(security >= 0, "Positive Security");

	Shop::fMyself = this;
	fSecurityLevel = security;

	ENSURE(this->isInitialized(), "Shop is initialized");
}



Shop::Shop(Shop& s)
: Building(s.getLocation(), s.getSize(), s.getHealth() ) {
	REQUIRE(s.isInitialized(), "Shop is initialized");

	Shop::fMyself = this;
	fSecurityLevel = s.getSecurity();

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->getSize() == s.getSize(), "Size is copied");
	ENSURE(this->getLocation() == s.getLocation(), "Location is copied");
}



bool Shop::operator= (Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");
	REQUIRE(this->isInitialized(), "Shop is initialized");

	this->setLocation(s.getLocation());
	this->setSize(s.getSize());
	this->setHealth(s.getHealth());
	fSecurityLevel = s.getSecurity();

	ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->getSize() == s.getSize(), "Size is copied");
	ENSURE(this->getLocation() == s.getLocation(), "Location is copied");
	return true;
}

int Shop::getSecurity(){
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return this->fSecurityLevel;
}

bool Shop::isRobbing(){
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return Shop::fIsRobbing;
}


bool Shop::StartRobbing(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->getSecurity() > 0, "Security Level is positive");

	Shop::fIsRobbing = true;

	ENSURE(this->fIsRobbing == true, "Robbery started");
	return true;
}


bool Shop::rob(int substracter){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsRobbing, "Robbery is going on");

	if(this->isRobbing() == true){
		Shop::fSecurityLevel -= substracter;
	}

	if (Shop::fSecurityLevel <= 0) {
		Shop::fIsRobbing = false;
	}

	return true;

}


bool Shop::StopRobbing(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	Shop::fIsRobbing = false;

	ENSURE(this->fIsRobbing == false, "The building is not being robbed anymore");

	return true;
}



