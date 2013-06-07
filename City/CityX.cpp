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
#include "Output.h"

int main(int argc, char* argv[]){
	char filename[] = "output.txt";

	City city; // Our City

	Output output(&city, filename); // Our output

	CityParser parser(&city, &output); // Our Parser

	Simulator simulator(&city, &output); // Our simulator

	GUI gui(&city, &simulator, &parser, &output); // Our GUI

	gui.readArguments(argc, argv); // give the arguments to the GUI

	gui.start();	// start the GUI
}


