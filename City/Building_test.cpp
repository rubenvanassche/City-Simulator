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

TEST(testBuilding, constructs) {
	ASSERT_NO_FATAL_FAILURE(Point loc(5, 1));
	Point loc(5, 1);
	EXPECT_NO_FATAL_FAILURE(Building house(loc));

	ASSERT_NO_FATAL_FAILURE(Size s(2));
	Size s(2);
	EXPECT_NO_FATAL_FAILURE(Building house(loc, s));

	ASSERT_NO_FATAL_FAILURE(Size size(4, 3));
	Size size(4, 3);
	EXPECT_NO_FATAL_FAILURE(Building depot(loc, size));
}

TEST(testBuilding, copying) {
	ASSERT_NO_FATAL_FAILURE(Point loc(5, 1));
	Point loc(5, 1);
	ASSERT_NO_FATAL_FAILURE(Building house(loc));
	Building house(loc);
	EXPECT_NO_FATAL_FAILURE(Building newHouse = house);
	Building newHouse = house;
	EXPECT_TRUE(*house.getLocation() == *newHouse.getLocation());
	EXPECT_TRUE(*house.getSize() == *newHouse.getSize());

	ASSERT_NO_FATAL_FAILURE(Point aloc(0, 3));
	Point aloc(0, 3);
	ASSERT_NO_FATAL_FAILURE(Building cpHouse(aloc));
	Building cpHouse(aloc);
	EXPECT_NO_FATAL_FAILURE(cpHouse = house);
	EXPECT_TRUE(*house.getLocation() == *cpHouse.getLocation());
	EXPECT_TRUE(*house.getSize() == *cpHouse.getSize());
}
