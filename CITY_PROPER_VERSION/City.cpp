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

bool City::isInitialized() {
	return this == City::fMyself;
}

City::City() {
	City::fMyself = this;
	fFailure = 0;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::City(const City& town) {
	//REQUIRE(town.isInitialized(), "City is initialized");

	City::fMyself = this;

	fFailure = 0;

	for (unsigned int index=0; index < town.fTrucks.size(); index++) {
		FireTruck* f = new FireTruck( *(town.fTrucks[index]) );
		City::fTrucks.push_back(f);
	}

	for (unsigned int index=0; index < town.fStreets.size(); index++) {
		Street* s = new Street( *(town.fStreets[index]) );
		City::fStreets.push_back(s);
	}

	for (unsigned int index=0; index < town.fHouses.size(); index++) {
		House* h = new House( *(town.fHouses[index]) );
		City::fHouses.push_back(h);
	}

	for (unsigned int index=0; index < town.fFireDepots.size(); index++) {
		FireDepot* f = new FireDepot( *(town.fFireDepots[index]) );
		City::fFireDepots.push_back(f);
	}

	ENSURE(this->isInitialized(), "City is copied");
}

bool City::addFireDepot(FireDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "FireDepot is initialized");

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
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(truck.isInitialized(), "FireTruck is initialized");

	FireTruck* f = new FireTruck(truck);
	City::fTrucks.push_back(f);

	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		if (City::fFireDepots[index]->getName() == truck.getBase()) {
			City::fFireDepots[index]->addFireTruck(truck);
			return true;
		}
	}

	std::cout << "FireTruck " << truck.getName() << " has unknown base." << std::endl;
	return false;
}

bool City::addStreet(Street& street) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(street.isInitialized(), "Street is initialized");

	if(this->check(street)){
		Street* s = new Street(street);
		City::fStreets.push_back(s);
		return true;

	}else{
		this->error(1);
		return false;
	}
}

bool City::addHouse(House& house) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	if(this->check(house)){
		House* h = new House(house);
		City::fHouses.push_back(h);
		return true;

	}else{
		this->error(1);
		return false;
	}
}

bool City::trucksOnWay() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		if (City::fTrucks[index]->getPosition() == City::fTrucks[index]->getDestination()) {
			continue;
		}
		else {
			return true;
		}
	}
	return false;
}


bool City::writeTrucksStatus(const char* filename) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	filestream << "Brandweerwagens onderweg:" << std::endl;
	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		if (City::fTrucks[index]->getPosition() != City::fTrucks[index]->getDestination()) {
			filestream << "\t" << *(City::fTrucks[index]) << std::endl;
		}
	}
	filestream.close();
	return true;
}

bool City::housesOnFire() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning()) {
			return true;
		}
		continue;
	}
	return false;
}

bool City::writeHousesStatus(const char* filename) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	filestream << "Brandende huizen:" << std::endl;
	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		if (City::fHouses[index]->isBurning()) {
			filestream << "\t" << *(City::fHouses[index]) << std::endl;
		}
	}
	filestream.close();
	return true;
}


bool City::writeDepotsStatus(const char* filename) {
	REQUIRE(this->isInitialized(), "City is initialized");

	std::ofstream filestream;
	filestream.open(filename, std::ios_base::app);
	for (unsigned int index=0; index < City::fFireDepots.size(); index++) {
		filestream << *(City::fFireDepots[index]) << std::endl;
	}
	filestream.close();
	return true;
}

std::vector<Point*> City::calculatePoints(House& house){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	int width = house.getSize().getWidth();
	int height = house.getSize().getHeight();
	Point location = house.getLocation();

	return this->calculatePoints(width, height, location);
}

std::vector<Point*> City::calculatePoints(FireDepot& depot){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	int width = depot.getSize().getWidth();
	int height = depot.getSize().getHeight();
	Point location = depot.getLocation();
	

	return this->calculatePoints(width, height, location);
}

std::vector<Point*> City::calculatePoints(int width, int height, Point& location){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(location.isInitialized(), "Location is initialized");

	std::vector<Point*> out;

	for(int i = location.getX();i < location.getX() + width;i++){
		Point* p = new Point(i, location.getY());
		out.push_back(p);		
	} 

	for(int i = location.getY();i < location.getY() + height;i++){
		Point* p = new Point(location.getX(), i);
		out.push_back(p);			
	}

	ENSURE(out.size() > 0, "There are no points given as output");
	return out;
}

