/*
 * WorldMap.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 16 March 2013
 * 
 */

#include "WorldMap.h"
#include <cmath>

bool WorldMap::isInitialized() {
	return this == WorldMap::fMyself;
}

WorldMap::WorldMap() {
	WorldMap::fMyself = this;

	ENSURE(this->isInitialized(), "WorldMap is initialized");
}

WorldMap::~WorldMap() {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");

	for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
		delete WorldMap::fHorizontals[index];
	}
	WorldMap::fHorizontals.clear();

	for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
		delete WorldMap::fVerticals[index];
	}
	WorldMap::fVerticals.clear();

	ENSURE(this->fHorizontals.empty(), "Horizontals empty'd");
	ENSURE(this->fVerticals.empty(), "Verticals empty'd");
}

WorldMap::WorldMap(WorldMap& map) {
	REQUIRE(map.isInitialized(), "WorldMap is initialized");

	WorldMap::fMyself = this;
	for (unsigned int index=0; index < map.fHorizontals.size(); index++) {
		Street* newStr = new Street(*(map.fHorizontals[index]) );
		WorldMap::fHorizontals.push_back(newStr);

		ENSURE(*(WorldMap::fHorizontals[index]) == *(map.fHorizontals[index]), "Horizontals copied");
	}

	for (unsigned int index=0; index < map.fVerticals.size(); index++) {
		Street* newStr = new Street(*(map.fVerticals[index]) );
		WorldMap::fVerticals.push_back(newStr);

		ENSURE(*(WorldMap::fVerticals[index]) == *(map.fVerticals[index]), "Verticals copied");
	}

	ENSURE(this->isInitialized(), "WorldMap is initialized");
}

bool WorldMap::operator= (WorldMap& map) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(map.isInitialized(), "WorldMap is initialized");

	for (unsigned int index=0; index < map.fHorizontals.size(); index++) {
		Street* newStr = new Street(*(map.fHorizontals[index]) );
		WorldMap::fHorizontals.push_back(newStr);

		ENSURE(*(WorldMap::fHorizontals[index]) == *(map.fHorizontals[index]), "Horizontals copied");
	}

	for (unsigned int index=0; index < map.fVerticals.size(); index++) {
		Street* newStr = new Street(*(map.fVerticals[index]) );
		WorldMap::fVerticals.push_back(newStr);

		ENSURE(*(WorldMap::fVerticals[index]) == *(map.fVerticals[index]), "Horizontals copied");
	}
	return true;
}

bool WorldMap::addStreet(Street& str) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(str.isInitialized(), "Street is initialized");

	if (str.isVertical() ) {
		Street* newStr = new Street(str);
		WorldMap::fVerticals.push_back(newStr);
		return true;
	}
	else if (str.isHorizontal() ) {
		Street* newStr = new Street(str);
		WorldMap::fHorizontals.push_back(newStr);
		return true;
	}
	else {
		std::cerr << "Inconsistent street: " << str << std::endl;
		return false;
	}
}

bool WorldMap::isInMap(Point& p) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(p.isInitialized(), "Point is initialized");

	bool foundHorizontal = false;
	for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
		if (WorldMap::fHorizontals[index]->isElement(p) ) {
			return true;
		}
	}

	if (!foundHorizontal) {
		for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
			if (WorldMap::fVerticals[index]->isElement(p) ) {
				return true;
			}
		}
	}
	return false;
}

bool WorldMap::isCross(Point& curPos) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(this->isInMap(curPos), "Point is in map");
	REQUIRE(curPos.isInitialized(), "Point is initialized");

	bool foundHorizontal = false;
	for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
		if (WorldMap::fHorizontals[index]->isElement(curPos) ) {
			foundHorizontal = true;
			break;
		}
	}

	if (foundHorizontal) {
		for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
			if (WorldMap::fVerticals[index]->isElement(curPos) ) {
				return true;
			}
		}
	}
	return false;
}



