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
	bool isInitialized() const;

	Simulator(City* town);
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "Simulator is initialized");

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
	// let the city burn

	void commitRob();
	// let go rob a random shop

	void robbing();
	// substracting robbing points

	void policeTruckControl();
	// checks the vector of robbing shops ands sends a police truck to those who are being robbed

	void drive();

	void repairBuildings();

	void spreadFire();

	void step();
	// one step in the simulation

/*
	void burningDown(int factor=1);
	// BURN CITY BURN!!
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(factor > 0, "burning factor is greater than 0");

	void drive(int repeat=1);
	// let all the vehicles drive around
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
	// REQUIRE(repeat > 0, "repeat at least 1");

	void extinguish();
	// extinguish the fire (if a firetruck is arrived)
	// REQUIRE(this->isInitialized(), "Simulator is initialized");

	void sendTrucks();
	// send a trucks for houses on fire
	// REQUIRE(this->isInitialized(), "Simulator is initialized");
*/
private:
	bool fEndSimulation;
	City* fTown;

	Simulator* fMyself;
};

#endif /* SIMULATOR_H_ */
