/*
 * Check.h
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#ifndef CHECK_H_
#define CHECK_H_

#include "City.h"
#include "House.h"
#include "Street.h"
#include "FireDepot.h"
#include "Point.h"
#include <vector>
#include <iostream>

class Check {
public:
	Check();
	bool isInitialized();
	bool go(House& house);
	bool go(FireDepot& fireDepot);
	bool go(Street& street);

	~Check();
private:
	bool checkPoints(std::vector<Point*> newPoints);
	bool checkPoint(Point& p);
	/* For buildings if there is a building or a street then return false */
	bool checkStreetPoints(std::vector<Point*> newPoints);
	bool checkStreetPoint(Point& p);
	/* Only for streets, if there is a building, return false but if there is a street return true */

	void addPoints(std::vector<Point*>, char type);

	std::vector<Point*> fUsedPoints; // All Points used at the moment
	std::vector<char> fUsedPointTypes; // The type of the points in the dUsedPointsvector
	Check* fMyself; // I
};

#endif /* CHECK_H_ */
