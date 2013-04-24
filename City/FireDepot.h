/*
 * FireDepot.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef FIREDEPOT_H_
#define FIREDEPOT_H_

#include "Depot.h"
#include "DesignByContract.h"
#include <iostream>


class FireDepot: public Depot {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, FireDepot& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");

	FireDepot(const Point& location, const Point& entrance, const std::string& name, const double& health);
	// constructor
	// ENSURE(this->isInitialized(), "FireDepot is initialized");

	FireDepot(const FireDepot& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");

	void operator= (const FireDepot& f);
	// REQUIRE(f.isInitialized(), "FireDepot is initialized");
	// REQUIRE(this->isInitialized(), "FireDepot is initialized");
	// ENSURE(this->isInitialized(), "FireDepot is initialized");

	char getSymbol();
	/* Returns the symbol of this instance in the city to be used with the graphical impression */
private:
	FireDepot* fMyself;
};

#endif /* FIREDEPOT_H_ */
