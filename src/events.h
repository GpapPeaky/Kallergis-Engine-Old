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

/**
 * @brief Allows to pan the map
 * 
 * @param d_x cursor x
 * @param d_y cursor y
*/
event pan_map(int d_x, int d_y);
/* FIXME */

/**
 * @brief Zoom in/out event
 * 
 * @param scale How much to zoom in/out
 * @param cursor_w cursor coord x
 * @param cursor_h cursor coord y
*/
event zoom_map(float scale, int cursor_w, int cursor_h);
/* FIXME: ZOOM ON CURSOR INSTEAD ON 0,0 */

#endif
