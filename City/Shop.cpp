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
	ENSURE(this->getSecurity() == security, "SecurityLevel is set");
	ENSURE(this->isRobbing() == false, "Shop is not being robbed (yet)");
	ENSURE(this->isPoliceTruckAssigned() == false, "There is no PoliceTruck assigned to the shop");
}

Shop::Shop(const Shop& s)
: Building(s.getLocation(), s.getSize(), s.getHealth(), 2) {
	REQUIRE(s.isInitialized(), "Shop is initialized");

	fMyself = this;
	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();
	fPoliceTruckAssigned = s.fPoliceTruckAssigned;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->isRobbing() == s.isRobbing(), "Robbing is copied");
	ENSURE(this->isPoliceTruckAssigned() == s.isPoliceTruckAssigned(), "PoliceTruckAssigned is copied");
}

void Shop::operator= (const Shop& s){
	REQUIRE(s.isInitialized(), "Shop is initialized");
	REQUIRE(this->isInitialized(), "Shop is initialized");

	fSecurityLevel = s.getSecurity();
	fIsRobbing = s.isRobbing();
	fPoliceTruckAssigned = s.fPoliceTruckAssigned;

	ENSURE(this->isInitialized(), "Shop is initialized");
	ENSURE(this->getSecurity() == s.getSecurity(), "Security is copied");
	ENSURE(this->isRobbing() == s.isRobbing(), "Robbing is copied");
	ENSURE(this->isPoliceTruckAssigned() == s.isPoliceTruckAssigned(), "PoliceTruckAssigned is copied");
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

bool Shop::isEmpty() const {
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fSecurityLevel <= 0;
}

void Shop::startRobbing(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->isEmpty() == false, "Shop is not empty");
	REQUIRE(this->isRobbing() == false, "Shop is not being robbed already");

	fIsRobbing = true;

	ENSURE(this->isRobbing() == true, "Robbery started");
	return;
}

void Shop::rob(int substracter){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(substracter >= 0, "Substracter is positive");
	REQUIRE(this->isRobbing() == true, "Robbery is going on");

	fSecurityLevel -= substracter;

	if (fSecurityLevel == 0) {
		fIsRobbing = false;
	}

	return;
}


void Shop::stopRobbing(){
	REQUIRE(this->isInitialized(), "Building is initialized");
	REQUIRE(this->isRobbing() == true, "Shop is being robbed");

	fIsRobbing = false;

	ENSURE(this->isRobbing() == false, "The building is not being robbed anymore");

	return;
}

bool Shop::isPoliceTruckAssigned() const{
	REQUIRE(this->isInitialized(), "Shop is initialized");

	return fPoliceTruckAssigned;
}

void Shop::assignPoliceTruck(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->isRobbing() == true, "The shop is being robbed");
	REQUIRE(this->isPoliceTruckAssigned() == false, "There is no PoliceTruck assigned already");

	fPoliceTruckAssigned = true;

	ENSURE(this->isPoliceTruckAssigned() == true, "A police truck is assigned");
	return;
}

void Shop::withdrawPoliceTruckAssignment(){
	REQUIRE(this->isInitialized(), "Shop is initialized");
	REQUIRE(this->isRobbing() == false, "The shop is not being robbed anymore");
	REQUIRE(this->isPoliceTruckAssigned() == true, "A police truck is assigned");

	fPoliceTruckAssigned = false;

	ENSURE(this->isPoliceTruckAssigned() == false, "A police truck is withdrawed");
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
