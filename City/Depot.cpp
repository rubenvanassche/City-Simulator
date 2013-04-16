/*
 * Depot.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Depot.h"
#include <fstream>

bool Depot::isInitialized() {
	return this == Depot::fMyself;
}

Depot::Depot(Point& location, Point& entrance, Size& size, std::string name, double health)
	: Building(location, size, health), fEntrance(entrance), fName(name) {
	REQUIRE(health >= 0, "Health is positive");
	REQUIRE(location.isInitialized(), "Point is initialized");
	REQUIRE(size.isInitialized(), "Size is initialized");
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	Depot::fMyself = this;
	Depot::fName = name;
	Depot::fEntrance = entrance;

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->fName == name, "Name is set");
	ENSURE(this->getLocation() == location, "Location is set");
	ENSURE(this->getSize() == size, "Size is set");
	ENSURE(this->fEntrance == entrance, "Entrance is set");
	ENSURE(this->getHealth() == health, "Health is set");
}

Depot::Depot(Depot& d)
	: Building(d.getLocation(), d.getSize(), d.getHealth() ), fEntrance(d.getEntrance()) {
	REQUIRE(d.isInitialized(), "Depot is initialized");

	Depot::fMyself = this;
	Depot::fName = d.fName;
	Depot::fEntrance = d.fEntrance;
	Depot::fVehicles = d.fVehicles;
	this->setLocation(d.getLocation());
	this->setHealth(d.getHealth());
	this->setSize(d.getSize());

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->fName == d.fName, "Name is copied");
	ENSURE(this->getLocation() == d.getLocation(), "Location is copied");
	ENSURE(this->getSize() == d.getSize(), "Size is copied");
	ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");
	ENSURE(this->getHealth() == d.getHealth(), "Health is copied");
}

bool Depot::operator= (Depot& d) {
	REQUIRE(d.isInitialized(), "Depot is initialized");
	REQUIRE(this->isInitialized(), "Depot is initialized");

	this->setLocation(d.getLocation());
	this->setSize(d.getSize());
	this->setHealth(d.getHealth());
	Depot::fName = d.fName;
	Depot::fEntrance = d.fEntrance;
	Depot::fVehicles = d.fVehicles;

	ENSURE(this->fName == d.fName, "Name is initialized");
	ENSURE(this->getLocation() == d.getLocation(), "Location is copied");
	ENSURE(this->getSize() == d.getSize(), "Size is copied");
	ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");
	ENSURE(this->getHealth() == d.getHealth(), "Health is copied");
	return true;
}

bool Depot::addVehicle(Vehicle* v) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	Depot::fVehicles.push_back(v);

	ENSURE(this->fVehicles.back()->getName() == v->getName(), "Vehicle is added");
	return true;
}

unsigned int Depot::getNrVehicles() {
	REQUIRE(this->isInitialized(), "Depot is initialized");

	return Depot::fVehicles.size();
}

unsigned int Depot::getAvailableVehicles() {
	REQUIRE(this->isInitialized(), "Depot is initialized");

	unsigned int count = 0;
	for (unsigned int index=0; index < Depot::fVehicles.size(); index++) {
		if (Depot::fVehicles[index]->getPosition() == this->getLocation()) {
			count++;
		}
	}
	return count;
}

std::string& Depot::getName() {
	REQUIRE(this->isInitialized(), "Depot is initialized");
	return Depot::fName;
}

Point& Depot::getEntrance() {
	REQUIRE(this->isInitialized(), "Depot is initialized");
	return Depot::fEntrance;
}
