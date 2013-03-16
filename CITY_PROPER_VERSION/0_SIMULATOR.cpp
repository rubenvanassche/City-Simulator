/*
 * 0_SIMULATOR.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include <iostream>
#include "CityParser.h"
#include <sstream>
#include "Simulator.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " <XML-file> <Ouput-file>" << std::endl;
		return 0;
	}

	std::stringstream ss;
	ss << argv[1];
	std::string filename = ss.str();

	std::stringstream tt;
	tt << argv[2];
	std::string outputname = tt.str();

	City town = CityParser::parse(filename);
	Simulator sim(&town, outputname);
	while (!sim.endSimulation()	) {
		sim.simulate();
		sim.output();
	}

	return 0;
}


