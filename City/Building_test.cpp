/*
 * Building_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 9 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "Building.h"
#include "Point.h"
#include "Size.h"

TEST(Building, constructs) {
	EXPECT_NO_FATAL_FAILURE(Building building(Point(0, 0), Size(2), 0));
	EXPECT_NO_FATAL_FAILURE(Building building(Point(0, 0), Size(4), 5));

//	EXPECT_DEATH(Building magic(Point(-3, 2), Size(1), 0), "\\w");
//	EXPECT_DEATH(Building magic(Point(1, 1), Size(0), 5), "\\w");
//	EXPECT_DEATH(Building magic(Point(1, 1), Size(1), -1), "\\w");

	Building app(Point(0, 0), Size(5), 100);
	EXPECT_NO_FATAL_FAILURE(Building copy = app);
}

TEST(Building, getters) {
	Building app(Point(0, 0), Size(5), 100);

	EXPECT_EQ(Point(0, 0), app.getLocation());
	EXPECT_EQ(Size(5), app.getSize());
	EXPECT_EQ(100, app.getHealth());
}

TEST(Building, fire) {
	Building house(Point(0, 0), Size(2), 2);

	EXPECT_FALSE(house.isBurning());
	EXPECT_FALSE(house.isDead());
	EXPECT_EQ(2, house.getHealth());

	EXPECT_NO_FATAL_FAILURE(house.setFire());
	EXPECT_TRUE(house.isBurning());
	EXPECT_NO_FATAL_FAILURE(house.burningDown());
	EXPECT_EQ(1, house.getHealth());
	EXPECT_FALSE(house.isDead());

	EXPECT_NO_FATAL_FAILURE(house.stopFire());
	EXPECT_FALSE(house.isBurning());
	EXPECT_NO_FATAL_FAILURE(house.repair());
	EXPECT_EQ(1.5, house.getHealth());
	EXPECT_FALSE(house.isDead());

	//EXPECT_DEATH(house.burningDown(), "\\w");

	EXPECT_NO_FATAL_FAILURE(house.setFire());
	EXPECT_TRUE(house.isBurning());
	EXPECT_NO_FATAL_FAILURE(house.burningDown(2));
	EXPECT_EQ(-0.5, house.getHealth());
	EXPECT_TRUE(house.isDead());
}
