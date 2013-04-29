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

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

class Output {
public:
	Output(City* town, char filename[]);

	friend std::ostream& operator<< (std::ostream& stream, Output& o);

	void shopsOnFire();
	// Write all the shops on fire to the out stream
	void housesOnFire();
	// Write all the houses on fire to the out stream
	void fireDepotsOnFire();
	// Write all the fire depots on fire to the out stream
	void policeDepotsOnFire();
	// Write all the police depots on fire to the out stream
	void hospitalsOnFire();
	// Write all the hospitals on fire to the out stream

	void shopsBeingRobbed();
	// Write all the shops being robbed to the out stream

	void fireTrucksdriving();
	// Write all the fire trucks who are driving to the out stream
	void policeTrucksDriving();
	// Write all the police trucks who are driving to the out stream
	void ambulancesDriving();
	// Write all the ambulances who are driving to the out stream

	void fireDepotsTrucks();
	// Write all the fire trucks who are in a depot to the out stream
	void policeDepotsTrucks();
	// Write all the police trucks who are in a depot to the out stream
	void hospitalsTrucks();
	// Write all the ambulances who are in a depot to the out stream

	void parse();
	// Generate the out stream by using functions above

	std::string get();
	// Get a snapshot of the output at this moment

	void step();
	// Write a snapshot of the output to the file

	virtual ~Output();
	// DIE
private:
	City* fTown;
	std::stringstream fOut;
	std::ofstream fFile;
};

#endif /* OUTPUT_H_ */
