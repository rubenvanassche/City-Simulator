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
#include <cstdlib>

TEST(testPoint, validConstructs){
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range;
		int y = std::rand() % range;
		EXPECT_NO_FATAL_FAILURE(Point p(x, y));
	}
}

TEST(testPoint, invalidConstructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range;
		int y = -1 * (std::rand() % range);
		EXPECT_DEATH(Point p(x, y), "\\w");
	}

	for (int i=0; i < nrTests; i++) {
		int x = -1 * (std::rand() % range);
		int y = -1 * (std::rand() % range);
		EXPECT_DEATH(Point p(x, y), "\\w");
	}

	for (int i=0; i < nrTests; i++) {
		int x = -1 * (std::rand() % range);
		int y = std::rand() % range;
		EXPECT_DEATH(Point p(x, y), "\\w");
	}
}


TEST(testPoint, getters){
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range;
		int y = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x, y));
		Point p(x, y);

		EXPECT_EQ(x, p.getX());
		EXPECT_EQ(y, p.getY());
	}
}


TEST(testPoint, validSetters){
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range;
		int y = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x, y));
		Point p(x, y);

		int newX = std::rand() % range;
		int newY = std::rand() % range;

		EXPECT_NO_FATAL_FAILURE(p.set(newX, newY) );
		EXPECT_EQ(newX, p.getX() );
		EXPECT_EQ(newY, p.getY() );
	}
}

TEST(testPoint, invalidSetters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range;
		int y = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x, y));
		Point p(x, y);

		int newX = -1 * (std::rand() % range);
		int newY = -1 * (std::rand() % range);

		EXPECT_DEATH(p.set(newX, newY), "\\w");
	}
}
/*
TEST(testPoint, operators){
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		EXPECT_NO_FATAL_FAILURE(Point q = p);
		Point q = p;

		EXPECT_TRUE(q == p);

		int x1 = std::rand() % x0;
		int y1 = std::rand() % y0;
		ASSERT_NO_FATAL_FAILURE(Point r(x1, y1) );
		Point r(x1, y1);

		int xResult = x0 - x1;
		int yResult = y0 - y1;
		EXPECT_NO_FATAL_FAILURE(p - r);
		EXPECT_EQ(xResult, (p - r).getX() );
		EXPECT_EQ(yResult, (p - r).getY() );

		xResult = x0 + x1;
		yResult = y0 + y1;
		EXPECT_NO_FATAL_FAILURE(p + r);
		EXPECT_EQ(xResult, (p + r).getX() );
		EXPECT_EQ(yResult, (p + r).getY() );

		EXPECT_NO_FATAL_FAILURE(r = p);
		EXPECT_TRUE(r == p);
	}
}
*/
