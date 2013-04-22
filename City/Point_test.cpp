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

TEST(Point, construct){
	EXPECT_NO_FATAL_FAILURE(Point Default);
	EXPECT_NO_FATAL_FAILURE(Point zero(0, 0));
	EXPECT_NO_FATAL_FAILURE(Point positive(1, 3));

	//EXPECT_DEATH(Point negative(-1, -3), "\\w");
	//EXPECT_DEATH(Point xNegative(-1, 3), "\\w");
	//EXPECT_DEATH(Point yNegative(1, -3), "\\w");

	Point positive(1, 3);
	EXPECT_NO_FATAL_FAILURE(Point copy = positive);
}

TEST(Point, setters_getters) {
	Point Default;
	Point zero(0, 0);
	Point positive0(1, 3);
	Point positive1(5, 2);

	EXPECT_EQ(0, Default.getX());
	EXPECT_EQ(0, Default.getY());
	EXPECT_EQ(0, zero.getX());
	EXPECT_EQ(0, zero.getY());
	EXPECT_EQ(1, positive0.getX());
	EXPECT_EQ(3, positive0.getY());
	EXPECT_EQ(5, positive1.getX());
	EXPECT_EQ(2, positive1.getY());

	EXPECT_NO_FATAL_FAILURE(Default.set(5, 3));
	EXPECT_EQ(5, Default.getX());
	EXPECT_EQ(3, Default.getY());

	//EXPECT_DEATH(Default.set(-5, 3), "\\w");
	//EXPECT_DEATH(Default.set(5, -3), "\\w");
	//EXPECT_DEATH(Default.set(-5, -3), "\\w");
}

TEST(Point, operators) {
	Point pointDefault;
	Point pointZero(0, 0);
	Point pointPos0(1, 3);
	Point pointPos1(5, 2);

	EXPECT_TRUE(pointDefault == pointZero);
	EXPECT_FALSE(pointPos0 == pointPos1);
	EXPECT_TRUE(pointPos0 != pointPos1);
	EXPECT_NO_FATAL_FAILURE(pointPos0 = pointPos1);
	EXPECT_TRUE(pointPos0 == pointPos1);
}
