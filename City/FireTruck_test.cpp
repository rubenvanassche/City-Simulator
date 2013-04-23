/*
 * FireTruck_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireTruck.h"
#include "FireDepot.h"
#include "House.h"

TEST(FireTruck, constructs) {
	FireDepot base(Point(0, 0), Point(1, 1), "firedepot", 10);

	EXPECT_NO_FATAL_FAILURE(FireTruck truck("truck", &base));
}

TEST(FireTruck, sending) {
	FireDepot base(Point(0, 0), Point(1, 1), "firedepot", 10);
	FireTruck truck("truck", &base);

	House houseOnFire(Point(3, 3), 3);

	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	//EXPECT_DEATH(truck.enterDepot(), "\\w");

	EXPECT_NO_FATAL_FAILURE(truck.send(&houseOnFire, Point(2, 2)));
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_EQ(Point(1, 1), truck.getPosition());
	EXPECT_TRUE(truck.isOnWay());

	truck.goRight();
	truck.goUp();

	EXPECT_TRUE(truck.isArrived());
	EXPECT_NO_FATAL_FAILURE(truck.sendBack());
	EXPECT_EQ(Point(1, 1), truck.getDestination());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isInDepot());
	//EXPECT_DEATH(truck.enterDepot(), "\\w");

	truck.goLeft();
	truck.goDown();
	EXPECT_TRUE(truck.isArrived());
	EXPECT_EQ(Point(1, 1), truck.getDestination());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_NO_FATAL_FAILURE(truck.enterDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isInDepot());
}
