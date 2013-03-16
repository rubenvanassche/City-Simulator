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

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <XML-file>" << std::endl;
		return 0;
	}

	std::stringstream ss;
	ss << argv[0];
	std::string filename = ss.str();

	City town = CityParser::parse(filename);
	// std::stringstream ss = Simulator::simulate(town); todo: write this function
	// output::writeToFile(ss);	todo: write this function

	return 0;
}


