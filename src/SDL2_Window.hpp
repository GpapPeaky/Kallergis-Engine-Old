#define SDL_MAIN_HANDLED

#include "SDL2/SDL_video.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "SDL2_Camera.hpp"
#include "auxf/definitions.aux"

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
int SDL2_CreateWindowAndRenderer(const char* name);

/**
 * @brief Renders the assets on screen
 * 
 * @param renderer Renderer to call
 * @param textures Textures vector to render
 * @param cam Camera for viewport
 */
void SDL2_RenderMap(SDL_Renderer* renderer, std::vector<SDL_Texture*> textures, camera cam);

/**
 * @brief Checks if the source rectangle is inside the destination rectangle (and vise versa)
 * 
 * @param src Source rectangle 
 * @param dst Destination rectangle
 * 
 * @returns 0 on success, 1 on failure
 */
int SDL2_ContainsRect(SDL_Rect src, SDL_Rect dst);

#endif
