#include "init_win.h"

SDL_Window* win;
SDL_Renderer* renderer;

void win_init(const char* name){

    SDL_Init(SDL_INIT_VIDEO); /* Initialises the GUI library */
    IMG_Init(IMG_INIT_PNG);
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError()); return; }

    win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 900, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); /* Create A Window */
    renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */

    if(win == nullptr){
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return;
    }
    if(renderer == nullptr){
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return;
    }

    SDL_RenderClear(renderer);
    
    return;
}
