/*
 * CityParser.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "CityParser.h"
#include <iostream>
#include <sstream>

CityParser::CityParser(const char* filename) {
	CityParser::fFileName = filename;
}

bool CityParser::parseAll() {
	TiXmlDocument doc;
	if (!doc.LoadFile(CityParser::fFileName)) {
		std::cerr << doc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load file: no root element" << std::endl;
		return false;
	}

	for (TiXmlElement* node=root->FirstChildElement(); node != NULL; node = node->NextSiblingElement() ) {
		std::string tag = node->Value();
		for (unsigned int index=0; index < tag.size(); index++) {
			tag[index] = std::tolower(tag[index]);
		}

		if (tag == "huis") {
			if (!CityParser::parseHouse(node) ) {
				std::cout << "Cannot add " << tag << ", skipped." << std::endl;
			}
		}
		else if (tag == "straat") {
			if (!CityParser::parseStreet(node) ) {
				std::cout << "Cannot add " << tag << ", skipped." << std::endl;
			}
		}
		else if (tag == "brandweerkazerne") {
			if (!CityParser::parseFireDepot(node) ) {
				std::cout << "Cannot add " << tag << ", skipped." << std::endl;
			}
		}
		else if (tag == "brandweerwagen") {
			if (!CityParser::parseFireTruck(node) ) {
				std::cout << "Cannot add " << tag << ", skipped." << std::endl;
			}
		}
		else {
			std::cout << "Tag " << tag << " not recognized, skipped." << std::endl;
		}
	}

	doc.Clear();
	return true;
}

bool CityParser::parseHouse(TiXmlElement* node) {
	bool xLocFound =  false;
	bool yLocFound = false;
	bool flamFound = false;
	int xLocation;
	int yLocation;
	int flammability;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = subnode->Value();
		for (unsigned int index = 0; index < subtag.size(); index++) {
			subtag[index] = std::tolower(subtag[index]);
		}

		if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next() ) {
				std::string attrName = attr->Name();
				for (unsigned int index=0; index < attrName.size(); index++) {
					attrName[index] = std::tolower(attrName[index]);
				}

				if (attrName == "x") {
					xLocation = attr->IntValue();
					xLocFound = true;
				}
				else if (attrName == "y") {
					yLocation = attr->IntValue();
					yLocFound = true;
				}
				else {
					std::cout << "Unknown attribute " << attrName << " of " << subtag << " skipped." << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			std::string fl = subnode->GetText();
			std::stringstream ss;
			ss << fl;
			ss >> flammability;
			flamFound = true;
		}
		else {
			std::cout << "Unknown subtag " << subtag << " skipped." << std::endl;
		}
	}

	if (!xLocFound) {
		std::cout << "x location missing." << std::endl;
		return false;
	}

	if (!yLocFound) {
		std::cout << "y location missing." << std::endl;
		return false;
	}

	if (!flamFound) {
		std::cout << "Flammability missing." << std::endl;
		return false;
	}

	if (xLocation < 0) {
		std::cout << "Invalid x-coordinate." << std::endl;
		return false;
	}

	if (yLocation < 0) {
		std::cout << "Invalid y-coordinate." << std::endl;
		return false;
	}

	if (flammability < 0) {
		std::cout << "Invalid flammability." << std::endl;
	}

	std::cout << "House on (" << xLocation << ", " << yLocation << ") with flammability " << flammability << " created." << std::endl;

	return true;
}

bool CityParser::parseStreet(TiXmlElement* node) {
	bool xFromFound =  false;
	bool yFromFound = false;
	bool xToFound = false;
	bool yToFound = false;
	int xFrom;
	int yFrom;
	int xTo;
	int yTo;
	std::string name = "";

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = subnode->Value();
		for (unsigned int index = 0; index < subtag.size(); index++) {
			subtag[index] = std::tolower(subtag[index]);
		}

		if (subtag == "van") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next() ) {
				std::string attrName = attr->Name();
				for (unsigned int index=0; index < attrName.size(); index++) {
					attrName[index] = std::tolower(attrName[index]);
				}

				if (attrName == "x") {
					xFrom = attr->IntValue();
					xFromFound = true;
				}
				else if (attrName == "y") {
					yFrom = attr->IntValue();
					yFromFound = true;
				}
				else {
					std::cout << "Unknown attribute " << attrName << " of " << subtag << " skipped." << std::endl;
				}
			}
		}
		else if (subtag == "naar") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next() ) {
				std::string attrName = attr->Name();
				for (unsigned int index=0; index < attrName.size(); index++) {
					attrName[index] = std::tolower(attrName[index]);
				}

				if (attrName == "x") {
					xTo = attr->IntValue();
					xToFound = true;
				}
				else if (attrName == "y") {
					yTo= attr->IntValue();
					yToFound = true;
				}
				else {
					std::cout << "Unknown attribute " << attrName << " of " << subtag << " skipped." << std::endl;
				}
			}
		}
		else if (subtag == "naam") {
			name = subnode->GetText();
		}
		else {
			std::cout << "Unknown subtag " << subtag << " skipped." << std::endl;
		}
	}

	if (!xFromFound) {
		std::cout << "x location missing (van)." << std::endl;
		return false;
	}

	if (!yFromFound) {
		std::cout << "y location missing (van)." << std::endl;
		return false;
	}

	if (!xToFound) {
		std::cout << "x location missing (naar)." << std::endl;
		return false;
	}

	if (!yToFound) {
		std::cout << "y location missing (naar)." << std::endl;
		return false;
	}

	if (name == "") {
		std::cout << "name missing." << std::endl;
		return false;
	}

	if (xFrom < 0) {
		std::cout << "Invalid x-coordinate (van)." << std::endl;
		return false;
	}

	if (yFrom < 0) {
		std::cout << "Invalid y-coordinate (van)." << std::endl;
		return false;
	}

	if (xTo < 0) {
		std::cout << "Invalid x-coordinate (naar)." << std::endl;
		return false;
	}

	if (yTo < 0) {
		std::cout << "Invalid y-coordinate (naar)." << std::endl;
		return false;
	}

	std::cout << "Street " << name << " from (" << xFrom << ", " << yFrom << ") to (" << xTo << ", " << yTo << ") created." << std::endl;

	return true;
}

bool CityParser::parseFireDepot(TiXmlElement* node) {
	bool xLocFound =  false;
	bool yLocFound = false;
	bool xEntrFound = false;
	bool yEntrFound = false;
	int xLoc;
	int yLoc;
	int xEntr;
	int yEntr;
	std::string name = "";

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = subnode->Value();
		for (unsigned int index = 0; index < subtag.size(); index++) {
			subtag[index] = std::tolower(subtag[index]);
		}

		if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next() ) {
				std::string attrName = attr->Name();
				for (unsigned int index=0; index < attrName.size(); index++) {
					attrName[index] = std::tolower(attrName[index]);
				}

				if (attrName == "x") {
					xLoc = attr->IntValue();
					xLocFound = true;
				}
				else if (attrName == "y") {
					yLoc = attr->IntValue();
					yLocFound = true;
				}
				else {
					std::cout << "Unknown attribute " << attrName << " of " << subtag << " skipped." << std::endl;
				}
			}
		}
		else if (subtag == "ingang") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next() ) {
				std::string attrName = attr->Name();
				for (unsigned int index=0; index < attrName.size(); index++) {
					attrName[index] = std::tolower(attrName[index]);
				}

				if (attrName == "x") {
					xEntr = attr->IntValue();
					xEntrFound = true;
				}
				else if (attrName == "y") {
					yEntr= attr->IntValue();
					yEntrFound = true;
				}
				else {
					std::cout << "Unknown attribute " << attrName << " of " << subtag << " skipped." << std::endl;
				}
			}
		}
		else if (subtag == "naam") {
			name = subnode->GetText();
		}
		else {
			std::cout << "Unknown subtag " << subtag << " skipped." << std::endl;
		}
	}

	if (!xLocFound) {
		std::cout << "x location missing (locatie)." << std::endl;
		return false;
	}

	if (!yLocFound) {
		std::cout << "y location missing (locatie)." << std::endl;
		return false;
	}

	if (!xEntrFound) {
		std::cout << "x location missing (ingang)." << std::endl;
		return false;
	}

	if (!yEntrFound) {
		std::cout << "y location missing (ingang)." << std::endl;
		return false;
	}

	if (name == "") {
		std::cout << "name missing." << std::endl;
		return false;
	}

	if (xLoc < 0) {
		std::cout << "Invalid x-coordinate (locatie)." << std::endl;
		return false;
	}

	if (yLoc < 0) {
		std::cout << "Invalid y-coordinate (locatie)." << std::endl;
		return false;
	}

	if (xEntr < 0) {
		std::cout << "Invalid x-coordinate (ingang)." << std::endl;
		return false;
	}

	if (yEntr < 0) {
		std::cout << "Invalid y-coordinate (ingang)." << std::endl;
		return false;
	}

	std::cout << "FireDepot " << name << " location (" << xLoc << ", " << yLoc << "), entrance (" << xEntr << ", " << yEntr << ") created." << std::endl;

	return true;
}

bool CityParser::parseFireTruck(TiXmlElement* node) {
	bool nameFound =  false;
	bool baseFound = false;
	std::string name = "";
	std::string base = "";

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = subnode->Value();
		for (unsigned int index = 0; index < subtag.size(); index++) {
			subtag[index] = std::tolower(subtag[index]);
		}

		if (subtag == "naam") {
			name = subnode->GetText();
			nameFound = true;
		}
		else if (subtag == "basis") {
			base = subnode->GetText();
			baseFound = true;
		}
		else {
			std::cout << "Unknown subtag " << subtag << " skipped." << std::endl;
		}
	}

	if (!nameFound) {
		std::cout << "name missing." << std::endl;
		return false;
	}

	if (!baseFound) {
		std::cout << "base missing." << std::endl;
		return false;
	}

	std::cout << "FireTruck " << name << " with base " << base << " created." << std::endl;
	return true;
}
