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

bool Simulator::endSimulation() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	return Simulator::fEndSimulation;
}


bool Simulator::simulate(Output& out) {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	out.writeToFile();
	out.writeToFile("\n");
	Simulator::fTown->fireBreaksOut();
	out.writeToFile();
	out.writeToFile("\n");
	Simulator::fTown->burningDown();
	out.writeToFile();
	out.writeToFile("\n");
	Simulator::fTown->driveTrucks();
	out.writeToFile();
	out.writeToFile("\n");
	Simulator::fTown->extinguish();
	out.writeToFile();
	out.writeToFile("\n");

	if ( (Simulator::fTown->isDead()) && (Simulator::fTown->allTrucksBack() ) ) {
		Simulator::fEndSimulation = true;
	}
	return true;
}
