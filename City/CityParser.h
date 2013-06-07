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
#include <string>
#include "Output.h"

class CityParser {
public:
	bool isInitialized() const;

	CityParser(City* town, Output* out);
	// constructor
	// REQUIRE(town->isInitialized(), "City is initialized");
	// REQUIRE(out->isInitialized(), "Output is initialized");
	// ENSURE(this->fTown == town, "Town is set");
	// ENSURE(this->isInitialized(), "Parser is initialized()");

	bool parseStreet(TiXmlElement* node);
	// parse one street
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseHouse(TiXmlElement* node);
	// parse one house
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseFireDepot(TiXmlElement* node);
	// parse one firedepot
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseHospital(TiXmlElement* node);
	// parse one hosiptal
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parsePoliceDepot(TiXmlElement* node);
	// parse one policedepot
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseShop(TiXmlElement* node);
	// parse one shop
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseFireTruck(TiXmlElement* node);
	// parse one firetruck
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseAmbulance(TiXmlElement* node);
	// parse one ambulance
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parsePoliceTruck(TiXmlElement* node);
	// parse one ambulance
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseBuildings(const std::string& filename);
	// parse all buildings and street
	// REQUIRE(this->isInitialized(), "Parser is initialized");

	bool parseVehicles(const std::string& filename);
	// parse all vehicles
	// REQUIRE(this->isInitialized(), "Parser is initialized");

private:
	std::string toLower(const std::string& str);

	City* fTown;
	Output* fOut;

	CityParser* fMyself;
};

#endif /* CITYPARSER_H_ */
