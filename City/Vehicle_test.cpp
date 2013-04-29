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

class VehicleTest : public testing::Test {
protected:

	std::string name;
	Point pos;
	Point destination;

	virtual void SetUp() {
		name = "an ordinary car";
		pos.set(0, 0);
		destination.set(1, 1);
	}

	virtual void TearDown() {

	}

};

TEST_F(VehicleTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Vehicle car(name, pos));
}

TEST_F(VehicleTest, getters_setters) {
	Vehicle car(name, pos);

	EXPECT_EQ(name, car.getName());
	EXPECT_EQ(pos, car.getPosition());
	EXPECT_EQ(pos, car.getDestination());

	EXPECT_NO_FATAL_FAILURE(car.setPosition(destination));
	EXPECT_EQ(destination, car.getPosition());

	EXPECT_NO_FATAL_FAILURE(car.setDestination(destination));
	EXPECT_EQ(destination, car.getDestination());
}


TEST_F(VehicleTest, driving) {
	Vehicle car(name, pos);

	EXPECT_FALSE(car.isOnWay());
	EXPECT_TRUE(car.isArrived());

	EXPECT_NO_FATAL_FAILURE(car.setDestination(destination));
	EXPECT_TRUE(car.isOnWay());
	EXPECT_FALSE(car.isArrived());

	EXPECT_DEATH(car.goLeft(), "");	// oops, just got negative coordinates

	EXPECT_NO_FATAL_FAILURE(car.goRight());
	EXPECT_EQ(Point(pos.getX() + 1, pos.getY()), car.getPosition());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_FALSE(car.isArrived());

	EXPECT_DEATH(car.goDown(), "");	// oops, just got negative coordinates

	EXPECT_NO_FATAL_FAILURE(car.goUp());
	EXPECT_EQ(Point(pos.getX() + 1, pos.getY() + 1), car.getPosition());
	EXPECT_FALSE(car.isOnWay());
	EXPECT_TRUE(car.isArrived());

	// then go back to the original point
	EXPECT_NO_FATAL_FAILURE(car.setDestination(pos));
	EXPECT_EQ(destination, car.getPosition());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_FALSE(car.isArrived());

	EXPECT_NO_FATAL_FAILURE(car.goLeft());
	EXPECT_EQ(Point(pos.getX(), pos.getY() + 1), car.getPosition());
	EXPECT_TRUE(car.isOnWay());
	EXPECT_FALSE(car.isArrived());

	EXPECT_DEATH(car.goLeft(), "");	// oops, just got negative coordinates!

	EXPECT_NO_FATAL_FAILURE(car.goDown());
	EXPECT_EQ(pos, car.getPosition());
	EXPECT_FALSE(car.isOnWay());
	EXPECT_TRUE(car.isArrived());

	EXPECT_DEATH(car.goDown(), "");	// ooops, just got negative coordinates!

	// end of driving
}
