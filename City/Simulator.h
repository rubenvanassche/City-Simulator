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
#include "Output.h"
#include "DesignByContract.h"

class Simulator {
public:
	bool isInitialized() const;

	Simulator(City* town, Output* output);
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");
	// REQUIRE(output->isInitialized(), "Output is initialized");

	// ENSURE(this->isInitialized(), "Simulator is initialized");
	// ENSURE(this->fTown == town, "Town is set");
	// ENSURE(this->fOutput == output, "output is set");

	bool endSimulation() const;
	// checks whether it's the end of the simulation
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool fireBreaksOut();
	// set a random chosen house on fire
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool sendFireTrucks();
	// try to send a firetruck
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool burningDown();
	// let the city burn (substracting health points)
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool commitRob();
	// let rob a random shop
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool robbing();
	// substracting robbing points
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool sendPoliceTrucks();
	// try to send a policetruck
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool drive();
	// drive all the vehicles around, enter depot, extinguish fire/stop robbing and sendback
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	bool repairBuildings();
	// repair all the buildings
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	void spreadFire();
	// spreads the fire

	void step();
	// one step in the simulation

	void step(bool fireSpreading);
	// One step in the simulation, with the bool you can turn firespreading on/off

private:
	City* fTown;
	Output* fOutput;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
