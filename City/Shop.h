/*
 * Shop.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 *
 */

#ifndef SHOP_H_
#define SHOP_H_

#include "Building.h"
#include "DesignByContract.h"
#include <iostream>

class Shop: public Building {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Shop& s);
	// output operator overloading
	// REQUIRE(s.isInitialized(), "Shop is initialized");

	Shop(const Point& location, const Size& size, const double& health, const int& security);
	// constructor
	// REQUIRE(security >= 0, "Positive Security");
	// ENSURE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->fSecurityLevel == security, "SecurityLevel is set");
	// ENSURE(this->fIsRobbing == false, "Shop is not being robbed (yet)");

	Shop(const Shop& s);
	// copy constructor
	// REQUIRE(h.isInitialized(), "Shop is initialized");
	// ENSURE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->fSecurityLevel == s.fSecurityLevel, "Security is copied")
	// ENSURE(this->fIsRobbing == s.isRobbing(), "Robbing is copied");

	void operator= (const Shop& s);
	// copy by assignment operator overloading
	// REQUIRE(h.isInitialized(), "Shop is initialized");
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->fSecurityLevel == s.fSecurityLevel, "Security is copied")
	// ENSURE(this->fIsRobbing == s.fIsRobbing, "Robbing is copied");

	int getSecurity() const;
	// Returns the securitylevel of a shop
	// REQUIRE(this->isInitialized(), "Shop is initialized");

	bool isRobbing() const;
	// checks whether the shop is being robbed
	// REQUIRE(this->isInitialized(), "Shop is initialized");

	void  StartRobbing();
	// Starts a robbery
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(this->getSecurity() > 0, "Security Level is positive");
	// ENSURE(this->fIsRobbing == true, "Robbery started");

	void rob(int substracter=1);
	// substract the shops its security level by a given value
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(substracter >= 0, "Substracter is positive");
	// REQUIRE(this->fIsRobbing, "Robbery is going on");

	void StopRobbing();
	// stop the robbery
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->fIsRobbing == false, "The shop is not being robbed anymore");

	bool isPoliceTruckAssigned() const;
	// checks whether a police truck is assigned to this shop
	// REQUIRE(this->isInitialized(), "Shop is initialized");

	void assignPoliceTruck();
	// assign a police truck to the shop
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(this->fIsRobbing == true, "The shop is being robbed");
	// ENSURE(this->fPoliceTruckAssigned == true, "A police truck is assigned");

	void withdrawPoliceTruckAssignment();
	// send the police truck back to his depot
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(this->fIsRobbing == false, "The shop is not being robbed anymore");
	// ENSURE(this->fPoliceTruckAssigned == false, "A police truck is withdrawed");

	char getSymbol() const;
	// Returns the symbol of this instance in the city to be used with the graphical impression
	// REQUIRE(this->isInitialized(), "Shop is initialized");

private:
	Shop* fMyself;

	bool fIsRobbing;
	int fSecurityLevel;
	bool fPoliceTruckAssigned;
};

#endif /* SHOP_H_ */
