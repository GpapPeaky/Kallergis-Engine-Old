#include "events.h"

eng_event zoom_map(double scale){

    /* FIXME: make it to zoom on the centre of the screen, zooming out too much crashes the game and moves the camera in weird position */

    float new_scale = map_scale * scale; /* Adjust the scale */

    const float min_scale = 0.25f;
    const float max_scale = 2.0f;

    new_scale = std::max(min_scale, std::min(max_scale, new_scale));

    float center_x = viewport.x + viewport.w / 2;
    float center_y = viewport.y + viewport.h / 2;

    /* Calculate the new width and height of the viewport */
    float new_width = DEV_SCREEN_W / map_scale;
    float new_height = DEV_SCREEN_H / map_scale;

    float new_center_x = center_x * (new_width / viewport.w);
    float new_center_y = center_y * (new_height / viewport.h);

    /* Calculate the new viewport position to keep the zoom centered */
    viewport.x = new_center_x - viewport.x - new_width / 2;
    viewport.y = new_center_y - viewport.y - new_height / 2;
    viewport.w = new_width;
    viewport.h = new_height;

    map_scale = new_scale;

    return;
}

eng_event info_on_hover(){
        int cursor_x;
        int cursor_y;
        SDL_GetMouseState(&cursor_x, &cursor_y);

        SDL_Surface* info = IMG_Load("src/gfx/ui/infobox.png");
        SDL_CreateTextureFromSurface(renderer, info);

        /* Info box: 129 - 114 */
}

eng_event highlight_on_click(int x, int y){

    Uint8 r, g, b;

    SDL_Surface* surface = IMG_Load("src/regions/provinces.bmp");

    int map_x = (x - viewport.x) / map_scale; /* viewport offset to bring the camera to the correct place for the rgb values*/
    int map_y = (y - viewport.y) / map_scale;

    int index = map_y * surface->pitch + map_x * 3;

    b = ((Uint8*)surface->pixels)[index];
    g = ((Uint8*)surface->pixels)[index + 1];
    r = ((Uint8*)surface->pixels)[index + 2];

    SDL_Color clicked = {r, g, b, ALPHA};

    for(const auto& prov : provinces){
        if(prov.prov_colour.r == clicked.r && prov.prov_colour.g == clicked.g && prov.prov_colour.b == clicked.b){
            std::printf("Clicked Province: %s\n", prov.prov_name.c_str());
        }
    }

    SDL_FreeSurface(surface);

    /* TODO: add +50 to the clicked colour, reset after closing */

    return;
}

eng_event pan_map(int d_x, int d_y){
    /* FIXME */

    return;
}

void events_handling(bool& quit){
    SDL_Event e;

    // Panning variables
    //_______________________________
    // static int prev_mouse_x = 0;
    // static int prev_mouse_y = 0;

    // int delta_x;
    // int delta_y;

    // bool pan_active = false;
    //_______________________________
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
                    viewport.y -= -50;
                }
                if(e.key.keysym.sym == SDLK_a){
                    viewport.x -= -50;
                }
                if(e.key.keysym.sym == SDLK_s){
                    viewport.y += -50;
                }
                if(e.key.keysym.sym == SDLK_d){
                    viewport.x += -50;
                }
                break;
            // case SDL_MOUSEBUTTONDOWN:
            //     if (e.button.button == SDL_BUTTON_RIGHT) {
            //         pan_active = true;
            //         prev_mouse_x = e.button.x;
            //         prev_mouse_y = e.button.y;
            //     }
            //     break;
            // case SDL_MOUSEBUTTONUP:
            //     if (e.button.button == SDL_BUTTON_RIGHT) {
            //         pan_active = false;
            //     }
            //     break;
            // case SDL_MOUSEMOTION:
            //     if (pan_active) {
            //         delta_x += 1;
            //         delta_y += 
            //         prev_mouse_x = e.motion.x;
            //         prev_mouse_y = e.motion.y;
            //         pan_map(delta_x, delta_y);
            //     }
            //     break;
            case SDL_MOUSEWHEEL:
                if(e.wheel.y < 0){
                    zoom_map(0.9f); 
                }else if(e.wheel.y > 0){
                    zoom_map(1.1f); 
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                int cursor_x;
                int cursor_y;
                SDL_GetMouseState(&cursor_x, &cursor_y);
                highlight_on_click(cursor_x, cursor_y);
        }
    }

    return;
}
