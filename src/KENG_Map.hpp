#include <algorithm>
#include <vector>

#include "SDL2_Camera.hpp"
#include "SDL2_Pixel.hpp"

#include "KENG_Parser.hpp"
#include "KENG_Terrain.hpp"

#include "auxf/definitions.aux"

#ifndef MAP
/**
 * @brief Map rendering and viewport handling (for zoom-in/-out and WASD movement)
 */
#define MAP

extern SDL_Surface* KENG_ClickSurface;      /* Bitmap surface, different RGBs for clicking */

extern SDL_Texture* KENG_TerrainMap;        /* Terrain map */
extern SDL_Texture* KENG_Map;               /* Country colours map */
extern SDL_Texture* KENG_InnerBorderMap;    /* Province border map */
extern SDL_Texture* KENG_OutterBorderMap;   /* Country border map */

extern std::vector<SDL_Texture*> KENG_MapTextures; /* Map textures */

/**
 * @brief initialises the map textures, Surface for clicking, the
 * inner border surface and outter border surface
 * 
 * @returns 0 on SUCCESS 1 on FAIL
 */
int KENG_CreateMapTextures(void);

#endif
