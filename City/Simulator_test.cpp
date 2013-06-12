/*
 * Simulator_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Sunday 28 April 2013
 * 
 */

#include "gtest/gtest.h"
#include "Simulator.h"
#include "Output.h"
#include <vector>
#include <iostream>

class SimulatorTest : public testing::Test {
protected:
	City* ptrCity;
	Output* ptrOutput;

	virtual void SetUp() {
		ptrCity = new City;
		ptrOutput = new Output(ptrCity, "simulatorTest.txt");
	}

	virtual void TearDown() {
		delete ptrCity;
		delete ptrOutput;
	}
};

TEST_F(SimulatorTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Simulator sim(ptrCity, ptrOutput));
}


TEST_F(SimulatorTest, fire) {
	House newHouse(Point(0, 1), 2);
	Street verticalLeft("VerticalLeft", Point(2, 2), Point(2, 1));
	Street horizontal("Horizontal", Point(2, 2), Point(4, 2));
	Street verticalRight("VerticalRight", Point(4, 3), Point(4, 2));
	ASSERT_TRUE(ptrCity->add(newHouse));
	ASSERT_TRUE(ptrCity->add(horizontal));
	ASSERT_TRUE(ptrCity->add(verticalLeft));
	ASSERT_TRUE(ptrCity->add(verticalRight));

	Simulator sim(ptrCity, ptrOutput);
	House* ptrHouse = ptrCity->getHouses()[0];
	ASSERT_TRUE(ptrHouse != NULL);

	EXPECT_NO_FATAL_FAILURE(sim.fireBreaksOut());
	EXPECT_TRUE(ptrHouse->isBurning());
	EXPECT_EQ(2, ptrHouse->getHealth());

	EXPECT_NO_FATAL_FAILURE(sim.burningDown());
	EXPECT_TRUE(ptrHouse->isBurning());
	EXPECT_EQ(1, ptrHouse->getHealth());

	EXPECT_FALSE(sim.sendFireTrucks());	// oh, there isn't even a firedepot

	// now build a firedepot
	FireDepot newDepot(Point(4, 7), Point(4, 3), "Firedepot", 1);
	ASSERT_TRUE(ptrCity->add(newDepot));
	FireDepot* ptrDepot = ptrCity->findFireDepot("Firedepot");
	ASSERT_TRUE(ptrDepot != NULL);

	EXPECT_FALSE(sim.sendFireTrucks());	// oh, there isn't even a firetruck

	// add a firetruck
	FireTruck newTruck("Truck", ptrDepot);
	ASSERT_TRUE(ptrCity->add(newTruck));
	FireTruck* ptrTruck = ptrCity->getFireTrucks()[0];
	ASSERT_TRUE(ptrTruck != NULL);

	EXPECT_TRUE(sim.sendFireTrucks());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());
	EXPECT_TRUE(ptrHouse->isFireTruckAssigned());
	EXPECT_EQ(Point(2, 1), ptrTruck->getDestination());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(4, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(3, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(2, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(2, 1), ptrTruck->getPosition());
	EXPECT_TRUE(ptrTruck->isArrived());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(ptrDepot->getEntrance(), ptrTruck->getDestination());
	EXPECT_FALSE(ptrHouse->isBurning());
	EXPECT_FALSE(ptrHouse->isFireTruckAssigned());

	EXPECT_NO_FATAL_FAILURE(sim.repairBuildings());
	EXPECT_EQ(1.5, ptrHouse->getHealth());

	EXPECT_NO_FATAL_FAILURE(sim.fireBreaksOut());
	EXPECT_NO_FATAL_FAILURE(sim.fireBreaksOut());
	EXPECT_TRUE(ptrHouse->isBurning());
	EXPECT_TRUE(ptrDepot->isBurning());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(2, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(3, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(4, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(4, 3), ptrTruck->getPosition());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());
	EXPECT_TRUE(ptrTruck->isArrived());

	EXPECT_NO_FATAL_FAILURE(sim.burningDown());
	EXPECT_EQ(0.5, ptrHouse->getHealth());
	EXPECT_EQ(-1, ptrDepot->getHealth());
	EXPECT_TRUE(ptrDepot->isDead());
	EXPECT_FALSE(ptrDepot->isBurning());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());

	EXPECT_NO_FATAL_FAILURE(sim.burningDown());
	EXPECT_EQ(-0.5, ptrHouse->getHealth());
	EXPECT_EQ(-1, ptrDepot->getHealth());

	EXPECT_TRUE(sim.endSimulation());
}

TEST_F(SimulatorTest, robbing) {
	Shop appleStore(Point(0, 1), Size(2), 1, 2);
	Street verticalLeft("VerticalLeft", Point(2, 2), Point(2, 1));
	Street horizontal("Horizontal", Point(2, 2), Point(4, 2));
	Street verticalRight("VerticalRight", Point(4, 3), Point(4, 2));
	ASSERT_TRUE(ptrCity->add(appleStore));
	ASSERT_TRUE(ptrCity->add(horizontal));
	ASSERT_TRUE(ptrCity->add(verticalLeft));
	ASSERT_TRUE(ptrCity->add(verticalRight));

	Simulator sim(ptrCity, ptrOutput);
	Shop* ptrShop = ptrCity->getShops()[0];
	ASSERT_TRUE(ptrShop != NULL);

	EXPECT_TRUE(sim.commitRob());
	EXPECT_TRUE(ptrShop->isRobbing());
	EXPECT_EQ(2, ptrShop->getSecurity());

	EXPECT_TRUE(sim.robbing());
	EXPECT_TRUE(ptrShop->isRobbing());
	EXPECT_EQ(1, ptrShop->getSecurity());

	EXPECT_FALSE(sim.sendPoliceTrucks());	// oh, there isn't even a policedepot

	// now build a policedepot
	PoliceDepot newDepot(Point(4, 7), Point(4, 3), Size(4), "Policedepot", 1);
	ASSERT_TRUE(ptrCity->add(newDepot));
	PoliceDepot* ptrDepot = ptrCity->findPoliceDepot("Policedepot");
	ASSERT_TRUE(ptrDepot != NULL);

	EXPECT_FALSE(sim.sendFireTrucks());	// oh, there isn't even a policetruck

	// add a policetruck
	PoliceTruck newTruck("Truck", ptrDepot);
	ASSERT_TRUE(ptrCity->add(newTruck));
	PoliceTruck* ptrTruck = ptrCity->getPoliceTrucks()[0];
	ASSERT_TRUE(ptrTruck != NULL);

	EXPECT_TRUE(sim.sendPoliceTrucks());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());
	EXPECT_TRUE(ptrShop->isPoliceTruckAssigned());
	EXPECT_EQ(Point(2, 1), ptrTruck->getDestination());

	EXPECT_TRUE(sim.drive());
	EXPECT_EQ(Point(4, 2), ptrTruck->getPosition());

	EXPECT_TRUE(sim.drive());
	EXPECT_EQ(Point(3, 2), ptrTruck->getPosition());

	EXPECT_TRUE(sim.drive());
	EXPECT_EQ(Point(2, 2), ptrTruck->getPosition());

	EXPECT_TRUE(sim.drive());
	EXPECT_EQ(Point(2, 1), ptrTruck->getPosition());
	EXPECT_TRUE(ptrTruck->isArrived());

	EXPECT_TRUE(sim.drive());
	EXPECT_EQ(ptrDepot->getEntrance(), ptrTruck->getDestination());
	EXPECT_FALSE(ptrShop->isRobbing());
	EXPECT_FALSE(ptrShop->isPoliceTruckAssigned());

	EXPECT_FALSE(sim.robbing());
	EXPECT_FALSE(ptrShop->isRobbing());

	EXPECT_TRUE(sim.commitRob());
	EXPECT_TRUE(ptrShop->isRobbing());
	EXPECT_TRUE(sim.robbing());
	EXPECT_FALSE(ptrShop->isRobbing());

	EXPECT_TRUE(sim.fireBreaksOut());
	EXPECT_TRUE(sim.fireBreaksOut());
	EXPECT_TRUE(ptrDepot->isBurning());
	EXPECT_TRUE(ptrShop->isBurning());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(2, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(3, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(4, 2), ptrTruck->getPosition());

	EXPECT_NO_FATAL_FAILURE(sim.drive());
	EXPECT_EQ(Point(4, 3), ptrTruck->getPosition());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());
	EXPECT_TRUE(ptrTruck->isArrived());

	EXPECT_TRUE(sim.drive());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());

	EXPECT_TRUE(sim.burningDown());
	EXPECT_EQ(-1, ptrShop->getHealth());
	EXPECT_EQ(-1, ptrDepot->getHealth());
	EXPECT_TRUE(ptrDepot->isDead());
	EXPECT_FALSE(ptrDepot->isBurning());
	EXPECT_TRUE(ptrShop->isDead());

	EXPECT_TRUE(sim.endSimulation());
}

