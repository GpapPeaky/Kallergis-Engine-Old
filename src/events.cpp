#include "events.h"

event zoom_map(float scale){

    map_scale *= scale; /* Adjust the scale */

    if(map_scale < 0.5){
        map_scale = 0.5f;
    }else if(map_scale > 1.5f){
        map_scale = 1.5f;
    }

    render_map();
    
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
                break;
            case SDL_MOUSEWHEEL:
                if(e.wheel.y < 0){
                    zoom_map(0.9f); 
                }else if(e.wheel.y > 0){
                    zoom_map(1.1f); 
                }
                break;
        }
    }

    return;
}
