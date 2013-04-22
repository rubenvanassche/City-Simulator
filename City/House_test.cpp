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


TEST(House, constructs) {
	EXPECT_NO_FATAL_FAILURE(House house(Point(0, 0), 2));
	//EXPECT_DEATH(House magic(Point(-5, 3), 2), "\\w");
	//EXPECT_DEATH(House magic(Point(5, 3), -2), "\\w");

	House house(Point(5, 3), 10);
	EXPECT_NO_FATAL_FAILURE(House copy = house);
}
