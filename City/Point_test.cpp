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
/*
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
*/

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
/*
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
*/
