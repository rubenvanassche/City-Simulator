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
#include <sstream>

TEST(testVehicles, constructs) {
	ASSERT_NO_FATAL_FAILURE(Point position);
	Point position;
	ASSERT_NO_FATAL_FAILURE(Point destination);
	Point destination;
	std::string name = "Car BMW007";
	EXPECT_NO_FATAL_FAILURE(Vehicle truck(position, destination, name));

	ASSERT_NO_FATAL_FAILURE(Point cur_pos(5, 6));
	Point cur_pos(5, 6);
	ASSERT_NO_FATAL_FAILURE(Point home(10, 12));
	Point home(10, 12);
	EXPECT_NO_FATAL_FAILURE(Vehicle v(cur_pos, home, name));
}

TEST(testVehicles, getters) {
	ASSERT_NO_FATAL_FAILURE(Point position(5, 3));
	Point position(5, 3);
	ASSERT_NO_FATAL_FAILURE(Point destination(7, 9));
	Point destination(7, 9);
	std::string name = "Truck";
	ASSERT_NO_FATAL_FAILURE(Vehicle truck(position, destination, name));
	Vehicle truck(position, destination, name);

	EXPECT_TRUE(position == *truck.getPosition());
	EXPECT_TRUE(destination == *truck.getDestination());
	EXPECT_TRUE("Truck" == *truck.getName());
}

TEST(testVehicles, setters) {
	ASSERT_NO_FATAL_FAILURE(Point destination);
	Point destination;
	ASSERT_NO_FATAL_FAILURE(Point position);
	Point position;
	std::string name = "";
	ASSERT_NO_FATAL_FAILURE(Vehicle v(position, destination, name));
	Vehicle v(position, destination, name);

	std::string newName = "Opel Prius";
	EXPECT_NO_FATAL_FAILURE(v.setName(newName));

	ASSERT_NO_FATAL_FAILURE(Point newPosition(9, 14));
	Point newPosition(9, 14);
	EXPECT_NO_FATAL_FAILURE(v.setPosition(newPosition));

	ASSERT_NO_FATAL_FAILURE(Point newDestination(0, 5));
	Point newDestination(0, 5);
	EXPECT_NO_FATAL_FAILURE(v.setDestination(newDestination));
}

TEST(testVehicles, copying) {
	ASSERT_NO_FATAL_FAILURE(Point position(5, 3));
	Point position(5, 3);
	ASSERT_NO_FATAL_FAILURE(Point destination(7, 9));
	Point destination(7, 9);
	std::string name = "Pick-up";
	ASSERT_NO_FATAL_FAILURE(Vehicle truck(position, destination, name));
	Vehicle truck(position, destination, name);

	EXPECT_NO_FATAL_FAILURE(Vehicle pickup = truck);	// copy by initializing
	Vehicle pickup = truck;
	EXPECT_TRUE(*pickup.getPosition() == *truck.getPosition());
	EXPECT_TRUE(*pickup.getDestination() == *truck.getDestination());
	EXPECT_TRUE(*pickup.getName() == *truck.getName());

	ASSERT_NO_FATAL_FAILURE(Point pos(12, 1));
	Point pos(12, 1);
	ASSERT_NO_FATAL_FAILURE(Point des(0, 9));
	Point des(0, 9);
	std::string newName = "new pick-up";
	ASSERT_NO_FATAL_FAILURE(Vehicle newPick(pos, des, newName));
	Vehicle newPick(position, destination, name);
	EXPECT_NO_FATAL_FAILURE(newPick = pickup);	// copy by initializing
	newPick = pickup;
	EXPECT_TRUE(*pickup.getPosition() == *newPick.getPosition());
	EXPECT_TRUE(*pickup.getDestination() == *newPick.getDestination());
	EXPECT_TRUE(*pickup.getName() == *newPick.getName());
}

TEST(testVehicles, mix) {
	ASSERT_NO_FATAL_FAILURE(Point cur_pos);
	Point cur_pos;
	ASSERT_NO_FATAL_FAILURE(Point home(7, 5));
	Point home(7, 5);
	std::string name = "Peugeot 206";
	ASSERT_NO_FATAL_FAILURE(Vehicle car(cur_pos, home, name));
	Vehicle car(cur_pos, home, name);

	EXPECT_TRUE("Peugeot 206" == *car.getName());
	EXPECT_NO_FATAL_FAILURE(car.setName("Citroen MX"));
	car.setName("Citroen MX");
	EXPECT_TRUE("Citroen MX" == *car.getName());

	EXPECT_TRUE(cur_pos == *car.getPosition());
	ASSERT_NO_FATAL_FAILURE(Point newPos(3, 5));
	Point newPos(3, 5);
	EXPECT_NO_FATAL_FAILURE(car.setPosition(newPos));
	car.setPosition(newPos);
	EXPECT_TRUE(newPos == *car.getPosition());

	EXPECT_TRUE(home == *car.getDestination());
	ASSERT_NO_FATAL_FAILURE(Point newHome(5, 3));
	Point newHome(5, 3);
	EXPECT_NO_FATAL_FAILURE(car.setDestination(newHome));
	car.setDestination(newHome);
	EXPECT_TRUE(newHome == *car.getDestination());
}
