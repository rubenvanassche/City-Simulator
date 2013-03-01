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
	bool isInitialized();
	/*
	 * Checks if the Size object is initialized properly
	 */

	Size(const unsigned int& value);
	/*
	 * Constructor.
	 *
	 * REQUIRE(value > 0, "Invalid value")
	 * ENSURE(isInitialized(), "The Size object is not initialized properly")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	Size(const unsigned int& width, const unsigned int& height);
	/*
	 * Constructor
	 *
	 * REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height")
	 * REQUIRE(this->isInitialized(), "The Size object is not initialized properly")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	bool set(const unsigned int& width, const unsigned int& height);
	/*
	 * Change the width & height.
	 *
	 * REQUIRE(this->isInitialized(), "The Size object is not initialized properly")
	 * REQUIRE( ( (width > 0) && (height > 0) ), "Invalid width and/or height")
	 * ENSURE( ( (this->fWidth == value) && (this->fHeight == value)), "Width and/or height not set properly")
	 */

	unsigned int getWidth() const;
	/*
	 * Gets the width
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * ENSURE(this->fWidth > 0, "Returned width is not valid.")
	 */

	unsigned int getHeight() const;
	/*
	 * Gets the height
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * ENSURE(this->fHeight > 0, "Returned height is not valid.")
	 */

	bool setValue(const unsigned int& value);
	/*
	 * set the width & height to value
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * REQUIRE(value > 0, "Invalid value")
	 * ENSURE( ( (this->fX == value) && this->fY == value), "Width and/or height is not set.")
	 */

	unsigned int getValue() const;
	/*
	 * Returns the value
	 *
	 * REQUIRE(this->isInitialized, "The Size object is not initialized properly")
	 * REQUIRE(this->fHeight == this->fWidth, "The width and height are not both the same")
	 * ENSURE(this->fWidth > 0, "Returned value is invalid")
	 */

private:
	unsigned int fWidth;
	unsigned int fHeight;

	Size* fMyself;	// a pointer to myself to check if I'm initialized properly
};


#endif /* SIZE_H_ */
