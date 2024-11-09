#include "KENG_Map.hpp"

SDL_Surface* KENG_clickSurface; /* Surface For Clicking */

SDL_Texture* map; /* Main Map */
SDL_Texture* inner_border_map;
SDL_Texture* outter_border_map;

std::vector<SDL_Texture*> textures; /* Map Textures */

int KENG_CreateMapTextures(void){
    map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    inner_border_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    if(SDL_SetTextureBlendMode(inner_border_map, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set blend mode: %s\n", SDL_GetError());
        return FAIL;
    }
    outter_border_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    if(SDL_SetTextureBlendMode(outter_border_map, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set blend mode: %s\n", SDL_GetError());
        return FAIL;
    }
    KENG_clickSurface = SDL_LoadBMP("history/map/prov.bmp");
    if(!KENG_clickSurface){
        std::printf("Loading clicking bitmap failed, path not found\n");
        return FAIL;
    }
    SDL2_LoadBitmap(map, "history/map/prov.bmp");

    textures.push_back(map);
    textures.push_back(inner_border_map);

    return SUCCESS;
}