/*
 * City.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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

#include "Ambulance.h"
#include "PoliceTruck.h"
#include "FireTruck.h"

enum EDirection {kHORIZONTAL, kVERTICAL};

class City {
public:
	bool isInitialized() const;

	friend std::ostream& operator<< (std::ostream& stream, City& c);
	// output operator overloading
	// REQUIRE(c.isInitialized(), "City is initialized");

	City();
	// Constructor
	// ENSURE(this->isInitialized(), "City is initialized");

	~City();
	// destructor
	//REQUIRE(this->isInitialized(), "City is initialized");

	//ENSURE(this->getFireDepots().empty(), "FireDepots empty'd");
	//ENSURE(this->getPoliceDepots().empty(), "Policedepots empty'd");
	//ENSURE(this->getHospitals().empty(), "Hospitals empty'd");
	//ENSURE(this->getShops().empty(), "Shops empty'd");
	//ENSURE(this->getHouses().empty(), "Houses empty'd");
	//ENSURE(this->getFireTrucks().empty(), "FireTrucks empty'd");
	//ENSURE(this->getPoliceTrucks().empty(), "PoliceTrucks empty'd);
	//ENSURE(this->getAmbulance().empty(), "Ambulance empty'd");

	bool isDead();
	// checks whether all buildings are burnt down
	// or, also, if all shops are robbed (because there is no food at all)
	// REQUIRE(this->isInitialized(), "City is initialized");

	bool add(const Street& str);
	// add a street, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(str.isInitialized(), "Street is initialized");

	bool add(const FireTruck& truck);
	// add a FireTruck, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(truck.isInitialized(), "Truck is initialized");

	bool add(const PoliceTruck& car);
	// add a PoliceTruck, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(car.isInitialized(), "EmergencyCar is initialized");

	bool add(const Ambulance& ambulance);
	// add an ambulance, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(ambulance.isInitialized(), "Ambulance is initialized");

	bool add(const FireDepot& depot);
	// add a street, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	bool add(const PoliceDepot& depot);
	// add a PoliceDepot, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "PoliceDepot is initialized");

	bool add(const Hospital& depot);
	// add a hospital, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(depot.isInitialized(), "Hospital is initialized");

	bool add(const House& house);
	// add a house, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(house.isInitialized(), "House is initialized");

	bool add(const Shop& shop);
	// add a shop, return whether succeed
	//REQUIRE(this->isInitialized(), "City is initialized");
	//REQUIRE(shop.isInitialized(), "Shop is initialized");

	FireDepot* findFireDepot(const std::string& name);
	// find a firedepot with the given name, NULL if not in city
	// REQUIRE(this->isInitialized(), "City is initialized");

	Hospital* findHospital(const std::string& name);
	// find a hospital with the given name, NULL if not in city
	// REQUIRE(this->isInitialized(), "City is initialized");

	PoliceDepot* findPoliceDepot(const std::string& name);
	// find a policedepot with the given name, NULL if not in city
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<House*> getHouses() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireDepot*> getFireDepots() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<PoliceDepot*> getPoliceDepots() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Hospital*> getHospitals() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Shop*> getShops() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireTruck*> getFireTrucks() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<PoliceTruck*> getPoliceTrucks() const;
	// REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Ambulance*> getAmbulances() const;
	// REQUIRE(this->isInitialized(), "City is initialized");


	bool isInMap(const Point& p);
	// checks whether a given point is on a street (so you can drive there)
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(p.isInitialized(), "City is initialized");

	Street* findStreet(const Point& position, const EDirection& dir);
	// find a street with the given position and desired direction (if not found, try the other direction)
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(position.isInitialized(), "Point is initialized");

	Point findClosestCrosspoint(const Point& position);
	// find the closest crosspoint;
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(position.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInMap(position) == true, "Position is in roadmap");

	Point nextStep(const Point& curPos, const Point& destination);
	// find the next step the driver has to take to go 1 step closer to the destination given
	// REQUIRE(this->isInitialized(), "City is initialized");
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(this->isInMap(curPos), "CurPos is in roadmap");
	// REQUIRE(this->isInMap(destination), "Destination is in roadmap");

	std::ostream& print();
	// Gives a graphical impression of the city
	// REQUIRE(this->isInitialized(), "City is initialized");

private:
	Check fChecker;
	std::vector<Street*> fVerticals;
	std::vector<Street*> fHorizontals;

	std::vector<FireDepot*> fFireDepots;
	std::vector<PoliceDepot*> fPoliceDepots;
	std::vector<Hospital*> fHospitals;
	std::vector<Shop*> fShops;
	std::vector<House*> fHouses;

	std::vector<FireTruck*> fFireTrucks;
	std::vector<PoliceTruck*> fPoliceTrucks;
	std::vector<Ambulance*> fAmbulances;

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
