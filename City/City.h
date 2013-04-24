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
#include <fstream>
#include "Street.h"
#include <vector>
#include "Check.h"

#include "FireDepot.h"
#include "PoliceDepot.h"
#include "Hospital.h"
#include "Shop.h"
#include "House.h"

#include "EmergencyCar.h"
#include "Ambulance.h"
#include "PoliceCar.h"
#include "FireTruck.h"

enum EBuilding {kFIREDEPOT, kPOLICEDEPOT, kHOSPITAL, kHOUSE, kSHOP};
enum EDirection {kHORIZONTAL, kVERTICAL};

class City {
public:
	bool isInitialized() const;

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	~City();
	// destructor
	//REQUIRE(this->isInitialized(), "City is initialized");
	//ENSURE(this->fBuildings.empty(), "Buildings empty'd");
	//ENSURE(this->fFireDepots.empty(), "FireDepots empty'd");
	//ENSURE(this->fPoliceDepots.empty(), "Policedepots empty'd");
	//ENSURE(this->fHospitals.empty(), "Hospitals empty'd");
	//ENSURE(this->fHorizontals.empty(), "Horizontals empty'd");
	//ENSURE(this->fVerticals.empty(), "Verticals empty'd");

	bool add(const Street& str);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(str.isInitialized(), "Street is initialized");

	bool add(const EmergencyCar& car);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(car.isInitialized(), "EmergencyCar is initialized");

	bool add(const FireDepot& depot);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	bool add(const PoliceDepot& depot);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "PoliceDepot is initialized");

	bool add(const Hospital& depot);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "Hospital is initialized");

	bool add(const House& house);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(house.isInitialized(), "House is initialized");

	bool add(const Shop& shop);
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(shop.isInitialized(), "Shop is initialized");

	FireDepot* findFireDepot(const std::string& name);
	Hospital* findHospital(const std::string& name);
	PoliceDepot* findPoliceDepot(const std::string& name);

	Building* randBuilding(const bool& onFire = false);
	std::vector< std::pair<Building*, EBuilding> > getBuildingsOnFire();

	Shop* randShop(const bool& isRobbing=false);
	std::vector<Shop*> getRobbingShop();

	Street* findStreet(const Point& position, const EDirection& dir);

	Point nextStep(const Point& curPos, const Point& destination);

/*
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
*/

private:
	Check fChecker;
	std::vector<Street*> fVerticals;
	std::vector<Street*> fHorizontals;

	std::vector<std::pair<Building*, EBuilding> > fBuildings;
	std::vector<FireDepot*> fFireDepots;
	std::vector<PoliceDepot*> fPoliceDepots;
	std::vector<Hospital*> fHospitals;
	std::vector<Shop*> fShops;

	std::vector<EmergencyCar*> fVehicles;

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
