#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include "definitions.aux"

#ifndef PROV
#define PROV

typedef struct prov{
    std::string prov_name;
    uint prov_id;
    uint region;
    SDL_Color prov_colour;
}prov;

#endif

