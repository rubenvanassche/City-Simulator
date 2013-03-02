/*
 * Point_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 2 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "Point.h"

TEST(Points, ValidPoints) {
	EXPECT_NO_FATAL_FAILURE(Point p);
	EXPECT_NO_FATAL_FAILURE(Point p(3));
	EXPECT_NO_FATAL_FAILURE(Point r(3, 5));
}
