/*
 * City.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "City.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

bool City::isInitialized() const {
	return fMyself == this;
}


std::ostream& operator<< (std::ostream& stream, City& c) {
	REQUIRE(c.isInitialized(), "City is initialized");

	stream << c.print();
	return stream;
}


City::City() {

	fMyself = this;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		delete fFireDepots[index];
	}
	fFireDepots.clear();

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		delete fPoliceDepots[index];
	}
	fPoliceDepots.clear();

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		delete fHospitals[index];
	}
	fHospitals.clear();

	for (unsigned int index = 0; index < fShops.size(); index++) {
		delete fShops[index];
	}
	fShops.clear();

	for (unsigned int index = 0; index < fHouses.size(); index++) {
		delete fHouses[index];
	}
	fHouses.clear();

	for (unsigned int index = 0; index < fHorizontals.size(); index++) {
		delete fHorizontals[index];
	}
	fHorizontals.clear();

	for (unsigned int index = 0; index < fVerticals.size(); index++) {
		delete fVerticals[index];
	}
	fVerticals.clear();

	for (unsigned int index = 0; index < fFireTrucks.size(); index++) {
		delete fFireTrucks[index];
	}
	fFireTrucks.clear();

	for (unsigned int index = 0; index < fPoliceTrucks.size(); index++) {
		delete fPoliceTrucks[index];
	}
	fPoliceTrucks.clear();

	for (unsigned int index = 0; index < fAmbulances.size(); index++) {
		delete fFireTrucks[index];
	}
	fAmbulances.clear();

	ENSURE(this->fFireDepots.empty(), "FireDepots empty'd");
	ENSURE(this->fPoliceDepots.empty(), "Policedepots empty'd");
	ENSURE(this->fHospitals.empty(), "Hospitals empty'd");
	ENSURE(this->fShops.empty(), "Shops empty'd");
	ENSURE(this->fHouses.empty(), "Houses empty'd");
	ENSURE(this->fHorizontals.empty(), "Horizontals empty'd");
	ENSURE(this->fVerticals.empty(), "Verticals empty'd");
	ENSURE(this->fFireTrucks.empty(), "FireTrucks empty'd");
	ENSURE(this->fPoliceTrucks.empty(), "PoliceTrucks empty'd");
	ENSURE(this->fAmbulances.empty(), "Ambulance empty'd");
}

bool City::add(const Street& str) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(str.isInitialized(), "Street is initialized");

	if (!fChecker.go(str) ) {
		return false;
	}

	if (str.isVertical()) {
		Street* ptrStreet = new Street(str);
		fVerticals.push_back(ptrStreet);
		return true;
	}
	else if (str.isHorizontal()) {
		Street* ptrStreet = new Street(str);
		fHorizontals.push_back(ptrStreet);
		return true;
	}
	else {
		return false;
	}
}


bool City::add(const FireTruck& truck){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(truck.isInitialized(), "Truck is initialized");

	FireTruck* ptrTruck = new FireTruck(truck);
	fFireTrucks.push_back(ptrTruck);
	return true;
}

bool City::add(const PoliceTruck& car){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(car.isInitialized(), "PoliceCar is initialized");

	PoliceTruck* ptrCar = new PoliceTruck(car);
	fPoliceTrucks.push_back(ptrCar);
	return true;
}

bool City::add(const Ambulance& ambulance){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(ambulance.isInitialized(), "Ambulance is initialized");

	Ambulance* ptrAmbulance = new Ambulance(ambulance);
	fAmbulances.push_back(ptrAmbulance);
	return true;
}

bool City::add(const FireDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	FireDepot* ptrDepot = new FireDepot(depot);
	fFireDepots.push_back(ptrDepot);
	return true;
}

bool City::add(const PoliceDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "PoliceDepot is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	PoliceDepot* ptrDepot = new PoliceDepot(depot);
	fPoliceDepots.push_back(ptrDepot);
	return true;
}

bool City::add(const Hospital& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "Hospital is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	Hospital* ptrDepot = new Hospital(depot);
	fHospitals.push_back(ptrDepot);
	return true;
}

bool City::add(const House& house) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	if (!fChecker.go(house)) {
		return false;
	}

	House* ptrHouse = new House(house);
	fHouses.push_back(ptrHouse);
	return true;
}

bool City::add(const Shop& shop) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(shop.isInitialized(), "Shop is initialized");

	if (!fChecker.go(shop)) {
		return false;
	}

	Shop* ptrShop = new Shop(shop);
	fShops.push_back(ptrShop);
	return true;
}

FireDepot* City::findFireDepot(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->getName() == name) {
			return fFireDepots[index];
		}
	}

	return NULL;
}

Hospital* City::findHospital(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->getName() == name) {
			return fHospitals[index];
		}
	}

	return NULL;
}

PoliceDepot* City::findPoliceDepot(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->getName() == name) {
			return fPoliceDepots[index];
		}
	}

	return NULL;
}

std::vector<Building*> City::getBuildingsOnFire() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Building*> vecBuilding;

	for (unsigned int index = 0; index < fHouses.size(); index++) {
		if (fHouses[index]->isBurning()) {
			vecBuilding.push_back(fHouses[index]);
		}
	}

	for (unsigned int index = 0; index < fShops.size(); index++) {
		if (fShops[index]->isBurning()) {
			vecBuilding.push_back(fShops[index]);
		}
	}

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->isBurning()) {
			vecBuilding.push_back(fPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->isBurning()) {
			vecBuilding.push_back(fHospitals[index]);
		}
	}

	return vecBuilding;
}

std::vector<FireDepot*> City::getFireDepotsOnFire() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireDepot*> vecDepot;

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->isBurning()) {
			vecDepot.push_back(fFireDepots[index]);
		}
	}

	return vecDepot;
}

std::vector<Building*> City::getBuildingsToRepair() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Building*> vecBuildings;


	for (unsigned int index = 0; index < fHouses.size(); index++) {
		if (fHouses[index]->startRepair()) {
			vecBuildings.push_back(fHouses[index]);
		}
	}

	for (unsigned int index = 0; index < fShops.size(); index++) {
		if (fShops[index]->startRepair()) {
			vecBuildings.push_back(fShops[index]);
		}
	}

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->startRepair()) {
			vecBuildings.push_back(fPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->startRepair()) {
			vecBuildings.push_back(fHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->startRepair()) {
			vecBuildings.push_back(fFireDepots[index]);
		}
	}

	return vecBuildings;
}

std::vector<Shop*> City::getRobbingShops() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Shop*> vecShops;

	for (unsigned int index = 0; index < fShops.size(); index++) {
		if (fShops[index]->isRobbing()) {
			vecShops.push_back(fShops[index]);
		}
	}

	return vecShops;
}

House* City::randHouse() {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int index = std::rand() % fHouses.size();

	if (fHouses[index]->isBurning()) {
		// the house is already on fire
		return this->randHouse();
	}

	return fHouses[index];
}

Shop* City::randShop(const bool& fire, const bool& rob) {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int index = std::rand() % fShops.size();

	if (fire) {
		if (fShops[index]->isBurning()) {
			return this->randShop(fire, rob);
		}

		return fShops[index];
	}
	else if (rob) {
		if (fShops[index]->isRobbing()) {
			return this->randShop(fire, rob);
		}

		return fShops[index];
	}
	else {
		return NULL;
	}
}

FireDepot* City::randFireDepot() {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int index = std::rand() % fFireDepots.size();

	if (fFireDepots[index]->isBurning()) {
		// the depot is already on fire
		return this->randFireDepot();
	}

	return fFireDepots[index];
}

PoliceDepot* City::randPoliceDepot() {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int index = std::rand() % fPoliceDepots.size();

	if (fPoliceDepots[index]->isBurning()) {
		// the house is already on fire
		return this->randPoliceDepot();
	}

	return fPoliceDepots[index];
}

Hospital* City::randHospital() {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int index = std::rand() % fHospitals.size();

	if (fHospitals[index]->isBurning()) {
		// the house is already on fire
		return this->randHospital();
	}

	return fHospitals[index];
}

std::vector<FireTruck*> City::getFireTrucksInDepot() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireTruck*> vecTrucks;

	for (unsigned int index = 0; index < fFireTrucks.size(); index++) {
		if (fFireTrucks[index]->isInDepot()) {
			vecTrucks.push_back(fFireTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<PoliceTruck*> City::getPoliceTrucksInDepot() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<PoliceTruck*> vecTrucks;

	for (unsigned int index = 0; index < fPoliceTrucks.size(); index++) {
		if (fPoliceTrucks[index]->isInDepot()) {
			vecTrucks.push_back(fPoliceTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<Ambulance*> City::getAmbulancesInDepot() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Ambulance*> vecAmulances;

	for (unsigned int index = 0; index < fAmbulances.size(); index++) {
		if (fAmbulances[index]->isInDepot()) {
			vecAmulances.push_back(fAmbulances[index]);
		}
	}

	return vecAmulances;
}

std::vector<FireTruck*> City::getFireTrucksOnWay() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireTruck*> vecTrucks;

	for (unsigned int index = 0; index < fFireTrucks.size(); index++) {
		if (fFireTrucks[index]->isOnWay()) {
			vecTrucks.push_back(fFireTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<PoliceTruck*> City::getPoliceTrucksOnWay() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<PoliceTruck*> vecTrucks;

	for (unsigned int index = 0; index < fPoliceTrucks.size(); index++) {
		if (fPoliceTrucks[index]->isOnWay()) {
			vecTrucks.push_back(fPoliceTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<Ambulance*> City::getAmbulancesOnWay() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Ambulance*> vecAmulances;

	for (unsigned int index = 0; index < fAmbulances.size(); index++) {
		if (fAmbulances[index]->isOnWay()) {
			vecAmulances.push_back(fAmbulances[index]);
		}
	}

	return vecAmulances;
}

std::vector<FireTruck*> City::getFireTrucksArrived() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<FireTruck*> vecTrucks;

	for (unsigned int index = 0; index < fFireTrucks.size(); index++) {
		if (fFireTrucks[index]->isArrived()) {
			vecTrucks.push_back(fFireTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<PoliceTruck*> City::getPoliceTrucksArrived() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<PoliceTruck*> vecTrucks;

	for (unsigned int index = 0; index < fPoliceTrucks.size(); index++) {
		if (fPoliceTrucks[index]->isArrived()) {
			vecTrucks.push_back(fPoliceTrucks[index]);
		}
	}

	return vecTrucks;
}

std::vector<Ambulance*> City::getAmbulancesArrived() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Ambulance*> vecAmbuces;

	for (unsigned int index = 0; index < fAmbulances.size(); index++) {
		if (fAmbulances[index]->isArrived()) {
			vecAmbuces.push_back(fAmbulances[index]);
		}
	}

	return vecAmbuces;
}

Street* City::findStreet(const Point& position, const EDirection& dir) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(position.isInitialized(), "Point is initialized");

	if (dir == kHORIZONTAL) {
		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (fHorizontals[index]->isElement(position)) {
				return fHorizontals[index];
			}
		}

		// if you've reached here, then you have to look up in the verticals
		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (fVerticals[index]->isElement(position)) {
				return fVerticals[index];
			}
		}

		return NULL; // if not found
	}
	else if (dir == kVERTICAL) {
		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (fVerticals[index]->isElement(position)) {
				return fVerticals[index];
			}
		}

		// if you've reached here, then you have to look up in the horizontals
		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (fHorizontals[index]->isElement(position)) {
				return fHorizontals[index];
			}
		}

		return NULL; // if not found
	}
	else {
		return NULL;
	}
}

Point City::findClosestCrosspoint(const Point& position) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(position.isInitialized(), "Point is initialized");

	// first find the street where you are
	Street* street = this->findStreet(position, kVERTICAL);

	if (street->isVertical()) {
		// then search in the horizontals all streets that is crossing with this street
		std::vector<Point> vecPoints;

		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (street->isCrossing(*fHorizontals[index])) {
				Point crosspoint = street->getCrosspoint(*fHorizontals[index]);
				vecPoints.push_back(crosspoint);
			}
		}

		// then compare it with the current position
		Point crosspoint = vecPoints[0];
		for (unsigned int index = 0; index < vecPoints.size(); index++) {
			int delta0 = std::abs(crosspoint.getY() - position.getY());
			int delta1 = std::abs(vecPoints[index].getY() - position.getY() );

			if (delta1 < delta0) {
				// then change the crosspoint
				crosspoint = vecPoints[index];
			}
		}

		return crosspoint;
	}
	else {
		// street is horizontal
		// so find all streets in the verticals that is crossing with this street

		std::vector<Point> vecPoints;

		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (street->isCrossing(*fVerticals[index])) {
				Point crosspoint = street->getCrosspoint(*fVerticals[index]);
				vecPoints.push_back(crosspoint);
			}
		}

		// then compar it with the current position
		Point crosspoint = vecPoints[0];
		for (unsigned int index = 0; index < vecPoints.size(); index++) {
			int delta0 = std::abs(crosspoint.getX() - position.getX());
			int delta1 = std::abs(vecPoints[index].getX() - position.getX());

			if (delta1 < delta0) {
				// then change the crosspoint
				crosspoint = vecPoints[index];
			}
		}

		return crosspoint;
	}
}

Point City::nextStep(const Point& curPos, const Point& destination) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");

	int x = curPos.getX();
	int y = curPos.getY();

	Street* destStr = this->findStreet(destination, kHORIZONTAL);
	if (destStr->isElement(curPos)) {
		// current position is part of the  destination street
		if (destStr->isVertical()) {
			if (destination.getY() > curPos.getY() ) {
				return Point(x, y + 1);
			}
			else if (destination.getY() < curPos.getY() ) {
				return Point(x, y - 1);
			}

			return curPos;	// you're already on the destination
		}
		else { // destination street is horizontal
			if (destination.getX() > curPos.getX() ) {
				return Point(x + 1, y);
			}
			else if (destination.getX() < curPos.getX()) {
				return Point(x - 1, y);
			}

			return curPos;	// you're already on the destination
		}
	}

	// else, you have to find in which street you are now
	Street* curStr;
	if (destStr->isVertical()) {
		curStr = this->findStreet(curPos, kHORIZONTAL);
	}
	else {
		curStr = this->findStreet(curPos, kVERTICAL);
	}

	if (destStr->isCrossing(*curStr)) {
		// then find the crosspoint
		Point crosspoint = destStr->getCrosspoint(*curStr);
		if (curStr->isVertical()) {
			if (crosspoint.getY() > curPos.getY()) {
				return Point(x, y + 1);
			}
			else if (crosspoint.getY() < curPos.getY() ) {
				return Point(x, y - 1);
			}

			return curPos;
		}
		else {
			if (crosspoint.getX() > curPos.getX() ) {
				return Point(x + 1, y);
			}
			else if (crosspoint.getX() < curPos.getX() ) {
				return Point(x - 1, y);
			}

			return curPos;
		}
	}

	if (destStr->isParallel(*curStr) ) {
		// then find the closest crosspoint
		Point crosspoint = this->findClosestCrosspoint(curPos);
		if (curStr->isVertical()) {
			if (crosspoint.getY() > curPos.getY()) {
				return Point(x, y + 1);
			}
			else if (crosspoint.getY() < curPos.getY()) {
				return Point(x, y - 1);
			}

			return curPos;
		}
		else {
			if (crosspoint.getX() > curPos.getX()) {
				return Point(x + 1, y);
			}
			else if (crosspoint.getX() < curPos.getX()) {
				return Point(x - 1, y);
			}

			return curPos;
		}
	}

	return curPos;
}

bool City::isInMap(const Point& p) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fVerticals.size(); index++) {
		if (fVerticals[index]->isElement(p)) {
			return true;
		}
	}

	for (unsigned int index = 0; index < fHorizontals.size(); index++) {
		if (fHorizontals[index]->isElement(p)) {
			return true;
		}
	}

	return false;
}

std::ostream& City::print(){
	  std::filebuf fb; // No idea why this stands here but it's the only way to make it work
	  std::ostream stream(&fb);


	  // FireDepots
	  for (unsigned int i = 0;i < fFireDepots.size();i++){
		  this->fFireDepots.at(i);
	  }

	  stream << "leeg";

	  return stream;
}
