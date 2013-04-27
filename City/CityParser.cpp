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

bool CityParser::isInitialized() const {
	return this == fMyself;
}

CityParser::CityParser(City* town) {
	REQUIRE(town->isInitialized(), "City is initialized");

	fTown = town;
	fMyself = this;

	ENSURE(this->fTown == town, "Town is set");
	ENSURE(this->isInitialized(), "Parser is initialized()");
}

std::string CityParser::toLower(const std::string& str) {
	std::string lower;
	for (unsigned int index = 0; index < str.size(); index++) {
		lower += std::tolower(str[index]);
	}

	return lower;
}

bool CityParser::parseStreet(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundX0 = false;
	bool foundY0 = false;
	bool foundX1 = false;
	bool foundY1 = false;
	bool foundName = false;

	int x0, y0, x1, y1;
	std::string name;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "van") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				if (attrName == "x") {
					foundX0 = true;
					x0 = attr->IntValue();
				}
				else if (attrName == "y") {
					foundY0 = true;
					y0 = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "naar") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundX1 = true;
					x1 = attr->IntValue();
				}
				else if (attrName == "y") {
					foundY1 = true;
					y1 = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Naam van straat ontbreekt." << std::endl;
				return false;
			}

			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van straat ontbreekt." << std::endl;
		return false;
	}
	else if ( (!foundX0) || (x0 < 0) ) {
		std::cout << "X coordinaat van startpositie van straat " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundY0) || (y0 <0) ){
		std::cout << "Y coordinaat van startpositie van straat " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundX1) || (x1 < 0) ) {
		std::cout << "X coordinaat van eindpositie van straat " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundY1) || (y1 < 0) ) {
		std::cout << "Y coordinaat van eindpositie van straat" << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		Street newStr(name, Point(x0, y0), Point(x1, y1));
		if (!fTown->add(newStr) ) {
			std::cout << "Kan " << newStr << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseHouse(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundX = false;
	bool foundY = false;
	bool foundFlam = false;

	int x, y, flam;
	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundX = true;
					x = attr->IntValue();
				}
				else if (attrName == "y") {
					foundY = true;
					y = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Brandbaarheid van huis ontbreekt." << std::endl;
				return false;
			}

			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if ( (!foundX) || (x < 0) ) {
		std::cout << "X coordinaat van huis ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundY) || (y <0) ){
		std::cout << "Y coordinaat van huis ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if (!foundFlam) {
		std::cout << "Brandbaarheid van huis ontbreekt." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		House newHouse(Point(x, y), flam);
		if (!fTown->add(newHouse)) {
			std::cout << "Kan " << newHouse << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseFireDepot(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundXLoc = false;
	bool foundYLoc = false;
	bool foundXEntr = false;
	bool foundYEntr = false;
	bool foundFlam = false;

	std::string name;
	int xLoc, yLoc, xEntr, yEntr, flam;
	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Naam van brandweerkazerne ontbreekt." << std::endl;
				return false;
			}

			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXLoc = true;
					xLoc = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYLoc = true;
					yLoc = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "ingang") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXEntr = true;
					xEntr = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYEntr = true;
					yEntr = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van brandweerkazerne ontbreekt." << std::endl;
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::cout << "X coordinaat van brandweerkazerne " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::cout << "Y coordinaat van brandweerkazerne " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::cout << "X coordinaat van ingang brandweerkazerne " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::cout << "Y coordinaat van ingang brandweerkazerne " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::cout << "Brandbaarheid van brandweerkazerne " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		FireDepot newDepot(Point(xLoc, yLoc), Point(xEntr, yEntr), name, flam);
		if (!fTown->add(newDepot) ) {
			std::cout << "Kan " << newDepot << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseHospital(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundXLoc = false;
	bool foundYLoc = false;
	bool foundXEntr = false;
	bool foundYEntr = false;
	bool foundFlam = false;
	bool foundWidth = false;
	bool foundHeight = false;

	std::string name;
	int xLoc, yLoc, xEntr, yEntr, flam, width, height;
	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText()) {
				std::cout << "Naam van ziekenhuis ontbreekt" << std::endl;
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXLoc = true;
					xLoc = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYLoc = true;
					yLoc = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "ingang") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXEntr = true;
					xEntr = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYEntr = true;
					yEntr = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Brandbaarheid van ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "grootte") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "hoogte") {
					foundHeight = true;
					height = attr->IntValue();
				}
				else if (attrName == "breedte") {
					foundWidth = true;
					width = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van ziekenhuis ontbreekt" << std::endl;
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::cout << "X coordinaat van ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::cout << "Y coordinaat van ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::cout << "X coordinaat van ingang ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::cout << "Y coordinaat van ingang ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::cout << "Brandbaarheid van ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::cout << "Breedte van ziekenhuis " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::cout<< "Hoogte van ziekenhuis " << name << "ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		Hospital newHospital(Point(xLoc, yLoc), Point(xEntr, yEntr), Size(width, height), name, flam);
		if (!fTown->add(newHospital) ) {
			std::cout << "Kan " << newHospital << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parsePoliceDepot(TiXmlElement* node) {
	bool foundName = false;
	bool foundXLoc = false;
	bool foundYLoc = false;
	bool foundXEntr = false;
	bool foundYEntr = false;
	bool foundFlam = false;
	bool foundWidth = false;
	bool foundHeight = false;

	std::string name;
	int xLoc, yLoc, xEntr, yEntr, flam, width, height;
	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Naam van politiebureau ontbreekt" << std::endl;
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXLoc = true;
					xLoc = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYLoc = true;
					yLoc = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "ingang") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundXEntr = true;
					xEntr = attr->IntValue();
				}
				else if (attrName == "y") {
					foundYEntr = true;
					yEntr = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Brandbaarheid van politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "grootte") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "hoogte") {
					foundHeight = true;
					height = attr->IntValue();
				}
				else if (attrName == "breedte") {
					foundWidth = true;
					width = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van politiebureau ontbreekt" << std::endl;
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::cout << "X coordinaat van politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::cout << "Y coordinaat van politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::cout << "X coordinaat van ingang politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::cout << "Y coordinaat van ingang politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::cout << "Brandbaarheid van politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::cout << "Breedte van politiebureau " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::cout<< "Hoogte van politiebureau " << name << "ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		PoliceDepot newDepot(Point(xLoc, yLoc), Point(xEntr, yEntr), Size(width, height), name, flam);
		if (!fTown->add(newDepot) ) {
			std::cout << "Kan " << newDepot << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseShop(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundX = false;
	bool foundY = false;
	bool foundFlam = false;
	bool foundSec = false;
	bool foundHeight = false;
	bool foundWidth = false;

	int x, y, flam, security, height, width;
	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "locatie") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "x") {
					foundX = true;
					x = attr->IntValue();
				}
				else if (attrName == "y") {
					foundY = true;
					y = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Brandbaarheid van winkel ontbreekt/ongeldig." << std::endl;
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "grootte") {
			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());

				if (attrName == "hoogte") {
					foundHeight = true;
					height = attr->IntValue();
				}
				else if (attrName == "breedte") {
					foundWidth = true;
					width = attr->IntValue();
				}
				else {
					std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
				}
			}
		}
		else if (subtag == "overvalbaarheid") {
			foundSec = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Overvalbaarheid van winkel ontbreekt/ongeldig." << std::endl;
				return false;
			}
			security = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if ( (!foundX) || (x < 0) ) {
		std::cout << "X coordinaat van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundY) || (y <0) ){
		std::cout << "Y coordinaat van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::cout << "Brandbaarheid van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::cout << "Breedte van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::cout << "Hoogte van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundSec) || (security < 0) ) {
		std::cout << "Overvalbaarheid van winkel ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		Shop newShop(Point(x, y), Size(width, height), flam, security);
		if (!fTown->add(newShop) ) {
			std::cout << "Kan " << newShop << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseFireTruck(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundBase = false;

	std::string name;
	FireDepot* ptrBase;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Naam van brandweerwagen ontbreekt/ongeldig." << std::endl;
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Basis van brandweerwagen " << name << " ontbreekt/ongeldig." << std::endl;
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findFireDepot(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van brandweerwagen ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::cout << "Basis van brandweerwagen " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		FireTruck newTruck(name, ptrBase);
		if (!fTown->add(newTruck) ) {
			std::cout << "Kan " << newTruck << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseAmbulance(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundBase = false;

	std::string name;
	Hospital* ptrBase;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Naam van ambulance ontbreekt/ongeldig." << std::endl;
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Basis van ambulance " << name << " ontbreekt/ongeldig." << std::endl;
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findHospital(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van ambulance ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::cout << "Basis van ambulance " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		Ambulance newAmbuce(name, ptrBase);
		if (!fTown->add(newAmbuce) ) {
			std::cout << "Kan " << newAmbuce << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parsePoliceCar(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundBase = false;

	std::string name;
	PoliceDepot* ptrBase;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText()) {
				std::cout << "Naam van politiewagen ontbreekt/ongeldig." << std::endl;
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::cout << "Basis van politiewagen " << name << " ontbreekt/ongeldig." << std::endl;
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findPoliceDepot(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::cout << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen" << std::endl;
			}
		}
		else {
			std::cout << "Onbekende tag " << subtag << " overgeslagen." << std::endl;
		}
	}

	if (!foundName) {
		std::cout << "Naam van politiewagen ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::cout << "Basis van politiewagen " << name << " ontbreekt/ongeldig." << std::endl;
		return false;
	}
	else {
		// all attributes are ok
		PoliceTruck newTruck(name, ptrBase);
		if (!fTown->add(newTruck) ) {
			std::cout << "Kan " << newTruck << " niet toevoegen." << std::endl;
			return false;
		}
		return true;
	}
}

bool CityParser::parseBuildings(const std::string& filename) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan file niet laden: geen root element." << std::endl;
		return false;
	}

	for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
		std::string tag = CityParser::toLower(node->Value());

		if (tag == "huis") {
			this->parseHouse(node);
		}
		else if (tag == "straat") {
			this->parseStreet(node);
		}
		else if (tag == "brandweerkazerne") {
			this->parseFireDepot(node);
		}
		else if (tag == "winkel") {
			this->parseShop(node);
		}
		else if (tag == "politiebureau") {
			this->parsePoliceDepot(node);
		}
		else if (tag == "ziekenhuis") {
			this->parseHospital(node);
		}
		else {
			std::cout << "Onbekende tag " << tag << " overgeslagen." << std::endl;
		}
	}

	return true;
}

bool CityParser::parseVehicles(const std::string& filename) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::cout << "Kan file niet laden: geen root element." << std::endl;
		return false;
	}

	for (TiXmlElement* node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement()) {
		std::string tag = CityParser::toLower(node->Value());

		if (tag == "brandweerwagen") {
			this->parseFireTruck(node);
		}
		else if (tag == "ziekenwagen") {
			this->parseAmbulance(node);
		}
		else if (tag == "politiewagen") {
			this->parsePoliceCar(node);
		}
		else {
			std::cout << "Onbekende tag " << tag << " overgeslagen." << std::endl;
		}
	}

	return true;
}
