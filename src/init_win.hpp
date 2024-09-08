#define SDL_MAIN_HANDLED

#include "SDL2/SDL_video.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "auxf/definitions.aux"
#include "camera.hpp"

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

/**
 * @brief Renders the assets on screen
 * 
 * @param renderer Renderer to call
 * @param textures Textures vector to render
 * @param cam Camera for viewport
 */
render_capable render_map(SDL_Renderer* renderer, std::vector<SDL_Texture*> textures, camera cam);

#endif
