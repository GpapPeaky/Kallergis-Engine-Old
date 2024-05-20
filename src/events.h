#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <algorithm>
#include "init_win.h"
#include "map.h"
#include "font.h"
#include "definitions.aux"

#ifndef EVENTS
#define EVENTS

/**
 * @brief Handles events
 * 
 * @param quit Checks if the program has quit or not
*/
void events_handling(bool& quit);

/**
 * @brief displays info when hovering a province
*/
eng_event info_on_hover(void);

/**
 * @brief Highlights a province when clicked
 * 
 * @param mouse_x Mouse x 
 * @param mouse_y Mouse y
*/
eng_event highlight_on_click(int mouse_x, int mouse_y);

/**
 * @brief Allows to pan the map
 * 
 * @param d_x cursor x
 * @param d_y cursor y
*/
eng_event pan_map(int d_x, int d_y);

/**
 * @brief Zoom in/out event at the center of the screen
 * 
 * @param scale How much to zoom in/out
*/
eng_event zoom_map(float scale);

#endif
