/*
 * Hospital.h
 *
 *  Created on: 16 apr. 2013
 *      Author: Ruben
 */

#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include "Depot.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>

class Hospital: public Depot {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Hospital& h);
	// output operator overloading
	// REQUIRE(h.isInitialized(), "Hospital is initialized");

	Hospital(const Point& location, const Point& entrance, const Size& size, const std::string& name, const double& health);
	// constructor
	// ENSURE(this->isInitialized(), "PoliceDepot is initialized");

	Hospital(const Hospital& h);
	// copy constructor
	// REQUIRE(h.isInitialized(), "Hospital is initialized");
	// ENSURE(this->isInitialized(), "Hospital is initialized");

	void operator= (const Hospital& h);
	// REQUIRE(h.isInitialized(), "Hospital is initialized");
	// REQUIRE(this->isInitialized(), "Hospital is initialized");
	// ENSURE(this->isInitialized(), "Hospital is initialized");

	char getSymbol() const;
	// Returns the symbol of this instance in the city to be used with the graphical impression
	// REQUIRE(this->isInitialized(), "Hospital is initialized");

private:
	Hospital* fMyself;
};

#endif /* HOSPITAL_H_ */
