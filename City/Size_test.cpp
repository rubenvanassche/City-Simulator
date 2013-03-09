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

TEST(testSize, validConstructs) {
	EXPECT_NO_FATAL_FAILURE(Size s(5));
	EXPECT_NO_FATAL_FAILURE(Size s(4, 3));
}

TEST(testSize, invalidConstructs) {
	EXPECT_DEATH(Size s(0), "\\w");
	EXPECT_DEATH(Size s(-5), "\\w");
	EXPECT_DEATH(Size s(2, 0), "\\w");
	EXPECT_DEATH(Size s(-5, -3), "\\w");
	EXPECT_DEATH(Size s(5, -12), "\\w");
}

TEST(testSize, getters) {
	ASSERT_NO_FATAL_FAILURE(Size s(5));
	Size s(5);
	EXPECT_EQ(5, *s.getValue());
	EXPECT_EQ(5, *s.getHeight());
	EXPECT_EQ(5, *s.getWidth());

	ASSERT_NO_FATAL_FAILURE(Size p(3, 6));
	Size p(3, 6);
	EXPECT_EQ(3, *p.getWidth());
	EXPECT_EQ(6, *p.getHeight());
}

TEST(testSize, validSetters) {
	ASSERT_NO_FATAL_FAILURE(Size s(5));
	Size s(5);
	EXPECT_NO_FATAL_FAILURE(s.setValue(3));
	EXPECT_NO_FATAL_FAILURE(s.set(4, 2));

	ASSERT_NO_FATAL_FAILURE(Size p(3, 10));
	Size p(3, 10);
	EXPECT_NO_FATAL_FAILURE(p.set(5, 12));
}

TEST(testSize, invalidSetters) {
	ASSERT_NO_FATAL_FAILURE(Size s(5));
	Size s(5);
	EXPECT_DEATH(s.setValue(0), "\\w");
	EXPECT_DEATH(s.setValue(-3), "\\w");
	EXPECT_DEATH(s.set(2, 0), "\\w");
	EXPECT_DEATH(s.set(3, -5), "\\w");
}

TEST(testSize, operators) {
	ASSERT_NO_FATAL_FAILURE(Size o(12));
	Size o(12);
	ASSERT_NO_FATAL_FAILURE(Size p(12));
	Size p(12);
	ASSERT_NO_FATAL_FAILURE(Size q(5));
	Size q(5);

	EXPECT_TRUE(o == p);
	EXPECT_FALSE(o == q);

	ASSERT_NO_FATAL_FAILURE(Size r(5, 3));
	Size r(5, 3);
	ASSERT_NO_FATAL_FAILURE(Size s(5, 3));
	Size s(5, 3);
	ASSERT_NO_FATAL_FAILURE(Size t(12, 1));
	Size t(12, 1);

	EXPECT_TRUE(r == s);
	EXPECT_FALSE(t == s);

	EXPECT_NO_FATAL_FAILURE(Size u = s);
	Size u = s;
	EXPECT_TRUE(u == s);

	EXPECT_NO_FATAL_FAILURE(t = s);
	t = s;
	EXPECT_TRUE(t == s);
}

TEST(testSize, mix) {
	ASSERT_NO_FATAL_FAILURE(Size s(12));
	Size s(12);

	EXPECT_EQ(12, *s.getValue());
	EXPECT_EQ(12, *s.getHeight());
	EXPECT_EQ(12, *s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.setValue(5));
	s.setValue(5);
	EXPECT_EQ(5, *s.getValue());
	EXPECT_EQ(5, *s.getHeight());
	EXPECT_EQ(5, *s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.set(9, 6));
	s.set(9, 6);
	EXPECT_EQ(6, *s.getHeight());
	EXPECT_EQ(9, *s.getWidth());

	EXPECT_NO_FATAL_FAILURE(s.setValue(7));
	s.setValue(7);
	EXPECT_EQ(7, *s.getValue());
	EXPECT_EQ(7, *s.getHeight());
	EXPECT_EQ(7, *s.getWidth());
}
