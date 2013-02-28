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
	Size(const unsigned int& value);
	/*
	 * Constructor.
	 *
	 * REQUIRE:	The value is > 0
	 * ENSURE:	The Size is set properly
	 */

	Size(const unsigned int& width, const unsigned int& height);
	/*
	 * Constructor
	 *
	 * REQUIRE:	The values are > 0
	 * ENSURE:	The Size is set properly
	 */

	bool set(const unsigned int& width, const unsigned int& height);
	/*
	 * Change the width & height.
	 *
	 * REQUIRE:	The Size is set properly
	 * ENSURE:	width and height are > 0
	 * 			The Size is set properly
	 */

	unsigned int getWidth() const;
	/*
	 * Gets the width
	 *
	 * REQUIRE:	The Size is set properly
	 * ENSURE:	The given value is > 0
	 */

	unsigned int getHeight() const;
	/*
	 * Gets the height
	 *
	 * REQUIRE:	The Size is set properly
	 * ENSURE:	The given value is > 0
	 */

	bool setValue(const unsigned int& value);
	/*
	 * set the width & height to value
	 *
	 * REQUIRE:	The Size is set properly
	 * ENSURE:	the width and height are both the same and > 0
	 */

	unsigned int getValue() const;
	/*
	 * Returns the value
	 *
	 * REQUIRE:	The Size is set properly
	 * 			The width and height are both the same and > 0
	 * ENSURE:	The given value is > 0
	 */

private:
	unsigned int fWidth;
	unsigned int fHeight;
};


#endif /* SIZE_H_ */
