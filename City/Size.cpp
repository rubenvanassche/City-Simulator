/*
 * Size.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "Size.h"

bool Size::isInitialized() const {
	return this == fMyself;
}

bool operator== (const Size& s1, const Size& s2) {
	REQUIRE(s1.isInitialized(), "Size is initialized");
	REQUIRE(s2.isInitialized(), "Size is initialized");

	if ( (s1.fHeight == s2.fHeight) && (s1.fWidth == s2.fWidth) ) {
		return true;
	}
	return false;
}

Size::Size() {
	fMyself = this;
	fWidth = 1;
	fHeight = 1;

	ENSURE(this->isInitialized(), "Size is initialized");
	ENSURE(this->fWidth == 1, "Default width is 1");
	ENSURE(this->fHeight == 1, "Default height is 1");
}

Size::Size(const int& value) {
	REQUIRE(value > 0, "Positive value");

	fMyself = this;
	fWidth = value;
	fHeight = value;

	ENSURE(this->isInitialized(), "Size is initialized");
	ENSURE(this->fWidth == value, "Width is initialized");
	ENSURE(this->fHeight == value, "Height is initialized");
}

Size::Size(const int& width, const int& height) {
	REQUIRE(width > 0, "Positive width");
	REQUIRE(height > 0, "Positive height");

	fMyself = this;
	fWidth = width;
	fHeight = height;

	ENSURE(this->isInitialized(), "Size is initialized");
	ENSURE(this->fWidth == width, "Width is initialized");
	ENSURE(this->fHeight == height, "Height is initialized");
}

Size::Size(const Size& s) {
	REQUIRE(s.isInitialized(), "Size is initialized");

	fMyself = this;
	fWidth = s.fWidth;
	fHeight = s.fHeight;

	ENSURE(this->fWidth == s.fWidth, "Width is initialized");
	ENSURE(this->fHeight == s.fHeight, "Height is initialized");
	ENSURE(this->isInitialized(), "Size is initialized");
}

void Size::operator= (const Size& s) {
	REQUIRE(s.isInitialized(), "Size is initialized");
	REQUIRE(this->isInitialized(), "Size is initialized");

	fWidth = s.fWidth;
	fHeight = s.fHeight;

	ENSURE(this->fWidth == s.fWidth, "Width copied");
	ENSURE(this->fHeight == s.fHeight, "Heigt copied");
	return;
}

void Size::set(const int& width, const int& height) {
	REQUIRE(width > 0, "Positive width");
	REQUIRE(height > 0, "Positive height");
	REQUIRE(this->isInitialized(), "Size is initialized");

	fWidth = width;
	fHeight = height;

	ENSURE(this->fWidth == width, "Width is initialized");
	ENSURE(this->fHeight == height, "Height is initialized");
}

unsigned int Size::getWidth() const {
	REQUIRE(this->isInitialized(), "Size is initialized");
	return fWidth;
}

unsigned int Size::getHeight() const {
	REQUIRE(this->isInitialized(), "Size is initialized");
	return fHeight;
}
