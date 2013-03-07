/*
 * Size.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 7 March 2013
 * 
 */

#include "Size.h"
#include "DesignByContract.h"


bool operator== (Size& sizeobject1, Size& sizeobject2){
	if ( (sizeobject1.fHeight == sizeobject2.fHeight) && (sizeobject1.fWidth == sizeobject2.fWidth) ) {
			return true;
	}
	return false;	
}

bool Size::isInitialized() {
	return this == Size::fMyself;
}

Size::Size(const int& value) {
	REQUIRE(value > 0, "Invalid value");

	Size::fMyself = this;
	Size::fWidth = value;
	Size::fHeight = value;

	ENSURE(isInitialized(), "The Size object is not initialized properly");
	ENSURE( ( (this->fWidth == value) && (this->fHeight == value) ), "Width and/or height not set properly");
}

Size::Size(const int& width, const int& height) {
	REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height");

	Size::fMyself = this;
	Size::fWidth = width;
	Size::fHeight = height;

	ENSURE( ( (this->fWidth == width) && (this->fHeight == height) ), "Width and/or height not set properly");
}

bool Size::set(const int& width, const int& height) {
	REQUIRE(this->isInitialized(), "The Size object is not initialized properly");
	REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height");

	Size::fWidth = width;
	Size::fHeight = height;

	ENSURE( ( (this->fWidth == width) && (this->fHeight == height) ), "Width and/or height not set properly");
	return true;
}

unsigned int Size::getWidth() {
	REQUIRE(this->isInitialized(), "The Size object is not initialized properly");
	return Size::fWidth;
}

unsigned int Size::getHeight() {
	REQUIRE(this->isInitialized(), "The Size object is not initialized properly");
	return Size::fHeight;
}

bool Size::setValue(const int& value) {
	REQUIRE(this->isInitialized(), "The Size object is not initialized properly");
	REQUIRE(value > 0, "Invalid value");

	Size::fWidth = value;
	Size::fHeight = value;

	ENSURE( ( (this->fWidth == value) && (this->fHeight == value) ), "Width and/or height is not set");
	return true;
}

unsigned int Size::getValue() {
	REQUIRE(this->isInitialized(), "The Size object is not initialized properly");
	REQUIRE(this->fHeight == this->fWidth, "The Width and height are not both the same");
	return Size::fWidth;
}
