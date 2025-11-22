#include "SDL2_Event.hpp"

void SDL2_HandleEvents(bool& quit){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_e))){
            quit = true;
        }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w){ /* Camera movement */
            SDL2_MoveCamera(0.0F, 20.5F / SDL2_Cam->zoom);
        }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s){
            SDL2_MoveCamera(0.0F, -20.5F / SDL2_Cam->zoom);
        }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a){
            SDL2_MoveCamera(20.5F / SDL2_Cam->zoom, 0.0F);
        }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d){
            SDL2_MoveCamera(-20.5F / SDL2_Cam->zoom, 0.0F);
        }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q){
            SDL2_QuadOutlines = !SDL2_QuadOutlines;
        }

        /* Camera zoom */
        if(e.type == SDL_MOUSEWHEEL){
            if(e.wheel.y > 0){
                SDL2_RecalibrateZoom(1.1F);
            }else if(e.wheel.y < 0){
                SDL2_RecalibrateZoom(0.9F);
            }
        }
    }

    return;
}
