/*
 * GUI.cpp
 *
 *  Created on: 27 apr. 2013
 *      Author: Ruben
 */

#include "GUI.h"
#include <sstream>

GUI::GUI(City* cityPtr, Simulator* simulatorPtr, CityParser* parserPtr, Out* outputPtr) {
	this->cityRead = false;
	this->carsRead = false;
	this->city = cityPtr;
	this->simulator = simulatorPtr;
	this->parser = parserPtr;
	this->output = outputPtr;
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
	std::cout << "7) Wagens laten rondrijden" << std::endl;
	std::cout << "8) Simpele uitvoer tonen" << std::endl;
	std::cout << "9) Grafische impressie tonen" << std::endl;
	std::cout << "10) 1 stap in de simulatie uitvoeren" << std::endl;
	std::cout << "11) Meerdere stappen in de simulatie uitvoeren" << std::endl;
	std::cout << "12) Afsluiten" << std::endl;

	std::string in;
	std::cin >> in;

	int input;
	std::stringstream ss;
	ss << in;
	ss >> input;

	if(input == 1){
		return GUI::readCity();
	}else if(input == 2){
		return GUI::readVehicles();
	}else if(input == 3){
		return GUI::setBuildingOnFire();
	}else if(input == 4){
		return GUI::startRobbery();
	}else if(input == 5){
		return GUI::sendFireTruck();
	}else if(input == 6){
		return GUI::sendPoliceTruck();
	}else if(input == 7){
		return GUI::driveAround();
	}else if(input == 8){
		return GUI::simpleOutput();
	}else if(input == 9){
		return GUI::graphicalImpression();
	}else if(input == 10){
		return GUI::oneSimulationStep();
	}else if(input == 11){
		return GUI::multipleSimulationStep();
	}else if(input == 12){
		return;
	}else{
		std::cout << "Verkeerde keuze, probeer opnieuw!" << std::endl;
		return GUI::start();
	}
}

void GUI::readArguments(int argc, char* argv[]){
   if(argc == 1){
	   return;
   }else if(argc == 2){
	   std::string inputFile = "";
	   std::stringstream ss;
	   ss << argv[1];
	   ss >> inputFile;
		if (! (*parser).parseBuildings(inputFile) ) {
			std::cout << "(Stad)Mogelijk heeft u een verkeerde bestandsnaam ingevoerd." << std::endl << std::endl << std::endl;
			 return;
		}

		this->cityRead = true;

   }else if(argc == 3){
	   std::string inputFile = "";
	   std::stringstream ss;
	   ss << argv[1];
	   ss >> inputFile;
		if (! (*parser).parseBuildings(inputFile) ) {
			std::cout << "(Stad)Mogelijk heeft u een verkeerde bestandsnaam ingevoerd." << std::endl << std::endl << std::endl;
			 return;
		}

		this->cityRead = true;

	   std::string inputFile2 = "";
	   std::stringstream ss2;
	   ss2 << argv[2];
	   ss2 >> inputFile2;
		if (! (*parser).parseVehicles(inputFile2) ) {
			std::cout << "(Voertuigen)Mogelijk heeft u een verkeerde bestandsnaam ingevoerd." << std::endl << std::endl << std::endl;
			 return;
		}

		this->carsRead = true;

   }else{
	   std::cout << "U heeft te veel argumenten meegegeven." << std::endl;
   }
}

void GUI::readCity(){
	if(this->cityRead == true){
		std::cout << "De Stad is al reeds ingelezen." << std::endl;

		return GUI::start();
	}

	std::cout << "Stad inlezen" << std::endl;
	std::cout << "------------" <<std::endl << std::endl;
	std::cout << "Naam van het XML-bestand" << std::endl;

	std::string inputFile;
	std::cin >> inputFile;

	if (! (*parser).parseBuildings(inputFile) ) {
		std::cout << "Mogelijk heeft u een verkeerde bestandsnaam ingevoerd." << std::endl << std::endl << std::endl;
		return GUI::start();
	}

	this->cityRead = true;

	std::cout << "Stad " << inputFile << " ingelezen." << std::endl << std::endl << std::endl;
	return GUI::start();
}

