#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include "init_win.h"
#include "map.h"
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
event info_on_hover(void);
/*TODO*/

/**
 * @brief Highlights a province when clicked
*/
event highlight_on_click(void);
/*TODO*/

/* IDEA: ADD CAMERA PANING WITH RIGHT MOUSE CLICK AND MIDDLE CLICK */

/**
 * @brief Zoom in/out event
 * 
 * @param scale How much to zoom in/out
*/
event zoom_map(float scale);
/* FIXME: ZOOM ON CURSOR INSTEAD ON 0,0 */

#endif
