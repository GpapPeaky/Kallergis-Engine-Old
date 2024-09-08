#include <algorithm>
#include <vector>
#include "init_map.hpp"
#include "pixels.hpp"
#include "camera.hpp"
#include "auxf/definitions.aux"

#ifndef MAP
/**
 * @brief Map rendering and viewport handling (for zoom-in/-out and WASD movement)
 */
#define MAP

extern SDL_Surface* click_surface;

extern SDL_Texture* map;
extern SDL_Texture* inner_border_map;
extern SDL_Texture* outter_border_map;

extern std::vector<SDL_Texture*> textures;

/**
 * @brief initialises the map textures
 * 
 * @returns 0 on SUCCESS 1 on FAIL
 */
err_capable init_map_textures(void);

#endif
