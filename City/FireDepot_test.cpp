/*
 * FireDepot_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Saturday 27 April 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireDepot.h"

class FireDepotTest : public testing::Test {
protected:
	Point loc;
	Point entr;
	Size size;
	std::string name;
	int health;
	int reducer;
	Vehicle* ptrCar0;
	std::string carName0;
	Vehicle* ptrCar1;
	std::string carName1;

	virtual void SetUp() {
		loc.set(2, 2);
		entr.set(0, 0);
		size.set(4, 4);
		name = "an ordinary depot";
		health = 5;
		reducer = 2;

		carName0 = "BMW 007";
		carName1 = "Ferrari XVZF0125467982";

		ptrCar0 = new Vehicle(carName0, loc);
		ptrCar1 = new Vehicle(carName1, loc);
	}

	virtual void TearDown() {
		delete ptrCar0;
		delete ptrCar1;
	}

};

TEST_F(FireDepotTest, construct) {
	EXPECT_NO_FATAL_FAILURE(FireDepot depot(loc, entr, name, health));
}

TEST_F(FireDepotTest, getters) {
	FireDepot depot(loc, entr, name, health);

	EXPECT_EQ(loc, depot.getLocation());
	EXPECT_EQ(size, depot.getSize());
	EXPECT_EQ(health, depot.getHealth());
	EXPECT_EQ(entr, depot.getEntrance());
	EXPECT_EQ(name, depot.getName());
	EXPECT_EQ(0, depot.getNrVehicles());
	EXPECT_EQ(0, depot.getAvailableVehicles());
}

TEST_F(FireDepotTest, fire) {
	FireDepot depot(loc, entr, name, health);

	EXPECT_FALSE(depot.isBurning());

	EXPECT_DEATH(depot.burningDown(), "");	// ooops, depot is not on fire
	EXPECT_DEATH(depot.stopFire(), "");	// oops, depot is not on fire

	EXPECT_FALSE(depot.isDead());
	EXPECT_FALSE(depot.startSpreadingFire());
	EXPECT_FALSE(depot.startRepair());

	EXPECT_DEATH(depot.repair(), "");	// oops, Depot has still it's original health

	EXPECT_FALSE(depot.isFireTruckAssigned());
	EXPECT_DEATH(depot.assignFireTruck(), "");	// oops, the Depot is not on fire
	EXPECT_DEATH(depot.withdrawFireTruckAssignment(), "");	// oops, there is no firetruck assigned

	// okay, start the fire scenario
	EXPECT_NO_FATAL_FAILURE(depot.setFire());
	EXPECT_TRUE(depot.isBurning());
	EXPECT_NO_FATAL_FAILURE(depot.burningDown());
	EXPECT_EQ(health - reducer, depot.getHealth());
	EXPECT_FALSE(depot.isDead());
	EXPECT_FALSE(depot.startSpreadingFire());	// No, it has lost "only" 2 health points
	EXPECT_FALSE(depot.startRepair());

	EXPECT_DEATH(depot.repair(), "");	// oops, Depot is still on fire

	// let's send a firetruck
	EXPECT_NO_FATAL_FAILURE(depot.assignFireTruck());
	EXPECT_TRUE(depot.isFireTruckAssigned());

	// extinguish fire, repair and sendback firetruck
	EXPECT_DEATH(depot.withdrawFireTruckAssignment(), "");	// oops, Depot is still on fire

	EXPECT_NO_FATAL_FAILURE(depot.stopFire());
	EXPECT_FALSE(depot.isBurning());
	EXPECT_TRUE(depot.startRepair());
	EXPECT_NO_FATAL_FAILURE(depot.repair());
	EXPECT_EQ(health - reducer + 0.5, depot.getHealth());
	EXPECT_NO_FATAL_FAILURE(depot.withdrawFireTruckAssignment());
	EXPECT_FALSE(depot.isFireTruckAssigned());
	EXPECT_FALSE(depot.isDead());

	// fire breaks out again
	EXPECT_NO_FATAL_FAILURE(depot.setFire());
	EXPECT_TRUE(depot.isBurning());
	EXPECT_NO_FATAL_FAILURE(depot.burningDown());
	EXPECT_EQ(health - reducer + 0.5 - reducer, depot.getHealth());
	EXPECT_FALSE(depot.isDead());
	EXPECT_TRUE(depot.startSpreadingFire());

	// let them burning down 'till death
	EXPECT_NO_FATAL_FAILURE(depot.burningDown());
	EXPECT_TRUE(depot.isDead());
	EXPECT_EQ(health - reducer + 0.5 - reducer - reducer, depot.getHealth());

	// now, Depot is not on fire anymore
	EXPECT_FALSE(depot.isBurning());
	EXPECT_FALSE(depot.startRepair());	// you cannot repair a dead Depot
	EXPECT_FALSE(depot.startSpreadingFire());
}

TEST_F(FireDepotTest, vehicles) {
	FireDepot depot(loc, entr, name, health);

	EXPECT_NO_FATAL_FAILURE(depot.addVehicle(ptrCar0));
	EXPECT_EQ(1, depot.getAvailableVehicles());
	EXPECT_EQ(1, depot.getNrVehicles());

	EXPECT_NO_FATAL_FAILURE(depot.addVehicle(ptrCar1));
	EXPECT_EQ(2, depot.getAvailableVehicles());
	EXPECT_EQ(2, depot.getNrVehicles());

	EXPECT_NO_FATAL_FAILURE(ptrCar0->goUp());
	EXPECT_EQ(1, depot.getAvailableVehicles());
	EXPECT_EQ(2, depot.getNrVehicles());

	EXPECT_NO_FATAL_FAILURE(ptrCar1->goUp());
	EXPECT_EQ(0, depot.getAvailableVehicles());
	EXPECT_EQ(2, depot.getNrVehicles());

	EXPECT_NO_FATAL_FAILURE(ptrCar0->goDown());
	EXPECT_EQ(1, depot.getAvailableVehicles());
	EXPECT_EQ(2, depot.getNrVehicles());

	EXPECT_NO_FATAL_FAILURE(ptrCar1->goDown());
	EXPECT_EQ(2, depot.getAvailableVehicles());
	EXPECT_EQ(2, depot.getNrVehicles());
}
