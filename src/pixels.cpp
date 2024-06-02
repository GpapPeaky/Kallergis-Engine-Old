#include "pixels.h"

SDL_Surface* country_surface; /* Changes with every update */
SDL_Texture* country_texture;

err_capable generate_pixel_coords(std::string fname){
    return INSTRUCTION_UNDONE;
}

err_capable generate_province_connections(std::string fname){
    return INSTRUCTION_UNDONE;
}

/* FIXME */
err_capable generate_countries_surfaces(void){
    /* Scan for country rgb value */
    /* int map_x = (x - viewport.x) / map_scale; /* viewport offset to bring the camera to the correct place for the rgb values */
    /* int map_y = (y - viewport.y) / map_scale; */
    Uint8 r, g, b;
    country_surface = SDL_CreateRGBSurface(0, DEV_SCREEN_W, DEV_SCREEN_H, 32, 0, 0, 0, 0); /* Use viewport produced x and y to reduce CPU payloads */
    if(!country_surface){
        std::printf("Failed to create couintries surface\n"); 
        SDL_FreeSurface(country_surface);
        return FAIL;
    }

    /* Might have to destroy the texture here... */
    for(int j = 0 ; j < map_surface->h ; j++){
        for(int p = 0 ; p < map_surface->w ; p++){
            /* Parsing bitmap */
            Uint32 pixel = ((Uint32*)map_surface->pixels)[j * map_surface->pitch / 4 + p];
            SDL_GetRGB(pixel, map_surface->format, &r, &g, &b);
            if(r == 0 && g == 0 && b == 0){
                continue; /* Go to the next pixel, if 0, 0, 0 RGB is found */
            }

            for(int i = 0 ; i < countries.size() ; i++){
                /* std::printf("%s\n", countries[i].country_name.c_str()); */
                if(r == countries[i].country_rgb.r && g == countries[i].country_rgb.g && b == countries[i].country_rgb.b){
                    Uint32 country_pixel = SDL_MapRGB(country_surface->format, r, g, b); /* Fixing the pixel format */
                    ((Uint32*)country_surface->pixels)[j * country_surface->pitch / 4 + p] = country_pixel; /* Changing the RGB value of the new surface */
                    std::printf("%d %d %d\n", r, g, b);
                }
                break;
            }   
        }
    }

    /* Change the rgb value of the created surface on the specified location */
    country_texture = SDL_CreateTextureFromSurface(renderer, country_surface); /* Might bottleneck the GPU */
    if(!country_texture){
        std::printf("Failed to create couintries texture\n"); 
        SDL_FreeSurface(country_surface);
        return FAIL;
    }

    /* Completed Surface Processing */
    SDL_FreeSurface(country_surface);
    SDL_DestroyTexture(country_texture);

    return SUCCESS;
}
