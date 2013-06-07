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

CityParser::CityParser(City* town, Output* out) {
	REQUIRE(town->isInitialized(), "City is initialized");
	REQUIRE(out->isInitialized(), "Output is initialized");

	fTown = town;
	fOut = out;
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Naam van straat ontbreekt.\n";
				fOut->write(msg.str());
				return false;
			}

			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van straat ontbreekt.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundX0) || (x0 < 0) ) {
		std::stringstream msg; msg << "X coordinaat van startpositie van straat " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundY0) || (y0 <0) ){
		std::stringstream msg; msg << "Y coordinaat van startpositie van straat " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundX1) || (x1 < 0) ) {
		std::stringstream msg; msg << "X coordinaat van eindpositie van straat " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundY1) || (y1 < 0) ) {
		std::stringstream msg; msg << "Y coordinaat van eindpositie van straat" << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		Street newStr(name, Point(x0, y0), Point(x1, y1));
		if (!fTown->add(newStr) ) {
			std::stringstream msg; msg << "Kan " << newStr << " niet toevoegen.\n";
			fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Brandbaarheid van huis ontbreekt.\n";
				fOut->write(msg.str());
				return false;
			}

			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if ( (!foundX) || (x < 0) ) {
		std::stringstream msg; msg << "X coordinaat van huis ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundY) || (y <0) ){
		std::stringstream msg; msg << "Y coordinaat van huis ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::stringstream msg; msg << "Brandbaarheid van huis ontbreekt.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		House newHouse(Point(x, y), flam);
		if (!fTown->add(newHouse)) {
			std::stringstream msg; msg << "Kan " << newHouse << " niet toevoegen.\n";
			fOut->write(msg.str());
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
				std::stringstream msg; msg << "Naam van brandweerkazerne ontbreekt.\n";
				fOut->write(msg.str());
				return false;
			}

			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;

			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Brandbaarheid van brandweerkazerne ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}

			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van brandweerkazerne ontbreekt.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::stringstream msg; msg << "X coordinaat van brandweerkazerne " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::stringstream msg; msg << "Y coordinaat van brandweerkazerne " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::stringstream msg; msg << "X coordinaat van ingang brandweerkazerne " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::stringstream msg; msg << "Y coordinaat van ingang brandweerkazerne " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::stringstream msg; msg << "Brandbaarheid van brandweerkazerne " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		FireDepot newDepot(Point(xLoc, yLoc), Point(xEntr, yEntr), name, flam);
		if (!fTown->add(newDepot) ) {
			std::stringstream msg; msg << "Kan " << newDepot << " niet toevoegen.\n";
			fOut->write(msg.str());
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
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Naam van ziekenhuis ontbreekt\n";
				fOut->write(msg.str());
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Brandbaarheid van ziekenhuis " << name << " ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van ziekenhuis ontbreekt\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::stringstream msg; msg << "X coordinaat van ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::stringstream msg; msg << "Y coordinaat van ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::stringstream msg; msg << "X coordinaat van ingang ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::stringstream msg; msg << "Y coordinaat van ingang ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::stringstream msg; msg << "Brandbaarheid van ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::stringstream msg; msg << "Breedte van ziekenhuis " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::stringstream msg; msg << "Hoogte van ziekenhuis " << name << "ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		Hospital newHospital(Point(xLoc, yLoc), Point(xEntr, yEntr), Size(width, height), name, flam);
		if (!fTown->add(newHospital) ) {
			std::stringstream msg; msg << "Kan " << newHospital << " niet toevoegen.\n";
			fOut->write(msg.str());
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
				std::stringstream msg; msg << "Naam van politiebureau ontbreekt\n";
				fOut->write(msg.str());
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Brandbaarheid van politiebureau " << name << " ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van politiebureau ontbreekt\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXLoc) || (xLoc < 0) ) {
		std::stringstream msg; msg << "X coordinaat van politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYLoc) || (yLoc <0) ){
		std::stringstream msg; msg << "Y coordinaat van politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundXEntr) || (xEntr < 0) ) {
		std::stringstream msg; msg << "X coordinaat van ingang politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundYEntr) || (yEntr<0) ){
		std::stringstream msg; msg << "Y coordinaat van ingang politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::stringstream msg; msg << "Brandbaarheid van politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::stringstream msg; msg << "Breedte van politiebureau " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::stringstream msg; msg <<  "Hoogte van politiebureau " << name << "ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		PoliceDepot newDepot(Point(xLoc, yLoc), Point(xEntr, yEntr), Size(width, height), name, flam);
		if (!fTown->add(newDepot) ) {
			std::stringstream msg; msg << "Kan " << newDepot << " niet toevoegen.\n";
			fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "brandbaarheid") {
			foundFlam = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Brandbaarheid van winkel ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			flam = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
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
					std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
					fOut->write(msg.str());
				}
			}
		}
		else if (subtag == "overvalbaarheid") {
			foundSec = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Overvalbaarheid van winkel ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			security = std::atoi(subnode->GetText());

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if ( (!foundX) || (x < 0) ) {
		std::stringstream msg; msg << "X coordinaat van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundY) || (y <0) ){
		std::stringstream msg; msg << "Y coordinaat van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundFlam) || (flam < 0) ) {
		std::stringstream msg; msg << "Brandbaarheid van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundWidth) || (width < 1) ) {
		std::stringstream msg; msg << "Breedte van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundHeight) || (height < 1) ) {
		std::stringstream msg; msg << "Hoogte van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundSec) || (security < 0) ) {
		std::stringstream msg; msg << "Overvalbaarheid van winkel ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		Shop newShop(Point(x, y), Size(width, height), flam, security);
		if (!fTown->add(newShop) ) {
			std::stringstream msg; msg << "Kan " << newShop << " niet toevoegen.\n";
			fOut->write(msg.str());
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
				std::stringstream msg; msg << "Naam van brandweerwagen ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Basis van brandweerwagen " << name << " ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findFireDepot(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van brandweerwagen ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::stringstream msg; msg << "Basis van brandweerwagen " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		FireTruck newTruck(name, ptrBase);
		if (!fTown->add(newTruck) ) {
			std::stringstream msg; msg << "Kan " << newTruck << " niet toevoegen.\n";
			fOut->write(msg.str());
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
				std::stringstream msg; msg << "Naam van ambulance ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Basis van ambulance " << name << " ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findHospital(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van ambulance ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::stringstream msg; msg << "Basis van ambulance " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		Ambulance newAmbuce(name, ptrBase);
		if (!fTown->add(newAmbuce) ) {
			std::stringstream msg; msg << "Kan " << newAmbuce << " niet toevoegen.\n";
			fOut->write(msg.str());
		}
		return true;
	}
}

bool CityParser::parsePoliceTruck(TiXmlElement* node) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	bool foundName = false;
	bool foundBase = false;

	std::string name;
	PoliceDepot* ptrBase;

	for (TiXmlElement* subnode = node->FirstChildElement(); subnode != NULL; subnode = subnode->NextSiblingElement() ) {
		std::string subtag = CityParser::toLower(subnode->Value());

		if (subtag == "naam") {
			foundName = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Naam van politiewagen ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			name = subnode->GetText();

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else if (subtag == "basis") {
			foundBase = true;
			if (subnode->GetText() == NULL) {
				std::stringstream msg; msg << "Basis van politiewagen " << name << " ontbreekt/ongeldig.\n";
				fOut->write(msg.str());
				return false;
			}
			std::string basename  = subnode->GetText();

			ptrBase = fTown->findPoliceDepot(basename);

			for (TiXmlAttribute* attr = subnode->FirstAttribute(); attr != NULL; attr = attr->Next()) {
				std::string attrName = CityParser::toLower(attr->Name());
				std::stringstream msg; msg << "Kan attribuut " << attrName << " van " << subtag << " niet herkennen, overgeslagen\n";
				fOut->write(msg.str());
			}
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << subtag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	if (!foundName) {
		std::stringstream msg; msg << "Naam van politiewagen ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else if ( (!foundBase) || (ptrBase == NULL) ) {
		std::stringstream msg; msg << "Basis van politiewagen " << name << " ontbreekt/ongeldig.\n";
		fOut->write(msg.str());
		return false;
	}
	else {
		// all attributes are ok
		PoliceTruck newTruck(name, ptrBase);
		if (!fTown->add(newTruck) ) {
			std::stringstream msg; msg << "Kan " << newTruck << " niet toevoegen.\n";
			fOut->write(msg.str());
		}
		return true;
	}
}

bool CityParser::parseBuildings(const std::string& filename) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::stringstream msg; msg << doc.ErrorDesc();
		fOut->write(msg.str());
		return false;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::stringstream msg; msg << "Kan file niet laden: geen root element.\n";
		fOut->write(msg.str());
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
			std::stringstream msg; msg << "Onbekende tag " << tag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	return true;
}

bool CityParser::parseVehicles(const std::string& filename) {
	REQUIRE(this->isInitialized(), "Parser is initialized");

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::stringstream msg; msg << doc.ErrorDesc();
		fOut->write(msg.str());
		return false;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		std::stringstream msg; msg << "Kan file niet laden: geen root element.\n";
		fOut->write(msg.str());
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
			this->parsePoliceTruck(node);
		}
		else {
			std::stringstream msg; msg << "Onbekende tag " << tag << " overgeslagen.\n";
			fOut->write(msg.str());
		}
	}

	return true;
}