bool WorldMap::successor(Point& curPos, Point& destination) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInMap(curPos), "Current Position is in map");
	REQUIRE(this->isInMap(destination), "Destination is in map");

	bool foundDestStr = false;
	Street* destStr;
	for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
		if (WorldMap::fHorizontals[index]->isElement(destination) ) {
			destStr = WorldMap::fHorizontals[index];
			foundDestStr = true;
			break;
		}
	}

	if (!foundDestStr) {

		for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
			if (WorldMap::fVerticals[index]->isElement(destination) ) {
				destStr = WorldMap::fVerticals[index];
				foundDestStr = true;
				break;
			}
		}
	}

	if (destStr->isElement(curPos) ) {
		if (destStr->isHorizontal() ) {
			if (curPos.getX() < destination.getX() ) {
				return curPos.set(curPos.getX() + 1, curPos.getY() );
			}
			return curPos.set(curPos.getX() - 1, curPos.getY() );
		}
		else {
			if (curPos.getY() < destination.getY() ) {
				return curPos.set(curPos.getX(), curPos.getY() + 1);
			}
			return curPos.set(curPos.getX(), curPos.getY() - 1);
		}
	}

	Street* curStr;
	if (destStr->isHorizontal() ) {	// first search for a crossing street
		bool foundCurStr = false;
		for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
			if (WorldMap::fVerticals[index]->isElement(curPos) ) {
				curStr = WorldMap::fVerticals[index];
				foundCurStr = true;
				break;
			}
		}

		if (!foundCurStr) {
			for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
				if (WorldMap::fHorizontals[index]->isElement(curPos) ) {
					curStr = WorldMap::fHorizontals[index];
					foundCurStr = true;
					break;
				}
			}
		}
	}
	else {	// destination str is horizontal
		bool foundCurStr = false;
		for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
			if (WorldMap::fHorizontals[index]->isElement(curPos) ) {
				curStr = WorldMap::fHorizontals[index];
				foundCurStr = true;
				break;
			}
		}

		if (!foundCurStr) {
			for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
				if (WorldMap::fVerticals[index]->isElement(curPos) ) {
					curStr = WorldMap::fVerticals[index];
					foundCurStr = true;
					break;
				}
			}
		}
	}

	if (isParallel(*curStr, *destStr) ) {
		Point* cp = this->closestCrossPoint(*curStr, curPos);
		if (curStr->isVertical()) {
			if (curPos.getY() < cp->getY() ) {
				delete cp;
				return curPos.set(curPos.getX(), curPos.getY() + 1);
			}
			delete cp;
			return curPos.set(curPos.getX(), curPos.getY() - 1);
		}
		else {	// cur str is horizontal
			if (curPos.getX() < cp->getX() ) {
				delete cp;
				return curPos.set(curPos.getX() + 1, curPos.getY() );
			}
			delete cp;
			return curPos.set(curPos.getX() - 1, curPos.getY() );
		}
	}

	if ( (this->isCross(curPos)) || (isCrossing(*curStr, *destStr) ) ) {
		if (destStr->isHorizontal()) {
			Point* cp = crossPoint(*curStr, *destStr);
			if (curStr->isVertical()) {
				if (curPos.getY() < cp->getY() ) {
					return curPos.set(curPos.getX(), curPos.getY() + 1);
				}
				return curPos.set(curPos.getX(), curPos.getY() - 1);
			}
			else {	// cur str is horizontal
				if (curPos.getX() < cp->getX() ) {
					return curPos.set(curPos.getX() + 1, curPos.getY() );
				}
				return curPos.set(curPos.getX() - 1, curPos.getY() );
			}
		}
		else {
			Point* cp = crossPoint(*curStr, *destStr);
			if (curStr->isVertical()) {
				if (curPos.getY() < cp->getY() ) {
					return curPos.set(curPos.getX(), curPos.getY() + 1);
				}
				return curPos.set(curPos.getX(), curPos.getY() - 1);
			}
			else {	// cur str is horizontal
				if (curPos.getX() < cp->getX() ) {
					return curPos.set(curPos.getX() + 1, curPos.getY() );
				}
				return curPos.set(curPos.getX() - 1, curPos.getY() );
			}
		}
	}

	return false;
}

Point* WorldMap::closestCrossPoint(Street& curStr, Point& curPos) {
	REQUIRE(this->isInitialized(), "WorldMap is initialized");
	REQUIRE(curStr.isInitialized(), "Street is initialized");
	REQUIRE(curPos.isInitialized(), "Point is initialized");

	if (curStr.isVertical() ) {
		std::vector<Point*> crosspoints;
		for (unsigned int index=0; index < WorldMap::fHorizontals.size(); index++) {
			if ( isCrossing( *(WorldMap::fHorizontals[index]), curStr) ) {
				Point* cp = crossPoint( *(WorldMap::fHorizontals[index]), curStr );
				crosspoints.push_back(cp);
			}
		}

		while (crosspoints.size() != 1) {
			int delta0 = std::abs(crosspoints[0]->getY() - curPos.getY() );
			int delta1 = std::abs(crosspoints[1]->getY() - curPos.getY() );

			if (delta0 < delta1) {
				crosspoints.erase(crosspoints.begin() + 1);
			}
			else {
				crosspoints.erase(crosspoints.begin() );
			}
		}

		Point* p = new Point( *(crosspoints[0]) );
		crosspoints.clear();
		return p;
	}
	else {
		std::vector<Point*> crosspoints;
		for (unsigned int index=0; index < WorldMap::fVerticals.size(); index++) {
			if ( isCrossing( *(WorldMap::fVerticals[index]), curStr) ) {
				Point* cp = crossPoint( *(WorldMap::fVerticals[index]), curStr );
				crosspoints.push_back(cp);
			}
		}

		while (crosspoints.size() != 1) {
			int delta0 = std::abs(crosspoints[0]->getX() - curPos.getX() );
			int delta1 = std::abs(crosspoints[1]->getX() - curPos.getX() );

			if (delta0 < delta1) {
				crosspoints.erase(crosspoints.begin() + 1);
			}
			else {
				crosspoints.erase(crosspoints.begin() );
			}
		}

		Point* p = new Point( *(crosspoints[0]) );
		crosspoints.clear();

		return p;
	}
}
