#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../ThirdParty/SDL2/include/SDL2/SDL_image.h"

#include "SDL2_Window.hpp" /* For renderer */

/**
 * @brief SDL2 image data
 */
typedef struct SDL2_Images{
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_FRect position;
}SDL2_Images;

/**
 * @brief Get the value of the pixel from
 * a surface x and y coordinates
 * 
 * @param src Source image
 * @param x X coordinate
 * @param y Y coordinate
 * 
 * @returns The pixel at <x,y>
 */
Uint32 SDL2_GetPixel(SDL2_Images* src, int x, int y);

/**
 * @brief Sets a surface's pixel at x and y
 * to a given colour
 * 
 * @param dst Destination image
 * @param x X coordinate
 * @param y Y coordinate
 * @param colour Colour to set
 */
void SDL2_SetPixel(SDL2_Images* dst, int x, int y, Uint32 colour);

/**
 * @brief Draw the edges of a source surface
 * onto it, specifically non-transparent
 * with transparent
 * 
 * @attention Meh, not really usable the way this is coded
 * 
 * @param src Source image, position field holds the transformed size,
 * surface only has the primitive image data
 * @param colour RGB values for edge colour
 * 
 * @returns -1 on failure, 0 on success
 */
int SDL2_DrawEdgeOfSurface(SDL2_Images* src, Uint32 colour);


