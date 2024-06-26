#include "pixels.h"

SDL_Surface* country_surface; /* Changes with every update */
SDL_Texture* country_texture;

err_capable generate_pixel_coords(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_province_connections(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_countries_surfaces(void){
    return INSTRUCTION_UNDONE;
}

bool is_black(Uint32 pixel, SDL_PixelFormat* format){
    Uint8 r, g, b;
    SDL_GetRGB(pixel, format, &r ,&g ,&b);
    return (r == 0 && g == 0 && b == 0);
}

SDL_Colour get_country_colour(const std::string& owner_tag){
    for(const auto& cou : countries){
        if(cou.tag == owner_tag){
            return cou.country_rgb;
        }
    }

    return { 0, 0, 0, ALPHA }; /* Country not found, return black */
}
