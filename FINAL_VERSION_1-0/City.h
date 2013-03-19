/*
 * City.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef CITY_H_
#define CITY_H_

#include <iostream>
#include "DesignByContract.h"
#include "FireDepot.h"
#include "FireTruck.h"
#include "Street.h"
#include "House.h"
#include <fstream>
#include "WorldMap.h"

class City {
public:
	bool isInitialized();

//	friend std::ostream& operator<< (std::ostream& stream, City& objectCity);

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	City(City& town);
	// REQUIRE(town.isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "City is initialized");

	bool addFireDepot(FireDepot& depot);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(depot.isInitialized(), "FireDepot is initialized");

	bool addFireTruck(FireTruck& truck);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(truck.isInitialized(), "FireTruck is initialized");

	bool addStreet(Street& street);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(street.isInitialized(), "Street is initialized");

	bool addHouse(House& house);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(house.isInitialized(), "House is initialized");

	~City();
	// IMPORTANT! BECAUSE WE HOLD A VECTOR OF POINTERS
	// REQUIRE(this->isInitialized(), "City is initialized")
	// ENSURE(this->fFireDepots.empty(), "FireDepots is empty'd")
	// ENSURE(this->fHouses.empty(), "Houses is empty'd")

	bool isDead();
	// Checks whether there are no houses that is not fully burned down
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool fireBreaksOut();
	// REQUIRE( (this->fTown->isDead()) == false, "City is not dead");
	// ENSURE(City::fHouses[index]->isBurning(), "House is not set on fire");

	bool burningDown();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool driveTrucks();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool extinguish();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool statusBurningHouses(const char* fileName);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool statusTrucksOnWay(const char* fileName);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool statusAvailableTrucks(const char* fileName);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool allTrucksBack();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool check(House& house);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(house.isInitialized(), "House is initialized");

	bool check(FireDepot& depot);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	bool check(Street& street);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(street.isInitialized(), "Street is initialized");

	bool checkPoint(Point& p);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	bool isOnHouse(Point &p);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	bool isOnStreet(Point &p);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	bool checkPoint(Point& p, bool isStreet);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	bool isOnFireDepot(Point &p);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	void error(int level);
	// REQUIRE(this->isInitialized(), "City is initialized");

	int fFailure;
	// Sets 0 when everything is ok, 1 when something went wrong(but program can still work) and 2 when total crash



private:
	std::vector<FireDepot*> fFireDepots;	// all firedepots (must be pointers, or won't work)
	std::vector<House*> fHouses;	// all houses (must be pointers, or won't work)
	std::vector<Point*> fUsedPoints;	// all points that have been used (must be pointers, or won't work)
	WorldMap fMap;

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
