/*
 * Ambulance_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "gtest/gtest.h"
#include "Ambulance.h"
#include "Hospital.h"
#include "House.h"

class AmbulanceTest : public testing::Test {
protected:

	Point locDepot;
	Point entrDepot;
	Size size;
	std::string basename;
	int health;

	std::string carname;
	Hospital* ptrBase;

	House* ptrHouse;
	Point locHouse;

	virtual void SetUp() {
		locDepot.set(2, 2);
		entrDepot.set(0, 0);
		size.set(3, 3);
		basename = "Hospital";
		health = 10;

		carname = "Ambulance";
		ptrBase = new Hospital(locDepot, entrDepot, size, basename, health);

		locHouse.set(1, 1);
		ptrHouse = new House(locHouse, health);
	}

	virtual void TearDown() {
		delete ptrBase;
		delete ptrHouse;
	}

	Point right() {
		return Point(entrDepot.getX() + 1, entrDepot.getY());
	}

	Point up() {
		return Point(entrDepot.getX() + 1, entrDepot.getY() + 1);
	}

	Point left() {
		return Point(entrDepot.getX(), entrDepot.getY() + 1);
	}

	Point down() {
		return entrDepot;
	}
};

TEST_F(AmbulanceTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(Ambulance ambuce(carname, ptrBase));
}

TEST_F(AmbulanceTest, getters) {
	Ambulance ambuce(carname, ptrBase);

	EXPECT_EQ(ptrBase, ambuce.getBase());
	EXPECT_EQ(NULL, ambuce.getBuilding());
	EXPECT_EQ(carname, ambuce.getName());
}

TEST_F(AmbulanceTest, sending) {
	Ambulance ambuce(carname, ptrBase);

	EXPECT_TRUE(ambuce.isInDepot());
	EXPECT_FALSE(ambuce.isOnWay());

	// first, send an ambulance
	EXPECT_NO_FATAL_FAILURE(ambuce.send(ptrHouse, ptrHouse->getLocation()));
	EXPECT_EQ(locHouse, ambuce.getDestination());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_TRUE(ambuce.isOnWay());
	EXPECT_FALSE(ambuce.isArrived());
	EXPECT_EQ(entrDepot, ambuce.getPosition());

	// then drive
	EXPECT_DEATH(ambuce.goLeft(), "\\w");	// ooops, you just got negative coordinates!
	EXPECT_NO_FATAL_FAILURE(ambuce.goRight());
	EXPECT_EQ(right(), ambuce.getPosition());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_TRUE(ambuce.isOnWay());
	EXPECT_FALSE(ambuce.isArrived());

	EXPECT_DEATH(ambuce.goDown(), "\\w");	// ooops, you just got negative coordinates!
	EXPECT_NO_FATAL_FAILURE(ambuce.goUp());
	EXPECT_EQ(up(), ambuce.getPosition());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_FALSE(ambuce.isOnWay());
	EXPECT_TRUE(ambuce.isArrived());

	// sendback then
	EXPECT_NO_FATAL_FAILURE(ambuce.sendBack());
	EXPECT_EQ(entrDepot, ambuce.getDestination());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_TRUE(ambuce.isOnWay());
	EXPECT_FALSE(ambuce.isArrived());
	EXPECT_EQ(locHouse, ambuce.getPosition());

	// then drive
	EXPECT_NO_FATAL_FAILURE(ambuce.goLeft());
	EXPECT_EQ(left(), ambuce.getPosition());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_TRUE(ambuce.isOnWay());
	EXPECT_FALSE(ambuce.isArrived());

	EXPECT_NO_FATAL_FAILURE(ambuce.goDown());
	EXPECT_EQ(down(), ambuce.getPosition());
	EXPECT_FALSE(ambuce.isInDepot());
	EXPECT_FALSE(ambuce.isOnWay());
	EXPECT_TRUE(ambuce.isArrived());
	EXPECT_TRUE(ambuce.isAtEntranceDepot());
	EXPECT_EQ(entrDepot, ambuce.getPosition());

	// okay, then enter depot, but it went on fire suddenly,
	EXPECT_NO_FATAL_FAILURE(ptrBase->setFire());
	EXPECT_DEATH(ambuce.enterDepot(), "\\w");

	// a firetruck is arrived, so stop the fire
	EXPECT_NO_FATAL_FAILURE(ptrBase->stopFire());

	// now, you can enter the depot properly
	EXPECT_NO_FATAL_FAILURE(ambuce.enterDepot());
	EXPECT_TRUE(ambuce.isInDepot());
	EXPECT_EQ(locDepot, ambuce.getPosition());
	EXPECT_FALSE(ambuce.isOnWay());
	EXPECT_TRUE(ambuce.isArrived());
}
