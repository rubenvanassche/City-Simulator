/*
 * Building_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Saturday 27 April 2013
 * 
 */

#include "gtest/gtest.h"
#include "Building.h"

class BuildingTest : public testing::Test {
protected:
	Point loc;
	Size size;
	int health;
	int reducer;

	virtual void SetUp() {
		loc.set(0, 0);
		size.set(2, 2);
		health = 10;
		reducer = 5;
	}

	virtual void TearDown() {
		// nothing to clean up
	}
};

TEST_F(BuildingTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(Building build(loc, size, health, reducer));
}

TEST_F(BuildingTest, getters) {
	Building build(loc, size, health, reducer);

	EXPECT_EQ(loc, build.getLocation());
	EXPECT_EQ(size, build.getSize());
	EXPECT_EQ(health, build.getHealth());
}

TEST_F(BuildingTest, fire) {
	Building build(loc, size, health, reducer);

	EXPECT_FALSE(build.isBurning());

	EXPECT_DEATH(build.burningDown(), "");	// ooops, building is not on fire
	EXPECT_DEATH(build.stopFire(), "");	// oops, building is not on fire

	EXPECT_FALSE(build.isDead());
	EXPECT_FALSE(build.startSpreadingFire());
	EXPECT_FALSE(build.startRepair());

	EXPECT_DEATH(build.repair(), "");	// oops, building has still it's original health

	EXPECT_FALSE(build.isFireTruckAssigned());
	EXPECT_DEATH(build.assignFireTruck(), "");	// oops, the building is not on fire
	EXPECT_DEATH(build.withdrawFireTruckAssignment(), "");	// oops, there is no firetruck assigned

	// okay, start the fire scenario
	EXPECT_NO_FATAL_FAILURE(build.setFire());
	EXPECT_TRUE(build.isBurning());
	EXPECT_NO_FATAL_FAILURE(build.burningDown());
	EXPECT_EQ(health - reducer, build.getHealth());
	EXPECT_FALSE(build.isDead());
	EXPECT_TRUE(build.startSpreadingFire());	// yes, it has lost over more than 3 health points
	EXPECT_FALSE(build.startRepair());

	EXPECT_DEATH(build.repair(), "");	// oops, building is still on fire

	// let's send a firetruck
	EXPECT_NO_FATAL_FAILURE(build.assignFireTruck());
	EXPECT_TRUE(build.isFireTruckAssigned());

	// extinguish fire, repair and sendback firetruck
	EXPECT_DEATH(build.withdrawFireTruckAssignment(), "");	// oops, building is still on fire

	EXPECT_NO_FATAL_FAILURE(build.stopFire());
	EXPECT_FALSE(build.isBurning());
	EXPECT_TRUE(build.startRepair());
	EXPECT_NO_FATAL_FAILURE(build.repair());
	EXPECT_EQ(health - reducer + 0.5, build.getHealth());
	EXPECT_NO_FATAL_FAILURE(build.withdrawFireTruckAssignment());
	EXPECT_FALSE(build.isFireTruckAssigned());
	EXPECT_FALSE(build.isDead());

	// fire breaks out again
	EXPECT_NO_FATAL_FAILURE(build.setFire());
	EXPECT_TRUE(build.isBurning());
	EXPECT_NO_FATAL_FAILURE(build.burningDown());
	EXPECT_EQ(health - reducer + 0.5 - reducer, build.getHealth());
	EXPECT_FALSE(build.isDead());

	// let them burning down 'till death
	EXPECT_NO_FATAL_FAILURE(build.burningDown());
	EXPECT_TRUE(build.isDead());
	EXPECT_EQ(health - reducer + 0.5 - reducer - reducer, build.getHealth());

	// now, building is not on fire anymore
	EXPECT_FALSE(build.isBurning());
	EXPECT_FALSE(build.startRepair());	// you cannot repair a dead building
	EXPECT_FALSE(build.startSpreadingFire());
}
