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
	bool isInitialized() const;
	// check whether the Size is initialized properly

	friend bool operator== (const Size& s1, const Size& s2);
	// REQUIRE(s1.isInitialized(), "Size is initialized");
	// REQUIRE(s2.isInitialized(), "Size is initialized");

	Size();
	// default constructor
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == 1, "Default width is 1");
	// ENSURE(this->fHeight == 1, "Default height is 1");

	Size(const int& value);
	// constructor
	// REQUIRE(value > 0, "Positive value");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == value, "Width is initialized");
	// ENSURE(this->fHeight == value, "Height is initialized");

	Size(const int& width, const int& height);
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == width, "Width is initialized");
	// ENSURE(this->fHeight == height, "Height is initialized");

	Size(const Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width is initialized");
	// ENSURE(this->fHeight == s.fHeight, "Height is initialized");
	// ENSURE(this->isInitialized(), "Size is initialized");

	void operator= (const Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// REQUIRE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->fWidth == s.fWidth, "Width copied");
	// ENSURE(this->fHeight == s.fHeight, "Height copied");

	unsigned int getWidth() const;
	// 	REQUIRE(this->isInitialized(), "Size is initialized");

	unsigned int getHeight() const;
	// 	REQUIRE(this->isInitialized(), "Size is initialized");


private:
	unsigned int fWidth;
	unsigned int fHeight;

	Size* fMyself;
};

#endif /* SIZE_H_ */
