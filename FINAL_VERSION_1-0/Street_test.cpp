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
#include <cstdlib>

TEST(testStreets, constructs) {
	const int nrTests = 10;
	const int range = 100;
	std::string streetname = "HelloWorld";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		EXPECT_NO_FATAL_FAILURE(Street strasse(streetname, p, q));
	}
}

TEST(testStreets, getters) {
	const int nrTests = 10;
	const int range = 100;
	std::string streetname = "HelloWorld";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Street str(streetname, p, q));
		Street str(streetname, p, q);
		EXPECT_TRUE(p == str.getStartPoint());
		EXPECT_TRUE(q == str.getEndPoint() );
		EXPECT_TRUE(streetname == str.getName());
	}
}

TEST(testStreets, setters) {
	const int nrTests = 10;
	const int range = 100;
	std::string streetname = "HelloWorld";
	std::string newName = "Cstreet";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Street str(streetname, p, q));
		Street str(streetname, p, q);

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range;
		int newY1 = std::rand() % range;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Point newQ(newX1, newY1) );
		Point newQ(newX1, newY1);

		EXPECT_NO_FATAL_FAILURE(str.setStartPoint(newP));
		str.setStartPoint(newP);
		EXPECT_TRUE(newP == str.getStartPoint());

		EXPECT_NO_FATAL_FAILURE(str.setEndPoint(newQ));
		str.setEndPoint(newQ);
		EXPECT_TRUE(newQ == str.getEndPoint());

		EXPECT_NO_FATAL_FAILURE(str.setName(newName));
		str.setName(newName);
		EXPECT_TRUE(newName == str.getName());
	}
}

TEST(testStreets, copying) {
	const int nrTests = 10;
	const int range = 100;
	std::string streetname = "HelloWorld";
	std::string newName = "Cstreet";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Street str(streetname, p, q));
		Street str(streetname, p, q);

		EXPECT_NO_FATAL_FAILURE(Street copycat = str);
		Street copycat = str;
		EXPECT_TRUE(copycat.getStartPoint() == str.getStartPoint());
		EXPECT_TRUE(copycat.getEndPoint() == str.getEndPoint());
		EXPECT_TRUE(copycat.getName() == str.getName());

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range;
		int newY1 = std::rand() % range;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Point newQ(newX1, newY1) );
		Point newQ(newX1, newY1);
		ASSERT_NO_FATAL_FAILURE(Street cStr(newName, newP, newQ) );
		Street cStr(newName, newP, newQ);

		EXPECT_NO_FATAL_FAILURE(str = cStr);
		str = cStr;

		EXPECT_TRUE(cStr.getStartPoint() == str.getStartPoint());
		EXPECT_TRUE(cStr.getEndPoint() == str.getEndPoint());
		EXPECT_TRUE(cStr.getName() == str.getName());

	}
}
