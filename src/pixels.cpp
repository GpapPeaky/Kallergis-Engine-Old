#include "pixels.hpp"

err_capable generate_pixel_coords(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_province_connections(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_countries_surfaces(SDL_Surface* surface, SDL_Window* win){
    /* We need to check for Non-black pixels */
    Uint8* pixel_array = (Uint8*)map->pixels;
    for(int i = 0 ; i < map->w ; i++){
        for(int j = 0 ; j < map->h ; j++){
            if(
                pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 0] != 0 &&
                pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 1] != 0 &&
                pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 2] != 0
            ){
                /* Save the pixel for more checks */
                Uint8 r, g, b;
                r = pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 2];
                g = pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 1];
                b = pixel_array[j * map->pitch + i * map->format->BytesPerPixel + 0];
                for(auto& cou : countries){
                    SDL_Colour current_rgb;
                    current_rgb.r = cou.country_rgb.r;
                    current_rgb.g = cou.country_rgb.g;
                    current_rgb.b = cou.country_rgb.b;
                    // current_rgb = { 255, 255, 255 };

                    for(auto& reg : cou.country_regs){
                        for(auto& prov : reg.reg_provs){
                            if(
                                prov.prov_colour.r == r &&
                                prov.prov_colour.g == g &&
                                prov.prov_colour.b == b
                            ){
                                /* First Non Black at 813 x 602 */
                                // std::printf("Non-black pixel found and painted at %d %d\n", i, j);
                                set_pixel(map, win, i, j, current_rgb.r, current_rgb.g, current_rgb.b);
                            }else{
                                /* Make sure that all provinces have no 0 R, G, B value, else it will crash */
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }

    return SUCCESS;
}

void set_pixel(SDL_Surface* surface, SDL_Window* win, int x, int y, Uint8 r, Uint8 g, Uint8 b){
    SDL_LockSurface(surface); /* Lock in order to edit */
    Uint8* pixel_array = (Uint8*)surface->pixels;

    /* Making the correct offsets | format: { B, G, R } */
    /* It becomes { R, G, B } if a surface is blitted onto the window surface (screen) -> offsets need to change */
    pixel_array[y * surface->pitch + x * surface->format->BytesPerPixel + 0] = r; 
    pixel_array[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = g;
    pixel_array[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = b;
    SDL_UnlockSurface(surface);

    return;
}

void pixel_screen_fill(SDL_Surface* surface, SDL_Window* win){
    SDL_LockSurface(surface);
    /* Locking and unlocking the surface is not really required but it is good practice */
    Uint8* pixel_array = (Uint8*)surface->pixels;
    for(int i = 0 ; i < surface->w ; i++){
        for(int j = 0 ; j < surface->h ; j++){
            if(
                pixel_array[j * surface->pitch + i * surface->format->BytesPerPixel + 0] == 0 &&
                pixel_array[j * surface->pitch + i * surface->format->BytesPerPixel + 1] == 0 &&
                pixel_array[j * surface->pitch + i * surface->format->BytesPerPixel + 2] == 0
            ){
                set_pixel(surface, win, i, j, 255, 255, 255); /* Simple Example of image manipulation, quite fast... */
            }
        }
    }
    SDL_UnlockSurface(surface);

    return;
}

SDL_Colour get_country_colour(const std::string& owner_tag){
    for(const auto& cou : countries){
        if(strcmp(owner_tag.c_str(), cou.tag.c_str()) == 0){
            return cou.country_rgb;
        }
    }

    return { 0, 0, 0, ALPHA }; /* Country not found, return black */
}

void print_country_colours(void){
    for(const auto& cou : countries){
        std::printf("%s, %s RGB:%d %d %d\n",cou.tag.c_str(), cou.country_name.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
    }

    return;
}
