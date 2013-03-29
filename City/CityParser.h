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

class CityParser {
public:
	CityParser(City* town);

	bool parseBuildings(const char* filename);
	// parse buildings and streets

	bool parseHouse(TiXmlElement* node);
	// parse one house

	bool parseStreet(TiXmlElement* node);
	// parse one street

	bool parseFireDepot(TiXmlElement* node);
	// parse one firedepot

	bool parseFireTruck(TiXmlElement* node);
	// parse one truck

private:
	City* fTown;

};

#endif /* CITYPARSER_H_ */
