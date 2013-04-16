/*
 * out_test.cpp
 *
 *  Created on: 20 mrt. 2013
 *      Author: Ruben
 */

#include "gtest/gtest.h"
#include "Out.h"
#include <string>
#include <iostream>
#include "Point.h"

TEST(testOut, file1) {
	std::string file = "test.txt";
	Out output(file);
	Point p(2,2);
	output << "test";
	output << "Test" << "\n" << p << "\n" << 21;
	output.indent();
	output << p;
}
