/*
 * FireDepot.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "FireDepot.h"
#include <fstream>

bool FireDepot::isInitialized() {
	return this == FireDepot::fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");
	stream << "Brandweerkazerne " << f.fName;
	return stream;
}

FireDepot::FireDepot(std::string& name, Point& location, Size& size, Point& entrance)
	: Building(location, size), fEntrance(entrance) {
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	FireDepot::fMyself = this;
	FireDepot::fName = name;
	FireDepot::fEntrance = entrance;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->fName == name, "Name is initialized");
	ENSURE(this->getLocation() == location, "Location is initialized");
	ENSURE(this->getSize() == size, "Size is initialized");
	ENSURE(this->fEntrance == entrance, "Entrance is initialized");
}

FireDepot::FireDepot(FireDepot& f)
	: Building(f.getLocation(), f.getSize() ), fEntrance(f.fEntrance) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot::fMyself = this;
	FireDepot::fName = f.fName;
	FireDepot::fEntrance = f.fEntrance;

	for (unsigned int index=0; index < f.fTrucks.size(); index++) {
		FireTruck* pt = new FireTruck( *(f.fTrucks[index]) );
		FireDepot::fTrucks.push_back(pt);
	}

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->fName == f.fName, "Name is initialized");
	ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	ENSURE(this->getSize() == f.getSize(), "Size is copied");
	ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");

	for (unsigned int index=0; index < f.fTrucks.size(); index++) {
		ENSURE(this->fTrucks[index]->getName() == f.fTrucks[index]->getName(), "Vector is copied");
	}
}

bool FireDepot::operator= (FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	this->setLocation(f.getLocation());
	this->setSize(f.getSize());
	FireDepot::fName = f.fName;
	FireDepot::fEntrance = f.fEntrance;
	FireDepot::fTrucks = f.fTrucks;

	ENSURE(this->fName == f.fName, "Name is initialized");
	ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	ENSURE(this->getSize() == f.getSize(), "Size is copied");
	ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	for (unsigned int index=0; index < f.fTrucks.size(); index++) {
		ENSURE(this->fTrucks[index]->getName() == f.fTrucks[index]->getName(), "Vector is copied");
	}
	return true;
}

bool FireDepot::addFireTruck(FireTruck& f) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	FireTruck* p = new FireTruck(f);
	FireDepot::fTrucks.push_back(p);

	ENSURE(this->fTrucks.back()->getName() == f.getName(), "FireTruck is added");
	return true;
}

std::string& FireDepot::getName() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return FireDepot::fName;
}

bool FireDepot::setName(std::string& name) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	FireDepot::fName = name;

	ENSURE(this->fName == name, "Name is set");
	return true;
}

Point& FireDepot::getEntrance() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return FireDepot::fEntrance;
}

bool FireDepot::setEntrance(Point& entrance) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	FireDepot::fEntrance = entrance;

	ENSURE(this->fEntrance == entrance, "Entrance is set");
	return true;
}


FireDepot::~FireDepot() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		delete FireDepot::fTrucks[index];
	}
	FireDepot::fTrucks.clear();

	ENSURE(this->fTrucks.empty() == true, "No trucks in depot");
}

unsigned int FireDepot::getNrTrucks() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	return FireDepot::fTrucks.size();
}

unsigned int FireDepot::getAvailableTrucks() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	unsigned int count = 0;
	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->getPosition() == this->getLocation()) {
			count++;
		}
	}
	return count;
}

bool FireDepot::sendTruck(Point& location, House* house) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(this->getAvailableTrucks() > 0, "There is a truck available");

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->getPosition() == this->getLocation()) {
			FireDepot::fTrucks[index]->setDestination(location);
			FireDepot::fTrucks[index]->setPosition(FireDepot::fEntrance);
			FireDepot::fTrucks[index]->setHouseOnFire(house);
			return true;
		}
	}
	return false;
}

bool FireDepot::alreadySend(Point& location) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	REQUIRE(location.isInitialized(), "Point is initialized");

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->getDestination() == location) {
			return true;
		}
	}
	return false;
}

bool FireDepot::updateDrivingTrucks(WorldMap& map) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	REQUIRE(this->isInitialized(), "WorldMap is initialized");

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->isOnWay() ) {
			FireDepot::fTrucks[index]->drive(map);
		}
	}
	return true;
}

std::vector<Point*> FireDepot::updateArrivedTrucks() {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");

	std::vector<Point*> blushed;
	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->isArrived() ) {
			if (FireDepot::fTrucks[index]->getPosition() == FireDepot::fEntrance) {
				FireDepot::fTrucks[index]->setPosition(this->getLocation() );
				FireDepot::fTrucks[index]->setDestination(this->getLocation() );
			}
			else {
				Point* p = & (FireDepot::fTrucks[index]->getDestination() );
				blushed.push_back(p);
				FireDepot::fTrucks[index]->setDestination(FireDepot::fEntrance);
			}
		}
	}
	return blushed;
}

bool FireDepot::statusTrucksOnWay(const char* fileName) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->isOnWay()) {
			if (FireDepot::fTrucks[index]->getDestination() != this->getEntrance()) {
				filestream << "\t" << *(FireDepot::fTrucks[index]) << " op weg naar locatie "
						<< FireDepot::fTrucks[index]->getDestination()
						<< " [huidige positie: " << FireDepot::fTrucks[index]->getPosition()
						<< "]" << std::endl;
			}
			else {
				filestream << "\t" << *(FireDepot::fTrucks[index]) << " keert terug naar "
						<< FireDepot::fName << std::endl;
			}
		}
		else if ( FireDepot::fTrucks[index]->isArrived() ) {
			if (FireDepot::fTrucks[index]->getPosition() != this->getLocation() ) {
				filestream << "\t" << *(FireDepot::fTrucks[index]) << " blust de brand op "
						<< FireDepot::fTrucks[index]->getHouseOnFire() << std::endl;
			}
		}
	}
	filestream.close();
	return true;
}

bool FireDepot::statusAvailableTrucks(const char* fileName) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	std::ofstream filestream;
	filestream.open(fileName, std::ios_base::app);
	filestream << "\t" << *this << " heeft de volgende trucks ter beschikking: " << std::endl;

	for (unsigned int index=0; index < FireDepot::fTrucks.size(); index++) {
		if (FireDepot::fTrucks[index]->getPosition() == this->getLocation() ) {
			filestream << "\t\t" << *(FireDepot::fTrucks[index]) << std::endl;
		}
	}
	filestream.close();

	return true;
}
