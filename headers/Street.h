/*
 * Street.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef STREET_H_
#define STREET_H_

#include <iostream>
#include "Point.h"

class Street {
public:
	friend std::ostream& operator<< (std::ostream& stream, Street& objectStreet);

	Street(const Point& startPoint, const Point& endPoint, std::string name);
	/*
	 * Constructor
	 *
	 * REQUIRE:	The points are valid (a line, not a bend)
	 * ENSURE:	Street is set properly
	 */

	bool setEndPoint(const Point& end);
	/*
	 * Set the end of the street
	 *
	 * REQUIRE:	The point is valid
	 * ENSURE:	The street is valid (a straight line, not a bend)
	 * 			Street is set properly
	 */

	Point getEndPoint() const;
	/*
	 * Get the endpoint of the street
	 *
	 * REQUIRE:	The Street is set properly
	 * ENSURE:	The returned point is valid
	 */

	bool setStartPoint(const Point& start);
	/*
	 * Set the start of the street
	 *
	 * REQUIRE:	The point is valid
	 * ENSURE:	The street is valid (a straight line, not a bend)
	 * 			Street is set properly
	 */

	Point getStartPoint() const;
	/*
	 * Get the startpoint of the street
	 *
	 * REQUIRE:	The Street is set properly
	 * ENSURE:	The returned point is valid
	 */

	bool setName(const std::string& name);
	/*
	 * Set the name of the street
	 *
	 * REQUIRE:	The Street is set properly
	 * ENSURE:	The Street is set properly
	 */

	std::string getName() const;
	/*
	 * Get the name of the street
	 *
	 * REQUIRE:	The Street is set properly
	 * ENSURE:	A string is returned
	 */

private:
	Point fStartPoint;	// the start of the street
	Point fEndPoint;	// the end of the street
	std::string fName;	// the name of the street
};


#endif /* STREET_H_ */
