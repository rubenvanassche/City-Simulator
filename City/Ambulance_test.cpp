/*
 * Ambulance_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "gtest/gtest.h"
#include "Ambulance.h"
#include "Hospital.h"
#include "House.h"

TEST(Ambulance, constructs) {
	Hospital base(Point(0, 0), Point(1, 1), Size(10), "hospital", 10);

	EXPECT_NO_FATAL_FAILURE(Ambulance truck("truck", &base));
}

TEST(Ambulance, sending) {
	Hospital base(Point(0, 0), Point(1, 1), Size(10, 5), "Hospital", 10);
	Ambulance truck("ambuce", &base);

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
