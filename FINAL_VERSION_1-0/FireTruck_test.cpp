/*
 * FireTruck_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireTruck.h"
#include "Point.h"
#include "House.h"
#include <cstdlib>
#include <string>

TEST(testFireTruck, constructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

			std::string name = "Wagen";
			std::string baseName = "Base1";

		EXPECT_NO_FATAL_FAILURE(FireTruck f(name ,Pos, Pos,baseName) );
	}
}

TEST(testFireTruck, getters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		std::string name = "Wagen";
		std::string baseName = "Base1";

		EXPECT_NO_FATAL_FAILURE(FireTruck f(name ,Pos, Pos, baseName) );
		FireTruck f(name ,Pos, Pos, baseName);

		EXPECT_TRUE(f.getBase() == baseName);
	}
}

TEST(testFireTruck, setters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		std::string name = "Wagen";
		std::string baseName = "Base1";

		EXPECT_NO_FATAL_FAILURE(FireTruck f(name,Pos, Pos, baseName) );
		FireTruck f(name ,Pos, Pos, baseName);

		std::string baseName2 = "Base2";

		EXPECT_TRUE(f.setBase(baseName2));
		f.setBase(baseName2);

		EXPECT_TRUE(f.getBase() == baseName2);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Posh(x1, y1));
		Point Posh(x1, y1);

		int health = std::rand() % range + 1;
		Size s(2, 2);

		EXPECT_NO_FATAL_FAILURE(House h(Posh, s, health));
		House h(Posh, s, health);

		EXPECT_NO_FATAL_FAILURE(f.setHouseOnFire(&h));
		f.setHouseOnFire(&h);


		//EXPECT_TRUE(f.getHouseOnFire() == &h);
	}
}

TEST(testFireTruck, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		std::string name = "Wagen";
		std::string baseName = "Base1";

		EXPECT_NO_FATAL_FAILURE(FireTruck f(name ,Pos, Pos, baseName) );
		FireTruck f(name ,Pos, Pos, baseName);

		EXPECT_NO_FATAL_FAILURE(FireTruck copytruck = f);
		FireTruck copytruck = f;
		EXPECT_TRUE(copytruck.getBase() == f.getBase());
	}
}

