/*
 * GUI.h
 *
 *  Created on: 27 apr. 2013
 *      Author: Ruben
 */

#ifndef GUI_H_
#define GUI_H_

#include <iostream>
#include <string>
#include "City.h"
#include "Simulator.h"
#include "CityParser.h"
#include "Out.h"

class GUI {
public:
	GUI(City* cityPtr, Simulator* simulatorPtr, CityParser* parserPtr, Out* outputPtr);
	void start();
	void readCity();
	void readVehicles();
	void setBuildingOnFire();
	void startRobbery();
	void sendFireTruck();
	void sendPoliceTruck();
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
	Out* output;
};

#endif /* GUI_H_ */
