#include "unit.hpp"

unit* selected_unit = NULL;
SDL_Texture* inf;
SDL_Texture* art;
SDL_Texture* arm;
SDL_Texture* mec;
std::vector<unit> units;

void init_unit_assets(void){
    SDL_Surface* src = IMG_Load("assets/gfx/units/inf.png");
    if(!src){
        std::printf("Texture couldn't be created\n");
    }

    inf = SDL_CreateTextureFromSurface(renderer, src);
    if(!inf){
        std::printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }

    return;
}

void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface){   /* FIXME */
    if(type != INFANTRY && type != ARTILLERY && type != ARMOR && type != MECHANISED){ 
        std::printf("Incompatible type given in unit creation\n");
        return;
    }

    bool found = false;
    for(auto& reg : country.country_regs){
        for(auto& prov : reg.reg_provs){
            if(prov.prov_id == prov_id){
                std::printf("Province %d found in region %d\n", prov_id, reg.reg_id);
                found = true;
            }
        }
    }

    /* Wrong input, no unit is created */
    if(!found){ std::printf("Province %d doesn't belong to the country %s - %s\n", prov_id, country.tag.c_str(), country.country_name.c_str()); return; }

    unit new_unit;

    switch(type){
        case INFANTRY:
            new_unit.att = 1;
            new_unit.def = 2;
            new_unit.men = 1000;
            new_unit.type = type;
            new_unit.img = inf;   
            new_unit.rect.w = UNIT_SIZE;
            new_unit.rect.h = UNIT_SIZE;
            new_unit.owner_tag = country.tag; /* Copy tag to owner field */
            new_unit.prov_visited = prov_id; /* To know where the troop is */
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
    int count = 0, sum_x = 0, sum_y = 0; /* Number of pixels */

    for(int i = 0 ; i < surface->w ; i++){
        for(int j = 0 ; j < surface->h ; j++){
            Uint32 pixel = 0;
            memcpy(&pixel, pixels + j * surface->pitch + i * bpp, bpp);

            Uint8 sr, sg, sb;
            SDL_GetRGB(pixel, surface->format, &sr, &sg, &sb);

            if(sr == r && sg == g && sb == b){
                count++;
                sum_x += i;
                sum_y += j;
            }
        }
    }

    if (count > 0){
        int mid_x = sum_x / count;
        int mid_y = sum_y / count;

        new_unit.rect.x = mid_x;
        new_unit.rect.y = mid_y;
    }

    SDL_UnlockSurface(surface); /* Unlock the surface after accessing pixels */

    new_unit.id = country.units_num; /* Assign a unique id to each unit */
    units.push_back(new_unit); /* Push to vector */

    std::printf("Created unit for %s %s at %d %d\n",country.tag.c_str(),country.country_name.c_str(), new_unit.rect.x, new_unit.rect.y);
    
    return;
}

render_capable draw_units(camera cam){
    if(!units.empty()){
        for(auto& unit : units){
            /* Calculate the positions */
            int screen_x = static_cast<int>((unit.rect.x - cam.rect.x) * cam.zoom);
            int screen_y = static_cast<int>((unit.rect.y - cam.rect.y) * cam.zoom);

            /* Set destination rect */
            SDL_Rect dest_rect = { screen_x, screen_y, unit.rect.w, unit.rect.h };

            SDL_RenderCopy(renderer, unit.img, NULL, &dest_rect);
        }
    }

    highlight_selected_unit(cam);
    return;
}

render_capable highlight_selected_unit(camera cam){
    if(selected_unit){
        int screen_x = static_cast<int>((selected_unit->rect.x - cam.rect.x) * cam.zoom);
        int screen_y = static_cast<int>((selected_unit->rect.y - cam.rect.y) * cam.zoom);

        SDL_Rect highlight_rect = { screen_x, screen_y, UNIT_SIZE, UNIT_SIZE };

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
        SDL_RenderDrawRect(renderer, &highlight_rect);
    }else{
        return;
    }

    return;
}
