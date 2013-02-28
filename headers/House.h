/*
 * House.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef HOUSE_H_
#define HOUSE_H_

#include "Building.h"
#include <iostream>
#include "Point.h"

class House : public Building {
public:
	friend std::ostream& operator<< (std::ostream& stream, House& house);

	House(const Point& location, unsigned int health);
	/*
	 * Constructor
	 *
	 * REQUIRE:	Point is valid
	 * 			health point >= 0
	 * ENSURE:	The house is set properly
	 */

	bool isBurning() const;
	/*
	 * Check whether the house is burning
	 *
	 * REQUIRE:	The house is set properly
	 * ENSURE:	A boolean is returned
	 */

	bool setFire();
	/*
	 * Set the house on fire
	 *
	 * REQUIRE:	The house is set properly
	 * ENSURE:	The house is burning
	 */

	bool stopFire();
	/*
	 * stop burning down the house
	 *
	 * REQUIRE:	The house is set properly
	 * ENSURE:	The house is NOT burning
	 */

	bool setHealth(const unsigned int& health);
	/*
	 * Set the health point of the house
	 *
	 * REQUIRE:	The house is set properly
	 * 			The health is >= 0
	 * ENSURE:	The house is set properly
	 */

	unsigned int getHealth() const;
	/*
	 * Get the health points of the house
	 *
	 * REQUIRE:	The house is set properly
	 * ENSURE:	a value >= 0 is returned
	 */

private:
	bool fIsBurning;	// keep track whether the house is burning
	unsigned int fHealth;	// keep track whether the house is burned down
};


#endif /* HOUSE_H_ */
