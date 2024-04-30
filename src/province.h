#include <stdio.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "definitions.aux"

#ifndef PROV
#define PROV

typedef struct prov{
    std::string prov_name;
    uint prov_id;
    uint region;
    SDL_Color prov_colour;
    std::vector<struct prov> prov_con; /* Province connections */
}prov;

#endif

