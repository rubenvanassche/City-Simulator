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

	std::string validHouses;
	std::string invalidHouses;

	std::string validFireDepots;
	std::string invalidFireDepots;

	std::string validPoliceDepots;
	std::string invalidPoliceDepots;

	std::string validShops;
	std::string invalidShops;

	std::string validHospitals;
	std::string invalidHospitals;

	std::string validAmbulances;
	std::string invalidAmbulances;

	std::string validFireTrucks;
	std::string invalidFireTrucks;

	std::string validPoliceTrucks;
	std::string invalidPoliceTrucks;

	virtual void SetUp() {
		Hospital hosp(Point(10, 10), Point(10, 10), Size(1), "bestaat", 10);
		FireDepot fDept(Point(12, 12), Point(20, 20), "bestaat", 10);
		PoliceDepot pDept(Point(14, 14), Point(14, 14), Size(1), "bestaat", 10);

		ptrCity = new City;
		ASSERT_TRUE(ptrCity->add(hosp));
		ASSERT_TRUE(ptrCity->add(fDept));
		ASSERT_TRUE(ptrCity->add(pDept));

		validStreets = "XML-testfiles/streets_valid.xml";
		invalidStreets = "XML-testfiles/streets_invalid.xml";

		validHouses = "XML-testfiles/house_valid.xml";
		invalidHouses = "XML-testfiles/house_invalid.xml";

		validFireDepots = "XML-testfiles/firedepots_valid.xml";
		invalidFireDepots = "XML-testfiles/firedepots_invalid.xml";

		validPoliceDepots = "XML-testfiles/policedepots_valid.xml";
		invalidPoliceDepots = "XML-testfiles/policedepots_invalid.xml";

		validShops = "XML-testfiles/shop_valid.xml";
		invalidShops = "XML-testfiles/shop_invalid.xml";

		validHospitals = "XML-testfiles/hospital_valid.xml";
		invalidHospitals = "XML-testfiles/hospital_invalid.xml";

		validAmbulances = "XML-testfiles/ambulance_valid.xml";
		invalidAmbulances = "XML-testfiles/ambulance_invalid.xml";

		validFireTrucks = "XML-testfiles/firetrucks_valid.xml";
		invalidFireTrucks = "firetrucks_invalid.xml";

		validPoliceTrucks = "XML-testfiles/policetrucks_valid.xml";
		invalidPoliceTrucks = "XML-testfiles/policetrucks_invalid.xml";

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
		std::cout << "Kan " << invalidStreets << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseStreet(node));
		}
	}
}

TEST_F(CityParserTest, validHouses) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validHouses.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validHouses << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseHouse(node));
		}
	}
}

TEST_F(CityParserTest, invalidHouses) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidHouses.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidHouses << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseHouse(node));
		}
	}
}


TEST_F(CityParserTest, validFireDepots) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validFireDepots.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validFireDepots << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseFireDepot(node));
		}
	}
}

TEST_F(CityParserTest, invalidFireDepots) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidFireDepots.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidFireDepots << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseFireDepot(node));
		}
	}
}

TEST_F(CityParserTest, validPoliceDepots) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validPoliceDepots.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validPoliceDepots << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parsePoliceDepot(node));
		}
	}
}

TEST_F(CityParserTest, invalidPoliceDepots) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidPoliceDepots.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidPoliceDepots << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parsePoliceDepot(node));
		}
	}
}

TEST_F(CityParserTest, validShops) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validShops.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validShops << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseShop(node));
		}
	}
}

TEST_F(CityParserTest, invalidShops) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidShops.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidShops << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseShop(node));
		}
	}
}

TEST_F(CityParserTest, validHospitals) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validHospitals.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validHospitals << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseHospital(node));
		}
	}
}

TEST_F(CityParserTest, invalidHospitals) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidHospitals.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidHospitals << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseHospital(node));
		}
	}
}

TEST_F(CityParserTest, validAmbulances) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validAmbulances.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validAmbulances << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseAmbulance(node));
		}
	}
}

TEST_F(CityParserTest, invalidAmbulances) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidAmbulances.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidAmbulances << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseAmbulance(node));
		}
	}
}

TEST_F(CityParserTest, validFireTrucks) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validFireTrucks.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validFireTrucks << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parseFireTruck(node));
		}
	}
}

TEST_F(CityParserTest, invalidFireTrucks) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidFireTrucks.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidFireTrucks << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parseFireTruck(node));
		}
	}
}

TEST_F(CityParserTest, validPoliceTrucks) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(validPoliceTrucks.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << validPoliceTrucks << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_TRUE(parser.parsePoliceTruck(node));
		}
	}
}

TEST_F(CityParserTest, invalidPoliceTrucks) {
	CityParser parser(ptrCity);

	TiXmlDocument doc;
	if (!doc.LoadFile(invalidPoliceTrucks.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		EXIT_FAILURE;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan " << invalidPoliceTrucks << " niet laden: geen root element." << std::endl;
		EXIT_FAILURE;
	}
	else {
		for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
			EXPECT_FALSE(parser.parsePoliceTruck(node));
		}
	}
}
