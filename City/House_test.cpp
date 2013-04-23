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

TEST(House, constructs) {
	EXPECT_NO_FATAL_FAILURE(House house(Point(0, 0), 2));
	//EXPECT_DEATH(House magic(Point(-5, 3), 2), "\\w");
	//EXPECT_DEATH(House magic(Point(5, 3), -2), "\\w");

	House house(Point(5, 3), 10);
	EXPECT_NO_FATAL_FAILURE(House copy = house);
}

TEST(House, getters) {
	House app(Point(0, 0), 100);

	EXPECT_EQ(Point(0, 0), app.getLocation());
	EXPECT_EQ(Size(2), app.getSize());
	EXPECT_EQ(100, app.getHealth());
}

TEST(House, fire) {
	House house(Point(0, 0), 2);

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
