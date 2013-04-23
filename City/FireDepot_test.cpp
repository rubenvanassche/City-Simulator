/*
 * FireDepot_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireDepot.h"

TEST(FireDepot, constructs) {
	EXPECT_NO_FATAL_FAILURE(FireDepot depot(Point(0, 0), Point(0, 0), "depot", 10));
	EXPECT_NO_FATAL_FAILURE(FireDepot depot(Point(0, 0), Point(2, 3), "depot", 5));

	//EXPECT_DEATH(FireDepot magic(Point(-3, 2), Point(0, 0), Size(5, 1), "magic", 3), "\\w");
	//EXPECT_DEATH(FireDepot magic(Point(3, 2), Point(0, 0), Size(0), "magic", 3), "\\w");
	//EXPECT_DEATH(FireDepot magic(Point(3, 2), Point(0, 0), Size(5, 1), "magic", -3), "\\w");

	FireDepot depot(Point(0, 0), Point(0, 0), "depot", 10);
	EXPECT_NO_FATAL_FAILURE(FireDepot copy = depot);
}

TEST(FireDepot, vehicles) {
	FireDepot kazern(Point(0, 0), Point(1, 1), "kazern", 5);
	Vehicle car0("car0", Point(0, 0));
	Vehicle car1("car1", Point(1, 1));

	EXPECT_NO_FATAL_FAILURE(kazern.addVehicle(&car0));
	EXPECT_NO_FATAL_FAILURE(kazern.addVehicle(&car1));
	EXPECT_EQ(2, kazern.getNrVehicles());
	EXPECT_EQ(1, kazern.getAvailableVehicles());

	car1.goDown();
	car1.goLeft();
	EXPECT_EQ(2, kazern.getAvailableVehicles());
}
