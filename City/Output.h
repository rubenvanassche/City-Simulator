/*
 * Output.h
 *
 *  Created on: 29 apr. 2013
 *      Author: Ruben
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "City.h"
#include "Point.h"
#include "Building.h"
#include "Vehicle.h"
#include "Shop.h"
#include "DesignByContract.h"
#include "FileTest.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

class Output {
public:
	Output(City* town, char filename[]);
	// REQUIRE((*town).isInitialized(), "City is initialized");
	// ENSURE(this->fTown = town, "Town is set");
	// ENSURE(FileTest::fileExists(filename), "Empty file made");
	// ENSURE(this->isInitialized(), "Output is initialized");

	friend std::ostream& operator<< (std::ostream& stream, Output& o);
	// REQUIRE(o.isInitialized(), "Ouput is initialized");

	bool isInitialized() const;

	void parse();
	// Generate the out stream
	// REQUIRE(this->isInitialized(), "Output is initialized");

	std::string get();
	// Get a snapshot of the output at this moment
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void step();
	// Write a snapshot of the output to the file
	// REQUIRE(this->isInitialized(), "Output is initialized");

	virtual ~Output();
	// DIE
	// REQUIRE(this->isInitialized(), "Output is initialized");

private:
	void shopsOnFire();
	// Write all the shops on fire to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void housesOnFire();
	// Write all the houses on fire to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void fireDepotsOnFire();
	// Write all the fire depots on fire to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void policeDepotsOnFire();
	// Write all the police depots on fire to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void hospitalsOnFire();
	// Write all the hospitals on fire to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void shopsBeingRobbed();
	// Write all the shops being robbed to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void fireTrucksdriving();
	// Write all the fire trucks who are driving to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void policeTrucksDriving();
	// Write all the police trucks who are driving to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void ambulancesDriving();
	// Write all the ambulances who are driving to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void fireDepotsTrucks();
	// Write all the fire trucks who are in a depot to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void policeDepotsTrucks();
	// Write all the police trucks who are in a depot to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	void hospitalsTrucks();
	// Write all the ambulances who are in a depot to the out stream
	// REQUIRE((*fTown).isInitialized(), "City is initialized");
	// REQUIRE(this->isInitialized(), "Output is initialized");

	City* fTown;

	std::stringstream fOut;
	std::ofstream fFile;

	Output* fMyself;
};

#endif /* OUTPUT_H_ */
