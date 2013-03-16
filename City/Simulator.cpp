/*
 * Simulator.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 16 March 2013
 * 
 */

#include "Simulator.h"

bool Simulator::isInitialized() {
	return this == Simulator::fMyself;
}

Simulator::Simulator(City* town, std::string& outputfilename) {
	REQUIRE(town->isInitialized(), "City is initialized");

	Simulator::fMyself = this;
	Simulator::fTown = town;
	Simulator::fEndSimulation = false;
	Simulator::fFileName = outputfilename;

	ENSURE(this->isInitialized(), "Simulator is initialized");
}

bool Simulator::output() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::ofstream filestream;
	const char* charInput = Simulator::fFileName.c_str();

	Simulator::fTown->writeTrucksStatus(charInput);
	Simulator::fTown->writeHousesStatus(charInput);
	Simulator::fTown->writeDepotsStatus(charInput);

	if ( (Simulator::fTown->trucksOnWay() ) || (Simulator::fTown->housesOnFire() )) {
		Simulator::fEndSimulation = false;
	}
	else {
		Simulator::fEndSimulation = true;
	}

	return true;
}

bool Simulator::endSimulation() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	return Simulator::fEndSimulation;
}


bool Simulator::simulate() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	// comming soon!

	return true;
}
