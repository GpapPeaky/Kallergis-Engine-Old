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
eng_event info_on_hover(void);
/*TODO*/

/**
 * @brief Highlights a province when clicked
 * 
 * @param mouse_x Mouse x 
 * @param mouse_y Mouse y
*/
eng_event highlight_on_click(int mouse_x, int mouse_y);
/*TODO*/

/**
 * @brief Allows to pan the map
 * 
 * @param d_x cursor x
 * @param d_y cursor y
*/
eng_event pan_map(int d_x, int d_y);
/* FIXME */

/**
 * @brief Zoom in/out event
 * 
 * @param scale How much to zoom in/out
 * @param cursor_w cursor coord x
 * @param cursor_h cursor coord y
*/
eng_event zoom_map(float scale, int cursor_w, int cursor_h);
/* FIXME: ZOOM ON CURSOR INSTEAD ON 0,0 */

#endif
