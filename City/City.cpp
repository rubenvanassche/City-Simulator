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

	WorldMap map;
	City::fMap = map;
	fFailure = 0;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::City(City& town) {
	//REQUIRE(town.isInitialized(), "City is initialized");

	City::fMyself = this;

	City::fMap = town.fMap;

	for (unsigned int index=0; index < town.fHouses.size(); index++) {
		House* h = new House( *(town.fHouses[index]) );
		City::fHouses.push_back(h);
	}

	for (unsigned int index=0; index < town.fFireDepots.size(); index++) {
		FireDepot* f = new FireDepot( *(town.fFireDepots[index]) );
		City::fFireDepots.push_back(f);
	}

	fFailure = 0;

	ENSURE(this->isInitialized(), "City is copied");
}

bool City::addFireDepot(FireDepot& depot) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(depot.isInitialized(), "FireDepot is initialized");

	if(this->check(depot)){
		FireDepot* d = new FireDepot(depot);
		City::fFireDepots.push_back(d);
		return true;
	}else{
		this->error(1);
		return false;
	}
}

bool City::addFireTruck(FireTruck& truck) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(truck.isInitialized(), "FireTruck is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getName() == truck.getBase()) {
			truck.setPosition(City::fFireDepots[index]->getLocation());
			truck.setDestination(City::fFireDepots[index]->getLocation());
			City::fFireDepots[index]->addFireTruck(truck);
			return true;
		}
	}

	std::cout << "FireTruck " << truck.getName() << " has unknown base." << std::endl;
	return false;
}

bool City::addStreet(Street& street) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(street.isInitialized(), "Street is initialized");

	if(this->check(street)){
		City::fMap.addStreet(street);
		return true;
	}else{
		this->error(1);
		return false;
	}
}

bool City::addHouse(House& house) {
	ENSURE(this->isInitialized(), "City is initialized");
	ENSURE(house.isInitialized(), "House is initialized");

	if(this->check(house)){
		House* h = new House(house);
		City::fHouses.push_back(h);
		return true;

	}else{
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

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}
	City::fHouses.clear();

	ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	ENSURE(this->fHouses.empty() == true, "Houses is empty'd");
}

bool City::isDead() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (!City::fHouses[index]->isDead()) {
			return false;
		}
	}
	return true;
}

bool City::fireBreaksOut() {
	// REQUIRE( this->isDead() == false, "City is not dead");

	int index = std::rand() % City::fHouses.size();

	if ( (City::fHouses[index]->isBurning() ) || (City::fHouses[index]->isDead()) ) {
		return false;
	}

	City::fHouses[index]->setFire();

	ENSURE(City::fHouses[index]->isBurning(), "House is not set on fire");
	return true;
}

bool City::burningDown() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning()) {
			City::fHouses[index]->burningDown(1);
		}
	}
	return true;
}

bool City::driveTrucks() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (!City::fHouses[index]->isBurning()) {
			continue;
		}

		bool alreadySend = false;
		for (unsigned int i=0; i < City::fFireDepots.size(); i++) {
			if (City::fFireDepots[i]->alreadySend(City::fHouses[index]->getLocation() ) ) {
				alreadySend = true;
				break;
			}
		}

		if (alreadySend) {
			continue;	// go to the next house, a firetruck is on the way
		}

		// else we will send a firetruck;
		for (unsigned int i=0; i < City::fFireDepots.size(); i++) {
			if (City::fFireDepots[i]->getAvailableTrucks() > 0) {
				Point p = City::fHouses[index]->getLocation();
				int originX = p.getX();
				int originY = p.getY();

				if ( !City::fMap.isInMap(p) ) {
					int y = p.getY() + 1;
					p.set(originX, y);
				}
				if ( !City::fMap.isInMap(p) ) {
					int x = p.getX() - 1;
					p.set(x, originY);
				}
				if ( !City::fMap.isInMap(p) ) {
					int x =  originX + City::fHouses[index]->getSize().getWidth();
					p.set(x, originY);
				}
				if ( !City::fMap.isInMap(p) ) {
					int y = originY - City::fHouses[index]->getSize().getHeight();
					p.set(originX, y);
				}

				City::fFireDepots[i]->sendTruck(p, City::fHouses[index]);
				break;
			}
		}
	}

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->updateDrivingTrucks(City::fMap);
	}

	return true;
}

bool City::extinguish() {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::vector<Point*> blushed;
	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		blushed = City::fFireDepots[index]->updateArrivedTrucks();
		for (unsigned int index=0; index < blushed.size(); index++) {
			for (unsigned int i=0; i < City::fHouses.size(); i++) {
				if (City::fHouses[i]->getLocation() == *(blushed[index]) ) {
					City::fHouses[i]->stopFire();
					break;
				}
			}
		}

		blushed.clear();
	}
	return true;
}

bool City::statusBurningHouses(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning() ) {
			filestream << "\t" << *(City::fHouses[index]) << " staat in brand en heeft nog "
					<< City::fHouses[index]->getHealth() << " health points." << std::endl;
		}
		else if (City::fHouses[index]->isDead() ) {
			filestream << "\t" << *(City::fHouses[index]) << " is volledig afgebrand." << std::endl;
		}
	}

	filestream.close();
	return true;
}

bool City::statusTrucksOnWay(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->statusTrucksOnWay(fileName);
	}
	filestream.close();
	return true;
}

bool City::statusAvailableTrucks(const char* fileName) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		City::fFireDepots[index]->statusAvailableTrucks(fileName);
	}
	filestream.close();
	return true;
}

bool City::allTrucksBack() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getAvailableTrucks() != City::fFireDepots[index]->getNrTrucks() ) {
			return false;
		}
	}
	return true;
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
		}else{
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
		}else{
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
	}else if(y1 == y2){
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
	}else{
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

	for(it = fHouses.begin();it != fHouses.end();++it){
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

	std::vector<Street*>::iterator it;
	std::vector<Point*>::iterator it2;

	return this->fMap.isInMap(p);
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
			}else{
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
	}else if(level == 2){
		fFailure = 2;
		std::cout << "Something went wrong, and the program crashed." << std::endl;
		ENSURE(false, "Hard crash!");
	}
}
