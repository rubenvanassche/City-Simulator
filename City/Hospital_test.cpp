/*
 * Hospital_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */


#include "Hospital.h"
#include "gtest/gtest.h"
#include "Point.h"
#include "Size.h"

TEST(Hospital, constructs) {
	EXPECT_NO_FATAL_FAILURE(Hospital depot(Point(0, 0), Point(0, 0), Size(4), "depot", 10));
	EXPECT_NO_FATAL_FAILURE(Hospital depot(Point(0, 0), Point(2, 3), Size(2), "depot", 5));

	//EXPECT_DEATH(Hospital magic(Point(-3, 2), Point(0, 0), Size(5, 1), "magic", 3), "\\w");
	//EXPECT_DEATH(Hospital magic(Point(3, 2), Point(0, 0), Size(0), "magic", 3), "\\w");
	//EXPECT_DEATH(Hospital magic(Point(3, 2), Point(0, 0), Size(5, 1), "magic", -3), "\\w");

	Hospital depot(Point(0, 0), Point(0, 0), Size(4), "depot", 10);
	EXPECT_NO_FATAL_FAILURE(Hospital copy = depot);
}

TEST(Hospital, vehicles) {
	Hospital kazern(Point(0, 0), Point(1, 1), Size(2), "kazern", 5);
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
