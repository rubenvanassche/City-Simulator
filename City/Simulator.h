/*
 * Simulator.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "City.h"
#include "DesignByContract.h"

class Simulator {
public:
	bool isInitialized() const;

	Simulator(City* town);
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");

	// ENSURE(this->isInitialized(), "Simulator is initialized");
	// ENSURE(this->fTown == town, "Town is set");

	bool endSimulation() const;
	// checks whether it's the end of the simulation
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void fireBreaksOut();
	// set a random chosen house on fire
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void fireTruckControl();
	// checks the vector of burning houses and sends a firetruck to those who are burning
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void burningDown();
	// let the city burn (substracting health points)
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void commitRob();
	// let rob a random shop
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void robbing();
	// substracting robbing points
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void policeTruckControl();
	// Sends a police truck to shops being robbed
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void drive();
	// drive all the vehicles around
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void repairBuildings();
	// repair all the buildings
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void spreadFire();

	void step();
	// one step in the simulation

private:
	City* fTown;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
