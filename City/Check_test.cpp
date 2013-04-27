/*
 * Check_test.cpp
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#include "gtest/gtest.h"
#include "Check.h"

class CheckTest : public testing::Test {
protected:
	Street* ptrHorizontalBottom;
	Street* ptrHorizontalTop;
	Street* ptrHorizontalMid;

	Street* ptrVerticalLeft;
	Street* ptrVerticalRight;
	Street* ptrVerticalMid;

	Street* ptrIrregular;

	Street* ptrVerticalShort;
	Street* ptrVerticalLong;
	Street* ptrHorizontalShort;
	Street* ptrHorizontalLong;

	Building* ptrLeftTop;
	Building* ptrLeftBottom;
	Building* ptrRightTop;
	Building* ptrRightBottom;

	Building* ptrMid;

	virtual void SetUp() {
		ptrHorizontalBottom = new Street("HorizontalBottom", Point(0, 0), Point(10, 0));
		ptrHorizontalTop = new Street("HorizontalTop", Point(0, 10), Point(10, 10));
		ptrHorizontalMid = new Street("HorizontalMid", Point(0, 5), Point(10, 5));

		ptrVerticalLeft = new Street("VerticalLeft", Point(0, 0), Point(0, 10));
		ptrVerticalRight = new Street("VerticalRight", Point(10, 0), Point(10, 10));
		ptrVerticalMid = new Street("VerticalMid", Point(5, 0), Point(5, 10));

		ptrIrregular = new Street("Irregular", Point(0, 0), Point(10, 10));

		ptrVerticalShort = new Street("Short, vertical street", Point(2, 0), Point(2, 9));
		ptrVerticalLong = new Street("Long, vertical street", Point(8, 0), Point(8, 11));
		ptrHorizontalShort = new Street("Short, horizontal street", Point(0, 2), Point(9, 2));
		ptrHorizontalLong = new Street("Long, horizontal street", Point(0, 8), Point(11, 8));

		Size size(4, 4);
		int health = 10;
		int reducer = 1;

		ptrLeftTop = new Building(Point(1, 9), size, health, reducer);
		ptrLeftBottom = new Building(Point(1, 4), size, health, reducer);
		ptrRightTop = new Building(Point(6, 9), size, health, reducer);
		ptrRightBottom = new Building(Point(6, 4), size, health, reducer);

		ptrMid = new Building(Point(4, 6), Size(3, 3), health, reducer);
	}

	virtual void TearDown() {
		delete ptrHorizontalBottom;
		delete ptrHorizontalMid;
		delete ptrHorizontalTop;

		delete ptrVerticalLeft;
		delete ptrVerticalRight;
		delete ptrVerticalMid;

		delete ptrIrregular;

		delete ptrVerticalShort;
		delete ptrVerticalLong;
		delete ptrHorizontalShort;
		delete ptrHorizontalLong;

		delete ptrLeftTop;
		delete ptrLeftBottom;
		delete ptrRightTop;
		delete ptrRightBottom;

		delete ptrMid;
	}

};

TEST_F(CheckTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Check checker);
}

TEST_F(CheckTest, streets) {
	Check checker;

	EXPECT_TRUE(checker.go(*ptrHorizontalBottom));
	EXPECT_TRUE(checker.go(*ptrHorizontalTop));
	EXPECT_TRUE(checker.go(*ptrHorizontalMid));
	EXPECT_TRUE(checker.go(*ptrHorizontalBottom));	// heraanleg

	EXPECT_TRUE(checker.go(*ptrVerticalLeft));
	EXPECT_TRUE(checker.go(*ptrVerticalMid));
	EXPECT_TRUE(checker.go(*ptrVerticalRight));
	EXPECT_TRUE(checker.go(*ptrVerticalRight));

	EXPECT_FALSE(checker.go(*ptrIrregular));

	EXPECT_FALSE(checker.go(*ptrHorizontalShort));
	EXPECT_FALSE(checker.go(*ptrHorizontalLong));
	EXPECT_FALSE(checker.go(*ptrVerticalShort));
	EXPECT_FALSE(checker.go(*ptrVerticalLong));
}

TEST_F(CheckTest, Building) {
	Check checker;

	EXPECT_TRUE(checker.go(*ptrLeftTop));
	EXPECT_TRUE(checker.go(*ptrRightTop));
	EXPECT_TRUE(checker.go(*ptrLeftBottom));
	EXPECT_TRUE(checker.go(*ptrRightBottom));

	EXPECT_FALSE(checker.go(*ptrRightBottom));
	EXPECT_FALSE(checker.go(*ptrMid));
}

TEST_F(CheckTest, mix0) {
	// mix0 creates first streets, then buildings

	Check checker;

	EXPECT_TRUE(checker.go(*ptrHorizontalBottom));
	EXPECT_TRUE(checker.go(*ptrHorizontalTop));
	EXPECT_TRUE(checker.go(*ptrHorizontalMid));

	EXPECT_TRUE(checker.go(*ptrVerticalLeft));
	EXPECT_TRUE(checker.go(*ptrVerticalMid));
	EXPECT_TRUE(checker.go(*ptrVerticalRight));

	EXPECT_FALSE(checker.go(*ptrMid));

	EXPECT_TRUE(checker.go(*ptrLeftTop));
	EXPECT_TRUE(checker.go(*ptrRightTop));
	EXPECT_TRUE(checker.go(*ptrLeftBottom));
	EXPECT_TRUE(checker.go(*ptrRightBottom));

	EXPECT_FALSE(checker.go(*ptrMid));
}

TEST_F(CheckTest, mix1) {
	// mix1 creates building first, then streets
	Check checker;

	EXPECT_TRUE(checker.go(*ptrMid));

	EXPECT_FALSE(checker.go(*ptrLeftTop));
	EXPECT_FALSE(checker.go(*ptrRightTop));
	EXPECT_FALSE(checker.go(*ptrLeftBottom));
	EXPECT_FALSE(checker.go(*ptrRightBottom));

	EXPECT_TRUE(checker.go(*ptrHorizontalBottom));
	EXPECT_TRUE(checker.go(*ptrHorizontalTop));
	EXPECT_FALSE(checker.go(*ptrHorizontalMid));

	EXPECT_TRUE(checker.go(*ptrVerticalLeft));
	EXPECT_FALSE(checker.go(*ptrVerticalMid));
	EXPECT_TRUE(checker.go(*ptrVerticalRight));
}

TEST_F(CheckTest, mix2) {
	// same as mix1
	Check checker;

	EXPECT_TRUE(checker.go(*ptrLeftTop));
	EXPECT_TRUE(checker.go(*ptrRightTop));
	EXPECT_TRUE(checker.go(*ptrLeftBottom));
	EXPECT_TRUE(checker.go(*ptrRightBottom));

	EXPECT_FALSE(checker.go(*ptrMid));

	EXPECT_TRUE(checker.go(*ptrHorizontalBottom));
	EXPECT_TRUE(checker.go(*ptrHorizontalTop));
	EXPECT_TRUE(checker.go(*ptrHorizontalMid));

	EXPECT_TRUE(checker.go(*ptrVerticalLeft));
	EXPECT_TRUE(checker.go(*ptrVerticalMid));
	EXPECT_TRUE(checker.go(*ptrVerticalRight));
}
