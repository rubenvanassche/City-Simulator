/*
 * Point.h
 *
 * @author:		Ruben Van Assche & Stijn Wouters
 * @version:	1.0
 * @date:		Wednesday 27 February
 * 
 */

#include "Point.h"

Point::Point(){
	setX(0);
	setY(0);
}

Point::Point(int X, int Y){
	setX(X);
	setY(Y);
}

void Point::set(int X, int Y){
	setX(X);
	setY(Y);
}
void Point::setX(int X){
	REQUIRE(X >= 0,"No negative x allowed (Point)");

	Xcoordinate = X;
}

void Point::setY(int Y){
	REQUIRE(Y >= 0,"No negative y allowed (Point)");

	Ycoordinate = Y;
}

int Point::X(){
	return Xcoordinate;
}

int Point::Y(){
	return Ycoordinate;
}

std::ostream& operator<<(std::ostream &stream, Point &p){
  stream << '(' << p.Xcoordinate << ',' << p.Ycoordinate << ')';

  return stream;
}

Point Point::operator+(Point &p){
	Point P;
	P.setX(Xcoordinate + p.X());
	P.setY(Ycoordinate + p.Y());

	return P;
}

Point Point::operator-(Point &p){
	Point P;
	P.setX(Xcoordinate - p.X());
	P.setY(Ycoordinate - p.Y());

	return P;
}

int Point::operator<(Point &p){
	if((Xcoordinate < p.X()) && (Ycoordinate < p.Y())){
		return true;
	}else{
		return false;
	}
}

int Point::operator>(Point &p){
	if((Xcoordinate > p.X()) && (Ycoordinate > p.Y())){
		return true;
	}else{
		return false;
	}
}

bool Point::operator==(Point &p){
	if((Xcoordinate == p.X()) && (Ycoordinate == p.Y())){
		return true;
	}else{
		return false;
	}
}

bool Point::operator!=(Point &p){
	if((Xcoordinate != p.X()) || (Ycoordinate != p.Y())){
		return true;
	}else{
		return false;
	}
}
