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

    /*_______________________________________________________________________________________*/

    // void* pixels;
    // int pitch;
    // if (SDL_LockTexture(inner_border_map, NULL, &pixels, &pitch) < 0) {
    //     std::printf("Failed to lock texture: %s\n", SDL_GetError());
    //     return FAIL;
    // }

    // // Fill the texture with white pixels (255, 255, 255, 0)
    // Uint32 white_transparent = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 255, 255, 255, 0);
    // int bpp = 4; // Bytes per pixel for ARGB8888
    // for (int y = 0; y < BMP_HEIGHT; ++y) {
    //     for (int x = 0; x < BMP_WIDTH; ++x) {
    //         Uint32* pixel = (Uint32*)((Uint8*)pixels + y * pitch + x * bpp);
    //         *pixel = white_transparent;
    //     }
    // }

    // // Unlock the texture
    // SDL_UnlockTexture(inner_border_map);

    textures.push_back(map);
    textures.push_back(inner_border_map);

    return SUCCESS;
}