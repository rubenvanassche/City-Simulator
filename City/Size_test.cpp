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

TEST(Size, constructs) {
	EXPECT_NO_FATAL_FAILURE(Size Default);
	EXPECT_NO_FATAL_FAILURE(Size ones(1, 1));
	EXPECT_NO_FATAL_FAILURE(Size positive(5, 2));

	//EXPECT_DEATH(Size zero(0, 0), "\\w");
	//EXPECT_DEATH(Size negative(-1, -3), "\\w");
	//EXPECT_DEATH(Size wNegative(-1, 3), "\\w");
	//EXPECT_DEATH(Size hNegative(1, -3), "\\w");

	Size positive(5, 2);
	EXPECT_NO_FATAL_FAILURE(Size copy = positive);
}

TEST(Size, setters_getters) {
	Size Default;
	Size positive0(1, 3);
	Size positive1(5, 2);

	EXPECT_EQ(1, Default.getWidth());
	EXPECT_EQ(1, Default.getHeight());
	EXPECT_EQ(1, positive0.getWidth());
	EXPECT_EQ(3, positive0.getHeight());
	EXPECT_EQ(5, positive1.getWidth());
	EXPECT_EQ(2, positive1.getHeight());

	EXPECT_NO_FATAL_FAILURE(Default.set(5, 3));
	EXPECT_EQ(5, Default.getWidth());
	EXPECT_EQ(3, Default.getHeight());

	//EXPECT_DEATH(Default.set(-5, -3), "\\w");
	//EXPECT_DEATH(Default.set(-5, 3), "\\w");
	//EXPECT_DEATH(Default.set(5, -3), "\\w");
}

TEST(Size, operators) {
	Size Default;
	Size ones(1, 1);
	Size positive0(3, 2);
	Size positive1(5, 1);

	EXPECT_TRUE(Default == ones);
	EXPECT_FALSE(positive0 == positive1);
	EXPECT_NO_FATAL_FAILURE(positive0 = positive1);
	EXPECT_TRUE(positive0 == positive1);
}
