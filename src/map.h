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
extern int map_width;
extern int map_height;
extern int x_off;
extern int y_off;

/**
 * @brief renders the map png
 * 
 * @param scale scale of the map
 * @param x x Axis
 * @param y y Axis
*/
render_capable render_map(float scale, int x, int y);

/**
 * @brief Initialises the starting viewport of the map
 * 
 * @param screen_width x parameter
 * @param screen_height y parameter
*/
void initialise_viewport(float screen_width, float screen_height);

SDL_Surface* resize_province_bitmap(float w, float h);

#endif
