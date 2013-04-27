/*
 * FireTruck_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Saturday 27 April 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireTruck.h"
#include "FireDepot.h"
#include "House.h"

class FireTruckTest : public testing::Test {
protected:
	Point locDepot;
	Point entrDepot;
	std::string basename;
	int health;

	std::string carname;
	FireDepot* ptrBase;

	House* ptrHouse;
	Point locHouse;

	virtual void SetUp() {
		locDepot.set(2, 2);
		entrDepot.set(0, 0);
		basename = "FireDepot";
		health = 10;

		carname = "FireTruck";
		ptrBase = new FireDepot(locDepot, entrDepot, basename, health);

		locHouse.set(1, 1);
		ptrHouse = new House(locHouse, health);
	}

	virtual void TearDown() {
		delete ptrBase;
		delete ptrHouse;
	}

};

TEST_F(FireTruckTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(FireTruck truck(carname, ptrBase));
}

TEST_F(FireTruckTest, getters) {
	FireTruck truck(carname, ptrBase);

	EXPECT_EQ(ptrBase, truck.getBase());
	EXPECT_EQ(NULL, truck.getBuilding());
	EXPECT_EQ(carname, truck.getName());
}

TEST_F(FireTruckTest, sending) {
	FireTruck truck(carname, ptrBase);

	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isArrived());

	// first send the firetruck
	EXPECT_DEATH(truck.send(ptrHouse, ptrHouse->getLocation()), "\\w");	// ooops, house is not on fire!

	// so, what we really need to do first, is set that house on fire
	EXPECT_NO_FATAL_FAILURE(ptrHouse->setFire());

	// then send the firetruck
	EXPECT_NO_FATAL_FAILURE(truck.send(ptrHouse, ptrHouse->getLocation()));
	EXPECT_EQ(ptrHouse, truck.getBuilding());
	EXPECT_EQ(locHouse, truck.getDestination());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_EQ(entrDepot, truck.getPosition());

	// then drive to the house
	EXPECT_DEATH(truck.goLeft(), "\\w");	// ooops, you just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(truck.goRight());
	EXPECT_EQ(Point(entrDepot.getX() + 1, entrDepot.getY()), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE(truck.isArrived());

	EXPECT_DEATH(truck.goDown(), "\\w");	// oops, you just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(truck.goUp());
	EXPECT_EQ(Point(entrDepot.getX()+1, entrDepot.getY()+1), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());

	// then sendback
	EXPECT_DEATH(truck.sendBack(), "\\w");	// oops, the house is still on fire!
	EXPECT_NO_FATAL_FAILURE(truck.getBuilding()->stopFire());

	EXPECT_NO_FATAL_FAILURE(truck.sendBack());
	EXPECT_EQ(NULL, truck.getBuilding());
	EXPECT_EQ(entrDepot, truck.getDestination());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE(truck.isArrived());

	// then drive to the depot
	EXPECT_NO_FATAL_FAILURE(truck.goLeft());
	EXPECT_EQ(Point(entrDepot.getX(), entrDepot.getY() + 1), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE(truck.isArrived());

	EXPECT_DEATH(truck.goLeft(), "\\w");	// oops, just got negative coordinates

	EXPECT_NO_FATAL_FAILURE(truck.goDown());
	EXPECT_EQ(entrDepot, truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());

	// okay, enter depot, but it went on fire suddenly
	EXPECT_NO_FATAL_FAILURE(ptrBase->setFire());
	EXPECT_DEATH(truck.enterDepot(), "\\w");	// oops, base is on fire!

	// so stop the fire and then enter depot properly
	EXPECT_NO_FATAL_FAILURE(ptrBase->stopFire());
	EXPECT_NO_FATAL_FAILURE(truck.enterDepot());
	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());
	EXPECT_EQ(locDepot, truck.getPosition());

	// end of scenario
}
