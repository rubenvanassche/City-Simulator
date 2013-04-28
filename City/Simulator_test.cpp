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

	// now build a firedepot
	FireDepot newDepot(Point(4, 7), Point(4, 3), "Firedepot", 1);
	ASSERT_TRUE(ptrCity->add(newDepot));
	FireDepot* ptrDepot = ptrCity->findFireDepot("Firedepot");
	ASSERT_TRUE(ptrDepot != NULL);

	// add a firetruck
	FireTruck newTruck("Truck", ptrDepot);
	ASSERT_TRUE(ptrCity->add(newTruck));
	FireTruck* ptrTruck = ptrCity->getFireTrucks()[0];
	ASSERT_TRUE(ptrTruck != NULL);

	EXPECT_NO_FATAL_FAILURE(sim.fireTruckControl());
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

	EXPECT_NO_FATAL_FAILURE(sim.fireTruckControl());
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

	EXPECT_NO_FATAL_FAILURE(sim.fireTruckControl());
	EXPECT_TRUE(ptrTruck->isAtEntranceDepot());

	EXPECT_NO_FATAL_FAILURE(sim.burningDown());
	EXPECT_EQ(-0.5, ptrHouse->getHealth());
	EXPECT_EQ(-1, ptrDepot->getHealth());

	EXPECT_TRUE(sim.endSimulation());
}
