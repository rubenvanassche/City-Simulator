/*
 * FireDepot_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "FireDepot.h"
#include "FireTruck.h"
#include "House.h"
#include "Point.h"
#include <string>
#include <cstdlib>

TEST(testFireDepot, Constructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string name = "Kazern";
		int health = std::rand() % range + 1;

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(location, size, health, name, location));
	}
}

TEST(testFireDepot, getters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string name = "Kazern";
		int health = std::rand() % range + 1;

		ASSERT_NO_FATAL_FAILURE(FireDepot depot(location, size, health, name, location));
		FireDepot depot(location, size, health, name, location);

		EXPECT_TRUE(location == depot.getLocation());
		EXPECT_TRUE(size == depot.getSize());
		EXPECT_TRUE(location == depot.getEntrance());
		EXPECT_TRUE(name == depot.getName());
	}
}

TEST(testFireDepot, trucks){
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);
		Size size(4,4);
		std::string name = "Kazern";
		std::string truckName = "Truck";
		int health = std::rand() % range + 1;

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(location, size, health, name, location));
		FireDepot depot(location, size, health, name, location);

		ASSERT_NO_FATAL_FAILURE(FireTruck truck(truckName, &depot));
		FireTruck truck(truckName, &depot);

		EXPECT_NO_FATAL_FAILURE(depot.addFireTruck(&truck) );
		EXPECT_EQ(1, depot.getNrTrucks());
		EXPECT_EQ(1, depot.getAvailableTrucks());

		truck.goUp();
		EXPECT_EQ(1, depot.getNrTrucks());
		EXPECT_EQ(0, depot.getAvailableTrucks());
	}
}

TEST(testFireDepot, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point location(x0, y0));
		Point location(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Point entrance(x1, y1));
		Point entrance(x1, y1);
		Size size(4,4);
		std::string name = "Kazern";
		int health = std::rand() % range + 1;

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(location, size, health, name, location));
		FireDepot depot(location, size, health, name, location);

		EXPECT_NO_FATAL_FAILURE(FireDepot copydepot = depot);
		FireDepot copydepot = depot;
		EXPECT_TRUE(copydepot.getLocation() == depot.getLocation());
		EXPECT_TRUE(copydepot.getSize() == depot.getSize());
		EXPECT_TRUE(copydepot.getEntrance() == depot.getEntrance());
		EXPECT_TRUE(copydepot.getName() == depot.getName());
	}
}
