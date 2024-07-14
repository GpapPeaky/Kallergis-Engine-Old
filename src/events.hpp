#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <algorithm>
#include "init_win.hpp"
#include "map.hpp"
#include "font.hpp"
#include "../auxf/definitions.aux"
#include "camera.hpp"

#ifndef EVENTS
/**
 * @brief Event handling for every aspect of the engine (Map, mouse, provinces, regions, countries ...)
 */
#define EVENTS

/**
 * @brief Handles events
 * 
 * @param quit Checks if the program has quit or not
 * @param cam camera struct for viewport
*/
void events_handling(bool& quit, camera& cam);

/**
 * @brief displays info when hovering a province
*/
eng_event info_on_hover(void);

/**
 * @brief Highlights a province when clicked
 * 
 * @param mouse_x Mouse x
 * @param mouse_y Mouse y
 * @param map Surface to parse
*/
eng_event highlight_on_click(int mouse_x, int mouse_y, SDL_Surface* map);

/**
 * @brief Allows to pan the map
 * 
 * @param d_x cursor x
 * @param d_y cursor y
*/
eng_event pan_map(int d_x, int d_y);

#endif
