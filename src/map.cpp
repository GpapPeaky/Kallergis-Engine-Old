#include "map.hpp"

SDL_Texture* map;
SDL_Texture* click_map;
SDL_Texture* inner_border_map;
SDL_Texture* outter_border_map;
SDL_Texture* highlight_map;

err_capable init_map_textures(void){

    map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BMP_WIDTH, BMP_HEIGHT);
    load_bitmap(map, "history/map/province.bmp");

    return SUCCESS;
}