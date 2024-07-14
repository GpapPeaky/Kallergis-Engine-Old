#include "init_map.hpp"
#include "pixels.hpp"
#include "../auxf/definitions.aux"
#include "camera.hpp"
#include <algorithm>

#ifndef MAP
/**
 * @brief Map rendering and viewport handling (for zoom-in/-out and WASD movement)
 */
#define MAP

/**
 * @brief renders a surface onto the screen by blitting it
 * 
 * @param surface surface to copy
 * @param screen where to copy to
 * @param camera camera view
 * 
 * @warning zoom, x and y are defaulted to 0 if nothing is used as a parameter
*/
render_capable render_to_screen(SDL_Surface* surface, SDL_Surface* screen, camera cam);

#endif
