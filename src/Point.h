/*
 * Point.h
 *
<<<<<<< HEAD
 * @author:		Ruben Van Assche & Stijn Wouters
=======
<<<<<<< HEAD
 * @author:		Ruben Van Assche & Stijn Wouters
=======
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
>>>>>>> Contracts
>>>>>>> contracts
 * @version:	1.0
 * @date:		Wednesday 27 February
 * 
 */

#ifndef POINT_H_
#define POINT_H_

<<<<<<< HEAD
#include <iostream>
#include "DesignByContract.h"

=======
<<<<<<< HEAD
#include <iostream>
#include "DesignByContract.h"

class Point {
friend std::ostream& operator<<(std::ostream &stream, Point &p);
public:
	Point();
	Point(int X, int Y);
	void set(int X, int Yco);
	void setX(int X);
	void setY(int Y);
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
=======
>>>>>>> contracts
class Point {
friend std::ostream& operator<<(std::ostream &stream, Point &p);
public:
	Point();
	Point(int X, int Y);
	void set(int X, int Yco);
	void setX(int X);
	void setY(int Y);
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


<<<<<<< HEAD
#endif /* POINT_H_ */
=======
#endif /* POINT_H_ */
>>>>>>> Contracts
>>>>>>> contracts
