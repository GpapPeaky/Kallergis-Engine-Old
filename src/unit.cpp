#include "unit.hpp"

std::vector<unit> units;

void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface){   
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
            new_unit.owner_tag = country.tag; /* Copy tag to owner field */
            break;
        /* WRITE: Complete the function and the interface */
        default:
            break;
    }

    Uint8 r, g, b;
    prov* current = provinces_h[h(prov_id, PROV_M)];

    while(current != NULL){
        if(current->prov_id == prov_id){
            r = current->prov_colour.r;
            g = current->prov_colour.g;
            b = current->prov_colour.b;
            break;
        }

        current = current->next;
    }

    if(current == NULL){
        std::printf("Province ID %d not found\n", prov_id);
        return;
    }

    SDL_LockSurface(surface); // Lock the surface before accessing pixels

    int bpp = surface->format->BytesPerPixel;
    Uint8* pixels = (Uint8*)surface->pixels;

    bool found = false;
    for(int i = 0 ; i < surface->w ; i++){
        for(int j = 0 ; j < surface->h ; j++){
            Uint32 pixel = 0;
            memcpy(&pixel, pixels + j * surface->pitch + i * bpp, bpp);

            Uint8 sr, sg, sb;
            SDL_GetRGB(pixel, surface->format, &sr, &sg, &sb);

            if(sr == r && sg == g && sb == b){
                std::printf("Surface RGB %d %d %d\n", sr, sg, sb);
                std::printf("Parsed RGB %d %d %d\n", r, g, b);
                /* TODO: Make it so that the x,y are in the middle of the province */
                new_unit.rect.x = i;
                new_unit.rect.y = j;
                std::printf("Unit at %d %d\n", i, j);
                found = true;
                break;
            }
        }
        if(found) break;
    }

    SDL_UnlockSurface(surface); // Unlock the surface after accessing pixels

    country.units_num++; /* Increment */
    new_unit.id = country.units_num; /* Assign a unique id to each unit */
    units.push_back(new_unit); /* Push to vector */

    std::printf("\n\nCreated unit for %s %s at %d %d\n\n",country.tag.c_str(),country.country_name.c_str(), new_unit.rect.x, new_unit.rect.y);

    return;
}

render_capable draw_units(SDL_Surface* screen, camera cam){
    if(!units.empty()){
        for(auto& unit : units){
            /* Calculate the positions */
            int screen_x = static_cast<int>((unit.rect.x - cam.rect.x) * cam.zoom);
            int screen_y = static_cast<int>((unit.rect.y - cam.rect.y) * cam.zoom);

            /* Set destination rect */
            SDL_Rect dest_rect = { screen_x, screen_y, unit.img->w, unit.img->h };

            SDL_BlitScaled(unit.img, NULL, screen, &dest_rect);
        }
    }

    return;
}
