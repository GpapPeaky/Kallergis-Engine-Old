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

// void hsv2rgb(float h, float s, float v, Uint8& r, Uint8& g, Uint8& b) {
//     int i = static_cast<int>(h * 6);
//     float f = h * 6 - i;
//     float p = v * (1 - s);
//     float q = v * (1 - f * s);
//     float t = v * (1 - (1 - f) * s);

//     switch (i % 6) {
//         case 0: r = static_cast<Uint8>(v * 255); g = static_cast<Uint8>(t * 255); b = static_cast<Uint8>(p * 255); break;
//         case 1: r = static_cast<Uint8>(q * 255); g = static_cast<Uint8>(v * 255); b = static_cast<Uint8>(p * 255); break;
//         case 2: r = static_cast<Uint8>(p * 255); g = static_cast<Uint8>(v * 255); b = static_cast<Uint8>(t * 255); break;
//         case 3: r = static_cast<Uint8>(p * 255); g = static_cast<Uint8>(q * 255); b = static_cast<Uint8>(v * 255); break;
//         case 4: r = static_cast<Uint8>(t * 255); g = static_cast<Uint8>(p * 255); b = static_cast<Uint8>(v * 255); break;
//         case 5: r = static_cast<Uint8>(v * 255); g = static_cast<Uint8>(p * 255); b = static_cast<Uint8>(q * 255); break;
//     }
// }

// void colour_box(SDL_Surface* surface, int x, int y, int width, int height) {
//     SDL_LockSurface(surface);
//     Uint32* pixels = (Uint32*)surface->pixels;

//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             float hue = static_cast<float>(j) / width; // Hue changes horizontally
//             float saturation = 1.0; // Saturation can be a constant (1.0 for full saturation)
//             float value = static_cast<float>(height - i) / height; // Value changes vertically

//             Uint8 r, g, b;
//             hsv2rgb(hue, saturation, value, r, g, b);
//             Uint32 color = SDL_MapRGB(surface->format, r, g, b);

//             int pixel_x = x + j;
//             int pixel_y = y + i;

//             if (pixel_x >= 0 && pixel_x < surface->w && pixel_y >= 0 && pixel_y < surface->h) {
//                 pixels[pixel_y * surface->w + pixel_x] = color;
//             }
//         }
//     }
//     SDL_UnlockSurface(surface);
// }

void mark_borders(SDL_Surface* outter_surface, SDL_Surface* inner_surface, SDL_Window* win, int border_colour){
    // Uint8* pixel_array = (Uint8*)inner_surface->pixels;
    // int bpp = inner_surface->format->BytesPerPixel;

    // /* Inner Borders First */
    // for(int i = 0 ; i < inner_surface->w ; i++){
    //     for(int j = 0 ; j < inner_surface->h ; j++){

    //         int r = pixel_array[j * inner_surface->pitch + i * bpp + 0];
    //         int g = pixel_array[j * inner_surface->pitch + i * bpp + 1];
    //         int b = pixel_array[j * inner_surface->pitch + i * bpp + 2];
    //         if(r != 0 && g != 0 && b != 0){                
    //             if( /* red */
    //                 ((pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 0] != r  && pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 0] != 255) ||
    //                 (pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 0] != r && pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 0] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 0] != r && pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 0] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 0] != r && pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 0] != 255)) &&

    //                 /* green */
    //                 ((pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 1] != g && pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 1] != 255) ||
    //                 (pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 1] != g && pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 1] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 1] != g && pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 1] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 1] != g && pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 1] != 255)) &&

    //                 /* blue */
    //                 ((pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 2] != b && pixel_array[(j + 1) * inner_surface->pitch + i * bpp + 2] != 255) ||
    //                 (pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 2] != b && pixel_array[(j - 1) * inner_surface->pitch + i * bpp + 2] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 2] != b && pixel_array[j * inner_surface->pitch + (i - 1) * bpp + 2] != 255) ||
    //                 (pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 2] != b && pixel_array[j * inner_surface->pitch + (i + 1) * bpp + 2] != 255))

    //                 /* Not white */
    //             ){
    //                 set_pixel(outter_surface, win, i, j, 150, 150, 150);
    //             }
    //         }
    //     }
    // }

    Uint8* pixel_array = (Uint8*)outter_surface->pixels;
    int bpp = outter_surface->format->BytesPerPixel;

    /* Outer Borders Second */
    for(int i = 0 ; i < outter_surface->w ; i++){
        for(int j = 0 ; j < outter_surface->h ; j++){
            int r = pixel_array[j * outter_surface->pitch + i * bpp + 0];
            int g = pixel_array[j * outter_surface->pitch + i * bpp + 1];
            int b = pixel_array[j * outter_surface->pitch + i * bpp + 2];
            if(r != 0 && g != 0 && b != 0){
                if( /* red */
                    ((pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 0] != r  && pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 0] != border_colour) ||
                    (pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 0] != r && pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 0] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 0] != r && pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 0] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 0] != r && pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 0] != border_colour)) &&

                    /* green */
                    ((pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 1] != g && pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 1] != border_colour) ||
                    (pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 1] != g && pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 1] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 1] != g && pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 1] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 1] != g && pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 1] != border_colour)) &&

                    /* blue */
                    ((pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 2] != b && pixel_array[(j + 1) * outter_surface->pitch + i * bpp + 2] != border_colour) ||
                    (pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 2] != b && pixel_array[(j - 1) * outter_surface->pitch + i * bpp + 2] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 2] != b && pixel_array[j * outter_surface->pitch + (i - 1) * bpp + 2] != border_colour) ||
                    (pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 2] != b && pixel_array[j * outter_surface->pitch + (i + 1) * bpp + 2] != border_colour))

                    /* Not white */
                ){
                    set_pixel(outter_surface, win, i, j, border_colour, border_colour, border_colour); /* Set Border To Black For Now */
                }
            }
        }
    }

    return;
}

void print_country_colours(void){
    for(const auto& cou : countries){
        std::printf("%s, %s RGB:%d %d %d\n",cou.tag.c_str(), cou.country_name.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
    }

    return;
}
