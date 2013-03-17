/*
 * WorldMap.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	Saturday 16 March 2013
 * @date:		1.0
 * 
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

#include "Street.h"
#include "DesignByContract.h"
#include <vector>

class WorldMap {
public:
	bool isInitialized();

	WorldMap();
	// ENSURE(this->isInitialized(), "WorldMap is initialized");

	~WorldMap();
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// ENSURE(this->fHorizontals.empty(), "Horizontals empty'd");
	// ENSURE(this->fVerticals.empty(), "Verticals empty'd");

	WorldMap(WorldMap& map);
	// REQUIRE(map.isInitialized(), "WorldMap is initialized");
	// ENSURE(*(WorldMap::fHorizontals[index]) == *(map.fHorizontals[index]), "Horizontals copied");
	// ENSURE(*(WorldMap::fVerticals[index]) == *(map.fVerticals[index]), "Verticals copied");
	// ENSURE(this->isInitialized(), "WorldMap is initialized");

	bool operator= (WorldMap& map);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// ENSURE(*(WorldMap::fHorizontals[index]) == *(map.fHorizontals[index]), "Horizontals copied");
	// ENSURE(*(WorldMap::fVerticals[index]) == *(map.fVerticals[index]), "Verticals copied");

	bool addStreet(Street& str);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// REQUIRE(str.isInitialized(), "Street is initialized");

	bool isInMap(Point& p);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	bool isCross(Point& p);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// REQUIRE(this->isInMap(p), "Point is in map");
	// REQUIRE(p.isInitialized(), "Point is initialized");

	bool successor(Point& curPos, Point& destination);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// REQUIRE(curPos.isInitialized(), "Point is initialized");
	// REQUIRE(destination.isInitialized(), "Point is initialized");
	// REQUIRE(curPos != destination, "Points are different");
	// REQUIRE(this->isInMap(curPos), "Current Position is in map");
	// REQUIRE(this->isInMap(destination), "Destination is in map");

	Point* closestCrossPoint(Street& curStreet, Point& curPoint);
	// REQUIRE(this->isInitialized(), "WorldMap is initialized");
	// REQUIRE(curStr.isInitialized(), "Street is initialized");
	// REQUIRE(curPos.isInitialized(), "Point is initialized");


private:
	std::vector<Street*> fHorizontals;
	std::vector<Street*> fVerticals;

	WorldMap* fMyself;
};

#endif /* WORLDMAP_H_ */
