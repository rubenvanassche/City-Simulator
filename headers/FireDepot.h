/*
 * FireDepot.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef FIREDEPOT_H_
#define FIREDEPOT_H_

#include <iostream>
#include "Point.h"
#include "FireTruck.h"
#include <vector>
#include "Building.h"

class FireDepot : public Building {
public:
	friend std::ostream& operator<< (std::ostream& stream, FireDepot& objectDepot);

	FireDepot(const std::string& name, const Point& entrance);
	/*
	 * Constructor
	 *
	 * REQUIRE:	The point location is valid
	 * ENSURE:	The FireDepot is set properly
	 */

	bool addFireTruck(const FireTruck& truck);
	/*
	 * Add a firetruck to a fire depot
	 *
	 * REQUIRE:	The FireDepot is set properly
	 * ENSURE:	The FireTruck is added
	 */

	unsigned int getNrTrucks();
	/*
	 * Get the amount of FireTrucks in the depot
	 *
	 * REQUIRE:	The FireDepot is set properly
	 * ENSURE:	The given value is >= 0
	 */

	std::string getName() const;
	/*
	 * Get the name of the depot
	 *
	 * REQUIRE:	The FireDepot is set properly
	 * ENSURE:	A string is returned
	 */

	Point getEntrance() const;
	/*
	 * Get the entrance of the fire depot
	 *
	 * REQUIRE:	The FireDepot is set properly
	 * ENSURE:	The returned point is valid
	 */

private:
	std::vector<FireTruck> fTrucks;	// the vector of FireTrucks in depot
	std::string fName;	// the name of the depot
	Point fEntrance;	// the entrance of the depot
};


#endif /* FIREDEPOT_H_ */
