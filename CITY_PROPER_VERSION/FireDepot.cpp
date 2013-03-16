/*
 * FireDepot.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "FireDepot.h"

bool FireDepot::isInitialized() {
	return this == FireDepot::fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");
	stream << "Brandweerkazerne " << f.fName << " heeft de volgende trucks in de depot: " << std::endl;
	for (unsigned int index=0; index < f.fTrucks.size(); index++) {
		stream << "\t" << f.fTrucks[index] << std::endl;
	}
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
	FireDepot::fTrucks = f.fTrucks;

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

FireTruck& FireDepot::getAvailableTruck() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return *FireDepot::fTrucks[0];
}

bool FireDepot::popTruck() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	delete FireDepot::fTrucks[0];
	return true;
}

unsigned int FireDepot::getNrTrucks() {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");
	return FireDepot::fTrucks.size();
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

	ENSURE(this->fTrucks.empty(), "No trucks in depot");
}
