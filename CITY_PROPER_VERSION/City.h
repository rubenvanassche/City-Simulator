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
#include <vector>
#include "DesignByContract.h"
#include "FireDepot.h"
#include "FireTruck.h"
#include "Street.h"
#include "House.h"
#include "Size.h"
#include <fstream>
#include <algorithm> 

class City {
public:
	bool isInitialized();

//	friend std::ostream& operator<< (std::ostream& stream, City& objectCity);

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	City(const City& town);
	// REQUIRE(town.isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "City is initialized");


	bool addFireDepot(FireDepot& depot);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	bool addFireTruck(FireTruck& truck);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(truck.isInitialized(), "FireTruck is initialized");

	bool addStreet(Street& street);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(street.isInitialized(), "Street is initialized");

	bool addHouse(House& house);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(house.isInitialized(), "House is initialized");

	bool trucksOnWay();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool writeTrucksStatus(const char* filename);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool housesOnFire();
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool writeHousesStatus(const char* filename);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool writeDepotsStatus(const char* filename);
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Point*> calculatePoints(House& house);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(house.isInitialized(), "House is initialized");

	std::vector<Point*> calculatePoints(FireDepot& depot);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	std::vector<Point*> calculatePoints(int width, int height, Point& location);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(location.isInitialized(), "Location is initialized");
	// ENSURE(out.size() > 0, "There are no points given as output");

	std::vector<Point*> calculatePoints(Street& street);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(street.isInitialized(), "Street is initialized");
	// ENSURE(out.size() > 0, "There are no points given as output");

	bool check(House& house);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(house.isInitialized(), "House is initialized");

	bool check(FireDepot& depot);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	bool check(int width, int height, Point &location);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(location.isInitialized(), "Location is initialized");

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

	bool isOnFireDepot(Point &p);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Location is initialized");

	void error(int level);
	// REQUIRE(this->isInitialized(), "City is initialized");

	int fFailure;
	// Sets 0 when everything is ok, 1 when something went wrong(but program can still work) and 2 when total crash

	~City();
	// IMPORTANT! BECAUSE WE HOLD A VECTOR OF POINTERS
	// REQUIRE(this->isInitialized(), "City is initialized")
	// ENSURE(this->fFireDepots.empty(), "FireDepots is empty'd")
	// ENSURE(this->fStreets.empty(), "Street is empty'd")
	// ENSURE(this->fHouses.empty(), "Houses is empty'd")

private:
	std::vector<FireDepot*> fFireDepots;	// all firedepots (must be pointers, or won't work)
	std::vector<Street*> fStreets;	// all streets (must be pointers, or won't work)
	std::vector<House*> fHouses;	// all houses (must be pointers, or won't work)
	std::vector<FireTruck*> fTrucks;	// all trucks (must be pointers, or won't work)

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
