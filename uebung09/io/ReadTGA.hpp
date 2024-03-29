/*
 * ReadTGA.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

/**
 *  @source http://content.gpwiki.org/index.php/LoadTGACpp
 */

#ifndef READTGA_HPP_
#define READTGA_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <memory.h>

using std::string;

#define IMG_OK 0x1
#define IMG_ERR_NO_FILE 0x2
#define IMG_ERR_MEM_FAIL 0x4
#define IMG_ERR_BAD_FORMAT 0x8
#define IMG_ERR_UNSUPPORTED 0x40

#include "BitmapReader.hpp"
#include "../util/shared_array.hpp"

namespace asteroids
{

class ReadTGA : public BitmapReader
{
public:

	using uChrPtr = shared_array<unsigned char>;
	using intPtr = shared_array<int>;
	using floatPtr = shared_array<float>;

	/**
	 * @brief Constructor
	 */
    ReadTGA(string filename);

    /**
     * @brief Destruktor
     */
    ~ReadTGA();


    /**
     * @brief Gets the number of bytes per pixel
     */
    int getBitsPerPixel();

    /**
     * @brief Pixel data of the image
     */
    unsigned char* data();

    /**
     * @brief VGA palette information
     */
    unsigned char* palette();

private:

    /**
     * @brief Reads the given file
     */
    int load(const char* filename);

    /// Bits per pixel
    short int       m_bpp;

    /// Size of image
    unsigned long   m_imageSize;

    /// Encoding type
    char            m_enc;

    /// Color palette definitions
    
    uChrPtr  m_palette;

    /// Color palette data
    uChrPtr  m_paletteData;

    // Internal workers
    int readHeader();
    int loadRawData();
    int loadRLEData();
    int loadTgaPalette();
    void BGRtoRGB();
    void FlipImg();
};

}






#endif /* READTGA_HPP_ */
