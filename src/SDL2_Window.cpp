#include "SDL2_Window.hpp"

SDL_Window* win;
SDL_Renderer* renderer;

int SDL2_CreateWindowAndRenderer(const char* name){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){ fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError()); return FAIL; }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){ fprintf(stderr, "Unable to initialize IMG: %s\n", SDL_GetError()); return FAIL; } /* IMG_Init returns the flag */

    win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEV_SCREEN_W, DEV_SCREEN_H, SDL_WINDOW_FULLSCREEN_DESKTOP); /* Create A Window */
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */
    if(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0){
        std::printf("Failed to set renderer blend mode: %s\n", SDL_GetError());
        return FAIL;
    }

    if(win == nullptr){
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return FAIL;
    }
    if(renderer == nullptr){
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return FAIL;
    }

    return SUCCESS;
}

void SDL2_RenderMap(SDL_Renderer* renderer, std::vector<SDL_Texture*> textures, camera cam){
    SDL_RenderClear(renderer);

    for(SDL_Texture* texture : textures){
        SDL_RenderCopy(renderer, texture, &cam.rect, NULL);
    }

    return;
}

#include <SDL2/SDL.h>

int SDL2_ContainsRect(SDL_Rect src, SDL_Rect dst){
    if(src.x <= dst.x &&
        src.y <= dst.y && 
        (src.x + src.w) >= (dst.x + dst.w) &&
        (src.y + src.h) >= (dst.y + dst.h)){
        return SUCCESS; 
    }

    return FAIL; 
}
