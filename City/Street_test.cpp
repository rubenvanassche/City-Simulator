/*
 * Street_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Saturday 27 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "Street.h"
#include <cmath>

class StreetTest : public testing::Test {
protected:
	Point startHorizontal;
	Point endHorizontal;
	std::string nameHorizontal;

	Point startVertical;
	Point endVertical;
	std::string nameVertical;

	Point startIrregular;
	Point endIrregular;
	std::string nameIrregular;

	Point startHorizontal1;
	Point endHorizontal1;
	std::string nameHorizontal1;

	Point startVertical1;
	Point endVertical1;
	std::string nameVertical1;

	virtual void SetUp() {
		startHorizontal.set(0, 0);
		endHorizontal.set(10, 0);
		nameHorizontal = "Horizontal street";

		startVertical.set(0, 0);
		endVertical.set(0, 10);
		nameVertical = "Vertical street";

		startIrregular.set(0, 0);
		endIrregular.set(10, 10);
		nameIrregular = "Irregular street";

		startHorizontal1.set(0, 1);
		endHorizontal1.set(10, 1);
		nameHorizontal1 = "Another horizontal street";

		startVertical1.set(1, 0);
		endVertical1.set(1, 10);
		nameVertical1 = "Another vertical street";
	}

	virtual void TearDown() {
		// nothing to clean up
	}

	void isElementTest(const Point& start, const Point& end, Street& str) {
		/*
		 * Helper function: test whether for each point in the street is an element of the street
		 */
		if (str.isVertical()) {
			int yMin = std::min(start.getY(), end.getY());
			int yMax = std::max(start.getY(), end.getY());

			for (int y = yMin; y <= yMax; y++) {
				Point p(start.getX(), y);
				EXPECT_TRUE(str.isElement(p) );
			}

			return;
		}
		else if (str.isHorizontal()) {
			int xMin = std::min(start.getX(), end.getX());
			int xMax = std::max(start.getX(), end.getX());

			for (int x = xMin; x <= xMax; x++) {
				Point p(x, start.getY());
				EXPECT_TRUE(str.isElement(p));
			}
		}
		else {
			EXPECT_DEATH(str.isElement(start), "\\w");
			EXPECT_DEATH(str.isElement(end), "\\w");
			return;
		}
	}
};

TEST_F(StreetTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Street horizontal(nameHorizontal, startHorizontal, endHorizontal));
	EXPECT_NO_FATAL_FAILURE(Street horizontalRev(nameHorizontal, endHorizontal, startHorizontal));

	EXPECT_NO_FATAL_FAILURE(Street vertical(nameVertical, startVertical, endVertical));
	EXPECT_NO_FATAL_FAILURE(Street verticalRev(nameVertical, endVertical, startVertical));

	EXPECT_NO_FATAL_FAILURE(Street irregular(nameIrregular, startIrregular, endIrregular));
	EXPECT_NO_FATAL_FAILURE(Street irregularRev(nameIrregular, endIrregular, startIrregular));
}

TEST_F(StreetTest, getters) {
	Street horizontal(nameHorizontal, startHorizontal, endHorizontal);
	Street horizontalRev(nameHorizontal, endHorizontal, startHorizontal);

	Street vertical(nameVertical, startVertical, endVertical);
	Street verticalRev(nameVertical, endVertical, startVertical);

	Street irregular(nameIrregular, startIrregular, endIrregular);
	Street irregularRev(nameIrregular, endIrregular, startIrregular);

	EXPECT_EQ(nameHorizontal, horizontal.getName());
	EXPECT_EQ(startHorizontal, horizontal.getStartPoint());
	EXPECT_EQ(endHorizontal, horizontal.getEndPoint());

	EXPECT_EQ(nameHorizontal, horizontalRev.getName());
	EXPECT_EQ(endHorizontal, horizontalRev.getStartPoint());
	EXPECT_EQ(startHorizontal, horizontalRev.getEndPoint());

	EXPECT_EQ(nameVertical, vertical.getName());
	EXPECT_EQ(startVertical, vertical.getStartPoint());
	EXPECT_EQ(endVertical, vertical.getEndPoint());

	EXPECT_EQ(nameVertical, verticalRev.getName());
	EXPECT_EQ(endVertical, verticalRev.getStartPoint());
	EXPECT_EQ(startVertical, verticalRev.getEndPoint());

	EXPECT_EQ(nameIrregular, irregular.getName());
	EXPECT_EQ(startIrregular, irregular.getStartPoint());
	EXPECT_EQ(endIrregular, irregular.getEndPoint());

	EXPECT_EQ(nameIrregular, irregularRev.getName());
	EXPECT_EQ(endIrregular, irregularRev.getStartPoint());
	EXPECT_EQ(startIrregular, irregularRev.getEndPoint());
}

