/*
 * Depot.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Depot.h"
#include <fstream>

bool Depot::isInitialized() const {
	return this == fMyself;
}

Depot::Depot(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health)
	: Building(location, size, health, 2) {
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	fEntrance = entrance;
	fName = name;
	fMyself = this;
	fName = name;

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->getName() == name, "Name is set");
	ENSURE(this->getEntrance() == entrance, "Entrance is set");
}

Depot::Depot(const Depot& d)
	: Building(d.getLocation(), d.getSize(), d.getHealth(), 2 ), fEntrance(d.getEntrance()) {
	REQUIRE(d.isInitialized(), "Depot is initialized");

	fMyself = this;
	fName = d.fName;
	fEntrance = d.fEntrance;
	fVehicles = d.fVehicles;

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->getName() == d.getName(), "Name is copied");
	ENSURE(this->getEntrance() == d.getEntrance(), "Entrance is copied");
	ENSURE(this->getNrVehicles() == d.getNrVehicles(), "Vehicles copied");
}

void Depot::operator= (const Depot& d) {
	REQUIRE(d.isInitialized(), "Depot is initialized");
	REQUIRE(this->isInitialized(), "Depot is initialized");

	fName = d.fName;
	fEntrance = d.fEntrance;
	fVehicles = d.fVehicles;

	ENSURE(this->getName() == d.getName(), "Name is initialized");
	ENSURE(this->getEntrance() == d.getEntrance(), "Entrance is copied");
	ENSURE(this->getNrVehicles() == d.getNrVehicles(), "Vehicles copied");
	return;
}

void Depot::addVehicle(Vehicle* v) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	fVehicles.push_back(v);

	ENSURE(this->getNrVehicles() > 0, "There's at least one vehicle");
	return;
}

unsigned int Depot::getNrVehicles() const {
	REQUIRE(this->isInitialized(), "Depot is initialized");

	return fVehicles.size();
}

unsigned int Depot::getAvailableVehicles() const {
	REQUIRE(this->isInitialized(), "Depot is initialized");

	unsigned int count = 0;
	for (unsigned int index=0; index < fVehicles.size(); index++) {
		// check for each vehicles whether their position corresponds to the depot's location
		if (fVehicles[index]->getPosition() == this->getLocation()) {
			count++;
		}
	}
	return count;
}

std::string Depot::getName() const {
	REQUIRE(this->isInitialized(), "Depot is initialized");
	return fName;
}

Point Depot::getEntrance() const {
	REQUIRE(this->isInitialized(), "Depot is initialized");
	return fEntrance;
}
