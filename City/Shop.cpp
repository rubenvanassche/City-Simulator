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
	REQUIRE(security >= 0, "Positive Security");

	fMyself = this;
	fSecurityLevel = security;
	fIsRobbing = false;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == security, "SecurityLevel is set");
	ENSURE(this->fIsRobbing == false, "Shop is not being robbed (yet)");
}

Shop::Shop(const Shop& s)
: Building(s.getLocation(), s.getSize(), s.getHealth() ) {
	REQUIRE(s.isInitialized(), "Shop is initialized");

	fMyself = this;
	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == s.getSecurity(), "Security is copied");
	ENSURE(this->fIsRobbing == s.isRobbing(), "Robbing is copied");
}

void Shop::operator= (const Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");
	REQUIRE(this->isInitialized(), "Shop is initialized");

	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == s.fSecurityLevel, "Security is copied");
	ENSURE(this->fIsRobbing == s.fIsRobbing, "Robbing is copied");
	return;
}

int Shop::getSecurity() const{
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fSecurityLevel;
}

bool Shop::isRobbing() const {
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fIsRobbing;
}


void Shop::StartRobbing(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->getSecurity() > 0, "Security Level is positive");

	fIsRobbing = true;

	ENSURE(this->fIsRobbing == true, "Robbery started");
	return;
}


void Shop::rob(int substracter){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->fIsRobbing, "Robbery is going on");

	if(this->isRobbing() == true){
		fSecurityLevel -= substracter;
	}

	if (fSecurityLevel <= 0) {
		fIsRobbing = false;
	}

	return;

}


void Shop::StopRobbing(){
	REQUIRE(this->isInitialized(), "Building is initialized");

	fIsRobbing = false;

	ENSURE(this->fIsRobbing == false, "The building is not being robbed anymore");

	return;
}

char Shop::getSymbol(){
	if(this->isBurning()){
		return '#';
	}else{
		return 'W';
	}
}
