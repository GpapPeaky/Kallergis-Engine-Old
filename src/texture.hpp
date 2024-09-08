#include "SDL2/SDL.h"

typedef struct image_data{
    int w;
    int h;
    int pitch;
    Uint32 format;
    SDL_PixelFormat* pixel_format
    void* pixels;
}imgd;
