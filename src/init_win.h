#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#ifndef INIT_WIN
#define INIT_WIN 

/* GENERAL USE VARIABLES */

extern SDL_Window* win;
extern SDL_Renderer* renderer;

/**
 * @brief Initialises the window and the renderer
 * 
 * @param name Window name
*/
void win_init(const char* name);

#endif
