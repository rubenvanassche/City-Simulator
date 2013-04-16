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
#include <fstream>

bool City::isInitialized() {
	return this == City::fMyself;
}

City::City() {
	City::fMyself = this;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::City(City& town) {
	REQUIRE(town.isInitialized(), "City is initialized");

	City::fMyself = this;

	for (unsigned int index=0; index < town.fHouses.size(); index++) {
		House* h = new House( *(town.fHouses[index]) );
		City::fHouses.push_back(h);
	}

	for (unsigned int index=0; index < town.fFireDepots.size(); index++) {
		FireDepot* f = new FireDepot( *(town.fFireDepots[index]) );
		City::fFireDepots.push_back(f);
	}

	for (unsigned int index=0; index < town.fFireTrucks.size(); index++) {
		FireTruck* f = new FireTruck( *(town.fFireTrucks[index]) );
		City::fFireTrucks.push_back(f);
	}

	for (unsigned int index=0; index < town.fHorizontals.size(); index++) {
		Street* s = new Street( *(town.fHorizontals[index]) );
		City::fHorizontals.push_back(s);
	}

	for (unsigned int index=0; index < town.fVerticals.size(); index++) {
		Street* s = new Street( *(town.fVerticals[index]) );
		City::fVerticals.push_back(s);
	}

	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(this->fFireDepots.size() == town.fFireDepots.size(), "FireDepots copied");
	ENSURE(this->fFireTrucks.size() == town.fFireTrucks.size(), "FireTrucks copied");
	ENSURE(this->fHouses.size() == town.fHouses.size(), "Houses copied");
	ENSURE(this->fVerticals.size() == town.fVerticals.size(), "Verticals copied");
	ENSURE(this->fHorizontals.size() == town.fHorizontals.size(), "Horizontals copied");
}

bool City::add(FireDepot& depot) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(depot.isInitialized(), "FireDepot is initialized");

	if(this->checker.go(depot)) {
		FireDepot* d = new FireDepot(depot);
		City::fFireDepots.push_back(d);
		return true;
	}
	else{
		return false;
	}
}

bool City::add(FireTruck& truck) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(truck.isInitialized(), "FireTruck is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getName() == truck.getBase()->getName() ) {

			FireTruck* f = new FireTruck(truck);

			City::fFireDepots[index]->addFireTruck(f);	// add it in the corresponding firedepot
			City::fFireTrucks.push_back(f);
			return true;
		}
	}

	std::cout << "FireTruck " << truck.getName() << " has unknown base." << std::endl;
	return false;
}

bool City::add(Street& street) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(street.isInitialized(), "Street is initialized");

	if(this->checker.go(street)){
		if (street.isVertical() ) {
			Street* s = new Street(street);
			City::fVerticals.push_back(s);
			return true;
		}
		else if (street.isHorizontal() ) {
			Street* s = new Street(street);
			City::fHorizontals.push_back(s);
			return true;
		}
		else {
			return false;
		}
	}
	else{
		return false;
	}
}

bool City::add(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	if(this->checker.go(house)){
		House* h = new House(house);
		City::fHouses.push_back(h);
		return true;
	}
	else{
		return false;
	}
}


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


unsigned int City::burningHouses() {
	REQUIRE(this->isInitialized(), "City is initialized");

	unsigned int count = 0;
	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning() ) {
			count++;
		}
	}

	return count;
}


FireDepot* City::findDepot(std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getName() == name) {
			return City::fFireDepots[index];
		}
	}
	return NULL;
}


City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index--) {
		delete City::fFireDepots[index];
	}
	City::fFireDepots.clear();

	for (unsigned int index=0; index < City::fHorizontals.size(); index++) {
		delete City::fHorizontals[index];
	}
	City::fHorizontals.clear();

	for (unsigned int index=0; index < City::fVerticals.size(); index++) {
		delete City::fVerticals[index];
	}
	City::fVerticals.clear();

	for (unsigned int index=0; index < City::fFireTrucks.size(); index++) {
		delete City::fFireTrucks[index];
	}
	City::fFireTrucks.clear();

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}
	City::fHouses.clear();

	ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	ENSURE(this->fHouses.empty() == true, "Buildings is empty'd");
	ENSURE(this->fHorizontals.empty() == true, "Horizontals is empty'd");
	ENSURE(this->fVerticals.empty() == true, "Verticals is empty'd");
	ENSURE(this->fFireTrucks.empty() == true, "FireTrucks is empty'd");
}

