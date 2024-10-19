#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iomanip>
#include <sstream> 
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
extern TTF_Font* province_inspector_font;
extern TTF_Font* top_bar_font;
extern SDL_Rect rect;
extern SDL_Rect b_rect;
extern SDL_Rect c_rect;

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
 * @param x x axis
 * @param y y axis
 * @param font font to use
*/
render_capable render_text(std::string msg, int x, int y, TTF_Font* font);

/**
 * @brief Renders stats on hovering a sprite with the mouse
*/
render_capable render_on_mouse_hover(void);

/**
 * @brief Renders the country's stats
 * 
 * @param country country to render the stats of
 */
render_capable render_country_info(cou* country);

/**
 * @brief Renders the selected province info
 * 
 * @param province province clicked
 */
render_capable render_province_info(prov* province);

/**
 * @brief Formats a float to show two decimals
 * 
 * @param value value to format
 * 
 * @returns the new string
 */
std::string format_float(float value);

#endif/* FONT */
