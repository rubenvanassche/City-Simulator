/*
 * PoliceTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#ifndef POLICETRUCK_H_
#define POLICETRUCK_H_

#include "Vehicle.h"
#include "PoliceDepot.h"
#include "Shop.h"

class PoliceTruck: public Vehicle {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, PoliceTruck& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "PoliceTruck is initialized");

	PoliceTruck(const std::string& name, PoliceDepot* base);
	// constructor
	// REQUIRE(base->isInitialized(), "PoliceDepot is initialized");

	// ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->getBase() == base, "Base is set");
	// ENSURE(this->isInDepot(), "PoliceTruck is in depot");
	// ENSURE(this->getShop() == NULL, "PoliceTruck doesn't have a shop (yet)" );

	PoliceTruck(const PoliceTruck& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "PoliceTruck is initialized");

	// ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->getBase() == f.getBase(), "Base is copied");
	// ENSURE(this->getShop() == f.getShop(), "Building is copied");

	void operator= (const PoliceTruck& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	// ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->getBase() == f.getBase(), "Base is copied");
	// ENSURE(this->getShop() == f.getShop(), "Building is copied");

	PoliceDepot* getBase() const;
	// get it's base
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	Shop* getShop() const;
	// get the building that the PoliceTruck has to go
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	bool isInDepot() const;
	// Checks whether the PoliceTruck is in the depot now
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

	void send(Shop* building, const Point& destination);
	// send the PoliceTruck to the building with hurts
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(building->isRobbing() == true, "Shop is being robbed");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInDepot(), "PoliceTruck is in depot");

	// ENSURE(this->getShop() == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->isAtEntranceDepot(), "PoliceTruck is at the entrance of it's base");

	void sendBack();
	// send the PoliceTruck back to it's base
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(this->getShop()->isRobbing() == false, "Shop is not being robbed anymore");

	// ENSURE(this->getShop() == NULL, "PoliceTruck has not a shop to go anymore");
	// ENSURE(this->getDestination() == this->getBase()->getEntrance(), "Destination is set to it's base");

	bool isAtEntranceDepot() const;
	// checks whether the PoliceTruck is at the entrance of its base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	void enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(this->isAtEntranceDepot(), "PoliceTruck is at entrance");
	// REQUIRE(this->getBase()->isBurning(), "It's base is not on fire");
	// REQUIRE(this->getBase()->isDead() == false, "The base is not burnt down");

	// ENSURE(this->isInDepot(), "PoliceTruck is now in depot");

	char getSymbol() const;
	// for graphical impression
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

private:
	Shop* fBuilding;
	PoliceDepot* fBase;

	PoliceTruck* fMyself;
};

#endif /* POLICETRUCK_H_ */
