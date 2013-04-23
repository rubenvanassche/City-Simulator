/*
 * Check_test.cpp
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#include "gtest/gtest.h"
#include "House.h"
#include "FireDepot.h"
#include "Point.h"
#include "Size.h"
#include "Check.h"
#include "Street.h"
#include <string>

TEST(Check, streets) {
	Street horizontal0("Horizontal0", Point(0, 5), Point(5, 5));
	Street horizontal1("Horizontal1", Point(0, 0), Point(5, 0));
	Street vertical0("Vertical0", Point(0, 0), Point(0, 5));
	Street vertical1("Vertical1", Point(5, 0), Point(5, 5));

	Street horizontalShort("short horizontal", Point(1, 1), Point(4, 1));
	Street verticalShort("short vertical", Point(1, 1), Point(1, 4));
	Street horizontalLong("Long horizontal", Point(0, 3), Point(10, 3));
	Street verticalLong("Long vertical", Point(3, 0), Point(3, 12));
	Street irregular("irregular", Point(0, 0), Point(5, 5));
	Check check;

	EXPECT_TRUE(check.go(horizontal0));
	EXPECT_TRUE(check.go(horizontal1));
	EXPECT_TRUE(check.go(vertical0));
	EXPECT_TRUE(check.go(vertical1));

	EXPECT_FALSE(check.go(horizontalShort));
	EXPECT_FALSE(check.go(verticalShort));
	EXPECT_FALSE(check.go(horizontalLong));
	EXPECT_FALSE(check.go(verticalLong));
	EXPECT_FALSE(check.go(irregular));
}
/*
TEST(Check, building) {
	House home(Point(0, 2), 10);
	FireDepot firedepot(Point(5, 5), Point(3, 3), "firedepot", 10);
	House irregular(Point(0, 0), 10);
	Check check;

	EXPECT_TRUE(check.go(home));
	EXPECT_TRUE(check.go(firedepot));
	EXPECT_FALSE(check.go(irregular));
}

TEST(Check, mix) {
	Street horizontal0("Horizontal0", Point(0, 5), Point(5, 5));
	Street horizontal1("Horizontal1", Point(0, 0), Point(5, 0));
	Street vertical0("Vertical0", Point(0, 0), Point(0, 5));
	Street vertical1("Vertical1", Point(5, 0), Point(5, 5));

	House homeOnStreet(Point(0, 2), 10);
	House home(Point(1, 2), 10);

	Check check;

	EXPECT_TRUE(check.go(horizontal0));
	EXPECT_FALSE(check.go(horizontal0));
	EXPECT_TRUE(check.go(horizontal1));
	EXPECT_FALSE(check.go(horizontal1));
	EXPECT_TRUE(check.go(vertical0));
	EXPECT_FALSE(check.go(vertical0));
	EXPECT_TRUE(check.go(vertical1));
	EXPECT_FALSE(check.go(vertical1));
	EXPECT_TRUE(check.go(home));
	EXPECT_FALSE(check.go(homeOnStreet));
}

*/
