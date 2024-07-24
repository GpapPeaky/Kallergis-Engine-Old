#include "init_win.hpp"

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Surface* screen;

err_capable win_init(const char* name){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){ fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError()); return FAIL; }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){ fprintf(stderr, "Unable to initialize IMG: %s\n", SDL_GetError()); return FAIL; } /* IMG_Init returns the flag */


    win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 900, SDL_WINDOW_FULLSCREEN_DESKTOP); /* Create A Window */
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* Sprite Rendering */

    if(win == nullptr){
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return FAIL;
    }
    if(renderer == nullptr){
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return FAIL;
    }

    screen = SDL_GetWindowSurface(win);

    return SUCCESS;
}
