/*
 * CityParser_Test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */


#include "gtest/gtest.h"
#include "CityParser.h"

TEST(testParser, parsing) {
	std::string file1 = "stad.xml";
	std::string file2 = "simpleTown.xml";
	std::string file3 = "faultyTown.xml";
	std::string file4 = "badTown.xml";
	EXPECT_NO_FATAL_FAILURE(delete CityParser::parse(file1));
	EXPECT_NO_FATAL_FAILURE(delete CityParser::parse(file2));

}


