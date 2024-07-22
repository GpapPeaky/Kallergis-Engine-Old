#include "unit.hpp"

std::vector<unit> units;

void create_unit(unit_t type, cou country, int x, int y){   
    if(type != INFANTRY && type != ARTILLERY && type != ARMOR && type != MECHANISED){ 
        std::printf("Incompatible type given in unit creation\n");
        return;
    }
    // if(std::find(countries.begin(), countries.end(), country) == countries.end()){
    //     std::printf("Country specified, %s not found\n", country.tag.c_str());
    //     return;
    // } /* Error */

    unit new_unit;

    switch(type){
        case INFANTRY:
            new_unit.att = 1;
            new_unit.def = 2;
            new_unit.men = 1000;
            new_unit.type = type;
            new_unit.img = IMG_Load("assets/gfx/units/inf.png");    
            new_unit.rect.w = new_unit.img->w;
            new_unit.rect.h = new_unit.img->h;
            new_unit.rect.x = x;
            new_unit.rect.y = y;
            new_unit.owner_tag = country.tag; /* Copy tag to owner field */
            break;
        default:
            break;
        }

    country.units_num++; /* Increment */
    new_unit.id = country.units_num; /* Assign a unique id to each unit */
    units.push_back(new_unit); /* Push to vector */

    std::printf("\n\nCreated unit for %s %s\n\n",country.tag.c_str(),country.country_name.c_str());

    return;
}


render_capable draw_units(SDL_Surface* screen){
    if(!units.empty()){
        for(auto& unit : units){
            SDL_UpperBlitScaled(unit.img, NULL, screen, &unit.rect);
        }
    }
}
