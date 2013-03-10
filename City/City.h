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
#include "Fire.h"
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
	 * REQUIRE(true, "OOOOOOOOOoooops, something went wrong with city..")
	 * ENSURE(isInitialized(), "The City object is not initialized properly")
	 */

	bool addFireDepot(const FireDepot& depot);
	/*
	 * Adds a new FireDepot
	 *
	 * REQUIRE(this->isInitialized(), "The City object is not initialized properly
	 * REQUIRE(depot.isInitialized(), "The depot is not initialized properly")
	 * ENSURE(this->fFireDepots.back().getName() == depot.getName(), "The depot is not added")
	 */

	bool addHouse(const House& house);
	/*
	 * Add a new house
	 *
	 * REQUIRE(this->isInitialized(), "The City object is not initialized properly
	 * REQUIRE(house.isInitialized(), "The house is not initialized properly")
	 */

	bool addStreet(const Street& street);
	/*
	 * Add a new street
	 *
	 * REQUIRE(this->isInitialized(), "The City object is not initialized properly
	 * REQUIRE(street.isInitialized(), "The street is not initialized properly")
	 * ENSURE(this->fStreets.back().getName() == street.getName(), "The street is not added")
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

	City* fMyself;	// a pointer to myself for initialize checking
};


#endif /* CITY_H_ */
