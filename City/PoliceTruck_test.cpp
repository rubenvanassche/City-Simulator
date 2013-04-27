/*
 * PoliceTruck_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "gtest/gtest.h"
#include "PoliceTruck.h"
#include "PoliceDepot.h"
#include "Shop.h"

class PoliceTruckTest : public testing::Test {
protected:
	Point locDepot;
	Point entrDepot;
	Size size;
	std::string basename;
	int health;

	std::string carname;
	PoliceDepot* ptrBase;

	Shop* ptrAppleStore;
	Point locShop;
	int security;

	virtual void SetUp() {
		locDepot.set(2, 2);
		entrDepot.set(0, 0);
		size.set(3, 3);
		basename = "PoliceDepot";
		health = 10;

		carname = "PoliceTruck";
		ptrBase = new PoliceDepot(locDepot, entrDepot, size, basename, health);

		locShop.set(1, 1);
		security = 5;
		ptrAppleStore = new Shop(locShop, size, health, security);
	}

	virtual void TearDown() {
		delete ptrBase;
		delete ptrAppleStore;
	}

};

TEST_F(PoliceTruckTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(PoliceTruck truck(carname, ptrBase));
}

TEST_F(PoliceTruckTest, getters) {
	PoliceTruck truck(carname, ptrBase);

	EXPECT_EQ(ptrBase, truck.getBase());
	EXPECT_EQ(NULL, truck.getShop());
	EXPECT_EQ(carname, truck.getName());
}

TEST_F(PoliceTruckTest, sending) {
	PoliceTruck truck(carname, ptrBase);

	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isArrived());

	// first send the policetruck
	EXPECT_DEATH(truck.send(ptrAppleStore, ptrAppleStore->getLocation()), "\\w");	// ooops, AppleStore is not being robbed!

	// HOORAY! Let's rob AppleStore!
	EXPECT_NO_FATAL_FAILURE(ptrAppleStore->startRobbing());

	// okay, now we can send a policetruck
	EXPECT_NO_FATAL_FAILURE(truck.send(ptrAppleStore, ptrAppleStore->getLocation()));
	EXPECT_EQ(ptrAppleStore, truck.getShop());
	EXPECT_EQ(locShop, truck.getDestination());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_EQ(entrDepot, truck.getPosition());

	// then drive to the AppleStore
	EXPECT_DEATH(truck.goLeft(), "\\w");	// ooops, you just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(truck.goRight());
	EXPECT_EQ(Point(entrDepot.getX() + 1, entrDepot.getY()), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE(truck.isArrived());

	EXPECT_DEATH(truck.goDown(), "\\w");	// oops you just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(truck.goUp());
	EXPECT_EQ(Point(entrDepot.getX() + 1, entrDepot.getY() + 1), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());

	// then sendback
	EXPECT_DEATH(truck.sendBack(), "\\w");	// ooops, the AppleStore is still being robbed
	EXPECT_NO_FATAL_FAILURE(truck.getShop()->stopRobbing());

	EXPECT_NO_FATAL_FAILURE(truck.sendBack());
	EXPECT_EQ(NULL, truck.getShop());
	EXPECT_EQ(entrDepot, truck.getDestination());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE((truck.isArrived()));

	// then drive to the depot
	EXPECT_NO_FATAL_FAILURE(truck.goLeft());
	EXPECT_EQ(Point(entrDepot.getX(), entrDepot.getY() + 1), truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_TRUE(truck.isOnWay());
	EXPECT_FALSE(truck.isArrived());

	EXPECT_DEATH(truck.goLeft(), "\\w"); // oops, just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(truck.goDown());
	EXPECT_EQ(entrDepot, truck.getPosition());
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());

	// okay, enter depot, but it went on fire suddenly
	EXPECT_NO_FATAL_FAILURE(ptrBase->setFire());
	EXPECT_DEATH(truck.enterDepot(), "\\w");	// oops, base is on fire!

	// a firetruck is arrived and stopped the fire
	EXPECT_NO_FATAL_FAILURE(ptrBase->stopFire());

	// the truck can now enter the depot properly
	EXPECT_NO_FATAL_FAILURE(truck.enterDepot());
	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isArrived());
	EXPECT_EQ(locDepot, truck.getPosition());

	// end of scenario
}
