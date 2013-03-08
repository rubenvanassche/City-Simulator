/*
 * Size.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#ifndef SIZE_H_
#define SIZE_H_

class Size {
public:
	friend bool operator== (Size& sizeobject1, Size& sizeobject2);

	bool isInitialized();
	/*
	 * Checks if the Size object is initialized properly
	 */

	Size(const int value);
	/*
	 * Constructor.
	 *
	 * REQUIRE(value > 0, "Invalid value")
	 * ENSURE(isInitialized(), "The Size object is not initialized properly")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	Size(const int width, const int height);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	bool set(const int& width, const int& height);
	/*
	 * Change the width & height.
	 *
	 * REQUIRE(this->isInitialized(), "The Size object is not initialized properly")
	 * REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	unsigned int getWidth();
	/*
	 * Gets the width
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 */

	unsigned int getHeight();
	/*
	 * Gets the height
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 */

	bool setValue(const int& value);
	/*
	 * set the width & height to value
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * REQUIRE(value > 0, "Invalid value")
	 * ENSURE( ( (this->fX == value) && this->fY == value), "Width and/or height is not set.")
	 */

	unsigned int getValue();
	/*
	 * Returns the value
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * REQUIRE(this->fHeight == this->fWidth, "The width and height are not both the same")
	 */



private:
	unsigned int fWidth;
	unsigned int fHeight;

	Size* fMyself;	// a pointer to myself to check if I'm initialized properly
};


#endif /* SIZE_H_ */
