/*
 * Point.h
 *
 * @author:		Ruben Van Assche & Stijn Wouters
 * @version:	1.0
 * @date:		Wednesday 27 February
 * 
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include "DesignByContract.h"

class Point {
friend std::ostream& operator<<(std::ostream &stream, Point &p);
public:
	Point();
	Point(int X, int Y);
	void set(int X, int Y);
	void X(int X);
	void Y(int Y);
	int X();
	int Y();

	Point operator+(Point &p);
	Point operator-(Point &p);
	int operator<(Point &p);
  	int operator>(Point &p);
  	bool operator==(Point &p);
  	bool operator!=(Point &p);
private:
	int Xcoordinate;
	int Ycoordinate;
};


#endif /* POINT_H_ */

