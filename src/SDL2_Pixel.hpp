#include "SDL2/SDL.h"
#include "SDL2/SDL_pixels.h"

#include <string>
#include <math.h>

#include "SDL2_Window.hpp"

#include "KENG_Country.hpp"
#include "KENG_Parser.hpp"

#include "auxf/definitions.aux"

#ifndef _SDL2_PIXEL_HPP_
/**
 * @brief It has appeared that modifying the ! WINDOW ! surface is master and more efficient?
 *  Although I tried to change already loaded bitmaps, it appeared as it cannot happen?
 *  Still unsure...
 * 
 *  This module is for more direct pixel manipulation and all memory associated with it
 */
#define _SDL2_PIXEL_HPP_

/**
 * @brief Sets a pixel at specific coordinates to a specific colour
 * 
 * @param texture Texture to change the pixel of
 * @param x x axis
 * @param y y axis
 * @param r red value
 * @param g green value
 * @param b blue value
 * @param a alpha value (default = 255)
 * 
 * @returns 0 on SUCCESS 1 on FAILURE
 */
int SDL2_SetPixel(SDL_Texture* texture, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/**
 * @brief Test function, to understan memory manipulation better
 * 
 * @param texture Texture to colour
 * 
 * @warning DO NOT USE ON REGULAR, JUST A TEST!
 */
void SDL2_PixelScreenFill(SDL_Texture* texture);

/**
 * @brief Loads a bitmap, from a file
 * 
 * @param filename bmp to load
 * @param dest texture to load the bitmap
 * @param alpha Alpha of texture
 * 
 * @warning Make sure that the texture is empty, or else it will be overwritten
 * 
 * @returns 0 on SUCCESS 1 on FAILURE
 */
int SDL2_LoadBitmap(SDL_Texture* dest, const char* filename, int alpha);

/**
 * @brief Loads a png, from a file
 * 
 * @param filename png to load
 * @param dest texture to load the png
 * 
 * @warning Make sure that the texture is empty, or else it will be overwritten
 * 
 * @returns 0 on SUCCESS 1 on FAILURE
 */
int SDL2_LoadPNG(SDL_Texture* dest, const char* filename);

/**
 * @brief Parses the bmp and scans for each pixel
 *          it paints the cou RGB value onto a new surface that is rendered lastly
 * 
 * @attention the image might have to be of specific size (5760 x 3240)
 * 
 * @param src Surface to scan
 * @param texture texture to paint
 * 
 * @returns 1 on failure
 *              0 on success
*/
int KENG_MarkCountries(SDL_Surface* src, SDL_Texture* texture);

/**
 * @brief Generates borders between countries
 * 
 * @param src Surface to scan for edges
 * @param dst Destination of pixel sets
 * 
 * @warning There should be no 1 pixel threshold in order to produce good results, also no province shall have isolated 2x2 or 1xY / Xx1 type of mapdata
 */
void KENG_MarkInnerBorders(SDL_Surface* src, SDL_Texture* dst);

/**
 * @brief Prints the colours of all countries
 */
void KENG_PrintCountryColours(void);

#endif