void GUI::readVehicles(){
	std::cout << "Voertuigen inlezen" << std::endl;
	std::cout << "------------------" <<std::endl << std::endl;
	std::cout << "Naam van het XML-bestand" << std::endl;

	std::string inputFile;
	std::cin >> inputFile;

	if (! (*parser).parseVehicles(inputFile) ) {
		std::cout << "Mogelijk heeft u een verkeerde bestandsnaam ingevoerd." << std::endl << std::endl << std::endl;
		return GUI::start();
	}

	this->carsRead = true;

	std::cout << "Voetuigen " << inputFile << " ingelezen." << std::endl << std::endl << std::endl;
	return GUI::start();
}

void GUI::setBuildingOnFire(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "Zet een gebouw in brand" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	if ( (*simulator).fireBreaksOut() ) {
		std::cout << "Een willekeurig gebouw is in brand gestoken" << std::endl << std::endl << std::endl;
	}
	else {
		std::cout << "Er is geen enkele gebouw die niet in brand staat" << std::endl << std::endl << std::endl;
	}

	return GUI::start();
}

void GUI::startRobbery(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "Overval een winkel" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	if ( (*simulator).commitRob() ){
		std::cout << "Een willekeurige winkel wordt nu overvallen." << std::endl << std::endl << std::endl;

	}
	else {
		std::cout << "Er is geen winkel die niet overvallen word" << std::endl << std::endl << std::endl;
	}

	return GUI::start();
}

void GUI::sendFireTruck(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "Brandweerwagen laten uitrukken" << std::endl;
	std::cout << "------------------------------" << std::endl << std::endl;

	if ( (*simulator).sendFireTrucks() ) {
		std::cout << "Er zijn brandweerwagen(s) uitgestuurd." << std::endl << std::endl << std::endl;
	}
	else {
		std::cout << "Er zijn geen brandweerwagens beschikbaar." << std::endl << std::endl << std::endl;
	}

	return GUI::start();

}

void GUI::sendPoliceTruck(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "Politiewagen laten uitrukken" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;

	if ( (*simulator).sendPoliceTrucks() ) {
		std::cout << "Er zijn politiewagen(s) uitgestuurd." << std::endl << std::endl << std::endl;
	}
	else {
		std::cout << "Er zijn geen politiewagens beschikbaar" << std::endl << std::endl << std::endl;
	}
	return GUI::start();

}

void GUI::driveAround() {
	if (this->cityRead == false) {
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "Wagens laten rondrijden" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	if ( (*simulator).drive() ) {
		std::cout << "Er zijn wagens(s) rondgereden." << std::endl << std::endl << std::endl;
	}
	else {
		std::cout << "Er zijn geen wagens onderweg." << std::endl << std::endl << std::endl;
	}
	return GUI::start();

}

void GUI::simpleOutput(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	std::cout << "Simpele uitvoer tonen" << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	(*output).get();

	std::cout << std::endl << std::endl << std::endl;

	return GUI::start();
}

void GUI::graphicalImpression(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	std::cout << "Grafische impressie tonen" << std::endl;
	std::cout << "-------------------------" << std::endl << std::endl;

	std::cout << (*city).print() << std::endl << std::endl << std::endl;

	return GUI::start();
}

void GUI::oneSimulationStep(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
	}

	std::cout << "1 stap in de simulatie uitvoeren" << std::endl;
	std::cout << "--------------------------------" << std::endl << std::endl;

	(*simulator).step();

	return GUI::start();
}

void GUI::multipleSimulationStep(){
	if(this->cityRead == false){
		std::cout << "Gelieve eerst een stad in te lezen." << std::endl;

		return GUI::start();
	}

	if(this->carsRead == false){
		std::cout << "Gelieve eerst voertuigen in te lezen.." << std::endl;

		return GUI::start();
	}

	if (simulator->endSimulation()) {
		std::cout << "U kunt niets meer doen: de stad is platgebrand." << std::endl;
		return GUI::start();
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
	return GUI::start();
}
