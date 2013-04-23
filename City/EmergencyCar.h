/*
 * EmergencyCar.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#ifndef EMERGENCYCAR_H_
#define EMERGENCYCAR_H_

#include "Vehicle.h"
#include "Depot.h"

class EmergencyCar: public Vehicle {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	EmergencyCar(const std::string& name, Depot* base);
	// constructor
	// REQUIRE(base->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->fBase == base, "Base is set");
	// ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	// ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	// ENSURE(this->fBuilding == NULL, "EmergencyCar does not have a building yet");

	EmergencyCar(const EmergencyCar& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	void operator= (const EmergencyCar& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	Depot* getBase() const;
	// get the  its base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	Building* getBuilding() const;
	// get the building that the firetruck has to extinguish
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	bool isInDepot() const;
	// checks whether the truck is in the depot now
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	void send(Building* building, const Point& destination);
	// send the truck to the building that's on fire
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInDepot(), "EmergencyCar is in depot");
	// ENSURE(this->fBuilding == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->getPosition() == this->fBase->getEntrance(), "EmergencyCar is at the entrance");

	void sendBack();
	// send the truck back to it's base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	// ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");

	bool isAtEntranceDepot() const;
	// checks whether the firetruck is at the entrance of its base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	void enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(this->getPosition() == this->fBase->getEntrance(), "EmergencyCar is at entrance");
	// ENSURE(this->getPosition() == this->fBase->getLocation(), "EmergencyCar is now in depot");
	// ENSURE(this->getDestination() == this->fBase->getLocation(), "EmergencyCar is now in depot");

private:
	Building* fBuilding;	// a pointer to a building the emergency has to be there
	Depot* fBase;	// a pointer to its base

	EmergencyCar* fMyself;
};

#endif /* EMERGENCYCAR_H_ */
