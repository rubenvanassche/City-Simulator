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

#include "City.h"
#include <iostream>

namespace CityParser {

City* parse(std::string& filename);
// Create a city based upon a XML-file


} /* namespace CityParser */

#endif /* CITYPARSER_H_ */
