/*
 * Check_test.cpp
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#include "gtest/gtest.h"
#include "House.h"
#include "Point.h"
#include "Size.h"
#include "Check.h"
#include "Street.h"
#include <string>

class CheckTest : public ::testing::Test {
 protected:
	Check newCheck;

	// Start House
	Size sizeH;
	Size sizeF;
	Point l1;
	Point l2;
	Point l3;
	Point l4;
	Point l5;
	Point l6;
	Point l7;
	Point l8;
	Point l9;
	Point l10;

	virtual void SetUp() {
		sizeH.set(2,2);
		sizeF.set(4,4);

		l1.set(5,5);
		l2.set(1,1);
		l3.set(7,5);
		l4.set(9,5);
		l5.set(20,20);
		l6.set(1,10);
		l7.set(10,1);
		l8.set(7,10);
		l9.set(7,1);
	}
};

TEST_F(CheckTest, RegularHouse){
	House h1(l1, sizeH, 20);
	House h2(l2, sizeH, 20);
	House h3(l3, sizeH, 20);
	EXPECT_TRUE(newCheck.go(h1));
	EXPECT_TRUE(newCheck.go(h2));
	EXPECT_TRUE(newCheck.go(h3));
}

TEST_F(CheckTest, OnTopHouse){
	House h1(l1, sizeH, 20);
	House h2(l1, sizeH, 20);

	EXPECT_TRUE(newCheck.go(h1));
	EXPECT_FALSE(newCheck.go(h2));
}

TEST_F(CheckTest, RegularFireDepot){
	std::string name = "Station";
	FireDepot f1(name, l5, sizeF, l5);
	FireDepot f2(name, l1, sizeF, l1);
	FireDepot f3(name, l4, sizeF, l4);

	EXPECT_TRUE(newCheck.go(f1));
	EXPECT_TRUE(newCheck.go(f2));
	EXPECT_TRUE(newCheck.go(f3));
}

TEST_F(CheckTest, OnTopFireDepot){
	std::string name = "Station";
	FireDepot f1(name, l5, sizeF, l5);
	FireDepot f2(name, l5, sizeF, l5);

	EXPECT_TRUE(newCheck.go(f1));
	EXPECT_FALSE(newCheck.go(f2));
}

TEST_F(CheckTest, RegularStreet){
	std::string name = "Street";
	Street s1(name, l3, l4);
	Street s2(name, l2, l6);

	EXPECT_TRUE(newCheck.go(s1));
	EXPECT_TRUE(newCheck.go(s2));
}

TEST_F(CheckTest, Crossroads){
	std::string name = "Street";
	Street s1(name, l3, l4);
	Street s2(name, l8, l9);
	Street s3(name, l2, l6);

	EXPECT_TRUE(newCheck.go(s1));
	EXPECT_TRUE(newCheck.go(s2));
	EXPECT_TRUE(newCheck.go(s3));
}

TEST_F(CheckTest, MultiStreets){
	std::string name = "Street";
	Street f1(name, l2, l6);
	Street f2(name, l2, l7);

	EXPECT_TRUE(newCheck.go(f1));
	EXPECT_TRUE(newCheck.go(f2));
}



