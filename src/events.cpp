#include "events.h"

SDL_Rect viewport = {0, 0, 800, 600};

event zoom_map(SDL_Rect& viewport, float scale){
    int new_width = static_cast<int>(viewport.w * scale);
    int new_height = static_cast<int>(viewport.h * scale);
    
    if(new_width > 2000 || new_height > 2000 || new_width < 100 || new_height < 100){
        return;
    }
    
    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);
    
    int delta_x = static_cast<int>((mousex - viewport.x) * (scale - 1));
    int delta_y = static_cast<int>((mousey - viewport.y) * (scale - 1));
    
    viewport.x -= delta_x;
    viewport.y -= delta_y;
    viewport.w = new_width;
    viewport.h = new_height;
    
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
                if(e.wheel.y > 0){
                    zoom_map(viewport, 0.9f); 
                }else if(e.wheel.y < 0){
                    zoom_map(viewport, 1.1f); 
                }
                SDL_RenderSetViewport(renderer, &viewport);
                break;
        }
    }

    return;
}
