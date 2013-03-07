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
#include <sstream>

TEST(testSize, constructs) {
	EXPECT_NO_FATAL_FAILURE(Size s(5));
	EXPECT_NO_FATAL_FAILURE(Size s(4, 3));
}

TEST(testSize, getters) {
	ASSERT_NO_FATAL_FAILURE(Size s(5));
	Size s(5);
	EXPECT_EQ(5, s.getValue());
	EXPECT_EQ(5, s.getHeight());
	EXPECT_EQ(5, s.getWidth());

	ASSERT_NO_FATAL_FAILURE(Size p(3, 6));
	Size p(3, 6);
	EXPECT_EQ(3, p.getWidth());
	EXPECT_EQ(6, p.getHeight());
}

TEST(testSize, setters) {
	ASSERT_NO_FATAL_FAILURE(Size s(5));
	Size s(5);
	EXPECT_NO_FATAL_FAILURE(s.setValue(3));
	EXPECT_NO_FATAL_FAILURE(s.set(4, 2));

	ASSERT_NO_FATAL_FAILURE(Size p(3, 10));
	Size p(3, 10);
	EXPECT_NO_FATAL_FAILURE(p.set(5, 12));
}

TEST(testSize, mix) {
	ASSERT_NO_FATAL_FAILURE(Size s(12));
	Size s(12);

	EXPECT_EQ(12, s.getValue());
	EXPECT_EQ(12, s.getHeight());
	EXPECT_EQ(12, s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.setValue(5));
	s.setValue(5);
	EXPECT_EQ(5, s.getValue());
	EXPECT_EQ(5, s.getHeight());
	EXPECT_EQ(5, s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.set(9, 6));
	s.set(9, 6);
	EXPECT_EQ(6, s.getHeight());
	EXPECT_EQ(9, s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.setValue(7));
	s.setValue(7);
	EXPECT_EQ(7, s.getValue());
	EXPECT_EQ(7, s.getHeight());
	EXPECT_EQ(7, s.getWidth());
}
