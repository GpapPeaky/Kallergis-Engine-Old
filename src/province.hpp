#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "auxf/definitions.aux"
#include "economy.hpp"

#ifndef PROV
/**
 * @brief Province struct, most elementary form of ownership in the engine...
 */
#define PROV

typedef struct prov{
    std::string prov_name;
    uint prov_id;
    uint region;
    std::string owner_tag;
    SDL_Color prov_colour;
    eco province_economy;
    std::vector<struct prov> prov_con; /* Province connections */
    struct prov* next;
}prov;

#endif

