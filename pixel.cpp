#include "pixel.hpp"

namespace bmp {

Pixel::Pixel()	{}

Pixel::Pixel(std::vector<std::vector<bmp::Pixel> > *pParentArray, int32_t pX, int32_t pY, uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
	parentArray = pParentArray;
	x = pX;
	y = pY;
	r = pRed;
	g = pGreen;
	b = pBlue;
}

Pixel::~Pixel() {}

void Pixel::initialize(std::vector<std::vector<bmp::Pixel> > *pParentArray, int32_t pX, int32_t pY, uint8_t pRed, uint8_t pGreen, uint8_t pBlue)	{
	parentArray = pParentArray;
	x = pX;
	y = pY;
	r = pRed;
	g = pGreen;
	b = pBlue;
}

std::string Pixel::to_string()	{
	std::stringstream ss;

	ss << "X: " << x << " Y: " << y << std::endl;
	ss << "R: " << (int)r << " G: " << (int)g << " B: " << (int)b << std::endl;

	return ss.str();
}

} /* namespace bmp */
