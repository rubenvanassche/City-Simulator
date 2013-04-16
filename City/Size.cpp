/*
 * Size.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Friday 15 March 2013
 * 
 */

#include "Size.h"

bool Size::isInitialized() {
	return this == Size::fMyself;
}

bool operator== (Size& s1, Size& s2) {
	REQUIRE(s1.isInitialized(), "Size is initialized");
	REQUIRE(s2.isInitialized(), "Size is initialized");

	if ( (s1.fHeight == s2.fHeight) && (s1.fWidth == s2.fWidth) ) {
		return true;
	}
	return false;
}

Size::Size() {
	Size::fMyself = this;
	Size::fWidth = 0;
	Size::fHeight = 0;

	ENSURE(this->isInitialized(), "Size is initialized");
}

Size::Size(int value) {
	REQUIRE(value > 0, "Positive value");

	Size::fMyself = this;
	Size::fWidth = value;
	Size::fHeight = value;

	ENSURE(this->isInitialized(), "Size is initialized");
	ENSURE(this->fWidth == value, "Width is initialized");
	ENSURE(this->fHeight == value, "Height is initialized");
}

Size::Size(int width, int height) {
	REQUIRE(width > 0, "Positive width");
	REQUIRE(height > 0, "Positive height");

	Size::fMyself = this;
	Size::fWidth = width;
	Size::fHeight = height;

	ENSURE(this->isInitialized(), "Size is initialized");
	ENSURE(this->fWidth == width, "Width is initialized");
	ENSURE(this->fHeight == height, "Height is initialized");
}

Size::Size(Size& s) {
	REQUIRE(s.isInitialized(), "Size is initialized");

	Size::fMyself = this;
	Size::fWidth = s.fWidth;
	Size::fHeight = s.fHeight;

	ENSURE(this->fWidth == s.fWidth, "Width is initialized");
	ENSURE(this->fHeight == s.fHeight, "Height is initialized");
	ENSURE(this->isInitialized(), "Size is initialized");
}

bool Size::operator= (Size& s) {
	REQUIRE(s.isInitialized(), "Size is initialized");
	REQUIRE(this->isInitialized(), "Size is initialized");

	Size::fWidth = s.fWidth;
	Size::fHeight = s.fHeight;

	ENSURE(this->fWidth == s.fWidth, "Width copied");
	ENSURE(this->fHeight == s.fHeight, "Heigt copied");
	return true;
}

bool Size::set(int width, int height) {
	REQUIRE(this->isInitialized(), "Size is initialized");
	REQUIRE(width > 0, "Positive width");
	REQUIRE(height > 0, "Positive height");

	Size::fWidth = width;
	Size::fHeight = height;

	ENSURE(this->fWidth == width, "Width is set");
	ENSURE(this->fHeight == height, "Height is set");
	return true;
}

unsigned int Size::getWidth() {
	REQUIRE(this->isInitialized(), "Size is initialized");
	return Size::fWidth;
}

unsigned int Size::getHeight() {
	REQUIRE(this->isInitialized(), "Size is initialized");
	return Size::fHeight;
}
