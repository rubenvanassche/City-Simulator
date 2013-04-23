/*
 * Street_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 3 March 2013
 * 
 */



#include "gtest/gtest.h"
#include "Street.h"
#include "Point.h"

TEST(Street, constructs) {
	EXPECT_NO_FATAL_FAILURE(Street horizontal("Horizontal", Point(0, 5), Point(10, 5)));
	EXPECT_NO_FATAL_FAILURE(Street vertical("Vertical", Point(1, 3), Point(1, 7)));
	EXPECT_NO_FATAL_FAILURE(Street irregular("Irregular", Point(0, 0), Point(10, 10)));

	//EXPECT_DEATH(Street magic("magic", Point(-5, 0), Point(-3, 5)), "\\w");

	Street horizontal("Horizontal", Point(0, 5), Point(10, 5));
	EXPECT_NO_FATAL_FAILURE(Street copy = horizontal);
}

TEST(Street, getters) {
	Street horizontal("Horizontal", Point(0, 5), Point(10, 5));
	Street vertical("Vertical", Point(1, 3), Point(1, 7));
	Street irregular("Irregular", Point(0, 0), Point(5, 10));

	EXPECT_EQ(Point(0, 5), horizontal.getStartPoint());
	EXPECT_EQ(Point(10, 5), horizontal.getEndPoint());
	EXPECT_EQ("Horizontal", horizontal.getName());
	EXPECT_EQ(Point(1, 3), vertical.getStartPoint());
	EXPECT_EQ(Point(1, 7), vertical.getEndPoint());
	EXPECT_EQ("Vertical", vertical.getName());
	EXPECT_EQ(Point(0, 0), irregular.getStartPoint());
	EXPECT_EQ(Point(5, 10), irregular.getEndPoint());
	EXPECT_EQ("Irregular", irregular.getName());
}


TEST(Street, vertical_horizontal) {
	Street horizontal("Horizontal", Point(0, 5), Point(10, 5));
	Street vertical("Vertical", Point(1, 3), Point(1, 7));
	Street irregular("Irregular", Point(0, 0), Point(5, 10));

	EXPECT_TRUE(horizontal.isHorizontal());
	EXPECT_FALSE(horizontal.isVertical());
	EXPECT_TRUE(vertical.isVertical());
	EXPECT_FALSE(vertical.isHorizontal());
	EXPECT_FALSE(irregular.isHorizontal());
	EXPECT_FALSE(irregular.isVertical());
}

TEST(Street, element) {
	Street horizontal("Horizontal", Point(0, 5), Point(10, 5));
	Street vertical("Vertical", Point(1, 3), Point(1, 7));
	Street irregular("Irregular", Point(0, 0), Point(5, 10));

	EXPECT_TRUE(horizontal.isElement(Point(3, 5)));
	EXPECT_FALSE(horizontal.isElement(Point(1, 2)));
	EXPECT_FALSE(vertical.isElement(Point(3, 5)));
	EXPECT_TRUE(vertical.isElement(Point(1, 3)));

	//EXPECT_DEATH(irregular.isElement(Point(3, 5)), "\\w");
	//EXPECT_DEATH(irregular.isElement(Point(1, 2)), "\\w");
}

TEST(Street, crossing_parallel) {
	Street horizontal0("Horizontal0", Point(0, 3), Point(5, 3));
	Street horizontal1("Horizontal1", Point(5, 2), Point(10, 2));
	Street vertical0("Vertical0", Point(0, 0), Point(0, 5));
	Street vertical1("Vertical1", Point(5, 0), Point(5, 5));

	EXPECT_TRUE(horizontal0.isParallel(horizontal1));
	EXPECT_FALSE(horizontal0.isParallel(vertical0));
	EXPECT_FALSE(horizontal0.isParallel(vertical1));

	EXPECT_TRUE(horizontal1.isParallel(horizontal0));
	EXPECT_FALSE(horizontal1.isParallel(vertical0));
	EXPECT_FALSE(horizontal1.isParallel(vertical1));

	EXPECT_FALSE(vertical0.isParallel(horizontal1));
	EXPECT_FALSE(vertical0.isParallel(horizontal0));
	EXPECT_TRUE(vertical0.isParallel(vertical1));

	EXPECT_FALSE(vertical1.isParallel(horizontal1));
	EXPECT_FALSE(vertical1.isParallel(horizontal0));
	EXPECT_TRUE(vertical1.isParallel(vertical0));

	EXPECT_EQ(Point(0, 3), vertical0.getCrosspoint(horizontal0));
	EXPECT_EQ(Point(0, 3), horizontal0.getCrosspoint(vertical0));
//	EXPECT_DEATH(vertical0.getCrosspoint(vertical1), "\\w");

	EXPECT_EQ(Point(5, 3), vertical1.getCrosspoint(horizontal0));
	EXPECT_EQ(Point(5, 2), vertical1.getCrosspoint(horizontal1));
//	EXPECT_DEATH(vertical1.getCrosspoint(vertical0), "\\w");
}
