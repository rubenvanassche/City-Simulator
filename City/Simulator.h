/*
 * Simulator.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "City.h"
#include <iostream>

namespace Simulator {

City parse(std::string& filename);
/*
 * Create a city based upon a XML-file
 */

void simulate(City& town);
/*
 * Simulate the given town
 */


} /* namespace Simulator */
#endif /* SIMULATOR_H_ */
