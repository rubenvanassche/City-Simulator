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

TEST(testSize, constructs){
	EXPECT_NO_FATAL_FAILURE(Point p(5, 6));
}
TEST(DISABLED_testSize, negativeconstructs){
	EXPECT_NO_FATAL_FAILURE(Point p(-5, 6));
	EXPECT_NO_FATAL_FAILURE(Point p(5, -6));
	EXPECT_NO_FATAL_FAILURE(Point p(-5, -6));
}

TEST(testSize, getters){
	ASSERT_NO_FATAL_FAILURE(Point p(5, 6));
	Point p(5, 6);
	EXPECT_EQ(5, p.getX());
	EXPECT_EQ(6, p.getY());

	ASSERT_NO_FATAL_FAILURE(Point s(3, 6));
	Point s(3, 6);
	EXPECT_EQ(3, s.getX());
	EXPECT_EQ(6, s.getY());
}

TEST(testSize, setters){
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	EXPECT_NO_FATAL_FAILURE(s.set(3, 4));
	EXPECT_EQ(3, s.getX());
	EXPECT_EQ(4, s.getY());

	ASSERT_NO_FATAL_FAILURE(Point t(55, 33));
	Point t(55, 33);
	EXPECT_NO_FATAL_FAILURE(t.set(12, 4));
	EXPECT_EQ(12, t.getX());
	EXPECT_EQ(4, t.getY());
}

TEST(DISABLED_testSize, negativesetters){
	ASSERT_NO_FATAL_FAILURE(Point q(47, 3));
	Point q(47, 3);
	EXPECT_NO_FATAL_FAILURE(q.set(-12, -4));
	EXPECT_EQ(47, q.getX());
	EXPECT_EQ(3, q.getY());
}

TEST(testSize, operators){
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	ASSERT_NO_FATAL_FAILURE(Point p(55, 33));
	Point p(55, 33);

	Point t(60, 39);


	//Point r(0,0);
	//r = p;

	//t.getX();
	//r.getX();

	//EXPECT_EQ(t.getX(), r.getX());
	//EXPECT_EQ(r, p-s);
	//EXPECT_EQ(true, p != s);
	//EXPECT_EQ(false, p == s);

	//Point v(5, 6);

	//EXPECT_EQ(false, v != s);
	//EXPECT_EQ(true, v == s);
}
