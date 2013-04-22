/*
 * Shop_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "Shop.h"
#include "gtest/gtest.h"
#include "Point.h"
#include "Size.h"

TEST(Shop, constructs) {
	EXPECT_NO_FATAL_FAILURE(Shop benetton(Point(0, 0), Size(5), 10, 1000));
	EXPECT_NO_FATAL_FAILURE(Shop saturn(Point(2, 3), Size(2, 5), 9000, 9000));

	//EXPECT_DEATH(Shop magic(Point(-1, 5), Size(1, 1), 10, 1), "\\w");
	//EXPECT_DEATH(Shop lol(Point(1, 1), Size(0, 0), 1, 3), "\\w");
	//EXPECT_DEATH(Shop burnedDown(Point(0, 0), Size(1), -1, 10), "\\w");
	//EXPECT_DEATH(Shop empty(Point(0, 0), Size(1), 10, -1), "\\w");

	Shop goddamnAppleStore(Point(100000, 10000), Size(1), 1, 1);
	EXPECT_NO_FATAL_FAILURE(Shop chineseAppleStore = goddamnAppleStore);
}

TEST(Shop, robbing) {
	Shop appleStore(Point(0, 0), Size(1), 10, 5);

	EXPECT_EQ(5, appleStore.getSecurity());
	EXPECT_FALSE(appleStore.isRobbing());	// damn, let's rob that store!

	//EXPECT_DEATH(appleStore.rob(), "\\w");

	EXPECT_NO_FATAL_FAILURE(appleStore.StartRobbing());	// hell yeah!!
	EXPECT_TRUE(appleStore.isRobbing());
	EXPECT_NO_FATAL_FAILURE(appleStore.rob());
	EXPECT_EQ(4, appleStore.getSecurity());

	// oh noes, Steve Jobs comes back, get out here!
	EXPECT_NO_FATAL_FAILURE(appleStore.StopRobbing());
	EXPECT_FALSE(appleStore.isRobbing());

	//EXPECT_DEATH(appleStore.rob(), "\\w");

	// okay, he's gone now, let's take ALL the stuff in tha store!
	EXPECT_NO_FATAL_FAILURE(appleStore.StartRobbing());
	EXPECT_NO_FATAL_FAILURE(appleStore.StartRobbing());
	EXPECT_TRUE(appleStore.isRobbing());
	EXPECT_NO_FATAL_FAILURE(appleStore.rob(4));
	EXPECT_EQ(0, appleStore.getSecurity());

}
