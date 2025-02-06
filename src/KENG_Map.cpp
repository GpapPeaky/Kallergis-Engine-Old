#include "KENG_Map.hpp"

SDL_Surface* KENG_ClickSurface; /* Surface For Clicking */

SDL_Texture* KENG_TerrainMap;
SDL_Texture* KENG_Map;
SDL_Texture* KENG_InnerBorderMap;
SDL_Texture* KENG_OutterBorderMap;

std::vector<SDL_Texture*> KENG_MapTextures; /* Map Textures */

int KENG_CreateMapTextures(void){
    KENG_Map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    if(SDL_SetTextureBlendMode(KENG_Map, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set blend mode for country map: %s\n", SDL_GetError());
        return FAIL;
    }
    KENG_InnerBorderMap = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    if(SDL_SetTextureBlendMode(KENG_InnerBorderMap, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set blend mode for inner border map: %s\n", SDL_GetError());
        return FAIL;
    }
    KENG_OutterBorderMap = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    if(SDL_SetTextureBlendMode(KENG_OutterBorderMap, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set blend mode for outer border map: %s\n", SDL_GetError());
        return FAIL;
    }
    KENG_ClickSurface = SDL_LoadBMP("history/map/prov.bmp");
    if(!KENG_ClickSurface){
        std::printf("Loading clicking bitmap failed, path not found\n");
        return FAIL;
    }
    SDL2_LoadBitmap(KENG_Map, "history/map/prov.bmp", 255); /* 255 alpha value for map (currently provinces map),
    it changes in the KENG_MarkCountries(...) function, where we set the alpha to something other than 255, 
    to show the terrain background */

    /* Read terrain bitmap */
    KENG_TerrainMap = KENG_ReadTerrainMap(KENG_TerrainSurface);

    KENG_MapTextures.push_back(KENG_TerrainMap);         /* Index 0 */
    KENG_MapTextures.push_back(KENG_Map);                /* Index 1 */
    KENG_MapTextures.push_back(KENG_InnerBorderMap);     /* Index 2 */
    KENG_MapTextures.push_back(KENG_OutterBorderMap);    /* Index 3 */

    return SUCCESS;
}
