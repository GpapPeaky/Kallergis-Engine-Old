#include "events.hpp"

eng_event info_on_hover(void){

    /* Info box: 129 - 114 */
    return;
}

eng_event highlight_on_click(int x, int y, SDL_Surface* map){

    Uint8 r, g, b;

    /* Bounds check */
    if (x < 0 || x >= map->w || y < 0 || y >= map->h) {
        return;
    }

    int index = y * map->pitch + x * 3;

    b = ((Uint8*)map->pixels)[index + 0];
    g = ((Uint8*)map->pixels)[index + 1];
    r = ((Uint8*)map->pixels)[index + 2];

    SDL_Color clicked = { r, g, b, ALPHA };

    for(int i = 0 ; i < prov_hash_s ; i++){
        prov* current = provinces_h[h(i, PROV_M)];
        while(current != NULL){
            if(current->prov_colour.r == clicked.r && current->prov_colour.g == clicked.g && current->prov_colour.b == clicked.b){
                std::printf("Clicked Province: %s\n", current->prov_name.c_str());
                return;
            }
            current = current->next;
        }
    }

    return;
}

eng_event pan_map(int d_x, int d_y){
    return;
}

void events_handling(bool& quit, camera& cam){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h); /* For The Camera Readjustment */
        if(e.type == SDL_QUIT){
            quit = true;
        }else if(e.type == SDL_MOUSEWHEEL){
            /* Calculate new zoom level */
            float zoom_factor = (e.wheel.y > 0) ? 1.1f : 0.9f;
            cam.zoom *= zoom_factor;

            if(cam.zoom < 0.1f) cam.zoom = 0.1f;
            if(cam.zoom > 10.0f) cam.zoom = 10.0f;

            int center_x = cam.rect.x + cam.rect.w / 2;
            int center_y = cam.rect.y + cam.rect.h / 2;

            int new_w = static_cast<int>(w / cam.zoom); /* The handle_camera() function had 1000 and 900 px */
            int new_h = static_cast<int>(h / cam.zoom);

            cam.rect.x = center_x - new_w / 2;
            cam.rect.y = center_y - new_h / 2;
            cam.rect.w = new_w;
            cam.rect.h = new_h;
        }else if(e.type == SDL_KEYDOWN){
            /* Initial Values */
            float vel_x = 1.0f;
            float vel_y = 1.0f;

            Uint32 prev_time = SDL_GetTicks();
            Uint32 current_time;
            float dt = 1.0f; /* Initial Value */

            if(e.key.keysym.sym == SDLK_w){
                vel_y -= ACC / cam.zoom - 1;
            }else if(e.key.keysym.sym == SDLK_s){
                vel_y += ACC / cam.zoom + 1;
            }else if(e.key.keysym.sym == SDLK_a){
                vel_x -= ACC / cam.zoom - 1;
            }else if(e.key.keysym.sym == SDLK_d){
                vel_x += ACC / cam.zoom + 1;
            }else if(e.key.keysym.sym == SDLK_e){
                SDL_SaveBMP(map, "bin/output.bmp");
                quit = true;
            }

            current_time = SDL_GetTicks();
            dt = (current_time - prev_time) / 1000.0f; /* Convert to seconds */

            cam.rect.x += static_cast<int>(vel_x * (dt + 0.1f));
            cam.rect.y += static_cast<int>(vel_y * (dt + 0.1f));

            /* Decelerate */
            vel_x *= DEC;
            vel_y *= DEC;
        }else if(e.type == SDL_MOUSEBUTTONDOWN){
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            int surface_x = (mouse_x / cam.zoom) + cam.rect.x;
            int surface_y = (mouse_y / cam.zoom) + cam.rect.y;
            highlight_on_click(surface_x, surface_y, click_map);
        }
    }
}
