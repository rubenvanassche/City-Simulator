/*
 * Point.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point {
public:
	friend std::ostream& operator<< (std::ostream& stream, Point& pointobject);
	friend bool operator== (Point& pointobject1, Point& pointobject2);
	friend bool operator!= (Point& pointobject1, Point& pointobject2);
	friend Point operator+ (Point& pointobject1, Point& pointobject2);
	friend Point operator- (Point& pointobject1, Point& pointobject2);
	friend bool operator< (Point& pointobject1, Point& pointobject2);
	friend bool operator> (Point& pointobject1, Point& pointobject2);
	friend bool operator<= (Point& pointobject1, Point& pointobject2);
	friend bool operator>= (Point& pointobject1, Point& pointobject2);

	bool isInitialized();
	/*
	 * Checks if the Point is initialized Properly
	 */

	Point(const int& x=0, const int& y=0);
	/*
	 * Constructor.
	 *
	 * REQUIRE( ((x >= 0) && (y >= 0)), "Invalid xy-coordinates.")
	 * ENSURE(isInitialized(), "Point object is not initialized properly")
	 * ENSURE( ( (this->fX == x) && (this->fY == y) ), "Point object has not the given coordinates")
	 */

	bool set(const unsigned int& x=0, const unsigned int& y=0);
	/*
	 * Change the x, y values.
	 *
	 * REQUIRE(this->isInitialized(), "The Point object is not initialized properly")
	 * REQUIRE( ( (x >= 0) && (y >= 0) ), "Invalid xy-coordinates.")
	 * ENSURE( ( (x == this->fX) && (y == this->fY) ), "Point object has not the given coordinates")
	 */

	unsigned int getX() const;
	/*
	 * Returns the x-coordinate.
	 *
	 * REQUIRE(this->isInitialized(), "The Point object is not initialized properly")
	 * ENSURE(this->fX >= 0, "Returned x-coordinate is invalid")
	 */

	unsigned int getY() const;
	/*
	 * Returns the y-coordinate.
	 *
	 * REQUIRE(this->isInitialized(), "The Point object is not initialized properly")
	 * ENSURE(this->fY >= 0, "Returned y-coordinate is invalid")
	 */

private:
	unsigned int fX;	// the x-coordinate
	unsigned int fY;	// the y-coordinate

	Point* fMyself;	// a pointer to myself to check if it's initialized properly
};


#endif /* POINT_H_ */
