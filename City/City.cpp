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

	for (unsigned int index = 0; index < fVerticals.size(); index++) {
		delete fVerticals[index];
	}
	fVerticals.clear();

	for (unsigned int index = 0; index < fHorizontals.size(); index++) {
		delete fHorizontals[index];
	}
	fHorizontals.clear();

	for (unsigned int index = 0; index < fBuildings.size(); index++) {
		delete fBuildings[index].first;
	}
	fBuildings.clear();
	fFireDepots.clear();	// because they were also in the buildings, so no leaks will apear
	fPoliceDepots.clear();
	fHospitals.clear();
	fShops.clear();

	for (unsigned int index = 0; index < fVehicles.size(); index++) {
		delete fVehicles[index];
	}
	fVehicles.clear();

	ENSURE(this->fBuildings.empty(), "Buildings empty'd");
	ENSURE(this->fFireDepots.empty(), "FireDepots empty'd");
	ENSURE(this->fPoliceDepots.empty(), "Policedepots empty'd");
	ENSURE(this->fHospitals.empty(), "Hospitals empty'd");
	ENSURE(this->fHorizontals.empty(), "Horizontals empty'd");
	ENSURE(this->fVerticals.empty(), "Verticals empty'd");
	ENSURE(this->fShops.empty(), "Shops empty'd");
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

bool City::add(const EmergencyCar& car) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(car.isInitialized(), "EmergencyCar is initialized");

	EmergencyCar* ptrCar = new EmergencyCar(car);
	fVehicles.push_back(ptrCar);
	return true;
}

bool City::add(const FireDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	FireDepot* ptrDepot = new FireDepot(depot);
	std::pair<Building*, EBuilding> tupple(ptrDepot, kFIREDEPOT);
	fBuildings.push_back(tupple);
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
	std::pair<Building*, EBuilding> tupple(ptrDepot, kPOLICEDEPOT);
	fBuildings.push_back(tupple);
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
	std::pair<Building*, EBuilding> tupple(ptrDepot, kHOSPITAL);
	fBuildings.push_back(tupple);
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
	std::pair<Building*, EBuilding> tupple(ptrHouse, kHOUSE);
	fBuildings.push_back(tupple);
	return true;
}

bool City::add(const Shop& shop) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(shop.isInitialized(), "Shop is initialized");

	if (!fChecker.go(shop)) {
		return false;
	}

	Shop* ptrShop = new Shop(shop);
	std::pair<Building*, EBuilding> tupple(ptrShop, kSHOP);
	fBuildings.push_back(tupple);
	fShops.push_back(ptrShop);
	return true;
}

FireDepot* City::findFireDepot(const std::string& name) {
	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->getName() == name) {
			return fFireDepots[index];
		}
	}

	return NULL;
}

Hospital* City::findHospital(const std::string& name) {
	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->getName() == name) {
			return fHospitals[index];
		}
	}

	return NULL;
}

PoliceDepot* City::findPoliceDepot(const std::string& name) {
	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->getName() == name) {
			return fPoliceDepots[index];
		}
	}

	return NULL;
}

Building* City::randBuilding(const bool& onFire) {
	int index = std::rand() % fBuildings.size();

	if (!onFire) {
		if (!fBuildings[index].first->isBurning()) {
			return fBuildings[index].first;
		}
		else {// then try again
			return this->randBuilding(onFire);
		}
	}
	else {
		return fBuildings[index].first;
	}
}

std::vector< std::pair<Building*, EBuilding> > City::getBuildingsOnFire() {
	std::vector< std::pair<Building*, EBuilding> > vecBuilding;

	for (unsigned int index = 0; index < fBuildings.size(); index++) {
		if (fBuildings[index].first->isBurning()) {
			vecBuilding.push_back(fBuildings[index]);
		}
	}

	return vecBuilding;
}

Shop* City::randShop(const bool& isRobbing) {
	int index = std::rand() % fShops.size();

	return fShops[index];
}

std::vector<Shop*> City::getRobbingShop() {
	std::vector<Shop*> shops;

	for (unsigned int index = 0; index < fShops.size(); index++) {
		if (fShops[index]->isRobbing()) {
			shops.push_back(fShops[index]);
		}
	}

	return shops;
}

Street* City::findStreet(const Point& position, const EDirection& dir) {
	if (dir == kHORIZONTAL) {
		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (fHorizontals[index]->isElement(position)) {
				return fHorizontals[index];
			}
		}

		return NULL;
	}
	else if (dir == kVERTICAL) {
		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (fVerticals[index]->isElement(position)) {
				return fVerticals[index];
			}
		}
		return NULL;
	}
	return NULL;
}

