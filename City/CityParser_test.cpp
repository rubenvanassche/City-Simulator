/*
 * CityParser_test.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Saturday 27 April 2013
 * 
 */


#include "gtest/gtest.h"
#include "CityParser.h"

class CityParserTest : public testing::Test {
protected:

	City* ptrCity;

	std::string validStreets;
	std::string invalidStreets;

	virtual void SetUp() {
		ptrCity = new City;
		validStreets = "STREETS_valid.xml";
		invalidStreets = "STREETS_invalid.xml";
	}

	virtual void TearDown() {
		delete ptrCity;
	}

};

TEST_F(CityParserTest, construct) {
	EXPECT_NO_FATAL_FAILURE(CityParser parser(ptrCity));
}

TEST_F(CityParserTest, validStreets) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validStreets.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validStreets	 << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseStreet(node));
		}
	}
}


TEST_F(CityParserTest, invalidStreets) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidStreets.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidStreets	 << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseStreet(node));
		}
	}
}

