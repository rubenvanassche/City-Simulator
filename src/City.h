/*
 * City.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Wednesday 27 February
 * 
 */

#ifndef CITY_H_
#define CITY_H_

#include "Parser.h"
#include "Building.h"
#include "Street.h"
#include "Vehicle.h"
#include <vector>

class City {
public:
	City(XmlFile& inputfile);
	/*
	 * Constructor: create a file based upon an xml file.
	 *
	 * REQUIRE:	The input xml file exist
	 * ENSURE:	The City is initialized properly
	 */

	bool add(const Firedepot& newDepot);
	/*
	 * Adds a new firedepot (object) to the city
	 *
	 * REQUIRE:	The City is initialized properly
	 * ENSURE:	The new depot is added
	 */

	bool add(const House& newHouse);
	/*
	 * Adds a new house (object) to the city
	 *
	 * REQUIRE:	The City is initialized properly
	 * ENSURE:	The new house is added
	 */

	bool add(const Street& newStreet);
	/*
	 * Adds a new street (object) to the city
	 *
	 * REQUIRE:	The City is initialized properly
	 * ENSURE:	The new street is added
	 */

	/* UNCERTAIN:
	 *
	 * calculateMap();
	 *
	 * Calculate the width and the height of the map
	 */
private:
	bool _check();
	/*
	 * Checks if the city is still correct: there are no overlapping
	 * buildings or streets
	 */

	/* UNCERTAIN:
	 *
	 * unsigned int fWidth;	// to be defined by the calculateMap()
	 * unsigned int fHeight;	// to be defined by the calculateMap()
	 */

	std::vector<Firedepot> fFiredepots;	// stores all the firedepots
	std::vector<Street> fStreets;	// stores all the streets
	std::vector<House> fHouses;	// stores all the houses
	std::vector<Firedepot> fFiredepots;	// stores all the depots
};


#endif /* CITY_H_ */
