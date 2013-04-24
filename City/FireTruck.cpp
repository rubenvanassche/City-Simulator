/*
 * FireTruck.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "FireTruck.h"

bool FireTruck::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	stream << "Brandweerwagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

FireTruck::FireTruck(const std::string& name, Depot* base)
	: EmergencyCar(name, base) {
	REQUIRE(base->isInitialized(), "FireDepot is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
}

FireTruck::FireTruck(const FireTruck& f)
	: EmergencyCar(f.getName(), f.getBase()) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "FireTruck is initialized");
}

void FireTruck::operator= (const FireTruck& f) {
	REQUIRE(f.isInitialized(), "FireTruck is initialized");
	REQUIRE(this->isInitialized(), "FireTruck is initialized");

	// nothing to do here..

	ENSURE(this->isInitialized(), "FireTruck is initialized");
	return;
}

char FireTruck::getSymbol(){
	return '*';
}
