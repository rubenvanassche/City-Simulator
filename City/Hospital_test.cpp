/*
 * Hospital_test.cpp
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */


#include "Hospital.h"
#include "gtest/gtest.h"
#include "House.h"
#include "Point.h"
#include <string>

TEST(testHospital, construct){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	Hospital hospital(l1, e1, s1, name, 20);
	EXPECT_TRUE(s1 == hospital.getSize());
	EXPECT_TRUE(l1 == hospital.getLocation());
	EXPECT_TRUE(e1 == hospital.getEntrance());
	EXPECT_TRUE(name == hospital.getName());
	EXPECT_TRUE(20 == hospital.getHealth());
}

TEST(testHospital, copy){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	Hospital hospital(l1, e1, s1, name, 20);

	Hospital newhospital(hospital);
	EXPECT_TRUE(s1 == newhospital.getSize());
	EXPECT_TRUE(l1 == newhospital.getLocation());
	EXPECT_TRUE(e1 == newhospital.getEntrance());
	EXPECT_TRUE(name == newhospital.getName());
	EXPECT_TRUE(20 == newhospital.getHealth());
}

TEST(testHospital, asignment){
	Size s1(4, 6);
	Point l1(10, 10);
	Point e1(10, 10);
	std::string name = "Test";

	Size s2(8, 12);
	Point l2(20, 20);
	Point e2(20, 20);
	std::string name2 = "Test2";

	Hospital hospital(l1, e1, s1, name, 20);

	Hospital newhospital(l2, e2, s2, name, 40);

	newhospital = hospital;

	EXPECT_TRUE(s1 == newhospital.getSize());
	EXPECT_TRUE(l1 == newhospital.getLocation());
	EXPECT_TRUE(e1 == newhospital.getEntrance());
	EXPECT_TRUE(name == newhospital.getName());
	EXPECT_TRUE(20 == newhospital.getHealth());
}
