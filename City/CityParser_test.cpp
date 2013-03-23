/*
 * main.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#include "gtest/gtest.h"
#include "CityParser.h"

TEST(testCityParser, validXML) {
	std::string name1 = "rightTown1.xml";
	ASSERT_NO_FATAL_FAILURE(CityParser parser1(name1.c_str() ) );
	CityParser parser1(name1.c_str() );

	EXPECT_TRUE(parser1.parseAll());
}

TEST(testCityParser, edgeCaseXML) {
	std::string name1 = "edgeTown1.xml";
	ASSERT_NO_FATAL_FAILURE(CityParser parser1(name1.c_str() ) );
	CityParser parser1(name1.c_str() );

	EXPECT_TRUE(parser1.parseAll());
}

TEST(testCityParser, invalidXML) {

}