Point City::nextStep(const Point& curPos, const Point& destination) {
	Street* destStr;
	Street* curStr;

	destStr = this->findStreet(destination, kHORIZONTAL);
	if (destStr == NULL) {
		destStr = this->findStreet(destination, kVERTICAL);
	}

	if (destStr->isElement(curPos)) {
		if (destStr->isVertical()) {
			if (destination.getY() > curPos.getY()) {
				return Point(curPos.getX(), curPos.getY() + 1);
			}
			else {
				return Point(curPos.getX(), curPos.getY() - 1);
			}
		}
		else {
			if (destination.getX() > curPos.getX()) {
				return Point(curPos.getX() + 1, curPos.getY() );
			}
			else {
				return Point(curPos.getX() - 1, curPos.getY() );
			}
		}
	}

	if (destStr->isVertical()) {
		curStr = this->findStreet(curPos, kHORIZONTAL);
		if (curStr == NULL) {
			curStr = this->findStreet(curPos, kVERTICAL);
		}
	}
	else {
		curStr = this->findStreet(curPos, kVERTICAL);
		if (curStr == NULL) {
			curStr = this->findStreet(curPos, kHORIZONTAL);
		}
	}

	Street str = *curStr;
	if (destStr->isParallel( str ) ) {
		// do somehting here
	}
	else if (destStr->isCrossing(str)) {
		Point cross = destStr->getCrosspoint(str);
		if (curStr->isVertical()) {
			if (destination.getY() > curPos.getY()) {
				return Point(curPos.getX(), curPos.getY() + 1);
			}
			else {
				return Point(curPos.getX(), curPos.getY() - 1);
			}
		}
		else {
			if (destination.getX() > curPos.getX()) {
				return Point(curPos.getX() + 1, curPos.getY() );
			}
			else {
				return Point(curPos.getX() - 1, curPos.getY() );
			}
		}
	}

}

std::ostream City::print(){
	  std::filebuf fb; // No idea why this stands here but it's the only way to make it work
	  std::ostream stream(&fb);


	  // FireDepots
	  for(int i = 0;i < this->fFireDepots.size();i++){
		  this->fFireDepots.at(i);
	  }

	  stream << "leeg";

	  return stream;
}

/* DO NOT DELETE THIS, this may be usefull
bool City::isInMap(Point& p) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	bool foundHorizontal = false;
	for (unsigned int index=0; index < City::fHorizontals.size(); index++) {
		if (City::fHorizontals[index]->isElement(p) ) {
			return true;
		}
	}

	if (!foundHorizontal) {
		for (unsigned int index=0; index < City::fVerticals.size(); index++) {
			if (City::fVerticals[index]->isElement(p) ) {
				return true;
			}
		}
	}
	return false;
}

std::vector<House*> City::getHouses() {
	REQUIRE(this->isInitialized(), "City is initialized");

	return City::fHouses;
}

std::vector<FireTruck*> City::getTrucks() {
	REQUIRE(this->isInitialized(), "City is initialized");

	return City::fFireTrucks;
}

Street* City::findVerticalStreet(Point& p) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	for (unsigned int index=0; index < City::fVerticals.size(); index++) {
		if (City::fVerticals[index]->isElement(p)) {
			return City::fVerticals[index];
		}
	}

	return NULL;
}

Street* City::findHorizontalStreet(Point& p) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	for (unsigned int index=0; index < City::fVerticals.size(); index++) {
		if (City::fVerticals[index]->isElement(p)) {
			return City::fVerticals[index];
		}
	}

	return NULL;
}

Point* City::findCrosspoint(Street& destStr, Street& curStr, Point& curPos) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(destStr.isInitialized(), "Street is initialized");
	REQUIRE(curStr.isInitialized(), "Street is initialized");
	REQUIRE(curPos.isInitialized(), "Point is initialized");

	if (isCrossing(curStr, destStr) ) {
		return getCrosspoint(destStr, curStr);
	}

	if (isParallel(curStr, destStr) ) {
		std::vector<Point*> crosspoints;

		if (curStr.isVertical() ) {	// if the current street is vertical

			// then find a horizontal street that is crossing the current street

			for (unsigned int index=0; index < City::fHorizontals.size(); index++) {
				if ( isCrossing( *(City::fHorizontals[index]), curStr) ) {
					Point* cp = getCrosspoint( *(City::fHorizontals[index]), curStr);
					crosspoints.push_back(cp);
				}
			}
		}
		else {	// cur street is horizontal

			for (unsigned int index=0; index < City::fVerticals.size(); index++) {
				if ( isCrossing( *(City::fVerticals[index]), curStr) ) {
					Point* cp = getCrosspoint( *(City::fVerticals[index]), curStr);
					crosspoints.push_back(cp);
				}
			}
		}

		// then calculate the how far the curPos is from the crosspoint, we take the closest
		while (crosspoints.size() != 1) {
			int delta0 = crosspoints[0]->getY() - curPos.getY();
			delta0 = std::abs(delta0);
			int delta1 = crosspoints[1]->getY() - curPos.getY();
			delta1 = std::abs(delta1);

			if (delta0 < delta1) {
				crosspoints.erase(crosspoints.begin() + 1);
			}
			else {
				crosspoints.erase(crosspoints.begin() );
			}
		}
		Point* p = crosspoints[0];
		return p;
	}

	return NULL;
}


*/