TEST_F(SimulatorTest, spreadFireHouse2){
	House house0(Point(3, 5), 20); // First burning house
	House house1(Point(1, 3), 20);
	House house2(Point(1, 5), 20);
	House house3(Point(1, 7), 20);
	House house4(Point(3, 3), 20);
	House house5(Point(3, 7), 20);
	House house6(Point(5, 3), 20);
	House house7(Point(5, 5), 20);
	House house8(Point(5, 7), 20);

	Street horizontalDown("Horizontaldown", Point(0, 0), Point(8, 0));
	Street horizontalUp("Horizontalup", Point(0, 8), Point(8, 8));
	Street verticalLeft("verticalLeft", Point(0, 0), Point(0, 8));
	Street verticalRight("verticalRigth", Point(8, 0), Point(8, 8));

	EXPECT_TRUE(ptrCity->add(horizontalDown));
	EXPECT_TRUE(ptrCity->add(horizontalUp));
	EXPECT_TRUE(ptrCity->add(verticalLeft));
	EXPECT_TRUE(ptrCity->add(verticalRight));

	EXPECT_TRUE(ptrCity->add(house0));
	EXPECT_TRUE(ptrCity->add(house1));
	EXPECT_TRUE(ptrCity->add(house2));
	EXPECT_TRUE(ptrCity->add(house3));
	EXPECT_TRUE(ptrCity->add(house4));
	EXPECT_TRUE(ptrCity->add(house5));
	EXPECT_TRUE(ptrCity->add(house6));
	EXPECT_TRUE(ptrCity->add(house7));
	EXPECT_TRUE(ptrCity->add(house8));

	std::cout << ptrCity->print() << std::endl;

	Simulator sim(ptrCity, ptrOutput);

	std::vector<House*> houses = ptrCity->getHouses();
	std::vector<House*>::iterator it;

	// Set first house on fire
	houses.at(0)->setFire();
	ptrOutput->step();

	// Count houses on fire
	int counter = 0;

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 1);
	std::cout << ptrCity->print() << std::endl;

	sim.burningDown();
	ptrOutput->step();
	sim.burningDown();
	ptrOutput->step();
	sim.burningDown();
	sim.spreadFire();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 2);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 3);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 4);
	std::cout << ptrCity->print() << std::endl;
}

