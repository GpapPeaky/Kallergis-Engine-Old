#include "pixels.h"

err_capable generate_pixel_coords(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_province_connections(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_countries_surfaces(void){
    return INSTRUCTION_UNDONE;
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

    /* Locking and unlocking the surface is not really required but it is good practice */
    Uint8* pixel_array = (Uint8*)surface->pixels;

    SDL_LockSurface(surface);
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

// void flood_fill(SDL_Surface* surface, SDL_Window* win, int x, int y, Uint32 target, Uint32 fill_colour){
//     if(!surface) return; /* Surface is NULL */
//     if(target == fill_colour) return; /* Same colour picked, do nothing... return */

//     SDL_LockSurface(surface);

//     Uint32* pixels = (Uint32*)surface->pixels;
//     int w = surface->w;
//     int h = surface->h;

//     std::queue<std::pair<int, int>> points;
//     points.push({x, y}); /* Initial pixels */

//     while(!points.empty()){
//         std::pair<int, int> current = points.front();
//         points.pop();

//         int cx = current.first;
//         int cy = current.second;

//         /* Bounds check */
//         if(cx < 0 || cx >= w || cy < 0 || cy >= h) continue;

//         Uint32 current_colour = pixels[(cy * w) + cx];
//         if(current_colour != target) continue;

//         /* Set the new colour */ 
//         // pixels[(cy * w) + cx] = fill_colour;
//         // SDL_memset(surface->pixels, 255, h * surface->pitch);
//         set_pixel(surface, win, x, y, 255, 255, 255);


//         // Add neighboring pixels to the queue
//         points.push({cx + 1, cy});
//         points.push({cx - 1, cy});
//         points.push({cx, cy + 1});
//         points.push({cx, cy - 1});
//     }

//     SDL_UnlockSurface(surface);
//     // SDL_UpdateWindowSurface(win); /* To be removed -> Add at the end of the inner while in _main.cpp */

//     return;
// }

bool is_black(Uint32 pixel, SDL_PixelFormat* format){
    Uint8 r, g, b;
    SDL_GetRGB(pixel, format, &r ,&g ,&b);
    return (r == 0 && g == 0 && b == 0);
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
