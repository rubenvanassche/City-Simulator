/*
 * CityParser.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Sunday 10 March 2013
 * 
 */

#include "CityParser.h"
//#include "City.h"
#include "Point.h"
#include "Street.h"
#include "Fire.h"
#include "tinyxml.h"
#include <sstream>
#include "House.h"

namespace CityParser {

void getCity(const std::string& filename) {
	TiXmlDocument doc;
	const char* input = filename.c_str();
	if (!doc.LoadFile(input)) {
		std::cerr << doc.ErrorDesc() << std::endl;
		return;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load file: No root element." <<std::endl;
		doc.Clear();
		return;
	}

//	City city;
	int nrHouse = 0;
	int nrFireDepot = 0;
	int nrStreet = 0;
	for(TiXmlElement* node=root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
		std::string tag = node->Value();
		if (tag == "Huis") {
			nrHouse++;
			TiXmlElement* location = node->FirstChildElement("Locatie");
			TiXmlElement* flamable = node->FirstChildElement("Brandbaarheid");

			std::stringstream xx;
			xx << location->Attribute("X");
			int xValue;
			xx >> xValue;
			if (xValue < 0) {
				std::cout << "Invalid x-value, House object " << nrHouse << " is skipped." << std::endl;
				continue;
			}

			std::stringstream yy;
			yy << location->Attribute("Y");
			int yValue;
			yy >> yValue;
			if (yValue < 0) {
				std::cout << "Invalid x-value, House object " << nrHouse << " is skipped." << std::endl;
				continue;
			}

			std::stringstream ff;
			ff << flamable->GetText();
			int fValue;
			ff >> fValue;
			if (fValue < 0) {
				std::cout << "Invalid x-value, House object " << nrHouse << " is skipped." << std::endl;
				continue;
			}

			Point loc(xValue, yValue);
			House newHouse(loc, fValue);
//			city.addHouse(newHouse);
		}
		else if (tag == "Straat") {
			nrStreet++;
			TiXmlElement* name = node->FirstChildElement("Naam");
			TiXmlElement* from = node->FirstChildElement("Van");
			TiXmlElement* to = node->FirstChildElement("Naar");

			std::string streetname = name->GetText();

			std::stringstream xx0;
			xx0 << from->Attribute("x");
			int x0Value;
			xx0 >> x0Value;
			if (x0Value < 0) {
				std::cout << "Invalid to x-value, Street object " << nrStreet << " is skipped." << std::endl;
				continue;
			}

			std::stringstream yy0;
			yy0 << from->Attribute("y");
			int y0Value;
			yy0 >> y0Value;
			if (y0Value < 0) {
				std::cout << "Invalid from y-value, Street object " << nrStreet << " is skipped." << std::endl;
				continue;
			}

			std::stringstream xx1;
			xx1 << to->Attribute("x");
			int x1Value;
			xx1 >> x1Value;
			if (x1Value < 0) {
				std::cout << "Invalid to x-value, Street object " << nrStreet << " is skipped." << std::endl;
				continue;
			}

			std::stringstream yy1;
			yy1 << to->Attribute("y");
			int y1Value;
			yy1 >> y0Value;
			if (y1Value < 0) {
				std::cout << "Invalid to y-value, Street object " << nrStreet << " is skipped." << std::endl;
				continue;
			}

			Point fromValue(x0Value, y0Value);
			Point toValue(x1Value, y1Value);
			Street newStreet(fromValue, toValue, streetname);
//			city.addStreet(newStreet);
		}
		else if (tag == "Brandweerkazerne") {
			nrFireDepot++;
			TiXmlElement* name = node->FirstChildElement("Naam");
			TiXmlElement* location = node->FirstChildElement("Locatie");
			TiXmlElement* entrance = node->FirstChildElement("Ingang");

			std::string depotname = name->GetText();

			std::stringstream xx0;
			xx0 << location->Attribute("X");
			int x0Value;
			xx0 >> x0Value;
			if (x0Value < 0) {
				std::cout << "Invalid location x-value, FireDepot object " << nrFireDepot << " is skipped." << std::endl;
				continue;
			}

			std::stringstream yy0;
			yy0 << location->Attribute("Y");
			int y0Value;
			yy0 >> y0Value;
			if (y0Value < 0) {
				std::cout << "Invalid location y-value, FireDepot object " << nrFireDepot << " is skipped." << std::endl;
				continue;
			}

			std::stringstream xx1;
			xx1 << entrance->Attribute("X");
			int x1Value;
			xx1 >> x1Value;
			if (x1Value < 0) {
				std::cout << "Invalid entrance x-value, FireDepot object " << nrFireDepot << " is skipped." << std::endl;
				continue;
			}

			std::stringstream yy1;
			yy1 << entrance->Attribute("Y");
			int y1Value;
			yy1 >> y0Value;
			if (y1Value < 0) {
				std::cout << "Invalid location y-value, FireDepot object " << nrFireDepot << " is skipped." << std::endl;
				continue;
			}

			Point loc(x0Value, y0Value);
			Point entr(x1Value, y1Value);
			FireDepot newDepot(depotname, loc, entr);
//			city.addFireDepot(newDepot);
		}
		else if (tag == "Brandweerwagen") {
			TiXmlElement* name = node->FirstChildElement("Naam");
			TiXmlElement* base = node->FirstChildElement("Basis");

			std::string nameValue = name->GetText();
			std::string basename = base->GetText();

//			city.addFireTruck(nameValue, baseName);
		}
		else {
			std::cout << "Tag " << tag << " not recognized, skipped." << std::endl;
			continue;
		}
	}

	doc.Clear();
	return;

	return;
}

} /* namespace CityParser */


int main() {
	CityParser::getCity("stad.xml");
	return 0;
}
