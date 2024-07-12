#include "events.hpp"

eng_event info_on_hover(void){

    /* Info box: 129 - 114 */
    return;
}

eng_event highlight_on_click(int x, int y, SDL_Surface* map){

    Uint8 r, g, b;

    int index = y * map->pitch + x * 3;

    b = ((Uint8*)map->pixels)[index + 0];
    g = ((Uint8*)map->pixels)[index + 1];
    r = ((Uint8*)map->pixels)[index + 2];

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
                    SDL_SaveBMP(map, "bin/output.bmp");
                    quit = true;
                }
                #ifdef PIXEL_DISPLAY_DBG
                    if(e.key.keysym.sym == SDLK_TAB){
                        pixel_screen_fill(map, win); /* Gets the window surface and changes it to gray when TAB is pressed */
                        /* We have to update, or else it won't show */
                    }
                    /* If any other surface is chosen instead of the window one, it will stay the same visualy but it will bug out... */
                #endif
                break;
            case SDL_MOUSEWHEEL:
                /* TODO: Zoom */
                break;
            case SDL_MOUSEBUTTONDOWN:
                int mouse_x;
                int mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                highlight_on_click(mouse_x, mouse_y, click_map);
                break;
        }
    }

    return;
}
