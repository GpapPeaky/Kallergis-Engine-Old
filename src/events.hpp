#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <algorithm>
#include <cmath>
#include <chrono> /* For the clock */
#include <unordered_map>
#include "init_win.hpp"
#include "map.hpp"
#include "font.hpp"
#include "../auxf/definitions.aux"
#include "camera.hpp"
#include "unit.hpp"

#ifndef EVENTS
/**
 * @brief Event handling for every aspect of the engine (Map, mouse, provinces, regions, countries ...)
 */
#define EVENTS

extern const Uint8* state;

/**
 * @brief Handles events
 * 
 * @param quit Checks if the program has quit or not
 * @param cam camera struct for viewport
*/
eng_event events_handling(bool& quit, camera& cam);

/**
 * @brief displays info when hovering a province
*/
eng_event info_on_hover(void);

/**
 * @brief Highlights a province when clicked
 * 
 * @param mouse_x Mouse x
 * @param mouse_y Mouse y
 * @param src Surface to parse
 * @param dst Texture to highlight
 * @param cam Camera for coords transformation
*/
eng_event highlight_on_click(int mouse_x, int mouse_y, SDL_Surface* src, SDL_Texture* dst, camera cam);

/**
 * @brief Allows to pan the map
 * 
 * @param d_x cursor x
 * @param d_y cursor y
*/
eng_event pan_map(int d_x, int d_y);

#endif
