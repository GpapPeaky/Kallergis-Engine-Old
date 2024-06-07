#include "definitions.aux"
#include "country.h"
#include "init_win.h"
#include "init_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <string>

extern SDL_Surface* country_surface;
extern SDL_Texture* country_texture;

/**
 * @brief Parses the bmp and scans for each pixel
 *             generates a pixel data file pixdf
 *             that has all pixel coordinates saved along with their color, prov and reg id
 *              ignoring { 0, 0, 0 } RGB -> impassable terrain/sea/lake ...
 * 
 * @param fname .bmp to parse
 * 
 * @attention the image might have to be of specific size (5760 x 3240)
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable generate_pixel_coords(std::string fname);
/* WRITE */

/**
 * @brief Parses the bmp and scans for each pixel
 *             it then assigns to the prov_con vector of provinces for each province, it's connections
 *             if a different prov_rgb is found
 * 
 * @param fname .bmp to parse
 * 
 * @attention the image might have to be of specific size (5760 x 3240)
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable generate_province_connections(std::string fname);
/* WRITE */

/**
 * @brief Parses the bmp and scans for each pixel
 *          it paints the cou RGB value onto a new surface that is rendered lastly
 * 
 * @attention the image might have to be of specific size (5760 x 3240)
 * 
 * @returns 1 on failure
 *              0 on success
*/
err_capable generate_countries_surfaces(void);
/* WRITE */
