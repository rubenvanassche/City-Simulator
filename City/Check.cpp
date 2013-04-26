/*
 * Check.cpp
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#include "Check.h"

bool Check::isInitialized() const {
	return this == fMyself;
}

Check::Check() : fMyself(this), fHasWidth(false), fHasHeight(false), fWidth(0), fHeight(0) {
	ENSURE(this->isInitialized(), "Check is initialized");
	ENSURE(this->fHasHeight == false, "Check has not a width yet");
	ENSURE(this->fHasWidth == false, "Check has not a height yet");
	ENSURE(this->fWidth == 0, "Width is currently 0");
	ENSURE(this->fHeight == 0, "Height is currently 0");
}

EState Check::checkPoint(const Point& p, const EType& type) {
	REQUIRE(this->isInitialized(), "Check is initialized");
	REQUIRE(p.isInitialized(), "Check is initialized");

	// iterate over used points
	for (std::vector<Tupple>::iterator it = fUsedPoints.begin(); it != fUsedPoints.end(); it++) {
		// if you can find a point that is equal to the given one,
		if (it->first == p) {
			if (type == kSTREET) {	// if the point you want to check is a street
				if (it->second == kBUILDING) {	// but there's already a building on it
					return kOCCUPPIED;	// so return occupied
				}
				continue; //otherwise, streets may overlap (even if you've change the whole street)
			}
			else {	// the point is a building
				// whether the point found is a street or building, this place is occupied
				return kOCCUPPIED;
			}
		}
	}

	// if not any point is found, then you got the freedom
	return kFREE;
}

bool Check::fit(const Building& building) {
	REQUIRE(this->isInitialized(), "Check is initialized");
	REQUIRE(building.isInitialized(), "Building is initialized");

	unsigned int width = building.getSize().getWidth();
	unsigned int height = building.getSize().getHeight();

	for (unsigned int h = 0; h <= height; h++) {
		for (unsigned int w = 0; w <= width; w++) {
			int x = building.getLocation().getX() + w;
			int y = building.getLocation().getY() - h;

			if ( (x < 0) || (y < 0)) {
				// x || y is negative, so the building "felt" of the border
				return false;
			}
		}
	}
	return true;
}

bool Check::fit(const Street& street) {
	REQUIRE(this->isInitialized(), "Check is initialized");
	REQUIRE(street.isInitialized(), "Street is initialized");

	Point start = street.getStartPoint();
	Point end = street.getEndPoint();

	if (street.isVertical()) {
		unsigned int yMin = std::min(start.getY(), end.getY());
		unsigned int yMax = std::max(start.getY(), end.getY());

		if (fHasHeight) {
			return fHeight == (yMax - yMin);
		}
		else {
			// it's the first time you add a vertical street, so it's always ok
			fHeight = (yMax - yMin);	// this is the fixed height
			fHasHeight = true;	// Check has now a fixed height
			return true;
		}
	}
	else if (street.isHorizontal()) {
		unsigned int xMin = std::min(start.getX(), end.getX());
		unsigned int xMax = std::max(start.getX(), end.getX());

		if (fHasWidth) {
			return fWidth == (xMax - xMin);
		}
		else {
			// it's the first time you add a horizontal street, so it's always ok
			fWidth = (xMax - xMin);	// this is the fixed width
			fHasWidth = true;	// Check has now a fixed width
			return true;
		}
	}
	else {
		return false;	// diagonal street never fits
	}
}

bool Check::go(const Building& building) {
	REQUIRE(this->isInitialized(), "Check is initialized");
	REQUIRE(building.isInitialized(), "Building is initialized");

	if (!this->fit(building)) {
		return false;
	}

	unsigned int width = building.getSize().getWidth();
	unsigned int height = building.getSize().getHeight();
	std::vector<Tupple> vecTupple;

	for (unsigned int h = 0; h <= height; h++) {
		for (unsigned int w = 0; w <= width; w++) {
			int x = building.getLocation().getX() + w;
			int y = building.getLocation().getY() - h;

			Point p(x, y);

			if (Check::checkPoint(p, kBUILDING) == kOCCUPPIED) {
				return false;
			}

			// otherwise, this point is not occupied, so you may add it
			vecTupple.push_back(Tupple(p, kBUILDING));
			continue;
		}
	}

	// if you've reached here, then there's no problem at all
	for (unsigned int index = 0; index < vecTupple.size(); index++) {
		fUsedPoints.push_back(vecTupple[index]);
	}
	return true;
}

bool Check::go(const Street& street) {
	REQUIRE(this->isInitialized(), "Check is initialized");
	REQUIRE(street.isInitialized(), "Building is initialized");

	if (!this->fit(street)) {
		return false;
	}

	Point start = street.getStartPoint();
	Point end = street.getEndPoint();

	unsigned int xMin = std::min(start.getX(), end.getX());
	unsigned int xMax = std::max(start.getX(), end.getX());
	unsigned int yMin = std::min(start.getY(), end.getY());
	unsigned int yMax = std::max(start.getY(), end.getY());

	std::vector<Tupple> vecTupple;

	for (unsigned int x = xMin; x <= xMax; x++) {
		for (unsigned int y = yMin; y <= yMax; y++) {

			Point p(x, y);

			if (Check::checkPoint(p, kSTREET) == kOCCUPPIED) {
				return false;
			}

			// otherwise, this point is free, so you may add
			vecTupple.push_back(Tupple(p, kSTREET));
			continue;
		}
	}

	// if you've reached here, then there's no problem at all
	for (unsigned int index = 0; index < vecTupple.size(); index++) {
		fUsedPoints.push_back(vecTupple[index]);	// add all the new points to the used points
	}
	return true;
}
