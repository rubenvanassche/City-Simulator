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
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "Simulator is initialized");

	bool endSimulation();
	// checks whether it's the end of the simulation
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool fireBreaksOut();
	// set a random chosen house on fire
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// ENSURE(this->fTown->burningHouses() > 0, "At least 1 house is burning");

	bool burningDown(int factor=1);
	// BURN CITY BURN!!
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(factor > 0, "burning factor is greater than 0");

	bool drive(int repeat=1);
	// let all the vehicles drive around
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(repeat > 0, "repeat at least 1");

	bool extinguish();
	// extinguish the fire (if a firetruck is arrived)
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool sendTrucks();
	// send a trucks for houses on fire
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

private:
	bool fEndSimulation;
	City* fTown;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
