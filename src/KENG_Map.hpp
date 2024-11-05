#include <algorithm>
#include <vector>
#include "SDL2_Camera.hpp"
#include "KENG_Parser.hpp"
#include "SDL2_Pixel.hpp"
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
 * @brief initialises the map textures, Surface for clicking, the
 * inner border surface and outter border surface
 * 
 * @returns 0 on SUCCESS 1 on FAIL
 */
err_capable KENG_CreateMapTextures(void);

#endif
