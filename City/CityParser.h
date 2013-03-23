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

class CityParser {
public:
	CityParser(const char* filename);

	bool parseAll();
	bool parseHouse(TiXmlElement* node);
	bool parseStreet(TiXmlElement* node);
	bool parseFireDepot(TiXmlElement* node);
	bool parseFireTruck(TiXmlElement* node);

private:
	const char* fFileName;

};

#endif /* CITYPARSER_H_ */
