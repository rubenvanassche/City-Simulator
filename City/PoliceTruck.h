/*
 * PoliceTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#ifndef POLICETRUCK_H_
#define POLICETRUCK_H_

#include "Vehicle.h"
#include "Building.h"
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
	// ENSURE(this->fBase == base, "Base is set");
	// ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	// ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	// ENSURE(this->fBuilding == NULL, "PoliceTruck doesn't have building (yet)" );

	PoliceTruck(const PoliceTruck& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	void operator= (const PoliceTruck& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->isInitialized(), "PoliceTruck is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

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
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(building->isRobbing() == true, "Shop is being robbed");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInDepot(), "PoliceTruck is in depot");
	// ENSURE(this->fBuilding == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->getPosition() == this->fBase->getEntrance(), "PoliceTruck is at the entrance");

	void sendBack();
	// send the PoliceTruck back to it's base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(this->getBuilding()->isBurning() == false, "Building is not on fire anymore");
	// ENSURE(this->fBuilding == NULL, "PoliceTruck has not a building to extinguish anymore");
	// ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");

	bool isAtEntranceDepot() const;
	// checks whether the PoliceTruck is at the entrance of its base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	void enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");
	// REQUIRE(this->getPosition() == this->fBase->getEntrance(), "PoliceTruck is at entrance");
	// ENSURE(this->getPosition() == this->fBase->getLocation(), "PoliceTruck is now in depot");
	// ENSURE(this->getDestination() == this->fBase->getLocation(), "PoliceTruck is now in depot");

	char getSymbol() const;
	// for graphical impression
	// REQUIRE(this->isInitialized(), "PoliceTruck is initialized");

private:
	Shop* fBuilding;
	PoliceDepot* fBase;

	PoliceTruck* fMyself;
};

#endif /* POLICETRUCK_H_ */
