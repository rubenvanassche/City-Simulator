/*
 * City.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef CITY_H_
#define CITY_H_

#include <iostream>
#include "FireDepot.h"
#include "House.h"
#include "Street.h"
//#include "Point.h"
#include <vector>

class City {
public:
	friend std::ostream& operator<< (std::ostream& stream, City& objectCity);

	City();
	/*
	 * Constructor
	 *
	 * REQUIRE:	None
	 * ENSURE:	The City is set properly
	 */

	bool add(const FireDepot& depot);
	/*
	 * Adds a new FireDepot
	 *
	 * REQUIRE:	The City is set properly
	 * ENSURE:	a FireDepot is added
	 */

	bool add(const House& house);
	/*
	 * Add a new house
	 *
	 * REQUIRE:	The City is set properly
	 * ENSURE:	A house is added
	 */

	bool add(const Street& street);
	/*
	 * Add a new street
	 *
	 * REQUIRE:	The City is set properly
	 * ENSURE:	A street is added
	 */

	bool _check();
	/*
	 * Check whether the City is still right, no overlapping place
	 */

	/*
	 * UNCERTAIN
	 *
	 * calculateMap();
	 *
	 */

public:
	/*
	 * UNCERTAIN
	 *
	 * unsigned int fWidth;
	 * unsigned int fHeight;
	 */

	std::vector<FireDepot> fFireDepots;	// all firedepots
	std::vector<Street> fStreets;	// all streets
	std::vector<House> fHouses;	// all houses

};


#endif /* CITY_H_ */
