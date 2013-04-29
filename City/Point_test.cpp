/*
 * Point_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "gtest/gtest.h"
#include "Point.h"

class PointTest : public testing::Test {
public:
	int zero;
	int positive0;
	int positive1;

	int negative0;
	int negative1;

	virtual void SetUp() {
		zero = 0;
		positive0 = 5;
		positive1 = 10;

		negative0 = -1;
		negative1 = -12;
	}

	virtual void TearDown() {

	}
};


TEST_F(PointTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Point Default);
	EXPECT_NO_FATAL_FAILURE(Point null(zero, zero));
	EXPECT_NO_FATAL_FAILURE(Point positive(positive0, positive1));
	EXPECT_NO_FATAL_FAILURE(Point positive(positive1, positive0));

	EXPECT_DEATH(Point negative(negative0, negative1), "");
	EXPECT_DEATH(Point negative(negative1, negative0), "");
	EXPECT_DEATH(Point negative(negative0, positive1), "");
	EXPECT_DEATH(Point negative(negative1, positive0), "");
	EXPECT_DEATH(Point negative(positive0, negative1), "");
	EXPECT_DEATH(Point negative(positive1, negative0), "");
}

TEST_F(PointTest, setters_getters) {
	Point null(zero, zero);
	Point positive_0(positive0, positive1);
	Point positive_1(positive1, positive0);

	EXPECT_EQ(zero, null.getX());
	EXPECT_EQ(zero, null.getY());
	EXPECT_EQ(positive0, positive_0.getX());
	EXPECT_EQ(positive1, positive_0.getY());
	EXPECT_EQ(positive1, positive_1.getX());
	EXPECT_EQ(positive0, positive_1.getY());

	EXPECT_NO_FATAL_FAILURE(null.set(zero, zero));
	EXPECT_NO_FATAL_FAILURE(positive_0.set(positive1, positive0));
	EXPECT_NO_FATAL_FAILURE(positive_1.set(positive0, positive1));
	EXPECT_EQ(zero, null.getX());
	EXPECT_EQ(zero, null.getY());
	EXPECT_EQ(positive1, positive_0.getX());
	EXPECT_EQ(positive0, positive_0.getY());
	EXPECT_EQ(positive0, positive_1.getX());
	EXPECT_EQ(positive1, positive_1.getY());

	EXPECT_DEATH(null.set(negative0, negative1), "");
	EXPECT_DEATH(null.set(positive0, negative1), "");
	EXPECT_DEATH(null.set(negative1, positive1), "");
	EXPECT_DEATH(positive_0.set(negative0, negative1), "");
	EXPECT_DEATH(positive_0.set(positive0, negative1), "");
	EXPECT_DEATH(positive_0.set(negative1, positive1), "");
	EXPECT_DEATH(positive_1.set(negative0, negative1), "");
	EXPECT_DEATH(positive_1.set(positive0, negative1), "");
	EXPECT_DEATH(positive_1.set(negative1, positive1), "");
}

TEST_F(PointTest, copying) {
	Point positive(positive0, positive1);
	Point null;

	EXPECT_NO_FATAL_FAILURE(Point copy = positive);
	Point copy = positive;

	EXPECT_EQ(positive0, copy.getX());
	EXPECT_EQ(positive1, copy.getY());
	EXPECT_TRUE(copy == positive);

	EXPECT_FALSE(null == positive);
	EXPECT_NO_FATAL_FAILURE(null = positive);
	EXPECT_EQ(positive0, null.getX());
	EXPECT_EQ(positive1, null.getY());
	EXPECT_TRUE(null == positive);
}
