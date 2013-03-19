/*
 * House_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 9 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "House.h"
#include "Point.h"
#include <cstdlib>

TEST(testHouse, constructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		int health = std::rand() % range + 1;
		Size s(2, 2);

		EXPECT_NO_FATAL_FAILURE(House h(Pos, s, health) );
	}
}

TEST(testHouse, fires) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		int health = std::rand() % range + 1;
		Size s(2, 2);

		EXPECT_NO_FATAL_FAILURE(House h(Pos, s, health) );
		House h(Pos, s, health);
		EXPECT_TRUE(h.isBurning() == false);

		EXPECT_NO_FATAL_FAILURE(h.setFire());
		EXPECT_TRUE(h.isBurning() == true);
		EXPECT_TRUE(h.setHealth(10));
		EXPECT_TRUE(h.getHealth() == 10);
		EXPECT_TRUE(h.burningDown());
		EXPECT_TRUE(h.getHealth() == 9);
		EXPECT_TRUE(h.stopFire());
		EXPECT_TRUE(h.isDead() == false);
		EXPECT_TRUE(h.burningDown());
		EXPECT_TRUE(h.getHealth() == 9);
		EXPECT_TRUE(h.setHealth(1));
		EXPECT_NO_FATAL_FAILURE(h.setFire());
		EXPECT_TRUE(h.burningDown());
		EXPECT_TRUE(h.isDead());
	}
}


TEST(testBuilding, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		int health = std::rand() % range + 1;
		Size s(2, 2);

		EXPECT_NO_FATAL_FAILURE(House h(Pos, s, health) );
		House h(Pos, s, health);

		EXPECT_NO_FATAL_FAILURE(House copyhouse = h);
		House copyhouse = h;
		EXPECT_TRUE(copyhouse.getLocation() == h.getLocation());
		EXPECT_TRUE(copycat.getSize() == h.getSize());
		EXPECT_TRUE(copycat.isDead() == h.isDead());
		EXPECT_TRUE(copycat.isBurning() == h.isBurning());
		EXPECT_TRUE(copycat.getHealth() == h.getHealth());
	}
}
