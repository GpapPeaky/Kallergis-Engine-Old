#include "events.h"

eng_event zoom_map(float scale, int cursor_w, int cursor_h){

    float new_scale = map_scale * scale; /* Adjust the scale */

    const int max_width = 1000;
    const int max_height = 900;

    const float min_scale = 0.5f;
    const float max_scale = 2.0f;

    if(new_scale < min_scale){
        new_scale = min_scale;
    }else if (new_scale > max_scale){
        new_scale = max_scale;
    }

    float dscale = new_scale / map_scale;

    int new_w = static_cast<int>(map_width * new_scale);
    int new_h = static_cast<int>(map_height * new_scale);

    int new_cursor_x = static_cast<int>(cursor_w * dscale);
    int new_cursor_y = static_cast<int>(cursor_h * dscale);

    /* Cursor position calculation */

    int dx = cursor_w - new_cursor_x;
    int dy = cursor_h - new_cursor_y;

    viewport.x += dx;
    viewport.y += dy;
    viewport.w = new_w;
    viewport.h = new_h;

    map_scale = new_scale;

    return;
}

eng_event info_on_hover(){
        int cursor_x;
        int cursor_y;
        SDL_GetMouseState(&cursor_x, &cursor_y);

        SDL_Surface* info = IMG_Load("src/gfx/ui/infobox.png");
        SDL_CreateTextureFromSurface(renderer, info);

        if(cursor_x ... ){
            display info
        }

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
                break;
            //FIXME
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
                    int cursor_x;
                    int cursor_y;
                    SDL_GetMouseState(&cursor_x, &cursor_y);
                    zoom_map(0.9f, cursor_x, cursor_y); 
                }else if(e.wheel.y > 0){
                    int cursor_x;
                    int cursor_y;
                    SDL_GetMouseState(&cursor_x, &cursor_y);
                    zoom_map(1.1f, cursor_x, cursor_y); 
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
