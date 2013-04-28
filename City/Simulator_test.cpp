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

class SimulatorTest : public testing::Test {
protected:
	City* ptrCity;

	virtual void SetUp() {
		ptrCity = new City;
	}

	virtual void TearDown() {
		delete ptrCity;
	}
};

TEST_F(SimulatorTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Simulator sim(ptrCity));
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

	Simulator sim(ptrCity);
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

	Simulator sim(ptrCity);
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
