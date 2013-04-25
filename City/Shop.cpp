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
		: Building(location, size, health, 2) {
	REQUIRE(security >= 0, "Positive Security");

	fMyself = this;
	fSecurityLevel = security;
	fIsRobbing = false;
	fPoliceTruckAssigned = false;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == security, "SecurityLevel is set");
	ENSURE(this->fIsRobbing == false, "Shop is not being robbed (yet)");
	ENSURE(this->fPoliceTruckAssigned == false, "There is no PoliceTruck assigned to the shop");
}

Shop::Shop(const Shop& s)
: Building(s.getLocation(), s.getSize(), s.getHealth(), 2) {
	REQUIRE(s.isInitialized(), "Shop is initialized");

	fMyself = this;
	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();
	fPoliceTruckAssigned = s.fPoliceTruckAssigned;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == s.getSecurity(), "Security is copied");
	ENSURE(this->fIsRobbing == s.isRobbing(), "Robbing is copied");
	ENSURE(this->fPoliceTruckAssigned == s.fPoliceTruckAssigned, "PoliceTruckAssigned is copied");
}

void Shop::operator= (const Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");
	REQUIRE(this->isInitialized(), "Shop is initialized");

	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();
	fPoliceTruckAssigned = s.fPoliceTruckAssigned;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->fSecurityLevel == s.fSecurityLevel, "Security is copied");
	ENSURE(this->fIsRobbing == s.fIsRobbing, "Robbing is copied");
	ENSURE(this->fPoliceTruckAssigned == s.fPoliceTruckAssigned, "PoliceTruckAssigned is copied");
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

bool Shop::isPoliceTruckAssigned() const{
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fPoliceTruckAssigned;
}

void Shop::assignPoliceTruck(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->fIsRobbing == true, "The shop is being robbed");

	fPoliceTruckAssigned = true;

	ENSURE(this->fPoliceTruckAssigned == true, "A police truck is assigned");
	return;
}

void Shop::withdrawPoliceTruckAssignment(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->fIsRobbing == false, "The shop is not being robbed anymore");

	fPoliceTruckAssigned = false;

	ENSURE(this->fPoliceTruckAssigned == false, "A police truck is withdrawed");
	return;
}

char Shop::getSymbol() const {
	if (this->isBurning()){
		return '#';
	}
	else{
		return 'W';
	}
}
