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
		std::string name = "Wagen";

		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string basename = "Kazern";
		int health = std::rand() % range + 1;

		ASSERT_NO_FATAL_FAILURE(FireDepot depot(location, location, size, basename, health));
		FireDepot depot(location, location, size, basename, health);

		EXPECT_NO_FATAL_FAILURE(FireTruck f(name, &depot) );
	}
}

TEST(testFireTruck, sending) {
	const int nrTests = 1;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		std::string name = "Wagen";

		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string basename = "Kazern";
		int health = std::rand() % range + 1;
		Point entrance(x0 +1, y0 + 1);

		ASSERT_NO_FATAL_FAILURE(FireDepot depot(location, location, size, basename, health));
		FireDepot depot(location, entrance, size, basename, health);

		ASSERT_NO_FATAL_FAILURE(FireTruck f(name, &depot) );
		FireTruck f(name, & depot);

		EXPECT_TRUE(f.isInDepot() == true);
		ASSERT_NO_FATAL_FAILURE(Point p(y0 + 5, x0 + 5));
		Point p(y0 + 5, x0+5);
		Size s(2);
		ASSERT_NO_FATAL_FAILURE(Building b(p, s, 10) );
		Building b(p, s, 10);

		f.send(&b, p);
		EXPECT_TRUE(f.getPosition() == entrance);
		EXPECT_TRUE(f.isInDepot() == false);
		EXPECT_TRUE(f.isAtEntranceDepot() == true);
		EXPECT_TRUE(f.getDestination() == p);

		f.sendBack();
		EXPECT_TRUE(f.isInDepot() == false);
		EXPECT_TRUE(f.getDestination() == depot.getEntrance());
		EXPECT_TRUE(f.isAtEntranceDepot() == true);
		EXPECT_TRUE(f.isArrived() == true);

		f.enterDepot();
		EXPECT_TRUE(f.isInDepot() == true);
		EXPECT_TRUE(f.getPosition() == depot.getLocation());
	}

}

TEST(testFireTruck, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		std::string name = "Wagen";

		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string basename = "Kazern";
		int health = std::rand() % range + 1;
		Point entrance(x0 +1, y0 + 1);

		ASSERT_NO_FATAL_FAILURE(FireDepot depot(location, location, size, basename, health));
		FireDepot depot(location, location, size, basename, health);

		ASSERT_NO_FATAL_FAILURE(FireTruck f(name, &depot) );
		FireTruck f(name, & depot);

		EXPECT_NO_FATAL_FAILURE(FireTruck copytruck = f);
		FireTruck copytruck = f;
		EXPECT_TRUE(copytruck.getBase() == f.getBase());
	}
}
