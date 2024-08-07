#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../auxf/definitions.aux"

#ifndef INIT_WIN
/**
 * @brief Initialisation functions for the window and renderer
 */
#define INIT_WIN 

/* GENERAL USE VARIABLES */

extern SDL_Window* win;
extern SDL_Renderer* renderer;

/**
 * @brief Initialises the window and the renderer
 * 
 * @param name Window name
 * 
 * @returns 1 on failure 0 on success
*/
err_capable win_init(const char* name);

#endif
