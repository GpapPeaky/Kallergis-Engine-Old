#include "SDL2/SDL.h"
#include <iostream>

#ifndef CLEANUP
/**
 * @brief For Cleanup in _main.cpp
 */
#define CLEANUP

// namespace cln {} /* Could be used sometime... */

/**
 * @brief Cleans up the used window and renderer as well as other assets
 * 
 * @param win Window to clean
 * @param renderer Renderer to clean
 * 
 * @warning USE AT THE END OF THE MAIN FUNCTION, ELSE IT WILL CRASH THE PROGRAM
 */
void cleanup(SDL_Window* win, SDL_Renderer* renderer);

#endif