TEST_F(SimulatorTest, spreadFireHouse3){
	House house0(Point(3, 5), 20);
	House house1(Point(1, 3), 20);// First burning house
	House house2(Point(1, 5), 20);
	House house3(Point(1, 7), 20);
	House house4(Point(3, 3), 20);
	House house5(Point(3, 7), 20);
	House house6(Point(5, 3), 20);
	House house7(Point(5, 5), 20);
	House house8(Point(5, 7), 20);

	Street horizontalDown("Horizontaldown", Point(0, 0), Point(8, 0));
	Street horizontalUp("Horizontalup", Point(0, 8), Point(8, 8));
	Street verticalLeft("verticalLeft", Point(0, 0), Point(0, 8));
	Street verticalRight("verticalRigth", Point(8, 0), Point(8, 8));

	EXPECT_TRUE(ptrCity->add(horizontalDown));
	EXPECT_TRUE(ptrCity->add(horizontalUp));
	EXPECT_TRUE(ptrCity->add(verticalLeft));
	EXPECT_TRUE(ptrCity->add(verticalRight));

	EXPECT_TRUE(ptrCity->add(house0));
	EXPECT_TRUE(ptrCity->add(house1));
	EXPECT_TRUE(ptrCity->add(house2));
	EXPECT_TRUE(ptrCity->add(house3));
	EXPECT_TRUE(ptrCity->add(house4));
	EXPECT_TRUE(ptrCity->add(house5));
	EXPECT_TRUE(ptrCity->add(house6));
	EXPECT_TRUE(ptrCity->add(house7));
	EXPECT_TRUE(ptrCity->add(house8));

	std::cout << ptrCity->print() << std::endl;

	Simulator sim(ptrCity, ptrOutput);

	std::vector<House*> houses = ptrCity->getHouses();
	std::vector<House*>::iterator it;

	// Set first house on fire
	houses.at(1)->setFire();
	ptrOutput->step();

	// Count houses on fire
	int counter = 0;

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 1);
	std::cout << ptrCity->print() << std::endl;

	sim.burningDown();
	ptrOutput->step();
	sim.burningDown();
	ptrOutput->step();
	sim.burningDown();
	sim.spreadFire();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 2);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 3);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 4);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}

	EXPECT_EQ(counter, 4);
	std::cout << ptrCity->print() << std::endl;

	sim.spreadFire();
	sim.burningDown();
	ptrOutput->step();

	counter = 0;
	for(it = houses.begin();it != houses.end();it++){
		if((*it)->isBurning()){
			counter++;
		}
	}
}

