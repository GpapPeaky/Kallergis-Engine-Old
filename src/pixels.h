#include "definitions.aux"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <string>

/**
 * @brief Parses the png and scans for each pixel
 *             generates a pixel data file pixdf
 *             that has all pixel coordinates saved along with their color, prov and reg id
 *              ignoring { 0, 0, 0 } RGB -> impassable terrain/sea/lake ...
 * 
 * @param fname .png to parse
 * 
 * @attention the image might have to be of specific size (1000 x 900)
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable generate_pixel_coords(std::string fname);
/* WRITE: parses from .png */

/**
 * @brief Parses the png and scans for each pixel
 *             it then assigns to the prov_con vector of provinces for each province, it's connections
 *             if a different prov_rgb is found
 * 
 * @param fname .png to parse
 * 
 * @attention the image might have to be of specific size (1000 x 900)
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable generate_province_connections(std::string fname);
/* WRITE: parses from .png */
