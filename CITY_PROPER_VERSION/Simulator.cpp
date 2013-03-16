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

Simulator::Simulator(City* town) {
	REQUIRE(town->isInitialized(), "City is initialized");

	Simulator::fMyself = this;
	Simulator::fTown = town;
	Simulator::fEndSimulation = false;

	ENSURE(this->isInitialized(), "Simulator is initialized");
}

bool Simulator::output() {
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::fstream filestream;
	const char* charInput = Simulator::fFileName.c_str();
	filestream.open(charInput);

	while (Simulator::fTown->trucksOnWay()) {
		Simulator::fTown->writeTrucksStatus(filestream);
	}

	while (Simulator::fTown->housesOnFire()) {
		Simulator::fTown->writeHousesStatus(filestream);
	}

	Simulator::fTown->writeDepotsStatus(filestream);

	filestream.close();
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
