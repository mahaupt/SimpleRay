#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace bmp {

/** The Pixel class represents an individual RGB pixel in a the 2D array of a Bitmap.
 * @author U.G. Wilson
 * @link http://www.ugw.name/
 */
class Pixel {
public:
	/**
	 * Default Constructor.
	 */
	Pixel();

	/** A constructor used to fully initialize a pixel when it's values are known.
	 * @param pParentArray The array that this pixel is a value in.
	 * @param pX The X (column) this pixel belongs to in the parent array.
	 * @param pY The Y (row) this pixel belongs to in the parrent array.
	 * @param pRed The red color value of this pixel.
	 * @param pGreen The green color value of this pixel.
	 * @param pBlue The blue color value of this pixel.
	 */
	Pixel(std::vector<std::vector<bmp::Pixel> > *pParentArray, int32_t pX, int32_t pY, uint8_t pRed, uint8_t pGreen, uint8_t pBlue);

	/**
	 * Default Destructor.
	 */
	virtual ~Pixel();

	/** A method to initialize a pixel object with it's values.
	 * @param pParentArray The array that this pixel is a value in.
	 * @param pX The X (column) this pixel belongs to in the parent array.
	 * @param pY The Y (row) this pixel belongs to in the parrent array.
	 * @param pRed The red color value of this pixel.
	 * @param pGreen The green color value of this pixel.
	 * @param pBlue The blue color value of this pixel.
	 */
	void initialize(std::vector<std::vector<bmp::Pixel> > *pParentArray, int32_t pX, int32_t pY, uint8_t pRed, uint8_t pGreen, uint8_t pBlue);

	/**
	 * A method to return a string representation of this pixel.
	 * @return A string representation of the string.
	 */
	std::string to_string();

	//! The two dimensional array this pixel is located in.
	std::vector<std::vector<bmp::Pixel> > *parentArray = nullptr;
	//! The column that this pixel resides in the 2D array (Left to Right).
	uint32_t x=0;
	//! The row that this pixel resides in the 2D array (Top to Bottom).
	uint32_t y=0;

	//! The red color value of this pixel.
	uint8_t r=255;
	//! The green color value of this pixel.
	uint8_t g=255;
	//! The blue color value of this pixel.
	uint8_t b=255;
};

} /* namespace bmp */
#endif /* PIXEL_HPP_ */
