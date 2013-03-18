/*
 * WorldMap_Test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Monday 18 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "WorldMap.h"
#include "Street.h"
#include "Point.h"

TEST(testWorldMap, simpleMap) {
	ASSERT_NO_FATAL_FAILURE(Point leftBottom(0, 0) );
	ASSERT_NO_FATAL_FAILURE(Point leftMid(0, 1) );
	ASSERT_NO_FATAL_FAILURE(Point leftTop(0, 2) );
	ASSERT_NO_FATAL_FAILURE(Point bottom(1, 0) );
	ASSERT_NO_FATAL_FAILURE(Point mid(1, 1) );
	ASSERT_NO_FATAL_FAILURE(Point top(1, 2) );
	ASSERT_NO_FATAL_FAILURE(Point rightBottom(2, 0) );
	ASSERT_NO_FATAL_FAILURE(Point rightMid(2, 1) );
	ASSERT_NO_FATAL_FAILURE(Point rightTop(2, 2) );

	Point leftBottom(0, 0);
	Point leftMid(0, 1);
	Point leftTop(0, 2);
	Point bottom(1, 0);
	Point mid(1, 1);
	Point top(1, 2);
	Point rightBottom(2, 0);
	Point rightMid(2, 1);
	Point rightTop(2, 2);

	std::string h1 = "Horizontal1";
	std::string h2 = "Horizontal2";
	std::string v1 = "Vertical1";
	std::string v2 = "Vertical2";
	std::string v3 = "Vertical3";

	ASSERT_NO_FATAL_FAILURE(Street horizontalDown(h1, leftBottom, rightBottom) );
	ASSERT_NO_FATAL_FAILURE(Street horizontalTop(h2, leftTop, rightTop) );
	ASSERT_NO_FATAL_FAILURE(Street verticalLeft(v1, leftBottom, leftTop) );
	ASSERT_NO_FATAL_FAILURE(Street verticalMid(v2, bottom, top) );
	ASSERT_NO_FATAL_FAILURE(Street verticalRight(v3, rightBottom, rightTop) );

	Street horizontalDown(h1, leftBottom, rightBottom);
	Street horizontalTop(h2, leftTop, rightTop);
	Street verticalLeft(v1, leftBottom, leftTop);
	Street verticalMid(v2, bottom, top);
	Street verticalRight(v3, rightBottom, rightTop);

	ASSERT_NO_FATAL_FAILURE(WorldMap map);
	WorldMap map;

	EXPECT_NO_FATAL_FAILURE(map.addStreet(horizontalDown));
	map.addStreet(horizontalDown);
	EXPECT_NO_FATAL_FAILURE(map.addStreet(horizontalTop));
	map.addStreet(horizontalTop);
	EXPECT_NO_FATAL_FAILURE(map.addStreet(verticalLeft));
	map.addStreet(verticalLeft);
	EXPECT_NO_FATAL_FAILURE(map.addStreet(verticalRight));
	map.addStreet(verticalRight);
	EXPECT_NO_FATAL_FAILURE(map.addStreet(verticalMid));
	map.addStreet(verticalMid);

	for (int x=0; x < 3; x++) {
		for (int y=0; y < 3; y++) {
			Point p(x, y);
			EXPECT_TRUE(map.isInMap(p));
		}
	}

	for (int x=3; x < 5; x++) {
		for (int y=3; y < 5; y++) {
			Point p(x, y);
			EXPECT_FALSE(map.isInMap(p));
		}
	}

	EXPECT_TRUE(map.isCross(leftBottom) );
	EXPECT_FALSE(map.isCross(leftMid) );
	EXPECT_TRUE(map.isCross(leftTop) );
	EXPECT_TRUE(map.isCross(bottom) );
	EXPECT_FALSE(map.isCross(mid) );
	EXPECT_TRUE(map.isCross(top) );
	EXPECT_TRUE(map.isCross(rightBottom) );
	EXPECT_FALSE(map.isCross(rightMid));
	EXPECT_TRUE(map.isCross(rightTop) );

	for (int x=0; x < 3; x++) {
		for (int y=0; y < 3; y++) {
			Point startPoint(x, y);

			for (int xD=0; xD < 3; xD++) {
				for (int yD=0; yD < 3; yD++) {
					Point dest(xD, yD);

					while (dest != startPoint) {
						map.successor(startPoint, dest);
					}
					EXPECT_TRUE(dest == startPoint);
				}
			}
		}
	}
}
