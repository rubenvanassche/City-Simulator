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

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Point entrance(x1, y1));
		Point entrance(x1, y1);

		Size size(4,4);

		std::string name = "Kazern";

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(name, location, size, entrance));
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

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Point entrance(x1, y1));
		Point entrance(x1, y1);

		Size size(4,4);

		std::string name = "Kazern";

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(name, location, size, entrance));
		FireDepot depot(name, location, size, entrance);
		EXPECT_TRUE(location == depot.getLocation());
		EXPECT_TRUE(size == depot.getSize());
		EXPECT_TRUE(entrance == depot.getEntrance());
		EXPECT_TRUE(name == depot.getName());
	}
}

TEST(testFireDepot, setters) {
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

		EXPECT_NO_FATAL_FAILURE(FireDepot depot(name, location, size, entrance));
		FireDepot depot(name, location, size, entrance);

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range + 1;
		int newY1 = std::rand() % range + 1;

		ASSERT_NO_FATAL_FAILURE(Point newLocation(newX0, newY0) );
		Point newLocation(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Point newEntrance(newX1, newY1) );
		Point newEntrance(newX1, newY1);

		EXPECT_NO_FATAL_FAILURE(depot.setLocation(newLocation));
		depot.setLocation(newLocation);
		EXPECT_TRUE(newLocation == depot.getLocation());

		EXPECT_NO_FATAL_FAILURE(depot.setEntrance(newEntrance));
		depot.setEntrance(newEntrance);
		EXPECT_TRUE(newEntrance == depot.getEntrance());
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

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Point entrance(x1, y1));
		Point entrance(x1, y1);

		Size size(4,4);

		EXPECT_NO_FATAL_FAILURE(FireDepot depot("Kazern", location, size, entrance));
		FireDepot depot("Kazern", location, size, entrance);

		int nrOfTrucks = std::rand() % range;
		for(int j = 0;j < nrOfTrucks;j++){
			FireTruck truck("Truck", entrance, entrance, "Kazern");
			ASSERT_NO_FATAL_FAILURE(depot.addFireTruck(truck));
			depot.addFireTruck(truck);
		}

		EXPECT_TRUE(nrOfTrucks == depot.getNrTrucks());

		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point housePoint(x0, y0));
		Point housePoint(x0, y0);

		Size houseSize(2,2);

		House house(housePoint, houseSize, 20);

		ASSERT_NO_FATAL_FAILURE(depot.sendTruck(housePoint, &house));
		depot.sendTruck(housePoint, &house);

		EXPECT_TRUE(depot.alreadySend(housePoint));

		EXPECT_TRUE(depot.getAvailableTrucks() == nrOfTrucks -1);

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

		ASSERT_NO_FATAL_FAILURE(FireDepot depot("Kazern", location, size, entrance));
		FireDepot depot("Kazern", location, size, entrance);

		EXPECT_NO_FATAL_FAILURE(FireDepot copydepot = depot);
		FireDepot copydepot = depot;
		EXPECT_TRUE(copydepot.getLocation() == depot.getLocation());
		EXPECT_TRUE(copydepot.getSize() == depot.getSize());
		EXPECT_TRUE(copydepot.getEntrance() == depot.getEntrance());
		EXPECT_TRUE(copydepot.getName() == depot.getName());
	}
}


