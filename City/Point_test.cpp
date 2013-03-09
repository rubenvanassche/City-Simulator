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
#include <sstream>

TEST(testPoint, validConstructs){
	EXPECT_NO_FATAL_FAILURE(Point p(5, 6));
}

TEST(testPoint, invalidConstructs) {
	EXPECT_DEATH(Point p(-2), "\\w");
	EXPECT_DEATH(Point p(-5, 3), "\\w");
	EXPECT_DEATH(Point p(5, -3), "\\w");
	EXPECT_DEATH(Point p(-10, -8), "\\w");
}

TEST(testPoint, getters){
	ASSERT_NO_FATAL_FAILURE(Point p(5, 6));
	Point p(5, 6);
	EXPECT_EQ(5, p.getX());
	EXPECT_EQ(6, p.getY());

	ASSERT_NO_FATAL_FAILURE(Point s(3, 6));
	Point s(3, 6);
	EXPECT_EQ(3, s.getX());
	EXPECT_EQ(6, s.getY());
}

TEST(testPoint, validSetters){
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	EXPECT_NO_FATAL_FAILURE(s.set());
	EXPECT_EQ(0, s.getX());
	EXPECT_EQ(0, s.getY());
	EXPECT_NO_FATAL_FAILURE(s.set(10));
	EXPECT_EQ(10, s.getX());
	EXPECT_EQ(0, s.getY());
	EXPECT_NO_FATAL_FAILURE(s.set(1, 4));
	EXPECT_EQ(1, s.getX());
	EXPECT_EQ(4, s.getY());
}

TEST(testPoint, invalidSetters) {
	ASSERT_NO_FATAL_FAILURE(Point p(47, 3));
	Point p(47, 3);
	EXPECT_DEATH(p.set(-1), "\\w");
	EXPECT_DEATH(p.set(-5, -2), "\\w");
}

TEST(testPoint, operators){
	ASSERT_NO_FATAL_FAILURE(Point s(5, 6));
	Point s(5, 6);
	ASSERT_NO_FATAL_FAILURE(Point p(55, 33));
	Point p(55, 33);
	ASSERT_NO_FATAL_FAILURE(Point t(60, 39));
	Point t(60, 39);

	ASSERT_NO_FATAL_FAILURE(Point r);
	Point r;

	EXPECT_NO_FATAL_FAILURE(r = t);	// copy by assignment
	r = t;
	EXPECT_EQ(t.getX(), r.getX());
	EXPECT_EQ(t.getY(), r.getY());
	EXPECT_TRUE(t == r);


	EXPECT_NO_FATAL_FAILURE(Point q = t);	// copy by initialization
	Point q = r;
	EXPECT_EQ(t.getX(), q.getX());
	EXPECT_EQ(t.getY(), q.getY());
	EXPECT_TRUE(t == q);

	EXPECT_NO_FATAL_FAILURE(t - s);
	Point substr = t - s;
	EXPECT_TRUE(substr == p);

	EXPECT_NO_FATAL_FAILURE(p + s);
	Point add = p + s;
	EXPECT_TRUE(add == t);

	EXPECT_TRUE(t != s);

	std::stringstream ss;
	ss << s;
	EXPECT_EQ("(5, 6)", ss.str());
}
