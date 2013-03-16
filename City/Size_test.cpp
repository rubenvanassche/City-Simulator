/*
 * Size_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 7 March 2013
 * 
 */


#include "gtest/gtest.h"
#include "Size.h"
#include <cstdlib>

TEST(testSize, validConstructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int w = std::rand() % range + 1;
		int h = std::rand() % range + 1;
		EXPECT_NO_FATAL_FAILURE(Size s(w, h));
	}
}

TEST(testSize, invalidConstructs) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int w = std::rand() % range + 1;
		int h = -1 * (std::rand() % range + 1);
		EXPECT_DEATH(Size s(w, h), "\\w");
	}

	for (int i=0; i < nrTests; i++) {
		int w = -1 * (std::rand() % range + 1);
		int h = -1 * (std::rand() % range + 1);
		EXPECT_DEATH(Size s(w, h), "\\w");
	}

	for (int i=0; i < nrTests; i++) {
		int w = -1 * (std::rand() % range + 1);
		int h = std::rand() % range + 1;
		EXPECT_DEATH(Size s(w, h), "\\w");
	}
}

TEST(testSize, getters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int w = std::rand() % range + 1;
		int h = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size s(w, h));
		Size s(w, h);

		EXPECT_EQ(w, s.getWidth());
		EXPECT_EQ(h, s.getHeight());
	}
}

TEST(testSize, validSetters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int w = std::rand() % range + 1;
		int h = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size s(w, h));
		Size s(w, h);

		int newW = std::rand() % range + 1;
		int newH = std::rand() % range + 1;

		EXPECT_NO_FATAL_FAILURE(s.set(newW, newH) );
		EXPECT_EQ(newW, s.getWidth() );
		EXPECT_EQ(newH, s.getHeight() );
	}
}

TEST(testSize, invalidSetters) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x = std::rand() % range + 1;
		int y = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size p(x, y));
		Size p(x, y);

		int newX = -1 * (std::rand() % range + 1);
		int newY = -1 * (std::rand() % range + 1);

		EXPECT_DEATH(p.set(newX, newY), "\\w");
	}
}

TEST(testSize, copying) {
	const int nrTests = 10;
	const int range = 100;

	for (int i=0; i < nrTests; i++) {
		int x0 = std::rand() % range + 1;
		int y0 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size p(x0, y0));
		Size p(x0, y0);

		EXPECT_NO_FATAL_FAILURE(Size q = p);
		Size q = p;

		EXPECT_TRUE(q == p);

		int x1 = std::rand() % range + 1;
		int y1 = std::rand() % range + 1;
		ASSERT_NO_FATAL_FAILURE(Size r(x1, y1) );
		Size r(x1, y1);

		EXPECT_NO_FATAL_FAILURE(r = p);
		EXPECT_TRUE(r == p);
	}
}
