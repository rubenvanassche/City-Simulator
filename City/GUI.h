/*
 * GUI.h
 *
 *  Created on: 27 apr. 2013
 *      Author: Ruben
 */

#ifndef GUI_H_
#define GUI_H_

#include <iostream>
#include <sstream>
#include <string>
#include "City.h"
#include "Simulator.h"
#include "CityParser.h"
#include "Output.h"

class GUI {
public:
	GUI(City* cityPtr, Simulator* simulatorPtr, CityParser* parserPtr, Output* outputPtr);
	void start();
	void readArguments(int argc, char* argv[]);
	void readCity();
	void readVehicles();
	void setBuildingOnFire();
	void startRobbery();
	void sendFireTruck();
	void sendPoliceTruck();
	void burning();
	void robbing();
	void driveAround();
	void simpleOutput();
	void graphicalImpression();
	void oneSimulationStep();
	void multipleSimulationStep();
private:
	bool cityRead;
	bool carsRead;
	City* city;
	Simulator* simulator;
	CityParser* parser;
	Output* output;
};

#endif /* GUI_H_ */
