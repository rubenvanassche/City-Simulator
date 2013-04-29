/*
 * Shop_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Shop.h"
#include "gtest/gtest.h"

class ShopTest : public testing::Test {
protected:
	Point loc;
	Size size;
	int health;
	int reducer;
	int secLevel;

	virtual void SetUp() {
		loc.set(0, 0);
		size.set(4, 4);
		health = 5;
		reducer = 2;
		secLevel = 2;
	}

	virtual void TearDown() {
		// nothing to clean up
	}

};

TEST_F(ShopTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Shop appleStore(loc, size, health, secLevel));
}

TEST_F(ShopTest, getters) {
	Shop appleStore(loc, size, health, secLevel);

	EXPECT_EQ(loc, appleStore.getLocation());
	EXPECT_EQ(size, appleStore.getSize());
	EXPECT_EQ(health, appleStore.getHealth());
	EXPECT_EQ(secLevel, appleStore.getSecurity());
}

TEST_F(ShopTest, fire) {
	Shop appleStore(loc, size, health, secLevel);

	EXPECT_FALSE(appleStore.isBurning());

	EXPECT_DEATH(appleStore.burningDown(), "");	// oops, this shop is not on fire (damn!)
	EXPECT_DEATH(appleStore.stopFire(), "");	// oops, no fire in the shop!
	EXPECT_FALSE(appleStore.isDead());	// Bill Gates: "damn..", Steve Jobs: "oh dear..", Linus Torvalds: "What?"
	EXPECT_FALSE(appleStore.startSpreadingFire());
	EXPECT_FALSE(appleStore.startRepair());

	EXPECT_DEATH(appleStore.repair(), "");	// oops, shop has still it's original health

	EXPECT_FALSE(appleStore.isFireTruckAssigned());
	EXPECT_DEATH(appleStore.assignFireTruck(), "");	// oops, shop is not on fire
	EXPECT_DEATH(appleStore.withdrawFireTruckAssignment(), "");	// oops, no firetruck assigned

	// okay, start the fire scenario
	// Bill Gates: "HUEHUEHUE", Steve Jobs: "Oh noooo...", Linus Torvalds: "What?"
	EXPECT_NO_FATAL_FAILURE(appleStore.setFire());
	EXPECT_TRUE(appleStore.isBurning());
	EXPECT_NO_FATAL_FAILURE(appleStore.burningDown());
	EXPECT_EQ(health - reducer, appleStore.getHealth());
	EXPECT_FALSE(appleStore.isDead());
	EXPECT_FALSE(appleStore.startSpreadingFire());	// no, it has lost "only" 2 health points
	EXPECT_FALSE(appleStore.startRepair());

	// *Steve Jobs calling a firetruck with his EmergencyCallApp on his ridiculously big iPad version XL.0
	EXPECT_NO_FATAL_FAILURE(appleStore.assignFireTruck());
	EXPECT_TRUE(appleStore.isFireTruckAssigned());

	// extinguish fire, repair and sendback firetruck
	EXPECT_DEATH(appleStore.withdrawFireTruckAssignment(), "");	// oops, shop is still on fire

	EXPECT_NO_FATAL_FAILURE(appleStore.stopFire());
	EXPECT_FALSE(appleStore.isBurning());
	EXPECT_TRUE(appleStore.startRepair());
	EXPECT_NO_FATAL_FAILURE(appleStore.repair());
	EXPECT_EQ(health - reducer + 0.5, appleStore.getHealth());
	EXPECT_NO_FATAL_FAILURE(appleStore.withdrawFireTruckAssignment());
	EXPECT_FALSE(appleStore.isFireTruckAssigned());
	EXPECT_FALSE(appleStore.isDead());

	// fire breaks out again
	EXPECT_NO_FATAL_FAILURE(appleStore.setFire());
	EXPECT_TRUE(appleStore.isBurning());
	EXPECT_NO_FATAL_FAILURE(appleStore.burningDown());
	EXPECT_EQ(health - reducer + 0.5 - reducer, appleStore.getHealth());
	EXPECT_FALSE(appleStore.isDead());

	// let the shop burning down 'till death
	EXPECT_NO_FATAL_FAILURE(appleStore.burningDown());
	EXPECT_EQ(health - reducer + 0.5 - reducer - reducer, appleStore.getHealth());

	EXPECT_TRUE(appleStore.isDead());	// Bill Gates: "AAAAWW YEAH!", Steve Jobs: "Oh god..  Why?", Linus Torvalds: "What?"

	// now shop is not on fire anymore
	EXPECT_FALSE(appleStore.isBurning());
	EXPECT_FALSE(appleStore.startRepair());
	EXPECT_FALSE(appleStore.startSpreadingFire());
}

// let's do something more fun with appleStore!
TEST_F(ShopTest, robbing) {
	Shop appleStore(loc, size, health, secLevel);

	EXPECT_FALSE(appleStore.isRobbing());

	EXPECT_DEATH(appleStore.rob(), "");	// no burglar in here
	EXPECT_DEATH(appleStore.stopRobbing(), "");	// no burglar in here
	EXPECT_FALSE(appleStore.isEmpty());

	// okay, now a burglar enters the applestore
	EXPECT_NO_FATAL_FAILURE(appleStore.startRobbing());
	EXPECT_TRUE(appleStore.isRobbing());
	EXPECT_NO_FATAL_FAILURE(appleStore.rob());
	EXPECT_EQ(secLevel - 1, appleStore.getSecurity());
	EXPECT_FALSE(appleStore.isEmpty());

	// a policecar arrived, get out of there!
	EXPECT_NO_FATAL_FAILURE(appleStore.stopRobbing());
	EXPECT_FALSE(appleStore.isRobbing());

	// policecar is gone now, let's start rob again
	EXPECT_NO_FATAL_FAILURE(appleStore.startRobbing());
	EXPECT_TRUE(appleStore.isRobbing());
	EXPECT_NO_FATAL_FAILURE(appleStore.rob());
	EXPECT_TRUE(appleStore.isEmpty());

	EXPECT_FALSE(appleStore.isRobbing());	// there are no stuffs in the shop anymore
	EXPECT_DEATH(appleStore.rob(), ""); // nothing to rob
}
