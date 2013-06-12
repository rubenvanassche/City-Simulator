/*
 * Size.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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
	// ENSURE(this->getWidth() == 1, "Default width is 1");
	// ENSURE(this->getHeight() == 1, "Default height is 1");

	Size(const int& value);
	// constructor
	// REQUIRE(value > 0, "Positive value");

	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->getWidth() == value, "Width is initialized");
	// ENSURE(this->getHeight() == value, "Height is initialized");

	Size(const int& width, const int& height);
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");

	// ENSURE(this->isInitialized(), "Size is initialized");
	// ENSURE(this->getWidth() == width, "Width is initialized");
	// ENSURE(this->getHeight() == height, "Height is initialized");

	Size(const Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");

	// ENSURE(this->getWidth() == s.getWidth(), "Width is initialized");
	// ENSURE(this->getHeight() == s.getHeight(), "Height is initialized");
	// ENSURE(this->isInitialized(), "Size is initialized");

	void operator= (const Size& s);
	// REQUIRE(s.isInitialized(), "Size is initialized");
	// REQUIRE(this->isInitialized(), "Size is initialized");

	// ENSURE(this->getWidth() == s.getWidth(), "Width copied");
	// ENSURE(this->getHeight() == s.getHeight(), "Height copied");

	void set(const int& width, const int& height);
	// REQUIRE(width > 0, "Positive width");
	// REQUIRE(height > 0, "Positive height");
	// REQUIRE(this->isInitialized(), "Size is initialized");

	// ENSURE(this->getWidth() == width, "Width is initialized");
	// ENSURE(this->getHeight() == height, "Height is initialized");

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
