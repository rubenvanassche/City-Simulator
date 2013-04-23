/*
 * PoliceDepot_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "PoliceDepot.h"
#include "gtest/gtest.h"

TEST(PoliceDepot, constructs) {
	EXPECT_NO_FATAL_FAILURE(PoliceDepot depot(Point(0, 0), Point(0, 0), Size(4), "depot", 10));
	EXPECT_NO_FATAL_FAILURE(PoliceDepot depot(Point(0, 0), Point(2, 3), Size(2), "depot", 5));

	//EXPECT_DEATH(PoliceDepot magic(Point(-3, 2), Point(0, 0), Size(5, 1), "magic", 3), "\\w");
	//EXPECT_DEATH(PoliceDepot magic(Point(3, 2), Point(0, 0), Size(0), "magic", 3), "\\w");
	//EXPECT_DEATH(PoliceDepot magic(Point(3, 2), Point(0, 0), Size(5, 1), "magic", -3), "\\w");

	PoliceDepot depot(Point(0, 0), Point(0, 0), Size(4), "depot", 10);
	EXPECT_NO_FATAL_FAILURE(PoliceDepot copy = depot);
}

TEST(PoliceDepot, vehicles) {
	PoliceDepot kazern(Point(0, 0), Point(1, 1), Size(2), "kazern", 5);
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

