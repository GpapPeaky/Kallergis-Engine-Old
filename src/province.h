#include <stdio.h>
#include <SDL2/SDL.h>
#include "definitions.aux"

#ifndef PROV
#define PROV

typedef struct prov{
    uint prov_id;
    uint region;
    SDL_Color prov_colour;
}prov;

#endif

