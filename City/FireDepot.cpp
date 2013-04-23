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

bool FireDepot::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");

	stream << "Brandweerkazerne " << f.getName();
	return stream;
}

FireDepot::FireDepot(const Point& location, const Point& entrance, const std::string& name, const double& health)
: Depot(location, entrance, Size(4), name, health){

	fMyself = this;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
}

FireDepot::FireDepot(const FireDepot& f)
: Depot(f){
	REQUIRE(f.isInitialized(), "PoliceDepot is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "FireDepot is initialized");
}

void FireDepot::operator= (const FireDepot& f) {
	REQUIRE(f.isInitialized(), "FireDepot is initialized");
	REQUIRE(this->isInitialized(), "FireDepot is initialized");

	// nothing to do here...

	ENSURE(this->isInitialized(), "FireDepot is initialized");
}
