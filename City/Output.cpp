/*
 * Output.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "Output.h"
#include <fstream>

bool Output::isInitialized() {
	return this == Output::fMyself;
}

Output::Output(City* town, std::string filename) {
	REQUIRE(town->isInitialized(), "City is initialized");

	Output::fMyself = this;
	Output::fTown = town;
	Output::fFileName = filename.c_str();

	ENSURE(this->isInitialized(), "Output is initialized");
}

bool Output::writeToFile() {
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::ofstream filestream;
	filestream.open(Output::fFileName, std::ios_base::app);
	filestream << "Brandende huizen: " << std::endl;
	//Output::fTown->statusBurningHouses(Output::fFileName);
	filestream << "Brandweerwagens onderweg: " << std::endl;
	//Output::fTown->statusTrucksOnWay(Output::fFileName);
	filestream << "Beschikbare brandweerwagens: " << std::endl;
	//Output::fTown->statusAvailableTrucks(Output::fFileName);
	filestream.close();

	return true;
}

bool Output::writeToFile(std::string tokens) {
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::ofstream filestream;
	filestream.open(Output::fFileName, std::ios_base::app);
	filestream << tokens;
	filestream.close();

	return true;
}
