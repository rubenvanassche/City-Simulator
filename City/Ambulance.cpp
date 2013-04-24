/*
 * Ambulance.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "Ambulance.h"

bool Ambulance::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, Ambulance& f) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");
	stream << "Ziekenwagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

Ambulance::Ambulance(const std::string& name, Depot* base)
	: EmergencyCar(name, base) {
	REQUIRE(base->isInitialized(), "Depot is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
}

Ambulance::Ambulance(const Ambulance& f)
	: EmergencyCar(f.getName(), f.getBase()) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "Ambulance is initialized");
}

void Ambulance::operator= (const Ambulance& f) {
	REQUIRE(f.isInitialized(), "Ambulance is initialized");
	REQUIRE(this->isInitialized(), "Ambulance is initialized");

	// nothing to do here..

	ENSURE(this->isInitialized(), "Ambulance is initialized");
	return;
}

char Ambulance::getSymbol(){
	return '=';
}
