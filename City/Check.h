/*
 * Check.h
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#ifndef CHECK_H_
#define CHECK_H_

#include "Building.h"
#include "Point.h"
#include <vector>
#include "Street.h"

enum EType {kBUILDING, kSTREET};
enum EState {kOCCUPPIED, kFREE};

typedef std::pair<Point, EType> Tupple;

class Check {
public:
	bool isInitialized() const;
	// check whether the check object is initialized properly

	Check();
	// constructor

	// ENSURE(this->isInitialized(), "Check is initialized");

	bool go(const Building& building);
	// check whether you may add the building
	// REQUIRE(this->isInitialized(), "Check is initialized");
	// REQUIRE(building.isInitialized(), "Building is initialized");

	bool go(const Street& street);
	// check whether you may add the street
	// REQUIRE(this->isInitialized(), "Check is initialized");
	// REQUIRE(street.isInitialized(), "Building is initialized");

private:
	EState checkPoint(const Point& p, const EType& type);
	// check this point whether there is a building/street
	//REQUIRE(this->isInitialized(), "Check is initialized");
	//REQUIRE(p.isInitialized(), "Point is initialized");

	bool fit(const Building& building);
	// check whether the building 'fits'
	//REQUIRE(this->isInitialized(), "Check is initialized");
	//REQUIRE(building.isInitialized(), "Check is initialized");

	bool fit(const Street& street);
	// check whether the street 'fits'
	//REQUIRE(this->isInitialized(), "Check is initialized");
	//REQUIRE(street.isInitialized(), "Street is initialized");

private:
	Check* fMyself;
	std::vector<Tupple> fUsedPoints;	// All points used at the moment

	bool fHasWidth;
	bool fHasHeight;

	int fWidth;	// length and height of the roadmap
	int fHeight;
};

#endif /* CHECK_H_ */
