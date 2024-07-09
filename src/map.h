#include "definitions.aux"
#include "init_map.h"
#include "pixels.h"
#include <algorithm>

#ifndef MAP
/**
 * @brief Map rendering and viewport handling (for zoom-in/-out and WASD movement)
 */
#define MAP

extern SDL_Rect viewport;
extern float map_scale;

/**
 * @brief renders a surface onto the screen by blitting it
 * 
 * @param surface surface to copy
 * @param screen where to copy to
 * @param zoom scale of the map
 * @param x x Axis
 * @param y y Axis
 * 
 * @warning zoom, x and y are defaulted to 0 if nothing is used as a parameter
*/
render_capable render_to_screen(SDL_Surface* surface, SDL_Surface* screen, float zoom, int x, int y);

/**
 * @brief Initialises the starting viewport of the map
 * 
 * @param screen_width x parameter
 * @param screen_height y parameter
*/
void initialise_viewport(float screen_width, float screen_height);

#endif
