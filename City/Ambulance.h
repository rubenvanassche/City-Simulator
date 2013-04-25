/*
 * Ambulance.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#ifndef AMBULANCE_H_
#define AMBULANCE_H_

#include "Hospital.h"
#include "Vehicle.h"

class Ambulance : public Vehicle {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Ambulance& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");

	Ambulance(const std::string& name, Hospital* base);
	// constructor
	// REQUIRE(base->isInitialized(), "Hospital is initialized");
	// ENSURE(this->isInitialized(), "Ambulance is initialized");
	// ENSURE(this->fBase == base, "Base is set");
	// ENSURE(this->getPosition() == base->getLocation(), "Position is set");
	// ENSURE(this->getDestination() == base->getLocation(), "Destination is set");
	// ENSURE(this->fBuilding == NULL, "Ambulance doesn't have building (yet)" );

	Ambulance(const Ambulance& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");
	// ENSURE(this->isInitialized(), "Ambulance is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	void operator= (const Ambulance& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");
	// ENSURE(this->isInitialized(), "Ambulance is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is copied");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is copied");
	// ENSURE(this->fBase == f.fBase, "Base is copied");
	// ENSURE(this->fBuilding == f.fBuilding, "Building is copied");

	Hospital* getBase() const;
	// get it's base
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");

	Building* getBuilding() const;
	// get the building that the Ambulance has to go
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");

	bool isInDepot() const;
	// Checks whether the ambulance is in the depot now
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");

	void send(Building* building, const Point& destination);
	// send the ambulance to the building with hurts
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// REQUIRE(building->isInitialized(), "Building is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInDepot(), "Ambulance is in depot");
	// ENSURE(this->fBuilding == building, "Building is set");
	// ENSURE(this->getDestination() == destination, "Destination is set");
	// ENSURE(this->getPosition() == this->fBase->getEntrance(), "Ambulance is at the entrance");

	void sendBack();
	// send the ambulance back to it's base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");
	// ENSURE(this->fBuilding == NULL, "EmergencyCar has not a building to extinguish anymore");
	// ENSURE(this->getDestination() == this->fBase->getEntrance(), "Destination is set to it's base");

	bool isAtEntranceDepot() const;
	// checks whether the ambulance is at the entrance of its base
	// REQUIRE(this->isInitialized(), "EmergencyCar is initialized");

	void enterDepot();
	// enter the depot
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");
	// REQUIRE(this->getPosition() == this->fBase->getEntrance(), "Ambulance is at entrance");
	// ENSURE(this->getPosition() == this->fBase->getLocation(), "Ambulance is now in depot");
	// ENSURE(this->getDestination() == this->fBase->getLocation(), "Ambulance is now in depot");

	char getSymbol() const;
	// for graphical impression
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");

private:
	Building* fBuilding;	// a pointer to a building the ambulance has to be there
	Hospital* fBase;	// a pointer to its base

	Ambulance* fMyself;
};

#endif /* AMBULANCE_H_ */
