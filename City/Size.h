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
	// checks whether the object is initialized properly

	friend bool operator== (Size& s1, Size& s2);
	// is equal operator overloading
	// REQUIRE(s1.isInitialized(), "Size is initialized");
	// REQUIRE(s2.isInitialized(), "Size is initialized");

	Size(int value);
	// constructor, construct size with width == height == value
	// REQUIRE(value > 0, "Positive value");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == value, "Width is set");
	// ENSURE(this->fHeight == value, "Height is set");

	Size(int width, int height);
	// constructor
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == width, "Width is set");
	// ENSURE(this->fHeight == height, "Height is set");

	Size(Size& s);
	// copy constructor
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width is copied");
	// ENSURE(this->fHeight == s.fHeight, "Height is copied");
	// ENSURE(this->isInitialized(), "Size is initialized");

	bool operator= (Size& s);
	// copy by assignment overloading
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// REQUIRE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width copied");
	// ENSURE(this->fHeight == s.fHeight, "Height copied");

	bool set(int width, int height);
	// change the size
	// REQUIRE(this->isInitialized(), "Size is initialized");
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// ENSURE(this->fWidth == width, "Width is set");
	// ENSURE(this->fHeight == height, "Height is set");

	unsigned int getWidth();
	// get the width
	// REQUIRE(this->isInitialized(), "Size is initialized");

	unsigned int getHeight();
	// get the height
	// REQUIRE(this->isInitialized(), "Size is initialized");

private:
	unsigned int fWidth;
	unsigned int fHeight;

	Size* fMyself;
};

#endif /* SIZE_H_ */
