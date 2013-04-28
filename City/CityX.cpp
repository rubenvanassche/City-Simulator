/*
 * 0_SIMULATOR.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include <string>
#include "City.h"
#include "CityParser.h"
#include "Simulator.h"
#include "GUI.h"
#include "Out.h"

int main(int argc, char* argv[]){
	std::string outputFile = "output.txt";

	Out output(outputFile); // Our output

	City city; // Our City

	CityParser parser(&city); // Our Parser

	Simulator simulator(&city); // Our simulator

	GUI gui(&city, &simulator, &parser, &output); // Our GUI

	gui.readArguments(argc, argv); // give the arguments to the GUI

	gui.start();	// start the GUI
}


