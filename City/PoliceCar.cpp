/*
 * PoliceCar.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "PoliceCar.h"

bool PoliceCar::isInitialized() const {
	return this == fMyself;
}

std::ostream& operator<< (std::ostream& stream, PoliceCar& f) {
	REQUIRE(f.isInitialized(), "PoliceCar is initialized");
	stream << "Politiewagen " << f.getName() << " [basis: " << f.getBase()->getName() << "]";
	return stream;
}

PoliceCar::PoliceCar(const std::string& name, Depot* base)
	: EmergencyCar(name, base) {
	REQUIRE(base->isInitialized(), "Depot is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "PoliceCar is initialized");
}

PoliceCar::PoliceCar(const PoliceCar& f)
	: EmergencyCar(f.getName(), f.getBase()) {
	REQUIRE(f.isInitialized(), "PoliceCar is initialized");

	fMyself = this;

	ENSURE(this->isInitialized(), "PoliceCar is initialized");
}

void PoliceCar::operator= (const PoliceCar& f) {
	REQUIRE(f.isInitialized(), "PoliceCar is initialized");
	REQUIRE(this->isInitialized(), "PoliceCar is initialized");

	// nothing to do here..

	ENSURE(this->isInitialized(), "PoliceCar is initialized");
	return;
}

char PoliceCar::getSymbol(){
	return '%';
}

