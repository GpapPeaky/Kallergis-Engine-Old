#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include "init_win.hpp"
#include "init_map.hpp"
#include "map.hpp"
#include "regions.hpp"
#include "auxf/definitions.aux"

#ifndef FONT
/**
 * @brief Fonts Module
 */
#define FONT

extern SDL_Color text_colour;
extern SDL_Color text_colour_bg;
extern SDL_Surface * text;
extern SDL_Texture * txt;
extern SDL_Texture * b_txt;
extern TTF_Font* font;
extern SDL_FRect rect;
extern SDL_FRect b_rect;
extern SDL_FRect c_rect;

/**
 * @brief Initialises The UI
 * 
 * @returns 1 on FAILURE
 *                0 on SUCCESS
*/
err_capable init_font(void); 

/**
 * @brief Renders Text based on a string
 * 
 * @param msg Message to appear
 * @param position Rectangle to be placed at
 * 
 * @returns 1 on FAILURE
 *                0 on SUCCESS
*/
render_capable render_text(std::string msg, SDL_FRect* position);

/**
 * @brief Renders stats on hovering a sprite with the mouse
 * 
 * @returns 1 on FAILURE
 *                0 on SUCCESS
*/
render_capable render_on_mouse_hover(void);

#endif/* FONT */
