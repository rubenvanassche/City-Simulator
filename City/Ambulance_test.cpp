/*
 * Ambulance_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "gtest/gtest.h"
#include "Ambulance.h"
#include "Hospital.h"
#include "House.h"

class AmbulanceTest : public testing::Test {
protected:

	Point loc;
	Point entr;
	Size size;
	std::string basename;
	int health;

	std::string carname;
	Hospital* ptrBase;

	House* ptrHouse;

	virtual void SetUp() {
		loc.set(2, 2);
		entr.set(0, 0);
		size.set(3, 3);
		basename = "Hospital";
		health = 10;

		carname = "Ambulance";
		ptrBase = new Hospital(loc, entr, size, basename, health);

		ptrHouse()
	}

	virtual void TearDown() {
		delete ptrBase;
		delete ptrHouse;
	}

};

TEST_F(AmbulanceTest, constructs) {
	EXPECT_NO_FATAL_FAILURE(Ambulance ambuce(carname, ptrBase));
}

TEST_F(AmbulanceTest, sending) {

}

/*
TEST(Ambulance, sending) {
	Hospital base(Point(0, 0), Point(1, 1), Size(10, 5), "Hospital", 10);
	Ambulance truck("ambuce", &base);

	House houseOnFire(Point(3, 3), 3);

	EXPECT_TRUE(truck.isInDepot());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	//EXPECT_DEATH(truck.enterDepot(), "\\w");

	EXPECT_NO_FATAL_FAILURE(truck.send(&houseOnFire, Point(2, 2)));
	EXPECT_FALSE(truck.isInDepot());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_EQ(Point(1, 1), truck.getPosition());
	EXPECT_TRUE(truck.isOnWay());

	truck.goRight();
	truck.goUp();

	EXPECT_TRUE(truck.isArrived());
	EXPECT_NO_FATAL_FAILURE(truck.sendBack());
	EXPECT_EQ(Point(1, 1), truck.getDestination());
	EXPECT_FALSE(truck.isAtEntranceDepot());
	EXPECT_FALSE(truck.isInDepot());
	//EXPECT_DEATH(truck.enterDepot(), "\\w");

	truck.goLeft();
	truck.goDown();
	EXPECT_TRUE(truck.isArrived());
	EXPECT_EQ(Point(1, 1), truck.getDestination());
	EXPECT_TRUE(truck.isAtEntranceDepot());
	EXPECT_NO_FATAL_FAILURE(truck.enterDepot());
	EXPECT_FALSE(truck.isOnWay());
	EXPECT_TRUE(truck.isInDepot());
}
*/
