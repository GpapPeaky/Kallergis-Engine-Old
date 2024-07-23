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
                                set_pixel(map, win, i, j, current_rgb.r, current_rgb.g, current_rgb.b, ALPHA);
                            }else{
                                /* WARN: Make sure that all provinces have no 0 R, G, B value, else it will crash */
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

void set_pixel(SDL_Surface* surface, SDL_Window* win, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255){
    SDL_LockSurface(surface); /* Lock in order to edit */
    int bpp = surface->format->BytesPerPixel;
    Uint8* pixel_array = (Uint8*)surface->pixels;
    Uint8* p = pixel_array + y * surface->pitch + x * bpp;
    Uint32 pixel_value;

    /* Making the correct offsets | format: { B, G, R } */
    /* It becomes { R, G, B } if a surface is blitted onto the window surface (screen) -> offsets need to change */
    switch(bpp){
        case 3: /* 24 bit surface */
            p[0] = r;
            p[1] = g;
            p[2] = b;
            break;
        case 4:
            pixel_value = SDL_MapRGBA(surface->format, r, g, b, a);
            *(Uint32*)p = pixel_value;
            break;
        default:
            std::printf("Unsupported pixel format\n");
            break;
    }

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
                set_pixel(surface, win, i, j, 255, 255, 255, ALPHA); /* Simple Example of image manipulation, quite fast... */
            }
        }
    }
    SDL_UnlockSurface(surface);

    return;
}

void mark_borders(SDL_Surface* src, SDL_Surface* dst, SDL_Window* win, int border_colour){

    /* To Avoid Conflict Between 2 iterations */
    int counter_colour;
    if(border_colour == INNER_BORDER_COLOUR_GS){
        counter_colour = OUTTER_BORDER_COLOUR_GS;
    }else if(border_colour == OUTTER_BORDER_COLOUR_GS){
        counter_colour = INNER_BORDER_COLOUR_GS;
    }else{
        std::printf("Incorrect Colour Chosen For Border Generation\n");
        return;
    }

    Uint8* pixel_array = (Uint8*)src->pixels;
    int bpp = src->format->BytesPerPixel;

    if(src != NULL){
        pixel_array = (Uint8*)src->pixels;
        bpp = src->format->BytesPerPixel;

        for(int i = 0 ; i < src->w ; i++){
            for(int j = 0 ; j < src->h ; j++){
                int r = pixel_array[j * src->pitch + i * bpp + 0];
                int g = pixel_array[j * src->pitch + i * bpp + 1];
                int b = pixel_array[j * src->pitch + i * bpp + 2];

                if(r == 0 && g == 0 && b == 0){
                    continue;
                }
                
                bool is_border = false;

                /* Check Neighours */
                for (int y_off = -1; y_off <= 1; y_off++) {
                    for (int x_off = -1; x_off <= 1; x_off++) {
                        if(x_off == 0 && y_off == 0) continue; /* Skip current pixel */

                        int x_neighbor = i + x_off;
                        int y_neighbor = j + y_off;

                        /* Check if it is in-bounds */
                        if(x_neighbor >= 0 && x_neighbor < src->w && y_neighbor >= 0 && y_neighbor < src->h){
                            Uint8 r_neighbor = pixel_array[y_neighbor * src->pitch + x_neighbor * bpp + 0];
                            Uint8 g_neighbor = pixel_array[y_neighbor * src->pitch + x_neighbor * bpp + 1];
                            Uint8 b_neighbor = pixel_array[y_neighbor * src->pitch + x_neighbor * bpp + 2];

                            if((r_neighbor != r || g_neighbor != g || b_neighbor != b) &&
                                r_neighbor != border_colour && g_neighbor != border_colour && b_neighbor != border_colour &&
                                r_neighbor != counter_colour && g_neighbor != counter_colour && b_neighbor != counter_colour){
                                is_border = true;
                                break;
                            }
                        }
                    }
                    if(is_border) break;
                }

                if(is_border && (border_colour == OUTTER_BORDER_COLOUR_GS)){
                    set_pixel(dst, win, i, j, 255, border_colour, border_colour, ALPHA);
                }else if(is_border && (border_colour == INNER_BORDER_COLOUR_GS)){
                    set_pixel(dst, win, i, j, border_colour, border_colour, border_colour, 130);
                }
            }
        }
    }

    return;
}

void print_country_colours(void){
    for(const auto& cou : countries){
        std::printf("%s,\t%s\tRGB: <%d,%d,%d>\n",cou.tag.c_str(), cou.country_name.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
    }

    return;
}
