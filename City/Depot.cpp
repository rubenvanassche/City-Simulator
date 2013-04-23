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
	: Building(location, size, health) {
	REQUIRE(entrance.isInitialized(), "Point is initialized");

	fEntrance = entrance;
	fName = name;
	fMyself = this;
	fName = name;

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->fName == name, "Name is set");
	ENSURE(this->fEntrance == entrance, "Entrance is set");
}

Depot::Depot(const Depot& d)
	: Building(d.getLocation(), d.getSize(), d.getHealth() ), fEntrance(d.getEntrance()) {
	REQUIRE(d.isInitialized(), "Depot is initialized");

	fMyself = this;
	fName = d.fName;
	fEntrance = d.fEntrance;
	fVehicles = d.fVehicles;

	ENSURE(this->isInitialized(), "Depot is initialized");
	ENSURE(this->fName == d.fName, "Name is copied");
	ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");
}

void Depot::operator= (const Depot& d) {
	REQUIRE(d.isInitialized(), "Depot is initialized");
	REQUIRE(this->isInitialized(), "Depot is initialized");

	fName = d.fName;
	fEntrance = d.fEntrance;
	fVehicles = d.fVehicles;

	ENSURE(this->fName == d.fName, "Name is initialized");
	ENSURE(this->fEntrance == d.fEntrance, "Entrance is copied");
	ENSURE(this->fVehicles.size() == d.fVehicles.size(), "Vehicles copied");
	return;
}

void Depot::addVehicle(Vehicle* v) {
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	fVehicles.push_back(v);

	ENSURE(this->fVehicles.back()->getName() == v->getName(), "Vehicle is added");
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
