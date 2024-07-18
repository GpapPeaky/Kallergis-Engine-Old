#include "country.hpp"
#include "init_win.hpp"
#include "init_map.hpp"
#include "../auxf/definitions.aux"
#include <queue> /* For flood_fill() function */
#include <utility> /* For pairs */
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#ifndef PIXELS_H
/**
 * @brief It has appeared that modifying the ! WINDOW ! surface is master and more efficient?
 *  Although I tried to change already loaded bitmaps, it appeared as it cannot happen?
 *  Still unsure...
 * 
 *  This module is for more direct pixel manipulation and all memory associated with it
 */
#define PIXELS_H

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
 * @param surface Surface to paint
 * @param win Window of surface
 * 
 * @returns 1 on failure
 *              0 on success
*/
err_capable generate_countries_surfaces(SDL_Surface* surface, SDL_Window* win);

/**
 * @brief Sets a pixel at specific coordinates to a specific colour
 * 
 * @param surface Surface to change the pixel of
 * @param win window where the surface is shown
 * @param x x axis
 * @param y y axis
 * @param r red value
 * @param g green value
 * @param b blue value
 */
void set_pixel(SDL_Surface* surface, SDL_Window* win, int x, int y, Uint8 r, Uint8 g, Uint8 b);

/**
 * @brief Test function, to understan memory manipulation better
 * 
 * @param surface Surface to colour
 * @param win Window to go to
 * 
 * @warning DO NOT USE ON REGULAR, JUST A TEST!
 */
void pixel_screen_fill(SDL_Surface* surface, SDL_Window* win);

/**
 * @brief Generates borders between countries
 * 
 * @param outter_surface Surface to colour the country borders
 * @param inner_surface Surface to colour the province borders
 * @param win Window to go to
 * @param border_colour Border Colour
 * 
 * @warning There should be no 1 pixel threshold in order to produce good results, also no province shall have isolated 2x2 or 1xY / Xx1 type of mapdata
 */
void mark_borders(SDL_Surface* outter_surface, SDL_Surface* inner_surface, SDL_Window* win, int border_colour);

/**
 * @brief Prints the colours of all countries
 */
void print_country_colours(void);

#endif
