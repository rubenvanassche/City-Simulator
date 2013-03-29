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

FireDepot::FireDepot(Point& location, Size& size, double health, std::string& name, Point& entrance)
	: Building(location, size, health), fEntrance(entrance) {
	REQUIRE(health >= 0, "Health is positive");
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	FireDepot::fMyself = this;
	FireDepot::fName = name;
	FireDepot::fEntrance = entrance;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->fName == name, "Name is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
	ENSURE(this->fEntrance == entrance, "Entrance is set");
	ENSURE(this->getHealth() == health, "Health is set");
}

FireDepot::FireDepot(FireDepot& f)
	: Building(f.getLocation(), f.getSize(), f.getHealth() ), fEntrance(f.fEntrance) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot::fMyself = this;
	FireDepot::fName = f.fName;
	FireDepot::fEntrance = f.fEntrance;
	FireDepot::fTrucks = f.fTrucks;
	this->setLocation(f.getLocation());
	this->setHealth(f.getHealth());
	this->setSize(f.getSize());

	ENSURE(this->isInitialized(), "FireDepot is initialized");
	ENSURE(this->fName == f.fName, "Name is copied");
	ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	ENSURE(this->getSize() == f.getSize(), "Size is copied");
	ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	ENSURE(this->fTrucks.size() == f.fTrucks.size(), "Trucks copied");
	ENSURE(this->getHealth() == f.getHealth(), "Health is copied");
}

bool FireDepot::operator= (FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	this->setLocation(f.getLocation());
	this->setSize(f.getSize());
	this->setHealth(f.getHealth());
	FireDepot::fName = f.fName;
	FireDepot::fEntrance = f.fEntrance;
	FireDepot::fTrucks = f.fTrucks;

	ENSURE(this->fName == f.fName, "Name is initialized");
	ENSURE(this->getLocation() == f.getLocation(), "Location is copied");
	ENSURE(this->getSize() == f.getSize(), "Size is copied");
	ENSURE(this->fEntrance == f.fEntrance, "Entrance is copied");
	ENSURE(this->fTrucks.size() == f.fTrucks.size(), "Trucks copied");
	ENSURE(this->getHealth() == f.getHealth(), "Health is copied");
	return true;
}

bool FireDepot::addFireTruck(FireTruck* f) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	FireDepot::fTrucks.push_back(f);

	ENSURE(this->fTrucks.back()->getName() == f->getName(), "FireTruck is added");
	return true;
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

std::string& FireDepot::getName() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return FireDepot::fName;
}

Point& FireDepot::getEntrance() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return FireDepot::fEntrance;
}
