#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iomanip>
#include <sstream> 
#include "SDL2_Window.hpp"
#include "KENG_Parser.hpp"
#include "KENG_Map.hpp"
#include "KENG_Goods.hpp"
#include "KENG_Region.hpp"
#include "PGUI_GUI.hpp"
#include "PGUI_Overloads.hpp"
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
int SDL2_CreateFont(void); 

/**
 * @brief Renders Text based on a string
 * 
 * @param msg Message to appear
 * @param x x axis
 * @param y y axis
 * @param font font to use
*/
void SDL2_RenderText(std::string msg, int x, int y, TTF_Font* font);

/**
 * @brief Renders stats on hovering a sprite with the mouse
*/
void SDL2_RenderOnMouseHover(void);

/**
 * @brief Renders the country's stats
 * 
 * @param country country to render the stats of
 */
void SDL2_RenderCountryStats(KENG_country* country);

/**
 * @brief Renders the selected province info
 * 
 * @param province province clicked
 */
void SDL2_RenderProvinceInfo(prov* province);

/**
 * @brief Renders the leader of a selected country
 * 
 * @param country country right clicked
 */
void SDL2_RenderLeaderName(KENG_country* country);

/**
 * @brief Formats a float to show two decimals
 * 
 * @param value value to format
 * 
 * @returns the new string
 */
std::string SDL2_FormatFloat(float value);

#endif/* FONT */
