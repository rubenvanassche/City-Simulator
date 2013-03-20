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
#include "Output.h"

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

	City* town = CityParser::parse(filename);
	Simulator sim(town);
	Output out(town, outputname);

	// use this for debugging:
	for (unsigned int i=0; i < 50; i++) {
		sim.simulate(out);
		if (sim.endSimulation() ) {
			break;
		}
	}
	delete town;

	// USE THIS CODE BELOW ONLY IF YOU ARE SURE THAT EVERYTHING IS WORKING AND NO MEMORY LEAKS APPEARS!!
	//while (!sim.endSimulation() ) {
	//	sim.simulate(out);
	//}
	//delete town;

	return 0;
}


