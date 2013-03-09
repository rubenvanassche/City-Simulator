/*
 * Street_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 3 March 2013
 * 
 */



#include "gtest/gtest.h"
#include "Street.h"
#include "Point.h"
#include <sstream>

TEST(testStreets, validConstructs) {
	ASSERT_NO_FATAL_FAILURE(Point a);
	Point a;
	ASSERT_NO_FATAL_FAILURE(Point b);
	Point b;

	EXPECT_NO_FATAL_FAILURE(Street hello(a, b, "HelloWorldstreet"));
	Street hello(a, b, "HelloWorldstreet");
	std::stringstream ss;
	ss << hello;
	EXPECT_EQ("HelloWorldstreet [(0, 0) -> (0, 0)]", ss.str());


	Point c(5);
	Point d(3);

	EXPECT_NO_FATAL_FAILURE(Street cpp(c, d, "Cplusplusstreet"));
	Street cpp(c, d, "Cplusplusstreet");
	std::stringstream tt;
	tt << cpp;
	EXPECT_EQ("Cplusplusstreet [(5, 0) -> (3, 0)]", tt.str());


	Point e(3, 5);
	Point f(12, 5);

	EXPECT_NO_FATAL_FAILURE(Street java(e, f, "Javastreet"));
	Street java(e, f, "Javastreet");
	std::stringstream uu;
	uu << java;
	EXPECT_EQ("Javastreet [(3, 5) -> (12, 5)]", uu.str());
}

TEST(testStreets, getters) {
	ASSERT_NO_FATAL_FAILURE(Point p(3, 5));
	Point p(3, 5);
	ASSERT_NO_FATAL_FAILURE(Point q(12, 5));
	Point q(12, 5);
	ASSERT_NO_FATAL_FAILURE(Street street(p, q, "HelloWorldstreet"));
	Street street(p, q, "HelloWorldstreet");

	std::stringstream ss;
	ss << street;
	EXPECT_EQ("HelloWorldstreet [(3, 5) -> (12, 5)]", ss.str());
	EXPECT_EQ("HelloWorldstreet", *street.getName());
	Point result = *street.getStartPoint();
	EXPECT_TRUE(p == result);
	result = *street.getEndPoint();
	EXPECT_TRUE(q == result);
}

TEST(testStreets, setters) {
	ASSERT_NO_FATAL_FAILURE(Point p(3, 5));
	Point p(3, 5);
	ASSERT_NO_FATAL_FAILURE(Point q(12, 5));
	Point q(12, 5);
	ASSERT_NO_FATAL_FAILURE(Street street(p, q, "HelloWorldstreet"));
	Street street(p, q, "HelloWorldstreet");

	std::stringstream ss;
	ss << street;
	EXPECT_EQ("HelloWorldstreet [(3, 5) -> (12, 5)]", ss.str());

	ASSERT_NO_FATAL_FAILURE(Point newStart(2, 1));
	Point newStart(2, 1);
	EXPECT_NO_FATAL_FAILURE(street.setStartPoint(newStart));
	street.setStartPoint(newStart);
	std::stringstream tt;
	tt << street;
	EXPECT_EQ("HelloWorldstreet [(2, 1) -> (12, 5)]", tt.str());

	ASSERT_NO_FATAL_FAILURE(Point newEnd(0, 1));
	Point newEnd(0, 1);
	EXPECT_NO_FATAL_FAILURE(street.setEndPoint(newEnd));
	street.setEndPoint(newEnd);
	std::stringstream uu;
	uu << street;
	EXPECT_EQ("HelloWorldstreet [(2, 1) -> (0, 1)]", uu.str());

	EXPECT_NO_FATAL_FAILURE(street.setName("Pythonstreet"));
	street.setName("Pythonstreet");
	std::stringstream vv;
	vv << street;
	EXPECT_EQ("Pythonstreet [(2, 1) -> (0, 1)]", vv.str());
}

TEST(testStreets, copying) {
	ASSERT_NO_FATAL_FAILURE(Point p(3, 5));
	Point p(3, 5);
	ASSERT_NO_FATAL_FAILURE(Point q(12, 5));
	Point q(12, 5);
	ASSERT_NO_FATAL_FAILURE(Street str(p, q, "bananastreet"));
	Street str(p, q, "bananastreet");

	EXPECT_NO_FATAL_FAILURE(Street cpy = str);	// copy by initializing
	Street cpy = str;
	EXPECT_TRUE(*cpy.getStartPoint() == *str.getStartPoint());
	EXPECT_TRUE(*cpy.getEndPoint() == *str.getEndPoint());
	EXPECT_TRUE(*cpy.getName() == *str.getName());

	ASSERT_NO_FATAL_FAILURE(Point a(12, 0));
	Point a(12, 0);
	ASSERT_NO_FATAL_FAILURE(Point b(6, 3));
	Point b(6, 3);
	ASSERT_NO_FATAL_FAILURE(Street newStr(a, b, "chiquita"));
	Street newStr(a, b, "chiquita");
	EXPECT_NO_FATAL_FAILURE(newStr = str);	// copy by assignment
	newStr = str;
	EXPECT_TRUE(*newStr.getStartPoint() == *str.getStartPoint());
	EXPECT_TRUE(*newStr.getEndPoint() == *str.getEndPoint());
	EXPECT_TRUE(*newStr.getName() == *str.getName());

}

TEST(testStreets, mix) {
	ASSERT_NO_FATAL_FAILURE(Point start(1, 13));
	Point start(1, 13);
	ASSERT_NO_FATAL_FAILURE(Point end(1, 6));
	Point end(1, 6);
	ASSERT_NO_FATAL_FAILURE(Street street(start, end, "Bananastreet"));
	Street street(start, end, "Bananastreet");

	std::stringstream init;
	init << street;
	EXPECT_EQ("Bananastreet [(1, 13) -> (1, 6)]", init.str());

	EXPECT_EQ("Bananastreet", *street.getName());
	EXPECT_NO_FATAL_FAILURE(street.setName("Chiquitastreet"));
	street.setName("Chiquitastreet");
	EXPECT_EQ("Chiquitastreet", *street.getName());

	EXPECT_NO_FATAL_FAILURE(Point result = *street.getStartPoint());
	Point result = *street.getStartPoint();
	EXPECT_TRUE(start == result);

	ASSERT_NO_FATAL_FAILURE(Point newStart(5, 8));
	Point newStart(5, 8);
	EXPECT_NO_FATAL_FAILURE(street.setStartPoint(newStart));
	street.setStartPoint(newStart);
	result = *street.getStartPoint();
	EXPECT_TRUE(newStart == result);

	result = *street.getEndPoint();
	EXPECT_TRUE(end == result);
	Point newEnd(0, 8);
	EXPECT_NO_FATAL_FAILURE(street.setEndPoint(newEnd));
	street.setEndPoint(newEnd);
	result = *street.getEndPoint();
	EXPECT_TRUE(newEnd == result);

	std::stringstream final;
	final << street;
	EXPECT_EQ("Chiquitastreet [(5, 8) -> (0, 8)]", final.str());
}
