/*
 * Simulator.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 16 March 2013
 * 
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "City.h"
#include "DesignByContract.h"

class Simulator {
public:
	bool isInitialized();

	Simulator(City* town);
	// REQUIRE(town->isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "Simulator is initialized");

	bool endSimulation();
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool fireBreaksOut();
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool burningDown(int factor=1);
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(factor > 0, "burning factor is greater than 0");

	bool drive(int repeat=1);
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(repeat > 0, "repeat at least 1");

	bool extinguish();

	bool updateTrucks();

	bool sendTrucks();

private:
	bool fEndSimulation;
	City* fTown;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
