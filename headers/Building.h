/*
 * Building.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "Point.h"
#include "Size.h"

class Building {
public:
	Building(const Point& location, const Size& size);
	/*
	 * Create a new building
	 *
	 * REQUIRE:	The Point is valid.
	 * 			The size is valid
	 * ENSURE:	The Building is set properly
	 */

	bool setLocation(const Point& location);
	/*
	 * Set the location of the building
	 *
	 * REQUIRE:	The Building is set properly
	 * 			The Point is valid
	 * ENSURE:	The Building is set properly
	 */

	Point getLocation() const;
	/*
	 * Returns a the location
	 *
	 * REQUIRE:	The Building is set properly
	 * ENSURE:	The point is valid
	 */

	bool setSize(const Size& size);
	/*
	 * Set the size of the building
	 *
	 * REQUIRE:	The Size is valid
	 * 			The Building is set properly
	 * ENSURE:	The Building is set properly
	 */

	Size getSize() const;
	/*
	 * Get the size of the building
	 *
	 * REQUIRE:	The Building is set properly
	 * ENSURE:	The Size is valid
	 */

private:
	Size fSize;	// the size of the building
	Point fLocation;	// the location of the building
};


#endif /* BUILDING_H_ */
