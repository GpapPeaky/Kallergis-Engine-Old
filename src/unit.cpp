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

void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface){
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

    /* Untransformed coords */
    if(count > 0){
        int mid_x = sum_x / count;
        int mid_y = sum_y / count;

        new_unit.rect.x = mid_x;
        new_unit.rect.y = mid_y;
    }

    SDL_UnlockSurface(surface); /* Unlock the surface after accessing pixels */

    new_unit.id = country.units_num; /* Assign a unique id to each unit */
    units.push_back(new_unit); /* Push to vector */

    std::printf("Created unit for %s %s at %d %d\n",country.tag.c_str(),country.country_name.c_str(), new_unit.rect.x, new_unit.rect.y); /* World Coords / surface coords */
    
    return;
}

void move_unit(SDL_Surface* surface, camera cam){
    if(selected_unit){
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y); /* We use the untransformed coord for the mouse */

        int world_x = static_cast<int>(mouse_x / cam.zoom + cam.rect.x);
        int world_y = static_cast<int>(mouse_y / cam.zoom + cam.rect.y);

        SDL_LockSurface(surface);

        int bpp = surface->format->BytesPerPixel;
        Uint8* pixels = (Uint8*)surface->pixels;

        /* Pixel at mouse position */
        Uint32 pixel = 0;
        Uint8* pixel_ptr = pixels + (world_y * surface->pitch) + (world_x * bpp);
        switch(bpp){
            case 3: /* 24-bit format (little-endian) */
                pixel = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
                break;
            case 4: /* 32-bit format */
                pixel = *(Uint32*)pixel_ptr;
                break;
            default:
                std::printf("Unsupported pixel format\n");
                SDL_UnlockSurface(surface);
                return;
        }
        Uint8 r, g, b;
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);

        int count = 0, sum_x = 0, sum_y = 0; /* Number of pixels */

        /* PARSE ONLY WHAT THE CAMERA SEES -> INCREASE IN SPEED */
        for(int i = cam.rect.x ; i < cam.rect.w + cam.rect.x ; i++){
            for(int j = cam.rect.y ; j < cam.rect.y + cam.rect.h ; j++){
                Uint32 current_pixel = 0;
                Uint8* current_pixel_ptr = pixels + (j * surface->pitch) + (i * bpp);
                switch(bpp){
                    case 3: /* 24-bit format (little-endian) */
                        current_pixel = (current_pixel_ptr[0] << 16) | (current_pixel_ptr[1] << 8) | current_pixel_ptr[2]; /* 0x640000 | 0x9600 | 0xC8 results in 0x6496C8 */
                        break;
                    case 4: /* 32-bit format */
                        current_pixel = *(Uint32*)current_pixel_ptr;
                        break;
                    default:
                        std::printf("Unsupported pixel format\n");
                        SDL_UnlockSurface(surface);
                        return;
                }
                Uint8 sr, sg, sb; /* For the check */
                SDL_GetRGB(current_pixel, surface->format, &sr, &sg, &sb);

                if(sr == r && sg == g && sb == b){
                    count++;
                    sum_x += i;
                    sum_y += j;
                }
            }
        }

        if(count > 0){
            selected_unit->rect.x = sum_x / count;
            selected_unit->rect.y = sum_y / count;

            for(int i = 0 ; i < prov_hash_s ; i++){
                prov* current = provinces_h[i];
                while(current != NULL){
                    if(current->prov_colour.r == b && current->prov_colour.g == g && current->prov_colour.b == r){ /* HUH? Little endian */
                        selected_unit->prov_visited = current->prov_id;
                        break;
                    }
                    current = current->next;
                }
            }
        }

        SDL_UnlockSurface(surface); /* Unlock the surface after accessing pixels */

        return;
    }

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
