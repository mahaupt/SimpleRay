#include "bitmap.hpp"

namespace bmp {

//! @note I know I could have done the parsing faster using structs or block reading, but this is experimental code. YOLO!
Bitmap::Bitmap(const std::string pFile) {
	// Store filename.
	fileName_ = pFile;

	// Instantiate input stream.
	std::ifstream file;

	// Try to parse the file.
	try	{
		/* Parse Bitmap file header */
		// Open the file for binary read.
		file.open(pFile.c_str(), std::ios::in | std::ios::binary);

		// Read the file signature and confirm it matches the constant for a bitmap.
		file.read(reinterpret_cast<char*>(&signature_), sizeof(uint16_t));
		swapEndianness(&signature_);
		if (signature_ != BITMAP_SIGNATURE)	{
			std::cerr << "Error: The file signature for '" << pFile << "' is not a bitmap signature." << std::endl;
			//! @todo Throw exception.
		}

		// Read and store the file's size.
		file.read(reinterpret_cast<char*>(&fileSize_), sizeof(uint32_t));

		// Read, store, and reverse the 4 reserved bytes.
		file.read(reinterpret_cast<char*>(&reserved1_), sizeof(uint16_t));
		file.read(reinterpret_cast<char*>(&reserved2_), sizeof(uint16_t));

		// Read and store the starting address of the pixel array.
		file.read(reinterpret_cast<char*>(&arrayOffset_), sizeof(uint32_t));



		/* Parse DIB Header */
		// Read and store the size of this header.
		file.read(reinterpret_cast<char*>(&headerSize_), sizeof(uint32_t));

		// Read and store the pixel width and height.
		file.read(reinterpret_cast<char*>(&pixelWidth_), sizeof(int32_t));
		file.read(reinterpret_cast<char*>(&pixelHeight_), sizeof(int32_t));

		// Read and store number of color planes.
		file.read(reinterpret_cast<char*>(&colorPlanes_), sizeof(uint16_t));

		// Read and store the color depth, and throw exception if unsupported.
		file.read(reinterpret_cast<char*>(&colorDepth_), sizeof(uint16_t));
		if(colorDepth_ != COLOR_DEPTH_24){
			//! @todo Throw exception.
		}

		// Read and store the compression method.
		file.read(reinterpret_cast<char*>(&compression_), sizeof(uint32_t));

		// Read and store the image's size.
		file.read(reinterpret_cast<char*>(&imageSize_), sizeof(uint32_t));

		// Read and store the horizontal and vertical resolution.
		file.read(reinterpret_cast<char*>(&horRes_), sizeof(int32_t));
		file.read(reinterpret_cast<char*>(&verRes_), sizeof(int32_t));

		// Read and store the number of colors used.
		file.read(reinterpret_cast<char*>(&numOfColors_), sizeof(uint32_t));

		// Read and store the number of important colors used.
		file.read(reinterpret_cast<char*>(&numImpColors_), sizeof(uint32_t));



		/* Parse the Pixel Array into the 2D class member vector */
		//! @todo modify parsing for various color depths
		// Move read cursor to the start of the pixel array.
		file.seekg(arrayOffset_);

		// Create pixel color buffers.
		uint8_t b, g, r;

		// Determine pixel array row padding.
		padding_ = pixelWidth_ % 4;

		// Resize vector to accommodate width.
		pixelArray_.resize(pixelWidth_);

		// Iterate through columns resizing to accommodate height.
		for(std::vector<std::vector<bmp::Pixel> >::iterator it = pixelArray_.begin();
				it != pixelArray_.end();
				++it)	{
			(*it).resize(pixelHeight_);
		}

		// Iterate from the bottom row to the top row.
		for(int y = pixelHeight_-1; y >=0; y--)	{
			// Iterate from the left column to the right column.
			for (int x = 0; x < pixelWidth_; x++)	{
				// Buffer red, green, and blue values.
				file.read(reinterpret_cast<char*>(&b), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&g), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&r), sizeof(uint8_t));

				// Allocate new pixel into pixel array.
				pixelArray_[x][y].initialize(&pixelArray_, x, y, r, g, b);

				// Increment class member pixel counter.
				pixels_++;
			}

			// Burn off the remaining bytes to reach next row.
			for(int i = 0; i < padding_; i++){
				file.ignore();
			}
		}

		// Close the file.
		file.close();
	} catch(std::ios_base::failure &e)	{
		//! @todo Account for file failures.
		std::cerr << "Failed to load file" << std::endl;
	}
}

Bitmap::~Bitmap() {}

std::string Bitmap::lookupDIBHeaderType(uint32_t pHeaderSize)	{
	switch(pHeaderSize)	{
	case 12:
		return "BITMAPCOREHEADER / OS21XBITMAPHEADER";
		break;
	case 64:
		return "BITMAPCOREHEADER2 / OS22XBITMAPHEADER";
		break;
	case 40:
		return "BITMAPINFOHEADER";
		break;
	case 52:
		return "BITMAPV2INFOHEADER";
		break;
	case 56:
		return "BITMAPV3INFOHEADER";
		break;
	case 108:
		return "BITMAPV4HEADER";
		break;
	case 124:
		return "BITMAPV5HEADER";
		break;
	default:
		return "UNKNOWN";
		break;
	}
	return "UNKNOWN";
}

std::string Bitmap::to_string()	{
	std::stringstream ss;

	ss << "--- Bitmap Information ---" << std::endl;
	ss << "File Name:\t'" << fileName_ << "'" << std::endl;
	ss << "Pixels:\t\t" << pixels_ << std::endl;
	ss << "Padding:\t"	<< (uint16_t)padding_ << std::endl;
	ss << "Bitmap Header:" << std::endl;
	ss << "\tSignature:\t0x" << std::hex << signature_ << std::dec << std::endl;
	ss << "\tFile Size:\t" << fileSize_ << " bytes" << std::endl;
	ss << "\tArray Offset:\t0x" << std::hex << arrayOffset_ << std::dec << std::endl;
	ss << "DIB Header:" << std::endl;
	ss << "\tHeader Size:\t" << headerSize_ << " (" << lookupDIBHeaderType(headerSize_) << ")" << std::endl;
	ss << "\tWidth(Pixels):\t" << pixelWidth_ << std::endl;
	ss << "\tHeight(Pixels):\t" << pixelHeight_ << std::endl;
	ss << "\tColor Depth:\t" << colorDepth_ << " bit" << std::endl;
	ss << "\tCompression:\t" << compression_ << " (" << ")" << std::endl; //! @todo Build lookup for compression type
	ss << "\tImage Size:\t" << imageSize_ << std::endl;
	ss << "\tHorizontal Res:\t" << horRes_/INCHES_PER_METER << " dpi" << std::endl;
	ss << "\tVertical Res:\t" << verRes_/INCHES_PER_METER << " dpi" << std::endl;
	ss << "\t# of Colors:\t" << numOfColors_ << std::endl;
	ss << "\tImportant:\t" << numImpColors_ << std::endl;

	return ss.str();
}

} /* namespace bmp */
