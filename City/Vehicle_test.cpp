/*
 * Vehicle_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 3 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "Vehicle.h"
#include "Point.h"

TEST(Vehicles, constructs) {
	EXPECT_NO_FATAL_FAILURE(Vehicle car("car", Point(0, 0)));
	EXPECT_NO_FATAL_FAILURE(Vehicle car("car", Point(0, 0)));

	//EXPECT_DEATH(Vehicle magic("magic", Point(-5, 2), Point(-3, 2)), "\\w");

	Vehicle car("car", Point(0, 0));
	EXPECT_NO_FATAL_FAILURE(Vehicle copy = car);
}

TEST(Vehicles, getters_setters) {
	Vehicle car("car", Point(1, 2));

	EXPECT_EQ(Point(1, 2), car.getPosition());
	EXPECT_EQ(Point(1, 2), car.getDestination());
	EXPECT_EQ("car", car.getName());

	EXPECT_NO_FATAL_FAILURE(car.setDestination(Point(0, 0)));
	EXPECT_EQ(Point(0, 0), car.getDestination());

	//EXPECT_DEATH(car.setDestination(Point(-5, 0)), "\\w");
}

TEST(Vehicles, driving) {
	Vehicle car("car", Point(1, 1));

	EXPECT_TRUE(car.isArrived());
	EXPECT_FALSE(car.isOnWay());

	EXPECT_NO_FATAL_FAILURE(car.goLeft());
	EXPECT_FALSE(car.isArrived());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_EQ(Point(0, 1), car.getPosition());
	//EXPECT_DEATH(car.goLeft(), "\\w");

	EXPECT_NO_FATAL_FAILURE(car.goDown());
	EXPECT_FALSE(car.isArrived());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_EQ(Point(0, 0), car.getPosition());
	//EXPECT_DEATH(car.goDown(), "\\w");

	EXPECT_NO_FATAL_FAILURE(car.goRight());
	EXPECT_FALSE(car.isArrived());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_EQ(Point(1, 0), car.getPosition());

	EXPECT_NO_FATAL_FAILURE(car.goUp());
	EXPECT_TRUE(car.isArrived());
	EXPECT_FALSE(car.isOnWay());
	EXPECT_EQ(Point(1, 1), car.getPosition());
}
