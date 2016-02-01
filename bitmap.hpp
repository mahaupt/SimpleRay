#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "pixel.hpp"

namespace bmp {

/** The bitmap class is used to represent a bitmap file allowing for pixel by pixel access in the format of a 2D array.
 * @author U.G. Wilson
 * @link http://www.ugw.name/
 * @todo Add support for 16 and 256 color bitmaps.
 * @todo Add thrown exceptions for invalid files.
 * @todo Add thrown exceptions for unsupported files.
 * @todo Add getters for header information.
 */
class Bitmap {
public:
	Bitmap(const std::string pFile);
	virtual ~Bitmap();
	//! @todo Add Bounds protection
	std::vector<bmp::Pixel>& operator[] (int x) {
		return pixelArray_[x];
	}

	std::string to_string();

private:
	//! File Name.
	std::string fileName_;

	//! Number of Pixels
	uint32_t pixels_ = 0;

	//! Row Padding in Pixel Array
	uint8_t padding_ = 0;


	// Bitmap Header Variables
	//! File Signature.
	uint16_t signature_ = 0;

	//! File Size.
	uint32_t fileSize_ = 0;

	//! Reserved 1.
	uint16_t reserved1_ = 0;

	//! Reserved 2.
	uint16_t reserved2_ = 0;

	//! Pixel Array Offset.
	uint32_t arrayOffset_ = 0;


	// DIB Header Variables
	//! DIB Header Size. (bytes)
	uint32_t headerSize_ = 0;

	//! Image Width (pixels)
	int32_t pixelWidth_ = 0;

	//! Image Height (pixels)
	int32_t pixelHeight_ = 0;

	//! Number of Color Planes
	uint16_t colorPlanes_ = 0;

	//! Color Depth (bits per pixel)
	uint16_t colorDepth_ = 0;

	//! Compression Method
	uint32_t compression_ = 0;

	//! Image Size
	uint32_t imageSize_ = 0;

	//! Horizontal Resolution
	int32_t horRes_ = 0;

	//! Vertical Resolution
	int32_t verRes_ = 0;

	//! Number of Colors Used
	uint32_t numOfColors_ = 0;

	//! Number of Important Colors Used
	uint32_t numImpColors_ = 0;

	//! The 2D Pixel array vector (vector of
	std::vector<std::vector<bmp::Pixel> > pixelArray_;


	// Constants
	//! Signature of a bitmap file. (const)
	const uint16_t BITMAP_SIGNATURE = 0x424D;

	//! Number of inches in a meter. (const)
	const double INCHES_PER_METER = 39.3701;

	//! Supported color depth bit count.
	const uint8_t COLOR_DEPTH_24 = 24;

	/** Template function to swap endianness.  It swaps the endianness in place in memory.
	 *
	 * @param pVar The variable to be swapped.
	 */
	template <class T>
	void swapEndianness(T *pVar)	{
		uint8_t *memory = reinterpret_cast<uint8_t*>(pVar);
		std::reverse(memory, memory + sizeof(T));
	}

	std::string lookupDIBHeaderType(uint32_t pHeaderSize);

};

} /* namespace bmp */
#endif /* BITMAP_HPP_ */
