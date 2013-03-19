/*
 * Vehicle_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 3 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "Vehicle.h"
#include "Point.h"
#include <cstdlib>

TEST(testVehicles, constructs) {
	const int nrTests = 10;
	const int range = 100;
	std::string carname = "bananacar";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point curPos(x0, y0));
		Point curPos(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point d(x1, y1));
		Point d(x1, y1);

		EXPECT_NO_FATAL_FAILURE(Vehicle car(carname, curPos, d));
	}
}

TEST(testVehicles, getters) {
	const int nrTests = 10;
	const int range = 100;
	std::string carname = "fancy-car";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point curPos(x0, y0));
		Point curPos(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point d(x1, y1));
		Point d(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Vehicle car(carname, curPos, d));
		Vehicle car(carname, curPos, d);
		EXPECT_TRUE(curPos == car.getPosition());
		EXPECT_TRUE(d == car.getDestination());
		EXPECT_TRUE(carname == car.getName());
	}
}

TEST(testVehicles, drive) {
	const int nrTests = 10;
	const int range = 100;
	std::string carname = "bananacar";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point curPos(x0, y0));
		Point curPos(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point d(x1, y1));
		Point d(x1, y1);

		EXPECT_NO_FATAL_FAILURE(Vehicle car(carname, curPos, d));
		Vehicle car(carname, curPos, d);

		EXPECT_TRUE(car.isArrived() == false);	
		EXPECT_TRUE(car.isOnWay() == true);	
	}
}

TEST(testVehicles, setters) {
	const int nrTests = 10;
	const int range = 100;
	std::string carname = "truck";
	std::string newName = "pickup";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Vehicle str(carname, p, q));
		Vehicle car(carname, p, q);

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range;
		int newY1 = std::rand() % range;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Point newQ(newX1, newY1) );
		Point newQ(newX1, newY1);

		EXPECT_NO_FATAL_FAILURE(car.setPosition(newP));
		car.setPosition(newP);
		EXPECT_TRUE(newP == car.getPosition());

		EXPECT_NO_FATAL_FAILURE(car.setDestination(newQ));
		car.setDestination(newQ);
		EXPECT_TRUE(newQ == car.getDestination());

		EXPECT_NO_FATAL_FAILURE(car.setName(newName));
		car.setName(newName);
		EXPECT_TRUE(newName == car.getName());
	}
}

TEST(testVehicles, copying) {
	const int nrTests = 10;
	const int range = 100;
	std::string carname = "car";
	std::string newName = "zomfg-Car!";

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range;
		int y1 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point q(x1, y1));
		Point q(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Vehicle str(carname, p, q));
		Vehicle car(carname, p, q);

		EXPECT_NO_FATAL_FAILURE(Vehicle copycat = car);
		Vehicle copycat = car;
		EXPECT_TRUE(copycat.getPosition() == car.getPosition());
		EXPECT_TRUE(copycat.getDestination() == car.getDestination());
		EXPECT_TRUE(copycat.getName() == car.getName());

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range;
		int newY1 = std::rand() % range;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Point newQ(newX1, newY1) );
		Point newQ(newX1, newY1);
		ASSERT_NO_FATAL_FAILURE(Vehicle ccar(newName, newP, newQ) );
		Vehicle ccar(newName, newP, newQ);

		EXPECT_NO_FATAL_FAILURE(car = ccar);
		car = ccar;

		EXPECT_TRUE(ccar.getPosition() == car.getPosition());
		EXPECT_TRUE(ccar.getDestination() == car.getDestination());
		EXPECT_TRUE(ccar.getName() == car.getName());
	}
}
