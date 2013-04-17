/*
 * Building_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 9 March 2013
 * 
 */

#include "gtest/gtest.h"
#include "Building.h"
#include "Point.h"
#include "Size.h"
#include <cstdlib>

TEST(testBuilding, constructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		int health = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
		Point Pos(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
		Size s(x1, y1);

		EXPECT_NO_FATAL_FAILURE(Building build(Pos, s, health) );
	}
}

TEST(testBuilding, getters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point curPos(x0, y0));
		Point curPos(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		int health = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
		Size s(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Building app(curPos, s, health));
		Building app(curPos, s, health);
		EXPECT_TRUE(curPos == app.getLocation());
		EXPECT_TRUE(s == app.getSize());
		EXPECT_EQ(health, app.getHealth() );
	}
}

TEST(testBuilding, setters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		int health = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
		Size s(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Building app(p, s, health));
		Building app(p, s, health);

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range + 1;
		int newY1 = std::rand() % range + 1;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Size newS(newX1, newY1) );
		Size newS(newX1, newY1);

		EXPECT_NO_FATAL_FAILURE(app.setLocation(newP));
		app.setLocation(newP);
		EXPECT_TRUE(newP == app.getLocation());

		EXPECT_NO_FATAL_FAILURE(app.setSize(newS));
		app.setSize(newS);
		EXPECT_TRUE(newS == app.getSize());
	}
}

TEST(testBuilding, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point p(x0, y0));
		Point p(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		int health = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
		Size s(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Building app(p, s, health));
		Building app(p, s, health);

		EXPECT_NO_FATAL_FAILURE(Building copycat = app);
		Building copycat = app;
		EXPECT_TRUE(copycat.getLocation() == app.getLocation());
		EXPECT_TRUE(copycat.getSize() == app.getSize());

		int newX0 = std::rand() % range;
		int newY0 = std::rand() % range;
		int newX1 = std::rand() % range + 1;
		int newY1 = std::rand() % range + 1;

		ASSERT_NO_FATAL_FAILURE(Point newP(newX0, newY0) );
		Point newP(newX0, newY0);
		ASSERT_NO_FATAL_FAILURE(Size newS(newX1, newY1) );
		Size newS(newX1, newY1);
		ASSERT_NO_FATAL_FAILURE(Building cApp(newP, newS, health) );
		Building cApp(newP, newS, health);

		EXPECT_NO_FATAL_FAILURE(app = cApp);
		app = cApp;

		EXPECT_TRUE(cApp.getLocation() == app.getLocation());
		EXPECT_TRUE(cApp.getSize() == app.getSize());
	}
}

TEST(testBuilding, firetests) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range;
		int y0 = std::rand() % range;
		ASSERT_NO_FATAL_FAILURE(Point curPos(x0, y0));
		Point curPos(x0, y0);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		int health = std::rand() % range + 2;
		ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
		Size s(x1, y1);

		ASSERT_NO_FATAL_FAILURE(Building app(curPos, s, health));
		Building app(curPos, s, health);

		EXPECT_TRUE(app.isBurning() == false);
		app.setFire();
		EXPECT_TRUE(app.isBurning() == true);
		app.burningDown();
		EXPECT_EQ(health - 1, app.getHealth() );
		app.stopFire();
		EXPECT_TRUE(app.isBurning() == false);

		app.setFire();
		EXPECT_TRUE(app.isBurning());

		while (app.getHealth() > 0) {
			app.burningDown();
		}

		EXPECT_EQ(0, app.getHealth() );
		EXPECT_TRUE(app.isDead() == true);
		EXPECT_TRUE(app.isBurning() == false);
//		EXPECT_DEATH(app.burningDown(), "\\w");
	}
}

TEST(testBuilding, repair){
	const int range = 100;

	int x0 = std::rand() % range;
	int y0 = std::rand() % range;
	int health = 20;
	ASSERT_NO_FATAL_FAILURE(Point Pos(x0, y0));
	Point Pos(x0, y0);

	int x1 = std::rand() % range + 1;
	int y1 = std::rand() % range + 1;
	ASSERT_NO_FATAL_FAILURE(Size s(x1, y1));
	Size s(x1, y1);

	EXPECT_NO_FATAL_FAILURE(Building build(Pos, s, health) );
	Building build(Pos, s, health);

	build.setFire();
	build.burningDown();
	build.burningDown();
	build.burningDown();
	EXPECT_TRUE(17 == build.getHealth());
	EXPECT_FALSE(build.repair());
	build.stopFire();
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(17.5 == build.getHealth());
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(20 == build.getHealth());
	EXPECT_FALSE(build.repair());
	build.setFire();
	build.burningDown();
	EXPECT_TRUE(19 == build.getHealth());
	build.stopFire();
	EXPECT_TRUE(build.repair());
	EXPECT_TRUE(19.5 == build.getHealth());
}
