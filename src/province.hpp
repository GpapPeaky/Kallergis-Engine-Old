#include <stdio.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../auxf/definitions.aux"

#ifndef PROV
/**
 * @brief Province struct, most elementary form of ownership in the engine...
 */
#define PROV

/* TODO: Add another 3 fields for development: Administative(taxes), Military(manpower), Production(good)  */
/* TODO: Add another 2 fields for: Goods(coal, iron, steel ...), Infrastructure( none -> dirt path -> railway -> asphalt road -> highway) */
/* TODO: Add another field for: Province population (Will be added to the region one, per province) */
/* NOTE: Population will give an extra 5% of the good produced per 1000 ppl in the entire region, each good will provided different buffs to tax, manpower, mil... */

typedef struct prov{
    std::string prov_name;
    uint prov_id;
    uint region;
    std::string owner_tag;
    SDL_Color prov_colour;
    std::vector<struct prov> prov_con; /* Province connections */
    struct prov* next;
}prov;

#endif

