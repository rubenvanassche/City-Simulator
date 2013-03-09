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
#include "Point.h"

TEST(testHouse, validConstructs) {
	ASSERT_NO_FATAL_FAILURE(Point loc(5, 1));
	Point loc(5, 1);
	EXPECT_NO_FATAL_FAILURE(House house(loc, 10));
	EXPECT_NO_FATAL_FAILURE(House house(loc, 0));
}

TEST(testHouse, invalidConstructs) {
	ASSERT_NO_FATAL_FAILURE(Point loc(0, 1));
	Point loc(0, 1);
	EXPECT_DEATH(House house(loc, -5), "\\w");
}

TEST(testHouse, copying) {
	ASSERT_NO_FATAL_FAILURE(Point loc(5, 1));
	Point loc(5, 1);
	ASSERT_NO_FATAL_FAILURE(House house(loc, 11));
	House house(loc, 11);
	EXPECT_NO_FATAL_FAILURE(House newHouse = house);
	House newHouse = house;
	EXPECT_TRUE(*house.getLocation() == *newHouse.getLocation());
	EXPECT_TRUE(*house.getSize() == *newHouse.getSize());
	EXPECT_TRUE(*house.getHealth() == *newHouse.getHealth());

	ASSERT_NO_FATAL_FAILURE(Point aloc(0, 3));
	Point aloc(0, 3);
	ASSERT_NO_FATAL_FAILURE(House cpHouse(aloc, 3));
	House cpHouse(aloc, 3);
	EXPECT_NO_FATAL_FAILURE(cpHouse = house);
	EXPECT_TRUE(*house.getLocation() == *cpHouse.getLocation());
	EXPECT_TRUE(*house.getSize() == *cpHouse.getSize());
	EXPECT_TRUE(*house.getHealth() == *cpHouse.getHealth());
}
