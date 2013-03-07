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

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	FireTruck(FireDepot* base=NULL);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist")
	 * ENSURE(isInitialized(), "The FireTruck is not initialized properly")
	 */

	bool setBase(FireDepot* base);
	/*
	 * Set the base of the firetruck
	 *
	 * REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly")
	 * REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist")
	 * ENSURE(this->fBase == base, "The base is not set")
	 */

	FireDepot* getBase() const;
	/*
	 * Get the reference to his base
	 *
	 * REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly")
	 * REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist")
	 */

private:
	FireDepot* fBase;	// The base of the FireTruck

	FireTruck* fMyself;	// a pointer to myself for initialize check
};


#endif /* FIRETRUCK_H_ */
