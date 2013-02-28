/*
 * FireTruck.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef FIRETRUCK_H_
#define FIRETRUCK_H_

#include <iostream>
#include "FireDepot.h"
#include "Vehicle.h"

class FireTruck : public Vehicle {
public:
	friend std::ostream& operator<< (std::ostream& stream, FireTruck& firetruck);

	FireTruck(FireDepot* base=NULL);
	/*
	 * Constructor
	 *
	 * REQUIRE:	The reference to the base exist
	 * ENSURE:	The FireTruck is set properly
	 */

	bool setBase(FireDepot* base);
	/*
	 * Set the base of the firetruck
	 *
	 * REQUIRE:	The FireTruck is set properly
	 * ENSURE:	The FireTruck is set properly
	 */

	FireDepot* getBase() const;
	/*
	 * Get the reference to his base
	 *
	 * REQUIRE:	The FireTruck is set properly
	 * ENSURE:	The reference exist
	 */

private:
	FireDepot* fBase;	// The base of the FireTruck
};


#endif /* FIRETRUCK_H_ */
