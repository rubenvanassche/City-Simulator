/*
 * GUI.cpp
 *
 *  Created on: 27 apr. 2013
 *      Author: Ruben
 */

#include "GUI.h"


GUI::GUI(City* cityPtr, Simulator* simulatorPtr, CityParser* parserPtr, Out* outputPtr) {
	this->cityRead = false;
	this->carsRead = false;
	this->city = cityPtr;
	this->simulator = simulatorPtr;
	this->parser = parserPtr;
	this->output = outputPtr;

	GUI::start();
}

void GUI::start(){
	std::cout << "City Simulator" << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "1) Stad inlezen" << std::endl;
	std::cout << "2) Voertuigen inlezen" << std::endl;
	std::cout << "3) Zet een gebouw in brand" << std::endl;
	std::cout << "4) Overval een winkel" << std::endl;
	std::cout << "5) Brandweerwagen laten uitrukken" << std::endl;
	std::cout << "6) Politiewagen laten uitrukken" << std::endl;
	std::cout << "7) Simpele uitvoer tonen" << std::endl;
	std::cout << "8) Grafische impressie tonen" << std::endl;
	std::cout << "9) 1 stap in de simulatie uitvoeren" << std::endl;
	std::cout << "10) Meerdere stappen in de simulatie uitvoeren" << std::endl;
	std::cout << "11) Afsluiten" << std::endl;

	std::string input;
	std::cin >> input;
	if(input == "1"){
		GUI::readCity();
	}else if(input == "2"){
		GUI::readVehicles();
	}else if(input == "3"){
		GUI::setBuildingOnFire();
	}else if(input == "4"){
		GUI::startRobbery();
	}else if(input == "5"){
		GUI::sendFireTruck();
	}else if(input == "6"){
		GUI::sendPoliceTruck();
	}else if(input == "7"){
		GUI::simpleOutput();
	}else if(input == "8"){
		GUI::graphicalImpression();
	}else if(input == "9"){
		GUI::oneSimulationStep();
	}else if(input == "10"){
		GUI::multipleSimulationStep();
	}else if(input == "11"){
		return;
	}else{
		std::cout << "Verkeerde keuze, probeer opnieuw!" << std::endl;
		GUI::start();
	}
}

void GUI::readCity(){
	if(this->cityRead == true){
		std::cout << "De Stad is al reeds ingelezen." << std::endl;

		GUI::start();
	}

	std::cout << "Stad inlezen" << std::endl;
	std::cout << "------------" <<std::endl << std::endl;
	std::cout << "Naam van het XML-bestand" << std::endl;

	std::string inputFile;
	std::cin >> inputFile;

	(*parser).parseBuildings(inputFile);

	this->cityRead = true;

	std::cout << "Stad " << inputFile << " ingelezen." << std::endl << std::endl << std::endl;
	GUI::start();
}

void GUI::readVehicles(){
	std::cout << "Voertuigen inlezen" << std::endl;
	std::cout << "------------------" <<std::endl << std::endl;
	std::cout << "Naam van het XML-bestand" << std::endl;

	std::string inputFile;
	std::cin >> inputFile;

	(*parser).parseVehicles(inputFile);

	this->carsRead = true;

	std::cout << "Voetuigen " << inputFile << " ingelezen." << std::endl << std::endl << std::endl;
	GUI::start();
}

void GUI::setBuildingOnFire(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	std::cout << "Zet een gebouw in brand" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	(*simulator).fireBreaksOut();

	std::cout << "Een willekeurig gebouw is in brand gestoken" << std::endl << std::endl << std::endl;

	GUI::start();
}

void GUI::startRobbery(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	std::cout << "Overval een winkel" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	(*simulator).commitRob();

	std::cout << "Een willekeurige winkel wordt nu overvallen." << std::endl << std::endl << std::endl;

	GUI::start();
}

void GUI::sendFireTruck(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		GUI::start();
	}

	std::cout << "Brandweerwagen laten uitrukken" << std::endl;
	std::cout << "------------------------------" << std::endl << std::endl;

	(*simulator).fireTruckControl();

	std::cout << "Er is geprobeerd om een brandweerwagen(s) uit te sturen naar een brandend gebouw." << std::endl << std::endl << std::endl;

	GUI::start();

}

void GUI::sendPoliceTruck(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		GUI::start();
	}

	std::cout << "Politiewagen laten uitrukken" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;

	(*simulator).policeTruckControl();

	std::cout << "Er is geprobeerd om een politiewagen(s) uit te sturen naar een winkel die wordt overvallen." << std::endl << std::endl << std::endl;

	GUI::start();

}

void GUI::simpleOutput(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	std::cout << "Simpele uitvoer tonen" << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	(*output).get();

	std::cout << std::endl << std::endl << std::endl;

	GUI::start();
}

void GUI::graphicalImpression(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	std::cout << "Grafische impressie tonen" << std::endl;
	std::cout << "-------------------------" << std::endl << std::endl;

	std::cout << (*city).print() << std::endl << std::endl << std::endl;

	GUI::start();
}

void GUI::oneSimulationStep(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		GUI::start();
	}

	std::cout << "1 stap in de simulatie uitvoeren" << std::endl;
	std::cout << "--------------------------------" << std::endl << std::endl;

	(*simulator).step();

	GUI::start();
}

void GUI::multipleSimulationStep(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		GUI::start();
	}

	std::cout << "Meerdere stappen in de simulatie uitvoeren" << std::endl;
	std::cout << "------------------------------------------" << std::endl << std::endl;

	std::cout << "Hoeveel stappen : " << std::endl;

	int numberOfSteps;
	std::cin >> numberOfSteps;

	for(int i = 0;i < numberOfSteps;i++){
		(*simulator).step();
	}

	std::cout << numberOfSteps << " stappen in de simulatie uitgevoerd." << std::endl << std::endl << std::endl;
	GUI::start();
}


