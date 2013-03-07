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

TEST(testSize, constructs) {
	EXPECT_NO_FATAL_FAILURE(Point p(5, 6));
	EXPECT_NO_FATAL_FAILURE(Point p(-5, 6));
	EXPECT_NO_FATAL_FAILURE(Point p(5, -6));
	EXPECT_NO_FATAL_FAILURE(Point p(-5, -6));
}

TEST(testSize, getters) {
	ASSERT_NO_FATAL_FAILURE(Point p(5, 6));
	Point p(5, 6);
	EXPECT_EQ(5, s.getX());
	EXPECT_EQ(6, s.getY());

	ASSERT_NO_FATAL_FAILURE(Point p(3, 6));
	Point p(3, 6);
	EXPECT_EQ(3, s.getX());
	EXPECT_EQ(6, s.getY());
}

TEST(testSize, setters) {
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	EXPECT_NO_FATAL_FAILURE(s.setX(3));
	EXPECT_NO_FATAL_FAILURE(s.setY(4));
	EXPECT_EQ(3, s.getX());
	EXPECT_EQ(4, s.getY());

	ASSERT_NO_FATAL_FAILURE(Point s(55, 33));
	Point s(55, 33);
	EXPECT_NO_FATAL_FAILURE(s.setX(12));
	EXPECT_NO_FATAL_FAILURE(s.setY(4));
	EXPECT_EQ(12, s.getX());
	EXPECT_EQ(4, s.getY());

	ASSERT_NO_FATAL_FAILURE(Point s(47, 3));
	Point s(47, 3);
	EXPECT_NO_FATAL_FAILURE(s.setX(-12));
	EXPECT_NO_FATAL_FAILURE(s.setY(-4));
	EXPECT_EQ(47, s.getX());
	EXPECT_EQ(3, s.getY());
}

TEST(testSize, operators) {
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	ASSERT_NO_FATAL_FAILURE(Point p(55, 33));
	Point p(55, 33);

	Point t(60, 39);
	Point r(50, 27);

	EXPECT_EQ(t, s+p);
	EXPECT_EQ(r, p-s);
	EXPECT_EQ(true, p != s);
	EXPECT_EQ(false, p == s);

	Point v(5, 6);

	EXPECT_EQ(false, v != s);
	EXPECT_EQ(true, v == s);
}