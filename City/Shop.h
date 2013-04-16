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
	bool isInitialized();
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Shop& s);
	// output operator overloading
	// REQUIRE(s.isInitialized(), "Shop is initialized");

	Shop(Point& location, Size& size, double health, int security);
	// constructor
	// REQUIRE(location.isInitialized(), "Location is initialized");
	// REQUIRE(size.isInitialized(), "Size is initialized");
	// REQUIRE(health >= 0, "Positive healthpoints");
	// REQUIRE(security >= 0, "Positive Security");
	// ENSURE(this->isInitialized(), "Shop is initialized");

	Shop(Shop& s);
	// copy constructor
	// REQUIRE(h.isInitialized(), "Shop is initialized");
	// ENSURE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	// ENSURE(this->getSecurity() == s.getSecurity, "Security is copied")
	// ENSURE(this->getSize() == s.getSize(), "Size is copied");
	// ENSURE(this->getLocation() == s.getLocation(), "Location is copied");

	bool operator= (Shop& s);
	// copy by assignment operator overloading
	// REQUIRE(h.isInitialized(), "Shop is initialized");
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// ENSURE(this->getHealth() == s.getHealth(), "Health is copied");
	// ENSURE(this->getSecurity() == s.getSecurity, "Security is copied")
	// ENSURE(this->getSize() == s.getSize(), "Size is copied");
	// ENSURE(this->getLocation() == s.getLocation(), "Location is copied");

	int getSecurity();
	// Returns the securitylevel of a shop
	// REQUIRE(this->isInitialized(), "Shop is initialized");

	bool isRobbing();
	// checks whether the shop is being robbed
	// REQUIRE(this->isInitialized(), "Shop is initialized");

	bool StartRobbing();
	// Starts a robbery
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(this->getSecurity() > 0, "Security Level is positive");
	// ENSURE(this->fIsRobbing == true, "Robbery started");

	bool rob(int substracter=1);
	// substract the shops its security level by a given value
	// REQUIRE(this->isInitialized(), "Shop is initialized");
	// REQUIRE(substracter >= 0, "Substracter is positive");
	// REQUIRE(this->fIsRobbing, "Robbery is going on");

	bool StopRobbing();
	// stop the robbery
	// REQUIRE(this->isInitialized(), "Building is initialized");
	// ENSURE(this->fIsRobbing == false, "The building is not being robbed anymore");

private:
	Shop* fMyself;

	bool fIsRobbing;
	int fSecurityLevel;
};

#endif /* SHOP_H_ */