TEST_F(StreetTest, directions) {
	Street horizontal(nameHorizontal, startHorizontal, endHorizontal);
	Street vertical(nameVertical, startVertical, endVertical);
	Street irregular(nameIrregular, startIrregular, endIrregular);

	EXPECT_TRUE(horizontal.isHorizontal());
	EXPECT_FALSE(horizontal.isVertical());

	EXPECT_FALSE(vertical.isHorizontal());
	EXPECT_TRUE(vertical.isVertical());

	EXPECT_FALSE(irregular.isHorizontal());
	EXPECT_FALSE(irregular.isVertical());
}

TEST_F(StreetTest, elements) {
	Street horizontal(nameHorizontal, startHorizontal, endHorizontal);
	Street vertical(nameVertical, startVertical, endVertical);
	Street irregular(nameIrregular, startIrregular, endIrregular);

	EXPECT_NO_FATAL_FAILURE(isElementTest(startHorizontal, endHorizontal, horizontal));
	EXPECT_NO_FATAL_FAILURE(isElementTest(startVertical, endVertical, vertical));
	EXPECT_NO_FATAL_FAILURE(isElementTest(startIrregular, endIrregular, irregular));

	EXPECT_FALSE(horizontal.isElement(endIrregular));
	EXPECT_FALSE(horizontal.isElement(endVertical));

	EXPECT_FALSE(vertical.isElement(endIrregular));
	EXPECT_FALSE(vertical.isElement(endHorizontal));

	EXPECT_DEATH(irregular.isElement(endHorizontal), "\\w");	// oops, irregular street
	EXPECT_DEATH(irregular.isElement(endVertical), "\\w");	// oops, irregular street
}

TEST_F(StreetTest, crossing) {
	Street horizontal(nameHorizontal, startHorizontal, endHorizontal);
	Street vertical(nameVertical, startVertical, endVertical);
	Street irregular(nameIrregular, startIrregular, endIrregular);

	Street horizontal1(nameHorizontal1, startHorizontal1, endHorizontal1);
	Street vertical1(nameVertical1, startVertical1, endVertical1);

	EXPECT_TRUE(horizontal.isCrossing(vertical));
	EXPECT_TRUE(vertical.isCrossing(horizontal));
	EXPECT_FALSE(irregular.isCrossing(horizontal));
	EXPECT_FALSE(irregular.isCrossing(vertical));
	EXPECT_FALSE(horizontal.isCrossing(irregular));
	EXPECT_FALSE(vertical.isCrossing(irregular));
	EXPECT_FALSE(vertical.isCrossing(vertical1));
	EXPECT_FALSE(horizontal.isCrossing(horizontal1));

	EXPECT_EQ(startHorizontal, horizontal.getCrosspoint(vertical));
	EXPECT_EQ(startVertical, vertical.getCrosspoint(horizontal));
	EXPECT_DEATH(horizontal.getCrosspoint(irregular), "\\w");	// oops, irregular street
	EXPECT_DEATH(irregular.getCrosspoint(horizontal), "\\w");	// oops, irregular street

	EXPECT_TRUE(horizontal.isParallel(horizontal1));
	EXPECT_TRUE(horizontal1.isParallel(horizontal));
	EXPECT_DEATH(horizontal.getCrosspoint(horizontal1), "\\w");
	EXPECT_DEATH(horizontal1.getCrosspoint(horizontal), "\\w");

	EXPECT_TRUE(vertical.isParallel(vertical1));
	EXPECT_TRUE(vertical1.isParallel(vertical));
	EXPECT_DEATH(vertical.getCrosspoint(vertical1), "\\w");
	EXPECT_DEATH(vertical1.getCrosspoint(vertical), "\\w");
}









