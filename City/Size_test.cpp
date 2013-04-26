/*
 * Size_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */


#include "gtest/gtest.h"
#include "Size.h"

class SizeTest : public testing::Test {
public:
	int zero;
	int one;
	int positive0;
	int positive1;

	int negative0;
	int negative1;

	virtual void SetUp() {
		zero = 0;
		one = 1;
		positive0 = 5;
		positive1 = 10;

		negative0 = -1;
		negative1 = -12;
	}

	virtual void TearDown() {

	}
};

TEST_F(SizeTest, construct) {
	EXPECT_NO_FATAL_FAILURE(Size Default);
	EXPECT_NO_FATAL_FAILURE(Size positive(positive0, positive1));
	EXPECT_NO_FATAL_FAILURE(Size positive(positive1, positive0));
	/*
	EXPECT_DEATH(Size null(zero, zero), "\\w");
	EXPECT_DEATH(Size negative(negative0, negative1), "\\w");
	EXPECT_DEATH(Size negative(negative1, negative0), "\\w");
	EXPECT_DEATH(Size negative(negative0, positive1), "\\w");
	EXPECT_DEATH(Size negative(negative1, positive0), "\\w");
	EXPECT_DEATH(Size negative(positive0, negative1), "\\w");
	EXPECT_DEATH(Size negative(positive1, negative0), "\\w");
	*/
}

TEST_F(SizeTest, setters_getters) {
	Size ones(one, one);
	Size positive_0(positive0, positive1);
	Size positive_1(positive1, positive0);

	EXPECT_EQ(one, ones.getWidth());
	EXPECT_EQ(one, ones.getHeight());
	EXPECT_EQ(positive0, positive_0.getWidth());
	EXPECT_EQ(positive1, positive_0.getHeight());
	EXPECT_EQ(positive1, positive_1.getWidth());
	EXPECT_EQ(positive0, positive_1.getHeight());

	EXPECT_NO_FATAL_FAILURE(positive_0.set(positive1, positive0));
	EXPECT_NO_FATAL_FAILURE(positive_1.set(positive0, positive1));
	EXPECT_EQ(positive1, positive_0.getWidth());
	EXPECT_EQ(positive0, positive_0.getHeight());
	EXPECT_EQ(positive0, positive_1.getWidth());
	EXPECT_EQ(positive1, positive_1.getHeight());
	/*
	EXPECT_DEATH(ones.set(zero, zero), "\\w");
	EXPECT_DEATH(ones.set(negative0, negative1), "\\w");
	EXPECT_DEATH(ones.set(positive0, negative1), "\\w");
	EXPECT_DEATH(ones.set(negative1, positive1), "\\w");
	EXPECT_DEATH(positive_0.set(negative0, negative1), "\\w");
	EXPECT_DEATH(positive_0.set(positive0, negative1), "\\w");
	EXPECT_DEATH(positive_0.set(negative1, positive1), "\\w");
	EXPECT_DEATH(positive_1.set(negative0, negative1), "\\w");
	EXPECT_DEATH(positive_1.set(positive0, negative1), "\\w");
	EXPECT_DEATH(positive_1.set(negative1, positive1), "\\w");
	*/
}

TEST_F(SizeTest, copying) {
	Size positive(positive0, positive1);
	Size ones;

	EXPECT_NO_FATAL_FAILURE(Size copy = positive);
	Size copy = positive;

	EXPECT_EQ(positive0, copy.getWidth());
	EXPECT_EQ(positive1, copy.getHeight());
	EXPECT_TRUE(copy == positive);
	/*
	EXPECT_FALSE(ones == positive);
	EXPECT_NO_FATAL_FAILURE(ones = positive);
	EXPECT_EQ(positive0, ones.getWidth());
	EXPECT_EQ(positive1, ones.getHeight());
	EXPECT_TRUE(ones == positive);
	*/
}
