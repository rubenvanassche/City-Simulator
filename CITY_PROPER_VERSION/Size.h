/*
 * Size.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#ifndef SIZE_H_
#define SIZE_H_

#include "DesignByContract.h"

class Size {
public:
	bool isInitialized();

	friend bool operator== (Size& s1, Size& s2);

	Size(int& value);
	// constructor
	// REQUIRE(value > 0, "Positive value");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == value, "Width is initialized");
	// ENSURE(this->fHeight == value, "Height is initialized");

	Size(int& width, int& height);
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == width, "Width is initialized");
	// ENSURE(this->fHeight == height, "Height is initialized");

	Size(Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width is initialized");
	// ENSURE(this->fHeight == s.fHeight, "Height is initialized");
	// ENSURE(this->isInitialized(), "Size is initialized");

	bool operator= (Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width copied");
	// ENSURE(this->fHeight == s.fHeight, "Heigt copied");

	bool set(int& width, int& height);
	// REQUIRE(this->isInitialized(), "Size is initialized");
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// ENSURE(this->fWidth == width, "Width is set");
	// ENSURE(this->fHeight == height, "Height is set");

	unsigned int getWidth();
	// 	REQUIRE(this->isInitialized(), "Size is initialized");

	unsigned int getHeight();
	// 	REQUIRE(this->isInitialized(), "Size is initialized");


private:
	unsigned int fWidth;
	unsigned int fHeight;

	Size* fMyself;
};

#endif /* SIZE_H_ */
