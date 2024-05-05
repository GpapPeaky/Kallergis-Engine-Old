#ifndef EVENTS
#define EVENTS

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include "init_win.h"
#include "definitions.aux"

extern SDL_Rect viewport; /* Will be initialised in main */

/**
 * @brief Handles events
 * 
 * @param quit Checks if the program has quit or not
*/
void events_handling(bool& quit);

/**
 * @brief Zoom in/out event
 * 
 * @param viewport where to set the view
 * @param scale How much to zoom in/out
*/
event zoom_map(SDL_Rect& viewport, float scale);

#endif
