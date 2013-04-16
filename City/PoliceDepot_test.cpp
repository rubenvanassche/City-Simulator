/*
 * PoliceDepot_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#include "PoliceDepot.h"
#include "gtest/gtest.h"
#include "House.h"
#include "Point.h"
#include <string>

TEST(testPoliceDepot, construct){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	PoliceDepot depot(l1, e1, s1, name, 20);
	EXPECT_TRUE(s1 == depot.getSize());
	EXPECT_TRUE(l1 == depot.getLocation());
	EXPECT_TRUE(e1 == depot.getEntrance());
	EXPECT_TRUE(name == depot.getName());
	EXPECT_TRUE(20 == depot.getHealth());
}

TEST(testPoliceDepot, copy){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	PoliceDepot depot(l1, e1, s1, name, 20);

	PoliceDepot newDepot(depot);
	EXPECT_TRUE(s1 == newDepot.getSize());
	EXPECT_TRUE(l1 == newDepot.getLocation());
	EXPECT_TRUE(e1 == newDepot.getEntrance());
	EXPECT_TRUE(name == newDepot.getName());
	EXPECT_TRUE(20 == newDepot.getHealth());
}

TEST(testPoliceDepot, asignment){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	Size s2(8, 12);
	Point l2(20, 20);
	Point e2(20, 20);
	std::string name2 = "Test2";

	PoliceDepot depot(l1, e1, s1, name, 20);

	PoliceDepot newDepot(l2, e2, s2, name, 40);

	newDepot = depot;

	EXPECT_TRUE(s1 == newDepot.getSize());
	EXPECT_TRUE(l1 == newDepot.getLocation());
	EXPECT_TRUE(e1 == newDepot.getEntrance());
	EXPECT_TRUE(name == newDepot.getName());
	EXPECT_TRUE(20 == newDepot.getHealth());
}
