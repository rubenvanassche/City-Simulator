/*
 * Simulator_test.cpp
 *
 * @author:		Ruben Van Assche
 * @version:	2.0
 * @date:		Sunday 28 April 2013
 *
 */

#include "gtest/gtest.h"
#include "Simulator.h"
#include "City.h"
#include "CityParser.h"
#include "Output.h"
#include "FileTest.h"
#include <vector>
#include <iostream>

class OutputTest : public testing::Test {
protected:
	City* ptrCity;
	Output* ptrOutput;
	CityParser* ptrParser;
	Simulator* ptrSimulator;

	std::vector<Shop*> shops;
	std::vector<House*> houses;
	std::vector<FireDepot*> fireDepots;
	std::vector<PoliceDepot*> policeDepots;
	std::vector<Hospital*> hospitals;

	std::vector<FireTruck*> fireTrucks;
	std::vector<PoliceTruck*> policeTrucks;
	std::vector<Ambulance*> ambulances;


	virtual void SetUp() {
		ptrCity = new City;
		ptrParser = new CityParser(ptrCity);
		ptrOutput = new Output(ptrCity, "../Output-testfiles/OutputTest.txt");
		ptrSimulator = new Simulator(ptrCity, ptrOutput);

		ptrParser->parseBuildings("../XML-testfiles/stad.xml");
		ptrParser->parseVehicles("../XML-testfiles/voertuigen.xml");

		shops = ptrCity->getShops();
		houses = ptrCity->getHouses();
		fireDepots = ptrCity->getFireDepots();
		policeDepots = ptrCity->getPoliceDepots();
		hospitals = ptrCity->getHospitals();

		fireTrucks = ptrCity->getFireTrucks();
		policeTrucks = ptrCity->getPoliceTrucks();
		ambulances = ptrCity->getAmbulances();
	}

	virtual void TearDown() {
		delete ptrCity;
		delete ptrOutput;
		delete ptrParser;
		delete ptrSimulator;
	}
};

TEST_F(OutputTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Output out(ptrCity, "../Output-testfiles/OutputTest.txt"));
	EXPECT_TRUE(FileTest::fileExists("../Output-testfiles/OutputTest.txt"));
}

// Burn the whole city down
TEST_F(OutputTest, scenario1) {
	// Set everything on fire
	for(unsigned int i = 0;i < shops.size();i++){
		shops.at(i)->setFire();
	}

	for(unsigned int i = 0;i < houses.size();i++){
		houses.at(i)->setFire();
	}

	for(unsigned int i = 0;i < fireDepots.size();i++){
		fireDepots.at(i)->setFire();
	}

	for(unsigned int i = 0;i < policeDepots.size();i++){
		policeDepots.at(i)->setFire();
	}

	for(unsigned int i = 0;i < hospitals.size();i++){
		hospitals.at(i)->setFire();
	}

	// Let simulator run
	for(int i = 0;i < 100;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->burningDown();
			ptrOutput->step();
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario1.txt"));
}

// Set a policedepot on fire, don't extinghuish it and then start a robbery
TEST_F(OutputTest, scenario2) {
	policeDepots.at(0)->setFire();

	// Let simulator run
	for(int i = 0;i < 15;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->burningDown();
			ptrOutput->step();
		}
	}

	shops.at(0)->startRobbing();

	// Let simulator run
	for(int i = 0;i < 15;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario2.txt"));
}


// Set 5 houses on fire
TEST_F(OutputTest, scenario3) {
	// Set everything on fire

	houses.at(0)->setFire();
	houses.at(3)->setFire();
	houses.at(5)->setFire();
	houses.at(7)->setFire();
	houses.at(9)->setFire();


	// Let simulator run
	for(int i = 0;i < 44;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario3.txt"));
}


// Set 2 houses on fire and rob a shop
TEST_F(OutputTest, scenario4) {
	// Set everything on fire

	houses.at(0)->setFire();
	houses.at(3)->setFire();

	shops.at(0)->startRobbing();


	// Let simulator run
	for(int i = 0;i < 37;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario4.txt"));
}

// Set 4 houses on fire and a firedepot
TEST_F(OutputTest, scenario5) {
	// Set everything on fire

	houses.at(2)->setFire();
	houses.at(4)->setFire();
	houses.at(6)->setFire();
	houses.at(8)->setFire();

	fireDepots.at(0)->setFire();


	// Let simulator run
	for(int i = 0;i < 89;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario5.txt"));
}

// Set a fire depot on fire and don't extinghuish, then let 2 houses burn
TEST_F(OutputTest, scenario6) {
	// Set everything on fire

	fireDepots.at(0)->setFire();

	for(int i = 0;i < 25;i++){
		ptrSimulator->burningDown();
		ptrOutput->step();
	}

	houses.at(2)->setFire();
	houses.at(4)->setFire();


	// Let simulator run
	for(int i = 0;i < 19;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario6.txt"));
}

// Rob 2 shops, let teh police handle it and after that, start again
TEST_F(OutputTest, scenario7) {
	shops.at(1)->startRobbing();
	shops.at(3)->startRobbing();

	// Let simulator run
	for(int i = 0;i < 28;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	shops.at(1)->startRobbing();
	shops.at(3)->startRobbing();

	for(int i = 0;i < 28;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}


	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario7.txt"));
}

// Let an Hospital die at a very long time(with repairs)
TEST_F(OutputTest, scenario8) {
	hospitals.at(0)->setFire();

	// Let simulator run
	for(int i = 0;i < 28;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	hospitals.at(0)->setFire();

	// Let simulator run
	for(int i = 0;i < 28;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	hospitals.at(0)->setFire();

	// Let simulator run
	for(int i = 0;i < 28;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario8.txt"));
}

// Set one from each type of building on fire and check the repair function
TEST_F(OutputTest, scenario9) {
	houses.at(3)->setFire();
	shops.at(0)->setFire();
	policeDepots.at(0)->setFire();
	fireDepots.at(0)->setFire();
	hospitals.at(0)->setFire();

	// Let simulator run
	for(int i = 0;i < 78;i++){
		if(!ptrSimulator->endSimulation()){
			ptrSimulator->step(false);
		}
	}

	ptrOutput->write();
	EXPECT_TRUE(FileTest::compare("../Output-testfiles/OutputTest.txt", "../Output-testfiles/scenario9.txt"));
}



