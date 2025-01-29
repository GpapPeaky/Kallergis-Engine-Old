#include "SDL2_Images.hpp"

Uint32 SDL2_GetPixel(SDL2_Images* src, int x, int y){
    if(x < 0 || x >= src->position.w || y < 0 || y >= src->position.h){
        return 0; /* Transparent, out of bounds pixel */
    }

    /* Find the pixel */
    Uint8* p = (Uint8*)src->surface->pixels + y * src->surface->pitch + x * src->surface->format->BytesPerPixel;
    Uint32 pixel = 0;

    switch(src->surface->format->BytesPerPixel){
        case 1: pixel = *p;
        case 2: pixel = *(Uint16*)p;
        case 3:
            if(src->surface->format->Rmask == 0x0000ff){
                pixel = (p[2] << 16) | (p[1] << 8) | p[0]; /* If red last BGR */
            }else{
                pixel = (p[0] << 16) | (p[1] << 8) | p[2]; /* If red first (FF hex) RGB */
            }
        case 4: pixel = *(Uint32*)p;
    }

    std::fprintf(stderr ,"%x\n", pixel);
    return pixel; /* Transparent, invalid pixel format */
}

void SDL2_SetPixel(SDL2_Images* dst, int x, int y, Uint32 colour){
    if( x < 0 || x >= dst->position.w || y < 0 || y >= dst->position.h){
        return; /* Out of bounds */
    }

    Uint8* p = (Uint8*)dst->surface->pixels + y * dst->surface->pitch + x * dst->surface->format->BytesPerPixel;

    switch(dst->surface->format->BytesPerPixel){
        case 1: *p = colour; break;
        case 2: *(Uint16*)p = colour; break;
        case 3:
            if(dst->surface->format->Rmask == 0xff0000){ /* RGB */
                p[0] = (colour >> 16) & 0xff;
                p[1] = (colour >> 8) & 0xff;
                p[2] = colour & 0xff;
            }else{ /* BGR */
                p[2] = (colour >> 16) & 0xff;
                p[1] = (colour >> 8) & 0xff;
                p[0] = colour & 0xff;
            }

            break;
        case 4: *(Uint32*)p = colour; break;
    }

    return; /* Success */
}

int SDL2_DrawEdgeOfSurface(SDL2_Images* src, Uint32 colour){
    if(src == nullptr || src->surface == nullptr){ 
        std::fprintf(stderr, "Null img/surface for edge detection\n");
        return -FAIL;
    }

    if(SDL_LockSurface(src->surface) < 0){
        std::fprintf(stderr, "Failed to lock surface for edge detection\n");
        return -FAIL; /* Failled to lock surface */
    }

    /* Query required data */
    Uint8* pixels = (Uint8*)src->surface->pixels;
    int pitch = src->surface->pitch;
    int bpp = src->surface->format->BytesPerPixel;

    /* The images provided are transparent, and the edge detection
    only draws the edges that are neighbouring transparent pixels */
    for(int y = 0 ; y < src->position.h ; ++y){
        for(int x = 0 ; x < src->position.w ; ++x){
            Uint32 pixel = SDL2_GetPixel(src, x, y); /* Get the pixel at <x,y> */
            Uint8 alpha; /* Opacity value, to check for edges */
            SDL_GetRGBA(pixel, src->surface->format, nullptr, nullptr, nullptr, &alpha); /* Get alpha */
            std::fprintf(stderr, "Reach\n");

            if(alpha != 0){ continue; }

            bool isEdge = false;

            for(int dy = -1 ; dy <= 1 && !isEdge ; ++dy){
                for(int dx = - 1 ; dx <= 1 && !isEdge ; ++dx){
                    if(dx == 0 && dy == 0){ continue; } /* Skip the center pixel (the pixel itself) */

                    std::fprintf(stderr, "Checking pixel (%d, %d) neighbor (%d, %d)\n", x, y, x + dx, y + dy);

                    if(x + dx < 0 || x + dx >= src->position.w || y + dy < 0 || y + dy >= src->position.h){
                        continue; /* Out of bounds */
                    }

                    Uint32 neighbour = SDL2_GetPixel(src, x + dx, y + dy); /* Neigbouring pixel to the previously queried pixel */
                    Uint8 neighbourAlpha; /* Neighbour's alpha value */
                    SDL_GetRGBA(neighbour, src->surface->format, nullptr, nullptr, nullptr, &neighbourAlpha);

                    if(neighbourAlpha != 0){
                        isEdge = true;
                    }
                }
            }

            if(isEdge){
                SDL2_SetPixel(src, x, y, colour); /* Is edge, set pixel colour to the given one */
            }
        }
    }

    /* Unlock after we are done with quering data of the surface */
    SDL_UnlockSurface(src->surface);

    return SUCCESS;
}
