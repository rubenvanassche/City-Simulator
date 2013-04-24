/*
 * CityParser.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef CITYPARSER_H_
#define CITYPARSER_H_

#include "tinyxml.h"
#include "City.h"
#include "DesignByContract.h"

class CityParser {
public:
	bool isInitialized() const;

	CityParser(City* town);
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");
	// ENSURE(this->fTown == town, "Town is set");
	// ENSURE(this->isInitialized(), "Parser is initialized()");

	void parseStreet(TiXmlElement* node);
	// parse one street
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseHouse(TiXmlElement* node);
	// parse one house
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseFireDepot(TiXmlElement* node);
	// parse one firedepot
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseHospital(TiXmlElement* node);
	// parse one hosiptal
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parsePoliceDepot(TiXmlElement* node);
	// parse one policedepot
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseShop(TiXmlElement* node);
	// parse one shop
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseFireTruck(TiXmlElement* node);
	// parse one firetruck
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseAmbulance(TiXmlElement* node);
	// parse one ambulance
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parsePoliceCar(TiXmlElement* node);
	// parse one ambulance
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseBuildings(const char* filename);
	// parse all buildings and street
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	void parseVehicles(const char* filename);
	// parse all vehicles
	// REQUIRE(this->isInitialized(), "Parser is initialized");

private:
	std::string toLower(const std::string& str);

	City* fTown;

	CityParser* fMyself;
};

#endif /* CITYPARSER_H_ */
