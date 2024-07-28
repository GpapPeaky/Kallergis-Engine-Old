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

extern SDL_Texture* map;
extern SDL_Texture* click_map;
extern SDL_Texture* inner_border_map;
extern SDL_Texture* outter_border_map;
extern SDL_Texture* highlight_map;

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

/**
 * @brief initialises the map textures
 * 
 * @returns 0 on SUCCESS 1 on FAIL
 */
err_capable init_map_textures(void);

#endif
