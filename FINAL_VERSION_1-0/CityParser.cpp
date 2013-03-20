/*
 * CityParser.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "CityParser.h"
#include <fstream>
#include "tinyxml.h"
#include <sstream>
#include "FireDepot.h"
#include "FireTruck.h"
#include "Street.h"
#include "House.h"
#include "Size.h"

namespace CityParser {

City* parse(std::string& filename) {
	const char* charInput = filename.c_str();
	TiXmlDocument doc;
	if(!doc.LoadFile(charInput) ) {
		std::cerr << doc.ErrorDesc() << std::endl;
		City* c = new City;
		return c;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load file: no root element" << std::endl;
		City* c = new City;
		doc.Clear();
		return c;
	}

	City* town = new City;

	for (TiXmlElement* node=root->FirstChildElement(); node != NULL; node = node->NextSiblingElement() ) {
		std::string tag = node->Value();
		for (unsigned int index=0; index < tag.size(); index++) {
			tag[index] = std::tolower(tag[index]);	// make them lowercase
		}

		if (tag == "brandweerkazerne") {
			std::string name;
			std::stringstream xLocation;
			std::stringstream yLocation;
			std::stringstream xEntrance;
			std::stringstream yEntrance;

			for (TiXmlElement* subnode=node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
				std::string subtag = subnode->Value();
				for (unsigned int index=0; index < subtag.size(); index++) {
					subtag[index] = std::tolower(subtag[index]);
				}

				if (subtag == "naam") {
					name = subnode->GetText();
				}
				else if (subtag == "locatie") {
					xLocation << subnode->Attribute("X");
					if (xLocation.str() == "") {
						std::cout << "Did not find X-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}

					yLocation << subnode->Attribute("Y");
					if (yLocation.str() == "") {
						std::cout << "Did not find Y-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}
				}
				else if (subtag == "ingang") {
					xEntrance << subnode->Attribute("X");
					if (xEntrance.str() == "") {
						std::cout << "Did not find X-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}

					yEntrance << subnode->Attribute("Y");
					if (yEntrance.str() == "") {
						std::cout << "Did not find Y-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}
				}
				else {
					std::cout << "Subtag " << subtag << " of " << tag << " not recognized." << std::endl;
					std::cout << "\t" << subtag << " ignored" << std::endl;
				}
			}

			int xLoc;
			int yLoc;
			int xEntr;
			int yEntr;
			xLocation >> xLoc;
			yLocation >> yLoc;
			xEntrance >> xEntr;
			yEntrance >> yEntr;

			Point location(xLoc, yLoc);
			Point entrance(xEntr, yEntr);
			Size size(4);
			FireDepot newDepot(name, location, size, entrance);

			if (!town->addFireDepot(newDepot)) {
				std::cout << "Can not add FireDepot " << name << std::endl;
			}
		}

		else if (tag == "brandweerwagen") {
			std::string name;
			std::string base;
			for (TiXmlElement* subnode=node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
				std::string subtag = subnode->Value();
				for (unsigned int index=0; index < subtag.size(); index++) {
					subtag[index] = std::tolower(subtag[index]);
				}

				if (subtag == "naam") {
					name = subnode->GetText();
				}
				else if (subtag == "basis") {
					base = subnode->GetText();
				}
				else {
					std::cout << "Subtag " << subtag << " of " << tag << " not recognized." << std::endl;
					std::cout << "\t" << subtag << " ignored" << std::endl;
				}
			}

			Point curPos(0, 0);
			Point destination(0, 0);
			FireTruck newTruck(name, curPos, destination, base);

			if (!town->addFireTruck(newTruck)) {
				delete town;
				std::cerr << "Can not add FireTruck" << name << std::endl;
				City* c = new City;
				return c;
			}
		}

		else if (tag == "straat") {
			std::string name;
			std::stringstream xFrom;
			std::stringstream yFrom;
			std::stringstream xTo;
			std::stringstream yTo;

			for (TiXmlElement* subnode=node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
				std::string subtag = subnode->Value();
				for (unsigned int index=0; index < subtag.size(); index++) {
					subtag[index] = std::tolower(subtag[index]);
				}

				if (subtag == "naam") {
					name = subnode->GetText();
				}
				else if (subtag == "van") {
					xFrom << subnode->Attribute("x");
					if (xFrom.str() == "") {
						std::cout << "Did not find x-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}

					yFrom << subnode->Attribute("y");
					if (yFrom.str() == "") {
						std::cout << "Did not find y-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}
				}
				else if (subtag == "naar") {
					xTo << subnode->Attribute("x");
					if (xTo.str() == "") {
						std::cout << "Did not find x-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}

					yTo << subnode->Attribute("y");
					if (yTo.str() == "") {
						std::cout << "Did not find y-attribute of " << subtag << " of " << tag << " " << name << std::endl;
						std::cout << "\t" << tag << " " << name << " skipped" << std::endl;
						break;
					}
				}
				else {
					std::cout << "Subtag " << subtag << " of " << tag << " not recognized." << std::endl;
					std::cout << "\t" << subtag << " ignored" << std::endl;
				}
			}

			int xStart;
			int yStart;
			int xEnd;
			int yEnd;
			xFrom >> xStart;
			yFrom >> yStart;
			xTo >> xEnd;
			yTo >> yEnd;

			Point startPoint(xStart, yStart);
			Point endPoint(xEnd, yEnd);
			Street newStreet(name, startPoint, endPoint);

			if (!town->addStreet(newStreet)) {
				std::cout << "Can not add Street " << name << std::endl;
			}
		}

		if (tag == "huis") {
			std::stringstream xLocation;
			std::stringstream yLocation;
			std::string flammability;

			for (TiXmlElement* subnode=node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
				std::string subtag = subnode->Value();
				for (unsigned int index=0; index < subtag.size(); index++) {
					subtag[index] = std::tolower(subtag[index]);
				}

				if (subtag == "brandbaarheid") {
					flammability = subnode->GetText();
				}
				else if (subtag == "locatie") {
					xLocation << subnode->Attribute("X");
					if (xLocation.str() == "") {
						std::cout << "Did not find X-attribute of " << subtag << " of " << tag << std::endl;
						std::cout << "\t" << tag << " skipped" << std::endl;
						break;
					}

					yLocation << subnode->Attribute("Y");
					if (yLocation.str() == "") {
						std::cout << "Did not find Y-attribute of " << subtag << " of " << tag << std::endl;
						std::cout << "\t" << tag << " skipped" << std::endl;
						break;
					}
				}
				else {
					std::cout << "Subtag " << subtag << " of " << tag << " not recognized." << std::endl;
					std::cout << "\t" << subtag << " ignored" << std::endl;
				}
			}

			int xLoc;
			int yLoc;
			int hPoints;
			std::stringstream ss;
			xLocation >> xLoc;
			yLocation >> yLoc;
			ss << flammability;
			ss >> hPoints;

			Point location(xLoc, yLoc);
			Size size(2);
			House newHouse(location, size, hPoints);

			if (!town->addHouse(newHouse)) {
				std::cout << "Can not add House " << std::endl;
			}
		}
	}

	doc.Clear();
	return town;
}

} /* namespace CityParser */
