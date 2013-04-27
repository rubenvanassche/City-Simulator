/*
 * House_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 9 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "House.h"

class HouseTest : public testing::Test {
protected:
	Point loc;
	Size sizeFixed;
	int health;
	int reducer;

	virtual void SetUp() {
		loc.set(0, 0);
		sizeFixed.set(2, 2);
		health = 2;
		reducer = 1;
	}

	virtual void TearDown() {
		// nothing to clean up
	}
};

TEST_F(HouseTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(House home(loc, health));
}

TEST_F(HouseTest, getters) {
	House home(loc, health);

	EXPECT_EQ(loc, home.getLocation());
	EXPECT_EQ(sizeFixed, home.getSize());
	EXPECT_EQ(health, home.getHealth());
}

TEST_F(HouseTest, fire) {
	House home(loc, health);

	EXPECT_FALSE(home.isBurning());

	EXPECT_DEATH(home.burningDown(), "\\w");	// ooops, house is not on fire
	EXPECT_DEATH(home.stopFire(), "\\w");	// oops, house is not on fire

	EXPECT_FALSE(home.isDead());
	EXPECT_FALSE(home.startSpreadingFire());
	EXPECT_FALSE(home.startRepair());

	EXPECT_DEATH(home.repair(), "\\w");	// oops, house has still it's original health

	EXPECT_FALSE(home.isFireTruckAssigned());
	EXPECT_DEATH(home.assignFireTruck(), "\\w");	// oops, the house is not on fire
	EXPECT_DEATH(home.withdrawFireTruckAssignment(), "\\w");	// oops, there is no firetruck assigned

	// okay, start the fire scenario
	EXPECT_NO_FATAL_FAILURE(home.setFire());
	EXPECT_TRUE(home.isBurning());
	EXPECT_NO_FATAL_FAILURE(home.burningDown());
	EXPECT_EQ(health - reducer, home.getHealth());
	EXPECT_FALSE(home.isDead());
	EXPECT_FALSE(home.startSpreadingFire());	// no, it has lost only 1 health points
	EXPECT_FALSE(home.startRepair());

	EXPECT_DEATH(home.repair(), "\\w");	// oops, house is still on fire

	// let's send a firetruck
	EXPECT_NO_FATAL_FAILURE(home.assignFireTruck());
	EXPECT_TRUE(home.isFireTruckAssigned());

	// extinguish fire, repair and sendback firetruck
	EXPECT_DEATH(home.withdrawFireTruckAssignment(), "\\w");	// oops, house is still on fire

	EXPECT_NO_FATAL_FAILURE(home.stopFire());
	EXPECT_FALSE(home.isBurning());
	EXPECT_TRUE(home.startRepair());
	EXPECT_NO_FATAL_FAILURE(home.repair());
	EXPECT_EQ(health - reducer + 0.5, home.getHealth());
	EXPECT_NO_FATAL_FAILURE(home.withdrawFireTruckAssignment());
	EXPECT_FALSE(home.isFireTruckAssigned());
	EXPECT_FALSE(home.isDead());

	// fire breaks out again
	EXPECT_NO_FATAL_FAILURE(home.setFire());
	EXPECT_TRUE(home.isBurning());
	EXPECT_NO_FATAL_FAILURE(home.burningDown());
	EXPECT_EQ(health - reducer + 0.5 - reducer, home.getHealth());
	EXPECT_FALSE(home.isDead());

	// let it burning down 'till death
	EXPECT_NO_FATAL_FAILURE(home.burningDown());
	EXPECT_TRUE(home.isDead());
	EXPECT_EQ(health - reducer + 0.5 - reducer - reducer, home.getHealth());

	// now, house is not on fire anymore
	EXPECT_FALSE(home.isBurning());
	EXPECT_FALSE(home.startRepair());	// you cannot repair a dead house
	EXPECT_FALSE(home.startSpreadingFire());

	// end of fire scenario
}
