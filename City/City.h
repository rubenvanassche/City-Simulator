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
#include "Check.h"
#include <fstream>

class City {
public:
	bool isInitialized();

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	City(City& town);
	// copy constructor
	// REQUIRE(town.isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(this->fFireDepots.size() == town.fFireDepots.size(), "FireDepots copied");
	// ENSURE(this->fFireTrucks.size() == town.fFireTrucks.size(), "FireTrucks copied");
	// ENSURE(this->fHouses.size() == town.fHouses.size(), "Houses copied");
	// ENSURE(this->fVerticals.size() == town.fVerticals.size(), "Verticals copied");
	// ENSURE(this->fHorizontals.size() == town.fHorizontals.size(), "Horizontals copied");

	bool add(FireDepot& depot);
	// add a firedepot
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(depot.isInitialized(), "FireDepot is initialized");

	bool add(FireTruck& truck);
	// add a firetruck
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(truck.isInitialized(), "FireTruck is initialized");

	bool add(Street& street);
	// add a street
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(street.isInitialized(), "Street is initialized");

	bool add(House& house);
	// add a house
	// ENSURE(this->isInitialized(), "City is initialized");
	// ENSURE(house.isInitialized(), "House is initialized");

	~City();
	// destructor
	// REQUIRE(this->isInitialized(), "City is initialized");
	// ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	// ENSURE(this->fHouses.empty() == true, "Buildings is empty'd");
	// ENSURE(this->fHorizontals.empty() == true, "Horizontals is empty'd");
	// ENSURE(this->fVerticals.empty() == true, "Verticals is empty'd");
	// ENSURE(this->fFireTrucks.empty() == true, "FireTrucks is empty'd");

	bool isInMap(Point& p);
	// checks whether a point is in the streets
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	std::vector<House*> getHouses();
	// get all the houses
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireTruck*> getTrucks();
	// get all the trucks
	// REQUIRE(this->isInitialized(), "City is initialized");

	Street* findVerticalStreet(Point& p);
	// find a vertical street
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	Street* findHorizontalStreet(Point& p);
	// find a horizontal street
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	Point* findCrosspoint(Street& destStr, Street& curStr, Point& curPos);
	// find the (closest) crosspoint
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(destStr.isInitialized(), "Street is initialized");
	// REQUIRE(curStr.isInitialized(), "Street is initialized");
	// REQUIRE(curPos.isInitialized(), "Point is initialized");

	unsigned int burningHouses();
	// counts the amount of houses on fire
	// REQUIRE(this->isInitialized(), "City is initialized");

	FireDepot* findDepot(std::string& name);
	// find the depot
	// REQUIRE(this->isInitialized(), "City is initialized");


private:
	std::vector<House*> fHouses;	// all Houses
	std::vector<FireDepot*> fFireDepots;	// all FireDepots
	std::vector<FireTruck*> fFireTrucks;	// all firetrucks
	std::vector<Street*> fHorizontals;	// all horizontal streets
	std::vector<Street*> fVerticals;	// all vertical streets

	Check checker;

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
