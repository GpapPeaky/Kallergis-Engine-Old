#include "events.h"

eng_event info_on_hover(void){

    /* Info box: 129 - 114 */
    return;
}

eng_event highlight_on_click(int x, int y){

    Uint8 r, g, b;

    int map_x = (x - viewport.x) / map_scale; /* viewport offset to bring the camera to the correct place for the rgb values*/
    int map_y = (y - viewport.y) / map_scale;

    int index = map_y * map_surface->pitch + map_x * 3;

    b = ((Uint8*)map_surface->pixels)[index];
    g = ((Uint8*)map_surface->pixels)[index + 1];
    r = ((Uint8*)map_surface->pixels)[index + 2];

    SDL_Color clicked = {r, g, b, ALPHA};

    for(int i = 0 ; i < prov_hash_s ; i++){
        prov* current = provinces_h[h(i, PROV_M)];
        while(current != NULL){
            if(current->prov_colour.r == clicked.r && current->prov_colour.g == clicked.g && current->prov_colour.b == clicked.b){
                std::printf("Clicked Province: %s\n", current->prov_name.c_str());
                break;
            }
            current = current->next;
        }
    }

    return;
}

eng_event pan_map(int d_x, int d_y){
    /* FIXME */

    return;
}

void events_handling(bool& quit){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_e){
                    quit = true;
                }

                /* WASD panning */
                if(e.key.keysym.sym == SDLK_w){
                    y_off -= -50;
                }
                if(e.key.keysym.sym == SDLK_a){
                    x_off -= -50;
                }
                if(e.key.keysym.sym == SDLK_s){
                    y_off += -50;
                }
                if(e.key.keysym.sym == SDLK_d){
                    x_off += -50;
                }
                #ifdef PIXELS
                    if(e.key.keysym.sym == SDLK_TAB){
                        pixel_screen_fill(SDL_GetWindowSurface(win)); /* Gets the window surface and changes it to gray when TAB is pressed */
                    }
                    /* If any other surface is chosen instead of the window one, it will stay the same visualy but it will bug out... */
                #endif
                break;
            case SDL_MOUSEWHEEL:
                /* FIXME */
                /* set viewport boundaries */
                if(e.wheel.y < 0){
                    map_scale -= 0.1f;
                    if(map_scale <= 0.1f){
                        map_scale = 0.1f;
                    }
                }else if(e.wheel.y > 0){
                    map_scale += 0.1f;
                    if(map_scale >= 2.5f){
                        map_scale = 2.5f;
                    }
                }   
                break;
            case SDL_MOUSEBUTTONDOWN:
                int cursor_x;
                int cursor_y;
                SDL_GetMouseState(&cursor_x, &cursor_y);
                highlight_on_click(cursor_x, cursor_y);
                if(e.button.button == SDL_BUTTON_LEFT){
                    set_pixel(map, win, cursor_x, cursor_y, rand() % 255, rand() % 255, rand() % 255);
                /* Random Colours to be chosen when clicking */
            }
        }
    }

    return;
}