std::vector<Point*> City::calculatePoints(Street& street){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(street.isInitialized(), "Street is initialized");

	int x1 = street.getStartPoint().getX();
	int y1 = street.getStartPoint().getY();
	int x2 = street.getEndPoint().getX();
	int y2 = street.getEndPoint().getY();

	std::vector<Point*> out;

	bool checker = true;
	// Do we have an vertical or horizontal street?
	if(x1 == x2){
		// Vertical
		for(int i = std::min(y1, y2);i < std::max(y1, y2);i++){
			Point* p = new Point(x1, i);
			out.push_back(p);
		}
	}else if(y1 == y2){
		// Horizontal
		for(int i = std::min(x1, x2);i < std::max(x1, x2);i++){
			Point* p = new Point(i, y1);
			out.push_back(p);
		}
	}else{
		// Now we're having a serious issue
	}

	ENSURE(out.size() > 0, "There are no points given as output");
	return out;
}

bool City::check(House& house){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	int width = house.getSize().getWidth();
	int height = house.getSize().getHeight();
	Point location = house.getLocation();

	return this->check(width, height, location);
}

bool City::check(FireDepot& depot){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "Fire Depot is initialized");

	int width = depot.getSize().getWidth();
	int height = depot.getSize().getHeight();
	Point location = depot.getLocation();

	return this->check(width, height, location);
}

bool City::check(int width, int height, Point &location){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(location.isInitialized(), "Location is initialized");

	std::vector<Point*> points = this->calculatePoints(width, height, location);

	// So let check those points
	bool checker = true;
	for(std::vector<Point*>::iterator it = points.begin();it != points.end();++it){
		if(this->checkPoint(**it) == true){
			delete *it;
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
		for(int i = std::min(y1, y2);i < std::max(y1, y2);i++){
			Point p(x1, i);
			if(this->checkPoint(p) == true){
				continue; // This point is checked so move to the next one
			}else{
				checker =  false; // There is something at this point, we can't add something else
				break;
			}
		}
	}else if(y1 == y2){
		// Horizontal
		for(int i = std::min(x1, x2);i < std::max(x1, x2);i++){
			Point p(i, y1);
			if(this->checkPoint(p) == true){
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

	if(isOnHouse(p)){
		return false;
	}

	if(isOnStreet(p)){
		return false;
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
		std::vector<Point*> points = this->calculatePoints(**it);
		for(it2 = points.begin();it2 != points.end();++it){
			if(**it2 == p){
				return true;
			}else{
				continue;
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

	for(it = fStreets.begin();it != fStreets.end();++it){
		// Get points for each house and compare!
		std::vector<Point*> points = this->calculatePoints(**it);
		for(it2 = points.begin();it2 != points.end();++it){
			if(**it2 == p){
				return true;
			}else{
				continue;
			}
		}
	}

	return false;
}

bool City::isOnFireDepot(Point &p){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "Location is initialized");

	std::vector<FireDepot*>::iterator it;
	std::vector<Point*>::iterator it2;

	for(it = fFireDepots.begin();it != fFireDepots.end();++it){
		// Get points for each house and compare!
		std::vector<Point*> points = this->calculatePoints(**it);
		for(it2 = points.begin();it2 != points.end();++it){
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



City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index=0; index < City::fFireDepots.size(); index--) {
		delete City::fFireDepots[index];
	}
	City::fFireDepots.clear();

	for (unsigned int index=0; index < City::fStreets.size(); index++) {
		delete City::fStreets[index];
	}
	City::fStreets.clear();
	for (unsigned int index=0; index < City::fHouses.size(); index++) {
		delete City::fHouses[index];
	}
	City::fHouses.clear();

	for (unsigned int index=0; index < City::fTrucks.size(); index++) {
		delete City::fTrucks[index];
	}
	City::fTrucks.clear();

	ENSURE(this->fFireDepots.empty() == true, "FireDepots is empty'd");
	ENSURE(this->fStreets.empty() == true, "Street is empty'd");
	ENSURE(this->fHouses.empty() == true, "Houses is empty'd");
}
