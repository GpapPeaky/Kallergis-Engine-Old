#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_Window.hpp"

#define KENG_TERRAIN_TYPES 5 /* 4 different types of terrain */

#define KENG_TERRAIN_TILE_SIZE 256 /* 256 px per tile */

/* Enumerator for terrain types, easier access to the 
terrain colours array */
typedef enum KENG_TerrainEnum{
    KENG_URBAN,
    KENG_PLAIN,
    KENG_FOREST,
    KENG_HILLS,
    KENG_MOUNTAIN
}KENG_TerrainEnum;

/* Terrain surface */
extern SDL_Surface* KENG_TerrainSurface;

/* Terrain colours array */
extern SDL_Colour KENG_TerrainColours[KENG_TERRAIN_TYPES];

/* Terrain tiles surfaces array */
extern SDL_Surface* KENG_TerrainTextures[KENG_TERRAIN_TYPES];

/**
 * @brief Initialises the terrain textures
 */
void KENG_CreateTerrainSurfaces(void);

/**
 * @brief Read the terrain map and copies a texture to it
 * 
 * @param terrainMap Terrain bitmap to read
 * 
 * @returns The created texture
 */
SDL_Texture* KENG_ReadTerrainMap(SDL_Surface* terrainMap);
