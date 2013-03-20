/*
 * FireTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef FIRETRUCK_H_
#define FIRETRUCK_H_

#include "Vehicle.h"
#include "DesignByContract.h"
#include <iostream>
#include "House.h"

class FireTruck: public Vehicle {
public:
	bool isInitialized();

	friend std::ostream& operator<< (std::ostream& stream, FireTruck& f);
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	FireTruck(std::string& name, Point& curPos, Point& destination, std::string& basename);
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == name, "Name is initialized");
	// ENSURE(this->getPosition() == curPos, "Position is initialized");
	// ENSURE(this->getDestination() == destination, "Destination is initialized");
	// ENSURE(this->fBaseName == basename, "Base is initialized");

	FireTruck(FireTruck& f);
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// ENSURE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == f.getName(), "Name is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is initialized");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is initialized");
	// ENSURE(this->fBaseName == f.fBaseName, "Base is initialized");

	bool operator= (FireTruck& f);
	// REQUIRE(f.isInitialized(), "FireTruck is initialized");
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->getName() == f.getName(), "Name is initialized");
	// ENSURE(this->getPosition() == f.getPosition(), "Position is initialized");
	// ENSURE(this->getDestination() == f.getDestination(), "Destination is initialized");
	// ENSURE(this->fBaseName == f.fBaseName, "Base is initialized");

	bool setBase(std::string& basename);
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// ENSURE(this->fBaseName == basename, "Basename is set");

	std::string& getBase();
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

	bool setHouseOnFire(House* house);
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");
	// REQUIRE(house->isInitialized(), "House is initialized");

	House& getHouseOnFire();
	// REQUIRE(this->isInitialized(), "FireTruck is initialized");

private:
	std::string fBaseName;
	House* fHouseOnFire;

	FireTruck* fMyself;
};

#endif /* FIRETRUCK_H_ */
