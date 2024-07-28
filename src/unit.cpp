#include "unit.hpp"

std::vector<unit> units;

// void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface){   /* FIXME */
//     if(type != INFANTRY && type != ARTILLERY && type != ARMOR && type != MECHANISED){ 
//         std::printf("Incompatible type given in unit creation\n");
//         return;
//     }

//     bool found = false;
//     for(auto& reg : country.country_regs){
//         for(auto& prov : reg.reg_provs){
//             if(prov.prov_id == prov_id){
//                 std::printf("Province %d found in region %d\n", prov_id, reg.reg_id);
//                 found = true;
//             }
//         }
//     }

//     /* Wrong input, no unit is created */
//     if(!found){ std::printf("Province %d doesn't belong to the country %s - %s\n", prov_id, country.tag.c_str(), country.country_name.c_str()); return; }

//     unit new_unit;

//     switch(type){
//         case INFANTRY:
//             new_unit.att = 1;
//             new_unit.def = 2;
//             new_unit.men = 1000;
//             new_unit.type = type;
//             new_unit.img = IMG_Load("assets/gfx/units/inf.png");    
//             new_unit.rect.w = new_unit.img->w;
//             new_unit.rect.h = new_unit.img->h;
//             new_unit.owner_tag = country.tag; /* Copy tag to owner field */
//             new_unit.prov_visited = prov_id; /* To know where the troop is */
//             break;
//         /* WRITE: Complete the function and the interface */
//         default:
//             break;
//     }

//     Uint8 r, g, b;
//     prov* current = provinces_h[h(prov_id, PROV_M)];

//     while(current != NULL){
//         if(current->prov_id == prov_id){
//             r = current->prov_colour.r;
//             g = current->prov_colour.g;
//             b = current->prov_colour.b;
//             break;
//         }

//         current = current->next;
//     }

//     if(current == NULL){
//         std::printf("Province ID %d not found\n", prov_id);
//         return;
//     }

//     SDL_LockSurface(surface); // Lock the surface before accessing pixels

//     int bpp = surface->format->BytesPerPixel;
//     Uint8* pixels = (Uint8*)surface->pixels;
//     int count = 0, sum_x = 0, sum_y = 0; /* Number of pixels */

//     for(int i = 0 ; i < surface->w ; i++){
//         for(int j = 0 ; j < surface->h ; j++){
//             Uint32 pixel = 0;
//             memcpy(&pixel, pixels + j * surface->pitch + i * bpp, bpp);

//             Uint8 sr, sg, sb;
//             SDL_GetRGB(pixel, surface->format, &sr, &sg, &sb);

//             if(sr == r && sg == g && sb == b){
//                 count++;
//                 sum_x += i;
//                 sum_y += j;
//             }
//         }
//     }

//     if (count > 0){
//         int mid_x = sum_x / count;
//         int mid_y = sum_y / count;

//         new_unit.rect.x = mid_x;
//         new_unit.rect.y = mid_y;
//     }

//     SDL_UnlockSurface(surface); /* Unlock the surface after accessing pixels */

//     SDL_LockSurface(new_unit.img);

//     for(int x = 0 ; x < new_unit.img->w ; x++){
//         for(int y = 0 ; y < new_unit.img->w ; y++){
//             if(x == 0 || y == 0 || x == new_unit.img->w - 1 || y == new_unit.img->h - 1){
//                 set_pixel(new_unit.img, win, x, y, 255, 255, 255, 150); /* Add an outline to the unit */
//             }
//         }
//     }

//     SDL_UnlockSurface(new_unit.img);

//     country.units_num++; /* Increment */
//     new_unit.id = country.units_num; /* Assign a unique id to each unit */
//     units.push_back(new_unit); /* Push to vector */

//     std::printf("Created unit for %s %s at %d %d\n",country.tag.c_str(),country.country_name.c_str(), new_unit.rect.x, new_unit.rect.y);
    
//     return;
// }

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
