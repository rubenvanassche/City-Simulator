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

	bool output();
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool endSimulation();
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	bool simulate();
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

private:
	bool fEndSimulation;
	City* fTown;
	std::string fFileName;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
