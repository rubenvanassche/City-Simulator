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

class City {
public:
	bool isInitialized();

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	City(City& town);
	// REQUIRE(town.isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "City is initialized");

	bool add(FireDepot& depot);
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	bool add(FireTruck& truck);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(truck.isInitialized(), "FireTruck is initialized");

	bool add(Street& street);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(street.isInitialized(), "Street is initialized");

	bool add(House& house);
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(house.isInitialized(), "House is initialized");

	~City();
	// IMPORTANT! BECAUSE WE HOLD A VECTOR OF POINTERS
	// REQUIRE(this->isInitialized(), "City is initialized")
	// ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	// ENSURE(this->fBuildings.empty() == true, "Buildings is empty'd");
	// ENSURE(this->fHorizontals.empty() == true, "Horizontals is empty'd");
	// ENSURE(this->fVerticals.empty() == true, "Verticals is empty'd");
	// ENSURE(this->fVehicles.empty() == true, "Vehicles is empty'd");

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

	std::vector<Building*> getBuildings();
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireDepot*> getFireDepots();
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Vehicle*> getVehicles();
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Street*> getHorizontals();
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Street*> getVerticals();
	// REQUIRE(this->isInitialized(), "City is initialized");

	Point* getCrosspoint(Street& str, Street& astr);

	Point* closestCrosspoint(Street& str, Point& p);
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool isCrosspoint(Point& p);

	bool isInMap(Point& p);

private:
	std::vector<Building*> fBuildings;	// all buildings
	std::vector<FireDepot*> fFireDepots;	// all FireDepots
	std::vector<Street*> fHorizontals;	// all horizontal streets
	std::vector<Street*> fVerticals;	// all vertical streets
	std::vector<Vehicle*> fVehicles;	// all vehicles;

	std::vector<Point*> fUsedPoints;	// all points that have been used (must be pointers, or won't work)

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
