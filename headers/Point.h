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

	Point(const unsigned int& x=0, const unsigned int& y=0);
	/*
	 * Constructor.
	 *
	 * REQUIRE:	The x, y values must be >= 0
	 * ENSURE:	The point is set properly
	 */

	bool set(const unsigned int& x=0, const unsigned int& y=0);
	/*
	 * Change the x, y values.
	 *
	 * REQUIRE:	The point was set properly.
	 * ENSURE:	The x, y values are set properly
	 */

	unsigned int getX() const;
	/*
	 * Returns the x-coordinate.
	 *
	 * REQUIRE:	The point was set properly
	 * ENSURE:	The given x coordinate is >= 0
	 */

	unsigned int getY() const;
	/*
	 * Returns the y-coordinate.
	 *
	 * REQUIRE:	The point was set properly
	 * ENSURE:	The given y coordinate is >= 0
	 */

private:
	unsigned int fX;	// the x-coordinate
	unsigned int fY;	// the y-coordinate
};


#endif /* POINT_H_ */
