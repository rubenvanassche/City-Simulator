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
	Point position;
	Point destination;
	std::string name = "Car BMW007k";
	EXPECT_NO_FATAL_FAILURE(Vehicle truck(position, destination, name));

	Point cur_pos(5, 6);
	Point home(10, 12);
	EXPECT_NO_FATAL_FAILURE(Vehicle v(cur_pos, home, name));
}

TEST(testVehicles, getters) {
	Point position(5, 3);
	Point destination(7, 9);
	std::string name = "Truck";
	ASSERT_NO_FATAL_FAILURE(Vehicle truck(position, destination, name));
	Vehicle truck(position, destination, name);

	Point result = truck.getPosition();
	EXPECT_TRUE(result == position);
	result = truck.getDestination();
	EXPECT_TRUE(result == destination);
	EXPECT_TRUE("Truck" == truck.getName());
}

TEST(testVehicles, setters) {
	Point destination;
	Point position;
	std::string name = "";
	ASSERT_NO_FATAL_FAILURE(Vehicle v(position, destination, name));
	Vehicle v(position, destination, name);

	std::string newName = "Opel Prius";
	EXPECT_NO_FATAL_FAILURE(v.setName(newName));

	Point newPosition(9, 14);
	EXPECT_NO_FATAL_FAILURE(v.setPosition(newPosition));

	Point newDestination(0, 5);
	EXPECT_NO_FATAL_FAILURE(v.setDestination(newDestination));
}

TEST(testVehicles, mix) {
	Point cur_pos;
	Point home(7, 5);
	std::string name = "Peugeot 206";
	ASSERT_NO_FATAL_FAILURE(Vehicle car(cur_pos, home, name));
	Vehicle car(cur_pos, home, name);

	EXPECT_TRUE("Peugeot 206" == car.getName());
	EXPECT_NO_FATAL_FAILURE(car.setName("Citroen MX"));
	car.setName("Citroen MX");
	EXPECT_TRUE("Citroen MX" == car.getName());

	Point result = car.getPosition();
	EXPECT_TRUE(cur_pos == result);
	Point newPos(3, 5);
	EXPECT_NO_FATAL_FAILURE(car.setPosition(newPos));
	car.setPosition(newPos);
	result = car.getPosition();
	EXPECT_TRUE(result == newPos);

	result = car.getDestination();
	EXPECT_TRUE(result == home);
	Point newHome(5, 3);
	EXPECT_NO_FATAL_FAILURE(car.setDestination(newHome));
	car.setDestination(newHome);
	result = car.getDestination();
	EXPECT_TRUE(result == newHome);
}
