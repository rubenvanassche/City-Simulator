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
	City::fFailure = 0;

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

	City::fFailure = 0;

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

	if(this->check(depot)) {
		FireDepot* d = new FireDepot(depot);
		City::fFireDepots.push_back(d);
		return true;
	}
	else{
		this->error(1);
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

	if(this->check(street)){
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
		this->error(1);
		return false;
	}
}

bool City::add(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	if(this->check(house)){
		House* h = new House(house);
		City::fHouses.push_back(h);
		return true;
	}
	else{
		this->error(1);
		return false;
	}
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

bool City::check(House& house){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	Point location = house.getLocation();

	std::vector<Point*> points = house.calculatePoints();

	// So let check those points
	bool checker = true;
	for(std::vector<Point*>::iterator it = points.begin();it != points.end();++it){
		if(this->checkPoint(**it) == true){
			continue; // This point is checked so move to the next one
		}
		else{
			checker =  false; // There is something at this point, we can't add something else
			break;
		}
	}

	// Now let clean this mess up(the points we haven't deleted yet)!
	for(std::vector<Point*>::iterator it = points.begin();it != points.end();++it){
		delete *it;
	}

	return checker;
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

bool City::check(FireDepot& depot){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	Point location = depot.getLocation();

	std::vector<Point*> points = depot.calculatePoints();

	// So let check those points
	bool checker = true;
	for(std::vector<Point*>::iterator it = points.begin();it != points.end();++it){
		if(this->checkPoint(**it) == true){
			continue; // This point is checked so move to the next one
		}
		else{
			checker =  false; // There is something at this point, we can't add something else
			break;
		}
	}

	// Now let clean this mess up(the points we haven't deleted yet)!
	for(std::vector<Point*>::iterator it = points.begin();it != points.end();++it){
		delete *it;
	}

	return checker;
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

bool City::check(Street& street){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(street.isInitialized(), "Street is initialized");

	int x1 = street.getStartPoint().getX();
	int y1 = street.getStartPoint().getY();
	int x2 = street.getEndPoint().getX();
	int y2 = street.getEndPoint().getY();


	bool checker = true;
	// Do we have an vertical or horizontal street?
	if(x1 == x2){
		// Vertical
		for(int i = std::min(y1, y2);i <= std::max(y1, y2);i++){
			Point p(x1, i);
			if(this->checkPoint(p, true) == true){
				continue; // This point is checked so move to the next one
			}else{
				checker =  false; // There is something at this point, we can't add something else
				break;
			}
		}
	}
	else if(y1 == y2){
		// Horizontal
		for(int i = std::min(x1, x2);i <= std::max(x1, x2);i++){
			Point p(i, y1);
			if(this->checkPoint(p, true) == true){
				continue; // This point is checked so move to the next one
			}else{
				checker =  false; // There is something at this point, we can't add something else
				break;
			}
		}
	}
	else{
		// Now we're having a serious issue
	}

	return checker;
}

bool City::checkPoint(Point& p){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");

	std::vector<Point*>::iterator it;
	for(it = fUsedPoints.begin();it != fUsedPoints.end();++it){
		if(**it == p){
			return false;
		}
	}


	if(isOnHouse(p)){
		this->fUsedPoints.push_back(&p);
		return false;
	}

	if(isOnStreet(p)){
		this->fUsedPoints.push_back(&p);
		return false;
	}

	if(isOnFireDepot(p)){
		this->fUsedPoints.push_back(&p);
		return false;
	}


	return true;

}

bool City::checkPoint(Point& p, bool isStreet){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");


	if(isOnHouse(p)){
		return false;
	}

	if(isStreet == false){
		if(isOnStreet(p)){
			return false;
		}
	}

	if(isOnFireDepot(p)){
		return false;
	}

	return true;

}

bool City::isOnHouse(Point &p){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");

	std::vector<House*>::iterator it;
	std::vector<Point*>::iterator it2;

	for(it = City::fHouses.begin();it != City::fHouses.end();++it){
		// Get points for each house and compare!
		std::vector<Point*> points = (**it).calculatePoints();
		for(it2 = points.begin();it2 != points.end();++it2){
			if((**it2).getX() == p.getX() and (**it2).getY() == p.getY() ){
				std::cout << "HIER";
				return true;
			}
		}
	}

	return false;
}

bool City::isOnStreet(Point &p){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");

	// let's first check if this is in the horizontals streets
	for (unsigned int index=0; index < City::fHorizontals.size(); index++) {
		if (City::fHorizontals[index]->isElement(p) ) {
			return true;
		}
	}

	// else, let's search in the vertical streets
	for (unsigned int index=0; index < City::fVerticals.size(); index++) {
		if (City::fVerticals[index]->isElement(p) ) {
			return true;
		}
	}

	return false;	// point not found
}

bool City::isOnFireDepot(Point &p){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");

	std::vector<FireDepot*>::iterator it;
	std::vector<Point*>::iterator it2;

	for(it = fFireDepots.begin();it != fFireDepots.end();++it){
		// Get points for each house and compare!
		std::vector<Point*> points = (**it).calculatePoints();
		for(it2 = points.begin();it2 != points.end();++it2){
			if(**it2 == p){
				return true;
			}
			else{
				continue;
			}
		}
	}

	return false;
}

void City::error(int level){
	REQUIRE(this->isInitialized(), "City is initialized");
	if (level == 1){
		fFailure = 1;
		std::cout << "Something went wrong, but the program can still continue." << std::endl;
	}
	else if(level == 2){
		fFailure = 2;
		std::cout << "Something went wrong, and the program crashed." << std::endl;
		ENSURE(false, "Hard crash!");
	}
}
