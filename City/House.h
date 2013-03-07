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
#include "Size.h"

class House : public Building {
public:
	friend std::ostream& operator<< (std::ostream& stream, House& house);

	bool isInitialized();
	/*
	 * Check whether the FireDepot is initialized properly
	 */

	House(const Point& location,  int health);
	/*
	 * Constructor
	 *
	 * REQUIRE(location.isInitialized(), "The location is not initialized properly")
	 * REQUIRE(health >= 0, "The health point is not >= 0")
	 * ENSURE(isInitialized(), "The House object is not initialized properly")
	 */

	bool isBurning() const;
	/*
	 * Check whether the house is burning
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not initialized properly")
	 */

	bool setFire();
	/*
	 * Set the house on fire
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not initialized properly")
	 * ENSURE(this->fIsBurning == true, "The house is not set on fire")
	 */

	bool stopFire();
	/*
	 * stop burning down the house
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not initialized properly")
	 * ENSURE(this->fIsBurning == false, "The fire on the house is not stopped")
	 */

	bool setHealth(const  int& health);
	/*
	 * Set the health point of the house
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not initialized properly")
	 * REQUIRE(health >= 0, "The health point is not >= 0")
	 * ENSURE(this->fHealth == health, "The health point is not set")
	 */

	 int getHealth();
	/*
	 * Get the health points of the house
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not set properly")
	 * ENSURE(this->fHealth >= 0, "The returned health point is not valid")
	 */

	bool check(const int& subtracter = 1);
	/*
	 * Lower the health of the house by one, or a specified number if the house is burning
	 *
	 * REQUIRE(this->isInitialized(), "The House object is not initialized properly")
	 * REQUIRE(subtracter >= 0, "The subtracter is not >= 0")
	 * REQUIRE(subtracter > this->getHealth(), "The subtracter is greater then the health")
	 */

private:
	bool fIsBurning;	// keep track whether the house is burning
	 int fHealth;	// keep track whether the house is burned down

	House* fMyself;	// a pointer to myself to check if I'm initialized properly
};


#endif /* HOUSE_H_ */
